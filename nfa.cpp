#include "nfa.hpp"

#include "fort.hpp"

#include <algorithm>
#include <cassert>
#include <ctype.h>
#include <utility>

std::string pack(std::vector<std::shared_ptr<NFAState>> v) {
    std::sort(
        v.begin(), v.end(),
        [](std::shared_ptr<NFAState> left, std::shared_ptr<NFAState> right) {
            return left->label < right->label;
        });
    std::string ret = "{";
    for (auto const &state : v) {
        ret.append(state->label);
        ret.append(", ");
    }
    ret.pop_back();
    ret.pop_back();
    ret.push_back('}');
    return ret;
}

std::string pack(std::set<std::string> const &set) {
    if (set.empty())
        return "{}";
    std::string ret = "{";
    for (auto const &label : set) {
        ret.append(label);
        ret.append(", ");
    }
    ret.pop_back();
    ret.pop_back();
    ret.push_back('}');
    return ret;
}

void NFA::epsilon(std::set<std::string> &soFar,
                  std::shared_ptr<NFAState> state) {
    for (auto const &next : state->getTransitions().at(nullTransition)) {
        if (soFar.find(next->label) == soFar.end()) {
            soFar.insert(next->label);
            epsilon(soFar, next);
        }
    }
}

std::string NFA::epsilonClosure(std::shared_ptr<NFAState> state) {
    std::set<std::string> set;
    epsilon(set, state);
    return pack(set);
}

std::ostream &NFA::print(std::ostream &out) const {
    auto table = makeTable();
    for (auto [label, state] : states) {
        std::string pre;
        if (state->accept) {
            pre.push_back('+');
        }
        for (auto i : init) {
            if (i->label == label) {
                pre.push_back('-');
                break;
            }
        }
        table << pre + label;
        auto const &transitions = state->getTransitions();
        for (auto ch : alphabet) {
            auto it = transitions.find(ch);
            if (it == transitions.end()) {
                table << "";
            } else {
                table << pack(it->second);
            }
        }
        table << fort::endr;
    }
    return out << table.to_string();
}

void NFA::addState(String label, bool accept) {
    if (states.find(label) != states.end()) {
        throw "duplicate state label " + label;
    }
    states.emplace(label, std::make_shared<NFAState>(label, accept));
    addTransition(label, label, nullTransition);
}

void NFA::addInitialState(String label, bool accept) {
    addState(label, accept);
    init.push_back(states.at(label));
}

void NFA::addTransition(String from, String to, char input) {
    auto itFrom = states.find(from);
    if (itFrom == states.end()) {
        throw "no such state " + from;
    }
    auto itTo = states.find(to);
    if (itTo == states.end()) {
        throw "no such state " + to;
    }
    itFrom->second->addTransition(input, itTo->second);
    alphabet.insert(input);
}

bool NFA::process(State cur, String input, int i) const {
    if (i == input.length()) {
        return cur->accept;
    }
    auto const &trans = cur->getTransitions();
    auto it = trans.find(input.at(i));
    if (it != trans.end()) {
        for (auto next : it->second) {
            if (process(next, input, i + 1)) {
                return true;
            }
        }
    }
    auto nullIt = trans.find(nullTransition);
    if (nullIt != trans.end()) {
        for (auto next : nullIt->second) {
            if (process(next, input, i)) {
                return true;
            }
        }
    }
    return false;
}

bool NFA::process(String input) const {
    for (auto const &start : init) {
        if (process(start, input)) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> parseStates(String dfaLabel) {
    assert(dfaLabel.front() == '{');
    assert(dfaLabel.back() == '}');
    std::vector<std::string> ret;
    for (int i = 1; i < dfaLabel.length() - 1; ++i) {
        if (std::isalnum(dfaLabel.at(i))) {
            int j = dfaLabel.find_first_of(',', i);
            if (j == -1) {
                j = dfaLabel.length() - 1;
            }
            ret.push_back(dfaLabel.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

void NFA::dfaHelper(DFA &dfa, String curLabel) {
    auto labels = parseStates(curLabel);

    for (auto letter : alphabet) {
        if (letter == nullTransition) {
            continue;
        }
        std::set<std::string> nextSet;
        bool accept = false;
        for (auto nfaLabel : labels) {
            auto trans = states.at(nfaLabel)->getTransitions();
            auto it = trans.find(letter);
            if (it != trans.end()) {
                for (auto state : it->second) {
                    epsilon(nextSet, state);
                    accept = accept || state->accept;
                }
            }
        }
        std::string nextLabel = pack(nextSet);
        if (!dfa.hasState(nextLabel)) {
            dfa.addState(nextLabel, accept);
        }
        dfa.addTransition(curLabel, nextLabel, letter);
    }
}

DFA NFA::toDFA() {
    unifyInitial();
    DFA dfa;

    auto cur = init.front();
    auto startLabel = epsilonClosure(cur);
    dfa.addInitialState(startLabel, cur->accept);
    std::set<std::string> done;
    bool cont = true;
    while (cont) {
        cont = false;
        for (auto [label, state] : dfa.states) {
            if (done.find(label) == done.end()) {
                done.insert(label);
                dfaHelper(dfa, label);
                cont = true;
            }
        }
    }

    return dfa;
}

void NFA::unifyInitial() {
    if (init.size() == 1) {
        return;
    }
    bool accept = false;
    for (auto const &i : init) {
        if (i->accept) {
            accept = true;
            break;
        }
    }
    static std::string const startLabel = "S";
    addState(startLabel, accept);
    for (auto i : init) {
        addTransition(startLabel, i->label, nullTransition);
    }
    init.clear();
    init.push_back(states.at(startLabel));
}

bool NFA::isStartState(String label) const {
    for (auto const &state : init) {
        if (state->label == label) {
            return true;
        }
    }
    return false;
}
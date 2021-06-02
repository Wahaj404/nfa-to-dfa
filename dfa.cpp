#include "dfa.hpp"

#include "fort.hpp"

std::ostream &DFA::print(std::ostream &out) const {
    auto table = makeTable();
    for (auto [label, state] : states) {
        std::string pre = state->accept ? "+" : "";
        table << pre + (init->label == label ? "-" : "") + label;
        for (auto input : alphabet) {
            table << state->next(input)->label;
        }
        table << fort::endr;
    }
    return out << table.to_string();
}

void DFA::addState(String label, bool accept) {
    if (states.find(label) != states.end()) {
        throw "duplicate state label " + label;
    }
    states.emplace(label, std::make_shared<DFAState>(label, accept));
}

void DFA::addInitialState(String label, bool accept) {
    addState(label, accept);
    init = states.at(label);
}

void DFA::addTransition(String from, String to, char input) {
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

bool DFA::process(String input) const {
    auto state = init;
    for (char ch : input) {
        state = state->next(ch);
    }
    return state->accept;
}

bool DFA::hasState(String label) const {
    return states.find(label) != states.end();
}
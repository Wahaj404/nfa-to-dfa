#include "nfa-state.hpp"

NFAState::NFAState(String _label, bool _accept) :
    label(_label), accept(_accept) {}

void NFAState::addTransition(char input, State next) {
    auto it = transitions.find(input);
    if (it == transitions.end()) {
        transitions.emplace(input, std::vector<State>(1, next));
    } else {
        it->second.push_back(next);
    }
}

std::map<char, std::vector<NFAState::State>> const &
NFAState::getTransitions() const {
    return transitions;
}
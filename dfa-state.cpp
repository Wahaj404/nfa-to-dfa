#include "dfa-state.hpp"

DFAState::DFAState(String _label, bool _accept) :
    label(_label), accept(_accept) {}

void DFAState::addTransition(char input, State to) {
    if (transitions.find(input) != transitions.end()) {
        throw "dfa state can not have duplicate transition for " + input;
    }
    transitions.emplace(input, to);
}

DFAState::State DFAState::next(char input) const {
    auto it = transitions.find(input);
    if (it == transitions.end()) {
        throw "state has no transition for " + input;
    }
    return it->second;
}
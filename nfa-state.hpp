#ifndef __NFASTATE_HPP__
#define __NFASTATE_HPP__

#include "util.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

class NFAState {
    using State = std::shared_ptr<NFAState>;

private:
    std::map<char, std::vector<State>> transitions;

public:
    std::string const label;
    bool accept;
    NFAState(String label, bool accept);
    void addTransition(char input, State next);
    std::map<char, std::vector<State>> const &getTransitions() const;
};

#endif // __NFASTATE_HPP__

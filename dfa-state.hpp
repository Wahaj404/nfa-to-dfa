#ifndef __DFASTATE_HPP__
#define __DFASTATE_HPP__

#include "util.hpp"

#include <map>
#include <memory>

class DFAState {
    using State = std::shared_ptr<DFAState>;

private:
    std::map<char, State> transitions;

public:
    std::string const label;
    bool accept;
    DFAState(String label, bool accept);
    void addTransition(char input, State next);
    State next(char input) const;
};

#endif // __DFASTATE_HPP__

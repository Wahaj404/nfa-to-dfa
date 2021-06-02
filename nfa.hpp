#ifndef __NFA_HPP__
#define __NFA_HPP__

#include "dfa.hpp"
#include "fa.hpp"
#include "nfa-state.hpp"

#include <map>
#include <vector>

class NFA : public FA {
    using State = std::shared_ptr<NFAState>;
    static char constexpr nullTransition = '^';

private:
    std::map<std::string, State> states;
    std::vector<State> init;
    std::ostream &print(std::ostream &) const override;
    bool process(State cur, String input, int i = 0) const;
    bool isStartState(String label) const;
    std::string epsilonClosure(std::shared_ptr<NFAState> state);
    void epsilon(std::set<std::string> &soFar, std::shared_ptr<NFAState> state);

public:
    void addState(String label, bool accept) override;
    void addInitialState(String label, bool accept) override;
    void addTransition(String from, String to, char input) override;
    bool process(String input) const override;
    void unifyInitial();

    void dfaHelper(DFA &dfa, String curLabel);
    DFA toDFA();
};

#endif // __NFA_HPP__

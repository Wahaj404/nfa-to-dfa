#ifndef __DFA_HPP__
#define __DFA_HPP__

#include "dfa-state.hpp"
#include "fa.hpp"

#include <map>

class DFA : public FA {
    using State = std::shared_ptr<DFAState>;

private:
    std::map<std::string, State> states;
    State init;

    std::ostream &print(std::ostream &) const override;

public:
    void addState(String label, bool accept) override;
    void addInitialState(String label, bool accept) override;
    void addTransition(String from, String to, char input) override;
    bool process(String input) const override;
    bool hasState(String label) const;

    friend class NFA;
};

#endif // __DFA_HPP__

#ifndef __FA_HPP__
#define __FA_HPP__

#include "fort.hpp"
#include "util.hpp"

#include <iostream>
#include <set>

class FiniteAutomaton {
private:
    virtual std::ostream &print(std::ostream &) const = 0;

protected:
    std::set<char> alphabet;

    fort::char_table makeTable() const;

public:
    virtual void addState(String label, bool accept) = 0;
    virtual void addInitialState(String label, bool accept) = 0;
    virtual void addTransition(String from, String to, char input) = 0;
    virtual bool process(String input) const = 0;
    friend std::ostream &operator<<(std::ostream &, FiniteAutomaton const &);
};

using FA = FiniteAutomaton;

#endif // __FA_HPP__

#include "fort.hpp"
#include "nfa.hpp"

#include <iostream>
#include <string>

int main() {
    NFA nfa;
    int s = 0, t = 0;
    std::cin >> s;
    for (int i = 0; i < s; ++i) {
        std::string str;
        std::cin >> str;
        if (str.front() == '-') {
            if (str[1] == '+') {
                nfa.addInitialState(str.substr(2), true);
            } else {
                nfa.addInitialState(str.substr(1), false);
            }
        } else if (str.front() == '+') {
            nfa.addState(str.substr(1), true);
        } else {
            nfa.addState(str, false);
        }
    }
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::string a, b;
        char c;
        std::cin >> a >> b >> c;
        nfa.addTransition(a, b, c);
    }
    std::cout << nfa << '\n';
    std::cout << nfa.toDFA() << '\n';
}
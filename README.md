# nfa-to-dfa
4th semester Theory of Automata project to convert a user-designed [NFA-ε](https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton) to a [DFA](https://en.wikipedia.org/wiki/Deterministic_finite_automaton).

## Dependencies
Uses [libfort](https://github.com/seleznevae/libfort) for outputting well formatted transition tables for the finite automata.

## NFA Input Format
N <- number of states
N space separated strings <- (unique) state labels
T <- number of transitions
T lines of the form `a b c` each of which signify a transition from `a` to `b` on an input `c`. `c = ^` signifies a null transition.
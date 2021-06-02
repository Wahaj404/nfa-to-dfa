#!/usr/bin/bash

make -C .. clean
make -C ..

for file in $(ls test-*.txt); do
	# valgrind --leak-check=full \
    #      --show-leak-kinds=all \
    #      --track-origins=yes \
    #      --verbose \
    #      --log-file=valgrind-out.txt \
    #      ../nfa-to-dfa <$file >output-$file
    ../nfa-to-dfa <$file >output-$file
    diff output-$file expected-$file
done

rm output*
echo green
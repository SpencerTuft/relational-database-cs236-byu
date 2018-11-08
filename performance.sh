#!/usr/bin/env bash

# Compile
 echo "Ready to compile"
 ./readWait
 g++ -Wall -Werror -g -std=c++14 ./src/*.cpp -o ./relational-database-cs236-byu

# Memory Test
 echo "Next: Memory test"
 ./readWait
 valgrind --leak-check=full ./relational-database-cs236-byu ./test/in/62.txt

# Complexity Test
 echo "Next: Complexity test"
 ./readWait
 pmccabe ./src/*

# Unit Tests
 echo "Next: Unit tests"
 ./readWait
 ./test/test.sh

# Build Image
# docker build -t memory-test:0.1 .

# Run container
# docker run -it -v $PWD:/app memory-test:0.1 bash -c "cd /app/; g++ -Wall -Werror -g -std=c++14 ./src/*.cpp -o ./relational-database-cs236-byu && valgrind --leak-check=full ./relational-database-cs236-byu ./test/in/62.txt"
# docker run -it -v $PWD:/app memory-test:0.1 bash -c "./performance.sh"
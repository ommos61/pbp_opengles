#!/usr/bin/env bash

start=$(date +%s.%N)

clang -g -c glfw_main.cpp
clang -g -c models.cpp

clang -g -o game glfw_main.o models.o -lGLESv2 -lglfw

#
# unit testing of the game_math.h file
#
clang -g -o test_game_math test_game_math.cpp
if [ $? == 0 ]
then
    ./test_game_math
    if [ $? != 0 ]
    then
        echo "Error: game_math unit test failed."
    fi
else
    echo "Error: game_math unit test compile failed, no unit test run."
fi

#
# Some testing of the glm package in C++
#
##clang++ -g -o glm_test glm_test.cpp

duration=$(echo "$(date +%s.%N) - $start" | bc)
execution_time=$(printf "%.2f seconds" $duration)
echo "Execution time: $execution_time"

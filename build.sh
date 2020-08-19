#!/usr/bin/env bash

clang -g -c glfw_main.cpp
clang -g -c models.cpp

clang -g -o game glfw_main.o models.o -lGLESv2 -lglfw


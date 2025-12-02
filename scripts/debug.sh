#!/bin/bash
set -eu
gcc-15 -o jikan --debug -std=c99 -Werror -Wall -pedantic-errors src/main.c
lldb ./jikan


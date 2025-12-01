#!/bin/bash
set -eu
gcc-15 -o jikan --debug -std=c99 -Werror -Wall src/main.c
lldb ./jikan


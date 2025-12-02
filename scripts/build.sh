#!/bin/bash
set -eu
gcc-15 -o jikan --debug -std=c99 -D_GNU_SOURCE -pedantic-errors -Werror -Wall src/main.c

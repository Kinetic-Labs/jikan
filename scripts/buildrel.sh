#!/bin/bash
set -eu
gcc-15 -o jikan -O3 -std=c99 -D_GNU_SOURCE -Werror -pedantic-errors -Wall src/main.c

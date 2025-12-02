#!/bin/bash
set -eu
gcc-15 -o jikan -O3 -std=c99 -Werror -pedantic -Wall src/main.c


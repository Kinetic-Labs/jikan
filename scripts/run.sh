#!/bin/bash
set -eu
./scripts/build.sh
./jikan "$@"


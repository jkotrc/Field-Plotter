#!/usr/bin/env bash
set -euo pipefail

meson --reconfigure build .
ninja -C build
./build/src/fieldplotter/fieldplotter

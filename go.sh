#!/bin/bash
set -euo pipefail

cd "$(dirname "$0")"
cd mod
make >&2
cd ../tools
dune build

# dune exec bin/main.exe -- make-header -map-file ../data/test.map > ../mod/symbols.h

AR="$(dune exec bin/main.exe -- \
     make-ar -elf-file ../mod/payload.elf \
     -bin-file ../mod/payload.bin \
     -hook-file ../mod/hooks.sexp \
     -dol-file ../data/extract/sys/main.dol \
     -chunk-base 0x801c6254 | shuf)"

name=$(uuid)

echo -e "[ActionReplay_Enabled]
\$$name
[ActionReplay]
\$$name
$AR" > ~/.local/share/dolphin-emu/GameSettings/GIQE78.ini

echo "$AR"
printf "Lines: %d\n" $(echo "$AR" | wc -l) >&2

dolphin-emu -d -e ../data/iso/*.iso

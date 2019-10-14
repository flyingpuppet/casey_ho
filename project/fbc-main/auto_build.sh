#!/bin/bash
source setenv.sh 
make clean
cd ./boot/
make clean
make rom
cd ../
make rom
cat ./boot/rom_boot.hex rom.hex > boot.hex


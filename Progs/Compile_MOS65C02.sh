#!/bin/bash

SwapPage=$1
DirLib=$2
FileProg=$3
CompileParams=$4

rm -f ${DirLib}/_.h

echo "#define engine_mos65c02" >> ${DirLib}/_.h
echo "#define mem_swap 0x${SwapPage}00" >> ${DirLib}/_.h

cd Temp

sdcc -mmos65c02 ${CompileParams} -I${DirLib} --model-large ${FileProg}.c

mv *.ihx ../Bin_MOS65C02
cd ..

rm -f ${DirLib}/_.h


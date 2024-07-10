#!/bin/bash

SwapPage=$1
DirLib=$2
FileProg=$3
CompileParams=$4

rm -f ${DirLib}/_.h

echo "#define engine_z180" >> ${DirLib}/_.h
echo "#define mem_swap 0x${SwapPage}00" >> ${DirLib}/_.h

cd Temp

sdcc -mz180 ${CompileParams} -I${DirLib} --no-peep ${FileProg}.c

mv *.ihx ../Bin_Z180
cd ..

rm -f ${DirLib}/_.h


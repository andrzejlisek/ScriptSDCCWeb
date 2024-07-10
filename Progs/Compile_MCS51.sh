#!/bin/bash

SwapPage=$1
DirLib=$2
FileProg=$3
CompileParams=$4

rm -f ${DirLib}/_.h

echo "#define engine_mcs51" >> ${DirLib}/_.h
echo "#define mem_swap 0x${SwapPage}00" >> ${DirLib}/_.h

cd Temp

if [ "${SwapPage}" = "7F" ]; then
    sdcc -mmcs51 ${CompileParams} -I${DirLib} --model-large --xram-loc 0x8000 --xram-size 0x8000 ${FileProg}.c
fi

if [ "${SwapPage}" = "BF" ]; then
    sdcc -mmcs51 ${CompileParams} -I${DirLib} --model-large --xram-loc 0xC000 --xram-size 0x4000 ${FileProg}.c
fi

mv *.ihx ../Bin_MCS51
cd ..

rm -f ${DirLib}/_.h


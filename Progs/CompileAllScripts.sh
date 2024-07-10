#!/bin/bash


echo "### Getting directory information ###"
DirLib=$(pwd)'/Lib'
DirProg=$(pwd)'/Src'


echo "### Removing existing binaries ###"
rm -f Bin_MCS51/*.ihx
rm -f Bin_Z180/*.ihx
rm -f Bin_MOS65C02/*.ihx


echo "### Compiling Trefoil ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/Trefoil'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/Trefoil'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/Trefoil'

echo "### Compiling CubeOctahedron ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/CubeOctahedron'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/CubeOctahedron'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/CubeOctahedron'

echo "### Compiling Paraboloid ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/Paraboloid'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/Paraboloid'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/Paraboloid'

echo "### Compiling Eratosthenes ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/Eratosthenes'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/Eratosthenes'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/Eratosthenes'

echo "### Compiling GaltonBoard ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/GaltonBoard'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/GaltonBoard'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/GaltonBoard'

echo "### Compiling PascalTriangle ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/PascalTriangle'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/PascalTriangle'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/PascalTriangle'

echo "### Compiling ColorWheel ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/ColorWheel'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/ColorWheel'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/ColorWheel'

echo "### Compiling Spirograph ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/Spirograph'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/Spirograph'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/Spirograph'

echo "### Compiling FormulaChart ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/FormulaChart'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/FormulaChart'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/FormulaChart'

echo "### Compiling GraphRecursion ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/GraphRecursion'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/GraphRecursion'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/GraphRecursion'

echo "### Compiling InterruptDemo - Z180 and MOS65C02 - custom crt0 library ###"
./Compile_MCS51.sh    '7F' ${DirLib} ${DirProg}'/InterruptDemo'
./Compile_Z180.sh     '7F' ${DirLib} ${DirProg}'/InterruptDemo' '--no-std-crt0 '${DirLib}'/Z180_Lib/crt0_ints.rel'
./Compile_MOS65C02.sh '7F' ${DirLib} ${DirProg}'/InterruptDemo' '--no-std-crt0 '${DirLib}'/MOS65C02_Lib/crt0_ints.rel'

echo "### Compiling NumCalc - Swap page address is BF instead of 7F ###"
./Compile_MCS51.sh    'BF' ${DirLib} ${DirProg}'/NumCalc'
./Compile_Z180.sh     'BF' ${DirLib} ${DirProg}'/NumCalc'
./Compile_MOS65C02.sh 'BF' ${DirLib} ${DirProg}'/NumCalc'


echo "### All scripts compiled, cleaning up ###"
cd Temp
rm -f *.ihx
rm -f *.asm
rm -f *.lst
rm -f *.map
rm -f *.lk
rm -f *.mem
rm -f *.sym
rm -f *.rst
rm -f *.rel
rm -f *.noi
cd ..


read -p "### Press ENTER key ###"


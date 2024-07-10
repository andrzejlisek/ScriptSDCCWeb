#!/bin/bash

rm compiled/*

emcc -O3 -std=c++20 prog/guiwidgets.cpp prog/guifont.cpp prog/guigraph.cpp prog/guigraphinstance_repaint.cpp prog/guigraphinstance_draw.cpp prog/guigraphinstance.cpp \
 prog/gui.cpp prog/scriptshared.cpp prog/hex.cpp \
 progio.cpp -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap']" -o compiled/progio.js -s ALLOW_MEMORY_GROWTH

emcc -O3 -std=c++20 prog/arrayhandle.cpp prog/arraystruct.cpp prog/arraystructdense.cpp prog/arraystructsparse.cpp \
 prog/filehandle.cpp prog/hex.cpp prog/scriptshared.cpp \
 prog/scriptengine.cpp prog/scriptengine_swap.cpp \
 prog/scriptenginemcs51.cpp prog/scriptenginez180.cpp prog/scriptenginez180_ext.cpp prog/scriptenginemos65c02.cpp prog/scriptenginemos65c02_ext.cpp \
 prog/scriptdecompile.cpp prog/scriptdecompilemcs51.cpp prog/scriptdecompilez180.cpp prog/scriptdecompilemos65c02.cpp \
 progcore.cpp -s BUILD_AS_WORKER=1 -o compiled/progcore.js -s ALLOW_MEMORY_GROWTH


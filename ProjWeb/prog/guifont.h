#ifndef GUIFONT_H
#define GUIFONT_H

#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>

class GuiFont
{
public:
    std::string (*GetGlyphJS)( int );
    char * GetGlyph(int Chr);
    int CellW_ = 0;
    int CellH_ = 0;
    int CellW = 0;
    int CellH = 0;
    int CellWH = 0;

    void SetFontSize(int CellW__, int CellH__, int FontSizeW_, int FontSizeH_);
    GuiFont();
    ~GuiFont();
private:
    int FontSizeW = 1;
    int FontSizeH = 1;
    std::map<int, std::vector<char>> Glyphs;
};

#endif // GUIFONT_H

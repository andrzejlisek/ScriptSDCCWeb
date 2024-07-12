#include "guifont.h"

GuiFont::GuiFont()
{

}

GuiFont::~GuiFont()
{

}

void GuiFont::SetFontSize(int CellW__, int CellH__)
{
    CellW_ = CellW__;
    CellH_ = CellH__;
    /*CellW = CellW__ * FontSize;
    CellH = CellH__ * FontSize;
    CellWH = CellW * CellH;*/
}

char * GuiFont::GetGlyph(int Chr, int FontSize)
{
    int ChrIdx = Chr + (FontSize << 20);
    if (Glyphs.find(ChrIdx) == Glyphs.end())
    {
        std::string GlyphJS = GetGlyphJS(Chr);
        std::vector<char> GlyphRaw;
        if (GlyphJS[0] != 'X')
        {
            for (int Y = 0; Y < CellH_; Y++)
            {
                for (int YY = 0; YY < FontSize; YY++)
                {
                    for (int X = 0; X < CellW_; X++)
                    {
                        for (int XX = 0; XX < FontSize; XX++)
                        {
                            GlyphRaw.push_back(GlyphJS[Y * CellW_ + X] - 48);
                        }
                    }
                }
            }
        }
        Glyphs[ChrIdx] = GlyphRaw;
    }

    if (Glyphs[ChrIdx].size() > 0)
    {
        return Glyphs[ChrIdx].data();
    }
    else
    {
        return NULL;
    }
}

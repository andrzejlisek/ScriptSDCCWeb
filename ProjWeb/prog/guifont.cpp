#include "guifont.h"

GuiFont::GuiFont()
{

}

GuiFont::~GuiFont()
{

}

void GuiFont::SetFontSize(int CellW__, int CellH__, int FontSizeW_, int FontSizeH_)
{
    FontSizeW = FontSizeW_;
    FontSizeH = FontSizeH_;
    CellW_ = CellW__;
    CellH_ = CellH__;
    CellW = CellW__ * FontSizeW_;
    CellH = CellH__ * FontSizeH_;
    CellWH = CellW * CellH;
    Glyphs.clear();
}

char * GuiFont::GetGlyph(int Chr)
{
    if (Glyphs.find(Chr) == Glyphs.end())
    {
        std::string GlyphJS = GetGlyphJS(Chr);
        std::vector<char> GlyphRaw;
        if (GlyphJS[0] != 'X')
        {
            for (int Y = 0; Y < CellH_; Y++)
            {
                for (int YY = 0; YY < FontSizeH; YY++)
                {
                    for (int X = 0; X < CellW_; X++)
                    {
                        for (int XX = 0; XX < FontSizeW; XX++)
                        {
                            GlyphRaw.push_back(GlyphJS[Y * CellW_ + X] - 48);
                        }
                    }
                }
            }
        }
        Glyphs[Chr] = GlyphRaw;
    }

    if (Glyphs[Chr].size() > 0)
    {
        return Glyphs[Chr].data();
    }
    else
    {
        return NULL;
    }
}

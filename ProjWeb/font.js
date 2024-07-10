let FontImg = null;
let FontImgW = 0;
let FontImgH = 0;
let FontCellW = 0;
let FontCellH = 0;
let FontCanvas = document.getElementById("FontCanvas");
let FontCanvasCtx;
let FontCanvasData;
let FontPage = [];


function FontGetPixelBin(X, Y)
{
    let Ptr = (FontImgW * Y + X) << 2;
    if ((FontCanvasData.data[Ptr + 0] + FontCanvasData.data[Ptr + 1] + FontCanvasData.data[Ptr + 2]) >= 384)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


function FontInit()
{
    FontImg = new Image();
    FontImg.onload = function() { FontInitCallback(); };
    FontImg.parent = this;
    FontImg.src = "font.png";
}

function FontInitCallback()
{
    FontImgW = FontImg.width;
    FontImgH = FontImg.height;
    FontCanvas.width = FontImgW;
    FontCanvas.height = FontImgH;
    FontCanvasCtx = FontCanvas.getContext('2d');
    FontCanvasCtx.drawImage(FontImg, 0, 0);
    FontCanvasData = FontCanvasCtx.getImageData(0, 0, FontImgW, FontImgH);
    let IdxI = 0;
    let Val0 = -1;
    for (let I = 0; I < FontImgH; I++)
    {
        let Val = 0;
        Val += (FontGetPixelBin( 0, I) << 15);
        Val += (FontGetPixelBin( 1, I) << 14);
        Val += (FontGetPixelBin( 2, I) << 13);
        Val += (FontGetPixelBin( 3, I) << 12);
        Val += (FontGetPixelBin( 4, I) << 11);
        Val += (FontGetPixelBin( 5, I) << 10);
        Val += (FontGetPixelBin( 6, I) <<  9);
        Val += (FontGetPixelBin( 7, I) <<  8);
        Val += (FontGetPixelBin( 8, I) <<  7);
        Val += (FontGetPixelBin( 9, I) <<  6);
        Val += (FontGetPixelBin(10, I) <<  5);
        Val += (FontGetPixelBin(11, I) <<  4);
        Val += (FontGetPixelBin(12, I) <<  3);
        Val += (FontGetPixelBin(13, I) <<  2);
        Val += (FontGetPixelBin(14, I) <<  1);
        Val += (FontGetPixelBin(15, I));
        if (Val0 != Val)
        {
            FontPage[IdxI] = Val;
            IdxI++;
            Val0 = Val;
        }
    }
        
    FontCellW = Math.round((FontImgW - 16) / 256);
    FontCellH = Math.round((FontImgH) / IdxI);
    
    FontLoaded = true;
}


function FontGetParam(N)
{
    switch (N)
    {
        case 1: return FontCellW;
        case 2: return FontCellH;
        case 3: return LayoutConfGraphFontSize;
        default: return 0;
    }
}

function FontGetGlyph(Chr)
{
    let ChrP = Chr >> 8;
    let ChrN = Chr % 256;
    let Idx0 = FontPage.indexOf(ChrP);
    if (Idx0 >= 0)
    {
        let Vals = "";
        let Ptr = 0;
        for (let Y = 0; Y < FontCellH; Y++)
        {
            for (let X = 0; X < FontCellW; X++)
            {
                Vals = Vals + "" + FontGetPixelBin(16 + (ChrN * FontCellW) + X, (Idx0 * FontCellH) + Y) + "";
                Ptr++;
            }
        }
        return Vals;
    }
    else
    {
        return "X";
    }
}






FontInit();

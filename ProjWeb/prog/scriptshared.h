#ifndef SCRIPTSHARED_H
#define SCRIPTSHARED_H

#include "valuetypes.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "hex.h"
#include <iostream>

#define IOConsoleCmd 1
#define IOWidgetCmd 4
#define IOGraphCmd 10
#define IOGraphTextCmd 15
#define IOMemoCmd 20

class ScriptShared
{
public:
    ScriptShared();

    void MemoSwapOperation();
    bool MemoIsShared();

    ubyte1 MemoGet1(uchar N, arrayidx Idx);
    void MemoSet1(uchar N, arrayidx Idx, ubyte1 Val);

    ubyte2 MemoGet2(uchar N, arrayidx Idx);
    void MemoSet2(uchar N, arrayidx Idx, ubyte2 Val);

    ubyte4 MemoGet4(uchar N, arrayidx Idx);
    void MemoSet4(uchar N, arrayidx Idx, ubyte4 Val);

    void MemoSwapProcessGet();
    void MemoSwapProcessSet();

    uchar * SwapData;
    int SwapOffset = 0;

    void SwapCreate();
    void SwapDestroy();

    int SwapExportLength = 0;
    std::string SwapExport();
    void SwapImport(std::string SwapStr);

    schar SwapGetSC(int Addr);
    uchar SwapGetUC(int Addr);
    short SwapGetSS(int Addr);
    ushort SwapGetUS(int Addr);
    int SwapGetSI(int Addr);
    uint SwapGetUI(int Addr);
    long SwapGetSL(int Addr);
    ulong SwapGetUL(int Addr);
    float SwapGetF(int Addr);
    std::string SwapGetStr(uchar NumType, int Addr);

    void SwapSetSC(int Addr, schar Val);
    void SwapSetUC(int Addr, uchar Val);
    void SwapSetSS(int Addr, short Val);
    void SwapSetUS(int Addr, ushort Val);
    void SwapSetSI(int Addr, int Val);
    void SwapSetUI(int Addr, uint Val);
    void SwapSetSL(int Addr, long Val);
    void SwapSetUL(int Addr, ulong Val);
    void SwapSetF(int Addr, float Val);
    void SwapSetStr(uchar NumType, int Addr, std::string Val);

    void TextBufClear();
    void TextBufAppend(uchar Chr);
    void TextBufAppendStr(std::string Chr);
    std::string TextBufGetString();
    uint TextBufGetInit();
    uchar TextBufGetChar();


    std::stringstream TextBuff;
private:
    int MemoTypeThr = 127;
    bool MemoTypeX = true;

    std::string FloatingPointCorrect(std::string NumStr, int Digits);
    std::string TextBuffS;
    uint TextBuffI;

    std::vector<uchar> MemoDataP[256];
    std::vector<uchar> MemoDataN[256];
    TypeConv ByteData;
    TypeConv TypeConv_;
};

#endif // SCRIPTSHARED_H

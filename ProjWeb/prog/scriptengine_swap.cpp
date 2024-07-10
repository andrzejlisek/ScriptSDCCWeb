#include "scriptengine.h"


void ScriptEngine::EngineMath()
{
    uchar CmdX = MemData[SwapPage + 1];
    uchar Op = MemData[SwapPage + 2];
    switch (Op)
    {
        case 1: // Add
            switch(CmdX)
            {
                case 0: { ScriptShared_.SwapSetSC(0x08, ScriptShared_.SwapGetSC(0x10) + ScriptShared_.SwapGetSC(0x18)); } break;
                case 1: { ScriptShared_.SwapSetUC(0x08, ScriptShared_.SwapGetUC(0x10) + ScriptShared_.SwapGetUC(0x18)); } break;
                case 4: { ScriptShared_.SwapSetSS(0x08, ScriptShared_.SwapGetSS(0x10) + ScriptShared_.SwapGetSS(0x18)); } break;
                case 5: { ScriptShared_.SwapSetUS(0x08, ScriptShared_.SwapGetUS(0x10) + ScriptShared_.SwapGetUS(0x18)); } break;
                case 6: { ScriptShared_.SwapSetSI(0x08, ScriptShared_.SwapGetSI(0x10) + ScriptShared_.SwapGetSI(0x18)); } break;
                case 7: { ScriptShared_.SwapSetUI(0x08, ScriptShared_.SwapGetUI(0x10) + ScriptShared_.SwapGetUI(0x18)); } break;
                case 8: { ScriptShared_.SwapSetSL(0x08, ScriptShared_.SwapGetSL(0x10) + ScriptShared_.SwapGetSL(0x18)); } break;
                case 9: { ScriptShared_.SwapSetUL(0x08, ScriptShared_.SwapGetUL(0x10) + ScriptShared_.SwapGetUL(0x18)); } break;
                case 10:{ ScriptShared_.SwapSetF(0x08,  ScriptShared_.SwapGetF(0x10)  + ScriptShared_.SwapGetF(0x18));  } break;
            }
            break;
        case 2: // Subtract
            switch(CmdX)
            {
                case 0: { ScriptShared_.SwapSetSC(0x08, ScriptShared_.SwapGetSC(0x10) - ScriptShared_.SwapGetSC(0x18)); } break;
                case 1: { ScriptShared_.SwapSetUC(0x08, ScriptShared_.SwapGetUC(0x10) - ScriptShared_.SwapGetUC(0x18)); } break;
                case 4: { ScriptShared_.SwapSetSS(0x08, ScriptShared_.SwapGetSS(0x10) - ScriptShared_.SwapGetSS(0x18)); } break;
                case 5: { ScriptShared_.SwapSetUS(0x08, ScriptShared_.SwapGetUS(0x10) - ScriptShared_.SwapGetUS(0x18)); } break;
                case 6: { ScriptShared_.SwapSetSI(0x08, ScriptShared_.SwapGetSI(0x10) - ScriptShared_.SwapGetSI(0x18)); } break;
                case 7: { ScriptShared_.SwapSetUI(0x08, ScriptShared_.SwapGetUI(0x10) - ScriptShared_.SwapGetUI(0x18)); } break;
                case 8: { ScriptShared_.SwapSetSL(0x08, ScriptShared_.SwapGetSL(0x10) - ScriptShared_.SwapGetSL(0x18)); } break;
                case 9: { ScriptShared_.SwapSetUL(0x08, ScriptShared_.SwapGetUL(0x10) - ScriptShared_.SwapGetUL(0x18)); } break;
                case 10:{ ScriptShared_.SwapSetF(0x08,  ScriptShared_.SwapGetF(0x10)  - ScriptShared_.SwapGetF(0x18));  } break;
            }
            break;
        case 3: // Multiply
            switch(CmdX)
            {
                case 0: { ScriptShared_.SwapSetSC(0x08, ScriptShared_.SwapGetSC(0x10) * ScriptShared_.SwapGetSC(0x18)); } break;
                case 1: { ScriptShared_.SwapSetUC(0x08, ScriptShared_.SwapGetUC(0x10) * ScriptShared_.SwapGetUC(0x18)); } break;
                case 4: { ScriptShared_.SwapSetSS(0x08, ScriptShared_.SwapGetSS(0x10) * ScriptShared_.SwapGetSS(0x18)); } break;
                case 5: { ScriptShared_.SwapSetUS(0x08, ScriptShared_.SwapGetUS(0x10) * ScriptShared_.SwapGetUS(0x18)); } break;
                case 6: { ScriptShared_.SwapSetSI(0x08, ScriptShared_.SwapGetSI(0x10) * ScriptShared_.SwapGetSI(0x18)); } break;
                case 7: { ScriptShared_.SwapSetUI(0x08, ScriptShared_.SwapGetUI(0x10) * ScriptShared_.SwapGetUI(0x18)); } break;
                case 8: { ScriptShared_.SwapSetSL(0x08, ScriptShared_.SwapGetSL(0x10) * ScriptShared_.SwapGetSL(0x18)); } break;
                case 9: { ScriptShared_.SwapSetUL(0x08, ScriptShared_.SwapGetUL(0x10) * ScriptShared_.SwapGetUL(0x18)); } break;
                case 10:{ ScriptShared_.SwapSetF(0x08,  ScriptShared_.SwapGetF(0x10)  * ScriptShared_.SwapGetF(0x18));  } break;
            }
            break;
        case 4: // Divide
            switch(CmdX)
            {
                case 0: { ScriptShared_.SwapSetSC(0x08, ScriptShared_.SwapGetSC(0x10) / ScriptShared_.SwapGetSC(0x18)); } break;
                case 1: { ScriptShared_.SwapSetUC(0x08, ScriptShared_.SwapGetUC(0x10) / ScriptShared_.SwapGetUC(0x18)); } break;
                case 4: { ScriptShared_.SwapSetSS(0x08, ScriptShared_.SwapGetSS(0x10) / ScriptShared_.SwapGetSS(0x18)); } break;
                case 5: { ScriptShared_.SwapSetUS(0x08, ScriptShared_.SwapGetUS(0x10) / ScriptShared_.SwapGetUS(0x18)); } break;
                case 6: { ScriptShared_.SwapSetSI(0x08, ScriptShared_.SwapGetSI(0x10) / ScriptShared_.SwapGetSI(0x18)); } break;
                case 7: { ScriptShared_.SwapSetUI(0x08, ScriptShared_.SwapGetUI(0x10) / ScriptShared_.SwapGetUI(0x18)); } break;
                case 8: { ScriptShared_.SwapSetSL(0x08, ScriptShared_.SwapGetSL(0x10) / ScriptShared_.SwapGetSL(0x18)); } break;
                case 9: { ScriptShared_.SwapSetUL(0x08, ScriptShared_.SwapGetUL(0x10) / ScriptShared_.SwapGetUL(0x18)); } break;
                case 10:{ ScriptShared_.SwapSetF(0x08,  ScriptShared_.SwapGetF(0x10)  / ScriptShared_.SwapGetF(0x18));  } break;
            }
            break;
        case 5: // Modulo
            switch(CmdX)
            {
                case 0: { ScriptShared_.SwapSetSC(0x08, ScriptShared_.SwapGetSC(0x10) % ScriptShared_.SwapGetSC(0x18)); } break;
                case 1: { ScriptShared_.SwapSetUC(0x08, ScriptShared_.SwapGetUC(0x10) % ScriptShared_.SwapGetUC(0x18)); } break;
                case 4: { ScriptShared_.SwapSetSS(0x08, ScriptShared_.SwapGetSS(0x10) % ScriptShared_.SwapGetSS(0x18)); } break;
                case 5: { ScriptShared_.SwapSetUS(0x08, ScriptShared_.SwapGetUS(0x10) % ScriptShared_.SwapGetUS(0x18)); } break;
                case 6: { ScriptShared_.SwapSetSI(0x08, ScriptShared_.SwapGetSI(0x10) % ScriptShared_.SwapGetSI(0x18)); } break;
                case 7: { ScriptShared_.SwapSetUI(0x08, ScriptShared_.SwapGetUI(0x10) % ScriptShared_.SwapGetUI(0x18)); } break;
                case 8: { ScriptShared_.SwapSetSL(0x08, ScriptShared_.SwapGetSL(0x10) % ScriptShared_.SwapGetSL(0x18)); } break;
                case 9: { ScriptShared_.SwapSetUL(0x08, ScriptShared_.SwapGetUL(0x10) % ScriptShared_.SwapGetUL(0x18)); } break;
            }
            break;

        case 6:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, round(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 7:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, floor(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 8:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, ceil(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 9:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, trunc(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;

        case 11:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, cos(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 12:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, sin(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 13:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, tan(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 14:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, acos(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 15:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, asin(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 16:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, atan(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 17:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, atan2(ScriptShared_.SwapGetF(0x10), ScriptShared_.SwapGetF(0x18))); } break;
            }
            break;

        case 18:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, expm1(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 19:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, log1p(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;

        case 21:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, cosh(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 22:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, sinh(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 23:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, tanh(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 24:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, acosh(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 25:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, asinh(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 26:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, atanh(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;

        case 31:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, erf(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 32:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, erfc(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 33:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, tgamma(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 34:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, lgamma(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;

        case 35:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, log(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 36:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, log10(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 37:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, log2(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 38:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, exp(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 39:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, exp2(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;

        case 41:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, pow(ScriptShared_.SwapGetF(0x10), ScriptShared_.SwapGetF(0x18))); } break;
            }
            break;
        case 42:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, sqrt(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 43:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, cbrt(ScriptShared_.SwapGetF(0x10))); } break;
            }
            break;
        case 44:
            switch(CmdX)
            {
                case 10: { ScriptShared_.SwapSetF(0x08, hypot(ScriptShared_.SwapGetF(0x10), ScriptShared_.SwapGetF(0x18))); } break;
            }
            break;
    }
}


/*
                    uchar CmdX = MemData[SwapPage + 1];
                    switch(CmdX)
                    {
                        case 0: { std::uniform_int_distribution<schar>  dist(ScriptShared_.SwapGetSC(0x08), ScriptShared_.SwapGetSC(0x10)); ScriptShared_.SwapSetSC(0x08, dist(RandomGen)); } break;
                        case 1: { std::uniform_int_distribution<uchar>  dist(ScriptShared_.SwapGetUC(0x08), ScriptShared_.SwapGetUC(0x10)); ScriptShared_.SwapSetUC(0x08, dist(RandomGen)); } break;
                        case 4: { std::uniform_int_distribution<short>  dist(ScriptShared_.SwapGetSS(0x08), ScriptShared_.SwapGetSS(0x10)); ScriptShared_.SwapSetSS(0x08, dist(RandomGen)); } break;
                        case 5: { std::uniform_int_distribution<ushort> dist(ScriptShared_.SwapGetUS(0x08), ScriptShared_.SwapGetUS(0x10)); ScriptShared_.SwapSetUS(0x08, dist(RandomGen)); } break;
                        case 6: { std::uniform_int_distribution<int>    dist(ScriptShared_.SwapGetSI(0x08), ScriptShared_.SwapGetSI(0x10)); ScriptShared_.SwapSetSI(0x08, dist(RandomGen)); } break;
                        case 7: { std::uniform_int_distribution<uint>   dist(ScriptShared_.SwapGetUI(0x08), ScriptShared_.SwapGetUI(0x10)); ScriptShared_.SwapSetUI(0x08, dist(RandomGen)); } break;
                        case 8: { std::uniform_int_distribution<long>   dist(ScriptShared_.SwapGetSL(0x08), ScriptShared_.SwapGetSL(0x10)); ScriptShared_.SwapSetSL(0x08, dist(RandomGen)); } break;
                        case 9: { std::uniform_int_distribution<ulong>  dist(ScriptShared_.SwapGetUL(0x08), ScriptShared_.SwapGetUL(0x10)); ScriptShared_.SwapSetUL(0x08, dist(RandomGen)); } break;
                        case 10:{ std::uniform_real_distribution<float> dist(ScriptShared_.SwapGetF(0x08),  ScriptShared_.SwapGetF(0x10));  ScriptShared_.SwapSetF(0x08,  dist(RandomGen)); } break;
                    }
*/

/*                    int ValueType = ScriptShared_.SwapGetUC(1);
                    if (ValueType < 11)
                    {
                        ScriptShared_.TextBufGetInit();
                        ScriptShared_.SwapSetStr(ValueType, 0x08, ScriptShared_.TextBufGetString());
                    }
                    else
                    {
                        ScriptShared_.SwapSetUI(0x08, ScriptShared_.TextBufGetInit());
                    }
*/

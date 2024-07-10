#include "scriptenginemos65c02.h"

/*
void ScriptEngineMOS65C02::DebugTraceMem(int Addr, int Quan)
{
    std::cout << "  (" + Hex::IntToHex16(Addr) + ")=";
    for (int I = 0; I < Quan; I++)
    {
        std::cout << Hex::IntToHex8(MemGet(Addr + I));
    }
}

void ScriptEngineMOS65C02::DebugTrace()
{
    //std::cout << Hex::IntToHex16(Reg_PC) << "  " << Hex::IntToHex8(MemPrg(Reg_PC)) << Hex::IntToHex8(MemPrg(Reg_PC + 1)) << Hex::IntToHex8(MemPrg(Reg_PC + 2)) << Hex::IntToHex8(MemPrg(Reg_PC + 3)) << std::endl;


    if ((MemGet(SwapPage + 128) >= 0x80) && (StatusC == 0))
    {
        std::cout << "PC=" << Hex::IntToHex16(Reg_PC) << "   ";
        std::cout << "      ";
        std::cout << Hex::IntToHex8(MemGet(Reg_PC + 0));
        std::cout << Hex::IntToHex8(MemGet(Reg_PC + 1));
        std::cout << Hex::IntToHex8(MemGet(Reg_PC + 2));
        std::cout << Hex::IntToHex8(MemGet(Reg_PC + 3));

        std::cout << "      ";
        std::cout << "A=" << Hex::IntToHex8(Reg_A) << "   ";
        std::cout << "SP=" << Hex::IntToHex8(Reg_SP) << "   ";
        std::cout << "X=" << Hex::IntToHex8(Reg_X) << "   ";
        std::cout << "Y=" << Hex::IntToHex8(Reg_Y) << "   ";

        std::cout << "_N=" << ((Reg_F_N > 0) ? 1 : 0) << "  ";
        std::cout << "_V=" << ((Reg_F_V > 0) ? 1 : 0) << "  ";
        std::cout << "_B=" << ((Reg_F_B > 0) ? 1 : 0) << "  ";
        std::cout << "_D=" << ((Reg_F_D > 0) ? 1 : 0) << "  ";
        std::cout << "_I=" << ((Reg_F_I > 0) ? 1 : 0) << "  ";
        std::cout << "_Z=" << ((Reg_F_Z > 0) ? 1 : 0) << "  ";
        std::cout << "_C=" << ((Reg_F_C > 0) ? 1 : 0) << "  ";


        //DebugTraceMem(0x0000, 2);
        //DebugTraceMem(0x0863, 4);
        //DebugTraceMem(0x0868, 4);

        //DebugTraceMem(0x6864, 2);
        //DebugTraceMem(0x9000, 4);


        std::cout << "     " ;
        std::cout << Hex::IntToHex8(MemProg[SwapPage + 128]) << " " << (int)StatusC;
        std::cout << std::endl;

        if (MemData[SwapPage] == 255)
        {
            StatusC = 5;
        }
    }
}
*/

void ScriptEngineMOS65C02::DoCommandExt(uchar OpCode)
{
    uchar Temp_uchar;
    switch (OpCode)
    {
        default:
            MemData[SwapPage] = 255;
            FeedbackData("E", MessagePrefix, "Unknown instruction at " + Hex::IntToHex16(Reg_PC - 1) + ": " + Hex::IntToHex8(MemPrg(Reg_PC - 1)));
            break;

        case 0xEA: // NOP
            break;

        case 0x80: // BRA $nnnn
            DoBranch();
            break;

        case 0x1C: // TRB $nnnn
            Temp_uchar = AddrGetAbsolute() & (255 - Reg_A);
            MOS6502_FlagZVal(Temp_uchar == 0);
            AddrSetAbsolute(Temp_uchar);
            Reg_PC += 2;
            break;
        case 0x14: // TRB $nn
            Temp_uchar = AddrGetZeroPage() & (255 - Reg_A);
            MOS6502_FlagZVal(Temp_uchar == 0);
            AddrSetZeroPage(Temp_uchar);
            Reg_PC += 1;
            break;
        case 0x0C: // TSB $nnnn
            Temp_uchar = AddrGetAbsolute() | Reg_A;
            MOS6502_FlagZVal(Temp_uchar == 0);
            AddrSetAbsolute(Temp_uchar);
            Reg_PC += 2;
            break;
        case 0x04: // TSB $nn
            Temp_uchar = AddrGetZeroPage() | Reg_A;
            MOS6502_FlagZVal(Temp_uchar == 0);
            AddrSetZeroPage(Temp_uchar);
            Reg_PC += 1;
            break;

        case 0x9C: // STZ $nnnn
            AddrSetAbsolute(0);
            Reg_PC += 2;
            break;
        case 0x9E: // STZ $nnnn,X
            AddrSetXIndexedAbsolute(0);
            Reg_PC += 2;
            break;
        case 0x64: // STZ $nn
            AddrSetZeroPage(0);
            Reg_PC += 1;
            break;
        case 0x74: // STZ $nn,Y
            AddrSetXIndexedZeroPage(0);
            Reg_PC += 1;
            break;


        case 0x07: // RMB0 $nn
            AddrSetZeroPage(AddrGetZeroPage() & 0b11111110);
            Reg_PC += 1;
            break;
        case 0x17: // RMB1 $nn
            AddrSetZeroPage(AddrGetZeroPage() & 0b11111101);
            Reg_PC += 1;
            break;
        case 0x27: // RMB2 $nn
            AddrSetZeroPage(AddrGetZeroPage() & 0b11111011);
            Reg_PC += 1;
            break;
        case 0x37: // RMB3 $nn
            AddrSetZeroPage(AddrGetZeroPage() & 0b11110111);
            Reg_PC += 1;
            break;
        case 0x47: // RMB4 $nn
            AddrSetZeroPage(AddrGetZeroPage() & 0b11101111);
            Reg_PC += 1;
            break;
        case 0x57: // RMB5 $nn
            AddrSetZeroPage(AddrGetZeroPage() & 0b11011111);
            Reg_PC += 1;
            break;
        case 0x67: // RMB6 $nn
            AddrSetZeroPage(AddrGetZeroPage() & 0b10111111);
            Reg_PC += 1;
            break;
        case 0x77: // RMB7 $nn
            AddrSetZeroPage(AddrGetZeroPage() & 0b01111111);
            Reg_PC += 1;
            break;

        case 0x87: // SMB0 $nn
            AddrSetZeroPage(AddrGetZeroPage() | 0b00000001);
            Reg_PC += 1;
            break;
        case 0x97: // SMB1 $nn
            AddrSetZeroPage(AddrGetZeroPage() | 0b00000010);
            Reg_PC += 1;
            break;
        case 0xA7: // SMB2 $nn
            AddrSetZeroPage(AddrGetZeroPage() | 0b00000100);
            Reg_PC += 1;
            break;
        case 0xB7: // SMB3 $nn
            AddrSetZeroPage(AddrGetZeroPage() | 0b00001000);
            Reg_PC += 1;
            break;
        case 0xC7: // SMB4 $nn
            AddrSetZeroPage(AddrGetZeroPage() | 0b00010000);
            Reg_PC += 1;
            break;
        case 0xD7: // SMB5 $nn
            AddrSetZeroPage(AddrGetZeroPage() | 0b00100000);
            Reg_PC += 1;
            break;
        case 0xE7: // SMB6 $nn
            AddrSetZeroPage(AddrGetZeroPage() | 0b01000000);
            Reg_PC += 1;
            break;
        case 0xF7: // SMB7 $nn
            AddrSetZeroPage(AddrGetZeroPage() | 0b10000000);
            Reg_PC += 1;
            break;


        case 0x0F: // BBR0 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00000001) { Reg_PC += 2; } else { DoBranch1(); }
            break;
        case 0x1F: // BBR1 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00000010) { Reg_PC += 2; } else { DoBranch1(); }
            break;
        case 0x2F: // BBR2 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00000100) { Reg_PC += 2; } else { DoBranch1(); }
            break;
        case 0x3F: // BBR3 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00001000) { Reg_PC += 2; } else { DoBranch1(); }
            break;
        case 0x4F: // BBR4 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00010000) { Reg_PC += 2; } else { DoBranch1(); }
            break;
        case 0x5F: // BBR5 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00100000) { Reg_PC += 2; } else { DoBranch1(); }
            break;
        case 0x6F: // BBR6 $nn,$nnnn
            if (AddrGetZeroPage() & 0x01000000) { Reg_PC += 2; } else { DoBranch1(); }
            break;
        case 0x7F: // BBR7 $nn,$nnnn
            if (AddrGetZeroPage() & 0x10000000) { Reg_PC += 2; } else { DoBranch1(); }
            break;

        case 0x8F: // BBS0 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00000001) { DoBranch1(); } else { Reg_PC += 2; }
            break;
        case 0x9F: // BBS1 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00000010) { DoBranch1(); } else { Reg_PC += 2; }
            break;
        case 0xAF: // BBS2 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00000100) { DoBranch1(); } else { Reg_PC += 2; }
            break;
        case 0xBF: // BBS3 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00001000) { DoBranch1(); } else { Reg_PC += 2; }
            break;
        case 0xCF: // BBS4 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00010000) { DoBranch1(); } else { Reg_PC += 2; }
            break;
        case 0xDF: // BBS5 $nn,$nnnn
            if (AddrGetZeroPage() & 0x00100000) { DoBranch1(); } else { Reg_PC += 2; }
            break;
        case 0xEF: // BBS6 $nn,$nnnn
            if (AddrGetZeroPage() & 0x01000000) { DoBranch1(); } else { Reg_PC += 2; }
            break;
        case 0xFF: // BBS7 $nn,$nnnn
            if (AddrGetZeroPage() & 0x10000000) { DoBranch1(); } else { Reg_PC += 2; }
            break;
    }
}

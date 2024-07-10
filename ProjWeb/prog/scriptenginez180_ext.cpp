#include "scriptenginez180.h"

void ScriptEngineZ180::DoCommandExtCB(uchar OpCode0)
{
    uchar OpCode1 = MemPrg(Reg_PC);
    uchar Data1;
    Reg_PC++;

    // Reading register
    switch (OpCode1 & 0b00000111)
    {
        case 0: Data1 = Reg_B; break;
        case 1: Data1 = Reg_C; break;
        case 2: Data1 = Reg_D; break;
        case 3: Data1 = Reg_E; break;
        case 4: Data1 = Reg_H; break;
        case 5: Data1 = Reg_L; break;
        case 6: Data1 = MemGet(Reg_H, Reg_L); break;
        case 7: Data1 = Reg_A; break;
    }

    // Performing operation
    switch (OpCode1 & 0b11111000)
    {
        case 0x00: // RLC X
            DoRLC(Data1, true);
            break;
        case 0x08: // RRC X
            DoRRC(Data1, true);
            break;
        case 0x10: // RL X
            DoRL(Data1, true);
            break;
        case 0x18: // RR X
            DoRR(Data1, true);
            break;
        case 0x20: // SLA X
            DoSLA(Data1);
            break;
        case 0x28: // SRA X
            DoSRA(Data1);
            break;
        case 0x30: // SLL X undocumented
            DoSLL(Data1);
            break;
        case 0x38: // SRL X
            DoSRL(Data1);
            break;
        case 0x40: // BIT 0, X
            if (Data1 & 0b00000001) { FlagZClr; } else { FlagZSet; FlagPSet; } FlagHSet; FlagNClr; FlagSClr;
            break;
        case 0x48: // BIT 1, X
            if (Data1 & 0b00000010) { FlagZClr; } else { FlagZSet; FlagPSet; } FlagHSet; FlagNClr; FlagSClr;
            break;
        case 0x50: // BIT 2, X
            if (Data1 & 0b00000100) { FlagZClr; } else { FlagZSet; FlagPSet; } FlagHSet; FlagNClr; FlagSClr;
            break;
        case 0x58: // BIT 3, X
            if (Data1 & 0b00001000) { FlagZClr; } else { FlagZSet; FlagPSet; } FlagHSet; FlagNClr; FlagSClr;
            break;
        case 0x60: // BIT 4, X
            if (Data1 & 0b00010000) { FlagZClr; } else { FlagZSet; FlagPSet; } FlagHSet; FlagNClr; FlagSClr;
            break;
        case 0x68: // BIT 5, X
            if (Data1 & 0b00100000) { FlagZClr; } else { FlagZSet; FlagPSet; } FlagHSet; FlagNClr; FlagSClr;
            break;
        case 0x70: // BIT 6, X
            if (Data1 & 0b01000000) { FlagZClr; } else { FlagZSet; FlagPSet; } FlagHSet; FlagNClr; FlagSClr;
            break;
        case 0x78: // BIT 7, X
            if (Data1 & 0b10000000) { FlagZClr; } else { FlagZSet; FlagPSet; } FlagHSet; FlagNClr; FlagSClr;
            break;
        case 0x80: // RES 0, X
            Data1 = Data1 & 0b11111110;
            break;
        case 0x88: // RES 1, X
            Data1 = Data1 & 0b11111101;
            break;
        case 0x90: // RES 2, X
            Data1 = Data1 & 0b11111011;
            break;
        case 0x98: // RES 3, X
            Data1 = Data1 & 0b11110111;
            break;
        case 0xA0: // RES 4, X
            Data1 = Data1 & 0b11101111;
            break;
        case 0xA8: // RES 5, X
            Data1 = Data1 & 0b11011111;
            break;
        case 0xB0: // RES 6, X
            Data1 = Data1 & 0b10111111;
            break;
        case 0xB8: // RES 7, X
            Data1 = Data1 & 0b01111111;
            break;
        case 0xC0: // SET 0, X
            Data1 = Data1 | 0b00000001;
            break;
        case 0xC8: // SET 1, X
            Data1 = Data1 | 0b00000010;
            break;
        case 0xD0: // SET 2, X
            Data1 = Data1 | 0b00000100;
            break;
        case 0xD8: // SET 3, X
            Data1 = Data1 | 0b00001000;
            break;
        case 0xE0: // SET 4, X
            Data1 = Data1 | 0b00010000;
            break;
        case 0xE8: // SET 5, X
            Data1 = Data1 | 0b00100000;
            break;
        case 0xF0: // SET 6, X
            Data1 = Data1 | 0b01000000;
            break;
        case 0xF8: // SET 7, X
            Data1 = Data1 | 0b10000000;
            break;
        default:
            Reg_PC--;
            Reg_PC--;
            MemData[SwapPage] = 255;
            FeedbackData("E", MessagePrefix, "Unknown instruction at " + Hex::IntToHex16(Reg_PC) + ": " + Hex::IntToHex8(OpCode0) + " " + Hex::IntToHex8(OpCode1));
            break;
    }

    // Writing register
    switch (OpCode1 & 0b00000111)
    {
        case 0: Reg_B = Data1; break;
        case 1: Reg_C = Data1; break;
        case 2: Reg_D = Data1; break;
        case 3: Reg_E = Data1; break;
        case 4: Reg_H = Data1; break;
        case 5: Reg_L = Data1; break;
        case 6: MemSet(Reg_H, Reg_L, Data1); break;
        case 7: Reg_A = Data1; break;
    }
}

void ScriptEngineZ180::DoCommandExt_D(uchar OpCode0)
{
    uchar OpCode1 = MemPrg(Reg_PC);
    uchar OpCode2;
    uchar Data1;
    uchar Data2;
    uchar Data3;
    uchar Data4;
    uchar Arg1;
    uchar Arg2;
    int Data1I;
    int Data2I;

    Reg_PC++;

    // Reading IX/IY register
    if (OpCode0 == 0xDD)
    {
        Reg_Idx = Reg_IX;
    }
    else
    {
        Reg_Idx = Reg_IY;
    }

    // Performing instruction
    switch (OpCode1)
    {
        case 0x09: // ADD I_, BC
            DoADD2_I_(Reg_B, Reg_C);
            break;
        case 0x19: // ADD I_, DE
            DoADD2_I_(Reg_D, Reg_E);
            break;
        case 0x29: // ADD I_, I_
            DoADD2_I_(Reg_Idx);
            break;
        case 0x39: // ADD I_, SP
            DoADD2_I_(Reg_SP);
            break;
        case 0x23: // INC I_
            Reg_Idx++;
            break;
        case 0x2B: // DEC I_
            Reg_Idx--;
            break;
        case 0x34: // INC (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Data1 = MemGet(RegIdxD);
            DoINC(Data1);
            MemSet(RegIdxD, Data1);
            break;
        case 0x35: // DEC (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Data1 = MemGet(RegIdxD);
            DoDEC(Data1);
            MemSet(RegIdxD, Data1);
            break;

        case 0x21: // LD I_, NN
            Data1I = MemPrg(Reg_PC);
            Reg_PC++;
            Data2I = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_Idx = (Data2I << 8) + Data1I;
            break;
        case 0x22: // LD (NN), I_
            Data1I = MemPrg(Reg_PC);
            Reg_PC++;
            Data2I = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet((Data2I << 8) + Data1I, Reg_Idx & 255);
            MemSet((Data2I << 8) + Data1I + 1, Reg_Idx >> 8);
            break;
        case 0x2A: // LD I_, (NN)
            Data1I = MemPrg(Reg_PC);
            Reg_PC++;
            Data2I = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_Idx = MemGet(Data2I, Data1I);
            Data1I++;
            if (Data1I == 256)
            {
                Data2I++;
                Data1I = 0;
            }
            Reg_Idx = Reg_Idx + (((ushort)MemGet(Data2I, Data1I)) << 8);
            break;
        case 0xF9: // LD SP, I_
            Reg_SP = Reg_Idx;
            break;
        case 0x36: // LD (I_ + d), N
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet(RegIdxD, Arg2);
            break;

        case 0x46: // LD B, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_B = MemGet(RegIdxD);
            break;
        case 0x4E: // LD C, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_C = MemGet(RegIdxD);
            break;
        case 0x56: // LD D, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_D = MemGet(RegIdxD);
            break;
        case 0x5E: // LD E, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_E = MemGet(RegIdxD);
            break;
        case 0x66: // LD H, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_H = MemGet(RegIdxD);
            break;
        case 0x6E: // LD L, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_L = MemGet(RegIdxD);
            break;
        case 0x7E: // LD A, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_A = MemGet(RegIdxD);
            break;

        case 0x70: // LD (I_ + d), B
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet(RegIdxD, Reg_B);
            break;
        case 0x71: // LD (I_ + d), C
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet(RegIdxD, Reg_C);
            break;
        case 0x72: // LD (I_ + d), D
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet(RegIdxD, Reg_D);
            break;
        case 0x73: // LD (I_ + d), E
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet(RegIdxD, Reg_E);
            break;
        case 0x74: // LD (I_ + d), H
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet(RegIdxD, Reg_H);
            break;
        case 0x75: // LD (I_ + d), L
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet(RegIdxD, Reg_L);
            break;
        case 0x77: // LD (I_ + d), A
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            MemSet(RegIdxD, Reg_A);
            break;

        case 0x86: // ADD A, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            DoADD1(MemGet(RegIdxD), false);
            break;
        case 0x8E: // ADC A, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            DoADD1(MemGet(RegIdxD), true);
            break;
        case 0x96: // SUB, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            DoSUB1(MemGet(RegIdxD), false);
            break;
        case 0x9E: // SBC A, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            DoSUB1(MemGet(RegIdxD), true);
            break;
        case 0xA6: // AND, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            DoAND(MemGet(RegIdxD));
            break;
        case 0xAE: // XOR, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            DoXOR(MemGet(RegIdxD));
            break;
        case 0xB6: // OR, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            DoOR(MemGet(RegIdxD));
            break;
        case 0xBE: // CP, (I_ + d)
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            DoCP(MemGet(RegIdxD));
            break;

        case 0xE3: // EX (SP), I_
            Data1 = (Reg_Idx & 255);
            Data2 = (Reg_Idx >> 8);
            Data3 = MemGet(Reg_SP);
            Data4 = MemGet(Reg_SP + 1);
            MemSet(Reg_SP, Data1);
            MemSet(Reg_SP + 1, Data2);
            Reg_Idx = (((ushort)Data4) << 8) + ((ushort)Data3);
            break;
        case 0xE1: // POP I_
            DoPOP(Data1, Data2);
            Reg_Idx = (((ushort)Data1) << 8) + ((ushort)Data2);
            break;
        case 0xE5: // PUSH I_
            Data1 = (Reg_Idx >> 8);
            Data2 = (Reg_Idx & 255);
            DoPUSH(Data1, Data2);
            break;
        case 0xE9: // JP (I_)
            ScriptDecompile_->JumpVectorAddr(Reg_PC - 2, Reg_Idx);
            Reg_PC = Reg_Idx;
            break;

        case 0xCB: // CB instructions
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            OpCode2 = MemPrg(Reg_PC);
            Reg_PC++;
            Data1 = MemGet(RegIdxD);
            switch (OpCode2)
            {
                case 0x06: // RLC (I_ + d)
                    DoRLC(Data1, true);
                    break;
                case 0x0E: // RRC (I_ + d)
                    DoRRC(Data1, true);
                    break;
                case 0x16: // RL (I_ + d)
                    DoRL(Data1, true);
                    break;
                case 0x1E: // RR (I_ + d)
                    DoRR(Data1, true);
                    break;

                case 0x26: // SLA (I_ + d)
                    DoSLA(Data1);
                    break;
                case 0x2E: // SRA (I_ + d)
                    DoSRA(Data1);
                    break;
                case 0x36: // SLL (I_ + d) undocumented
                    DoSLL(Data1);
                    break;
                case 0x3E: // SRL (I_ + d)
                    DoSRL(Data1);
                    break;

                case 0x46: // BIT 0, (I_ + d)
                    if (Data1 & 0b00000001) { FlagZClr; } else { FlagZSet; } FlagHSet; FlagNClr;
                    break;
                case 0x4E: // BIT 1, (I_ + d)
                    if (Data1 & 0b00000010) { FlagZClr; } else { FlagZSet; } FlagHSet; FlagNClr;
                    break;
                case 0x56: // BIT 2, (I_ + d)
                    if (Data1 & 0b00000100) { FlagZClr; } else { FlagZSet; } FlagHSet; FlagNClr;
                    break;
                case 0x5E: // BIT 3, (I_ + d)
                    if (Data1 & 0b00001000) { FlagZClr; } else { FlagZSet; } FlagHSet; FlagNClr;
                    break;
                case 0x66: // BIT 4, (I_ + d)
                    if (Data1 & 0b00010000) { FlagZClr; } else { FlagZSet; } FlagHSet; FlagNClr;
                    break;
                case 0x6E: // BIT 5, (I_ + d)
                    if (Data1 & 0b00100000) { FlagZClr; } else { FlagZSet; } FlagHSet; FlagNClr;
                    break;
                case 0x76: // BIT 6, (I_ + d)
                    if (Data1 & 0b01000000) { FlagZClr; } else { FlagZSet; } FlagHSet; FlagNClr;
                    break;
                case 0x7E: // BIT 7, (I_ + d)
                    if (Data1 & 0b10000000) { FlagZClr; } else { FlagZSet; } FlagHSet; FlagNClr;
                    break;

                case 0x86: // RES 0, (I_ + d)
                    Data1 = Data1 & 0b11111110;
                    break;
                case 0x8E: // RES 1, (I_ + d)
                    Data1 = Data1 & 0b11111101;
                    break;
                case 0x96: // RES 2, (I_ + d)
                    Data1 = Data1 & 0b11111011;
                    break;
                case 0x9E: // RES 3, (I_ + d)
                    Data1 = Data1 & 0b11110111;
                    break;
                case 0xA6: // RES 4, (I_ + d)
                    Data1 = Data1 & 0b11101111;
                    break;
                case 0xAE: // RES 5, (I_ + d)
                    Data1 = Data1 & 0b11011111;
                    break;
                case 0xB6: // RES 6, (I_ + d)
                    Data1 = Data1 & 0b10111111;
                    break;
                case 0xBE: // RES 7, (I_ + d)
                    Data1 = Data1 & 0b01111111;
                    break;

                case 0xC6: // SET 0, (I_ + d)
                    Data1 = Data1 | 0b00000001;
                    break;
                case 0xCE: // SET 1, (I_ + d)
                    Data1 = Data1 | 0b00000010;
                    break;
                case 0xD6: // SET 2, (I_ + d)
                    Data1 = Data1 | 0b00000100;
                    break;
                case 0xDE: // SET 3, (I_ + d)
                    Data1 = Data1 | 0b00001000;
                    break;
                case 0xE6: // SET 4, (I_ + d)
                    Data1 = Data1 | 0b00010000;
                    break;
                case 0xEE: // SET 5, (I_ + d)
                    Data1 = Data1 | 0b00100000;
                    break;
                case 0xF6: // SET 6, (I_ + d)
                    Data1 = Data1 | 0b01000000;
                    break;
                case 0xFE: // SET 7, (I_ + d)
                    Data1 = Data1 | 0b10000000;
                    break;

                default:
                    Reg_PC--;
                    Reg_PC--;
                    Reg_PC--;
                    Reg_PC--;
                    MemData[SwapPage] = 255;
                    FeedbackData("E", MessagePrefix, "Unknown instruction at " + Hex::IntToHex16(Reg_PC) + ": " + Hex::IntToHex8(OpCode0) + " " + Hex::IntToHex8(OpCode1) + " __ " + Hex::IntToHex8(OpCode2));
                    break;
            }
            MemSet(RegIdxD, Data1);
            break;

        default:
            Reg_PC--;
            Reg_PC--;
            MemData[SwapPage] = 255;
            FeedbackData("E", MessagePrefix, "Unknown instruction at " + Hex::IntToHex16(Reg_PC) + ": " + Hex::IntToHex8(OpCode0) + " " + Hex::IntToHex8(OpCode1));
            break;
    }

    // Writing IX/IY register
    if (OpCode0 == 0xDD)
    {
        Reg_IX = Reg_Idx;
    }
    else
    {
        Reg_IY = Reg_Idx;
    }
}

void ScriptEngineZ180::DoCommandExtED(uchar OpCode0)
{
    uchar OpCode1 = MemPrg(Reg_PC);
    uchar Data1;
    uchar Data2;
    uchar Data3;
    uchar Data4;
    int Data1I;
    int Data2I;
    Reg_PC++;
    switch (OpCode1)
    {
        // Multiplication - Z180
        case 0x4C: // MLT BC
            Data1I = Reg_B;
            Data2I = Reg_C;
            Data1I = Data1I * Data2I;
            Reg_B = Data1I >> 8;
            Reg_C = Data1I & 255;
            break;
        case 0x5C: // MLT DE
            Data1I = Reg_D;
            Data2I = Reg_E;
            Data1I = Data1I * Data2I;
            Reg_D = Data1I >> 8;
            Reg_E = Data1I & 255;
            break;
        case 0x6C: // MLT HL
            Data1I = Reg_H;
            Data2I = Reg_L;
            Data1I = Data1I * Data2I;
            Reg_H = Data1I >> 8;
            Reg_L = Data1I & 255;
            break;
        case 0x7C: // MLT SP
            Data1I = Reg_SP >> 8;
            Data2I = Reg_SP & 255;
            Data1I = Data1I * Data2I;
            Reg_SP = Data1I;
            break;

        // Checking conjunction parity - Z180
        case 0x04: // TST B
            DoTST(Reg_B);
            break;
        case 0x0C: // TST C
            DoTST(Reg_C);
            break;
        case 0x14: // TST D
            DoTST(Reg_D);
            break;
        case 0x1C: // TST E
            DoTST(Reg_E);
            break;
        case 0x24: // TST H
            DoTST(Reg_H);
            break;
        case 0x2C: // TST L
            DoTST(Reg_L);
            break;
        case 0x34: // TST (HL)
            DoTST(MemGet(Reg_H, Reg_L));
            break;
        case 0x3C: // TST A
            DoTST(Reg_A);
            break;
        case 0x64: // TST N
            DoTST(MemPrg(Reg_PC));
            Reg_PC++;
            break;

            /*
        case 0x00: // IN0 B, (n)
            DoIN(0, MemPrg(Reg_PC), Reg_B, true);
            Reg_PC++;
            break;
        case 0x08: // IN0 C, (n)
            DoIN(0, MemPrg(Reg_PC), Reg_C, true);
            Reg_PC++;
            break;
        case 0x10: // IN0 D, (n)
            DoIN(0, MemPrg(Reg_PC), Reg_D, true);
            Reg_PC++;
            break;
        case 0x18: // IN0 E, (n)
            DoIN(0, MemPrg(Reg_PC), Reg_E, true);
            Reg_PC++;
            break;
        case 0x20: // IN0 H, (n)
            DoIN(0, MemPrg(Reg_PC), Reg_H, true);
            Reg_PC++;
            break;
        case 0x28: // IN0 L, (n)
            DoIN(0, MemPrg(Reg_PC), Reg_L, true);
            Reg_PC++;
            break;
        case 0x30: // IN0 F, (n)
            DoIN(0, MemPrg(Reg_PC), Reg_F, true);
            Reg_PC++;
            break;
        case 0x38: // IN0 A, (n)
            DoIN(0, MemPrg(Reg_PC), Reg_A, true);
            Reg_PC++;
            break;

        case 0x01: // OUT0 (n), B
            DoOUT(0, MemPrg(Reg_PC), Reg_B);
            Reg_PC++;
            break;
        case 0x09: // OUT0 (n), C
            DoOUT(0, MemPrg(Reg_PC), Reg_C);
            break;
        case 0x11: // OUT0 (n), D
            DoOUT(0, MemPrg(Reg_PC), Reg_D);
            break;
        case 0x19: // OUT0 (n), E
            DoOUT(0, MemPrg(Reg_PC), Reg_E);
            break;
        case 0x21: // OUT0 (n), H
            DoOUT(0, MemPrg(Reg_PC), Reg_H);
            break;
        case 0x29: // OUT0 (n), L
            DoOUT(0, MemPrg(Reg_PC), Reg_L);
            break;
        case 0x39: // OUT0 (n), A
            DoOUT(0, MemPrg(Reg_PC), Reg_A);
            break;

        case 0x74: // TSTIO N
            {
                uchar TSTIO_;
                DoIN(Reg_B, Reg_C, TSTIO_, true);
                DoTST(MemPrg(Reg_PC), TSTIO_);
            }
            Reg_PC++;
            break;

        case 0x76: // SLP
            break;

        case 0x83: // OTIM
            break;
        case 0x8B: // OTDM
            break;
        case 0x93: // OTIMR
            break;
        case 0x9B: // OTDMR
            break;

        case 0xA2: // INI
            break;
        case 0xA3: // OTI
            break;
        case 0xAA: // IND
            break;
        case 0xAB: // OTD
            break;
        case 0xB2: // INIR
            break;
        case 0xB3: // OTIR
            break;
        case 0xBA: // INDR
            break;
        case 0xBB: // OTDR
            break;
            */

        // ########################################################

        // Receiving from external device
        case 0x40: // IN B, (C)
            DoIN(Reg_B, Reg_C, Reg_B, true);
            break;
        case 0x48: // IN C, (C)
            DoIN(Reg_B, Reg_C, Reg_C, true);
            break;
        case 0x50: // IN D, (C)
            DoIN(Reg_B, Reg_C, Reg_D, true);
            break;
        case 0x58: // IN E, (C)
            DoIN(Reg_B, Reg_C, Reg_E, true);
            break;
        case 0x60: // IN H, (C)
            DoIN(Reg_B, Reg_C, Reg_H, true);
            break;
        case 0x68: // IN L, (C)
            DoIN(Reg_B, Reg_C, Reg_L, true);
            break;
        case 0x78: // IN A, (C)
            DoIN(Reg_B, Reg_C, Reg_A, true);
            break;

        // Sending to external device
        case 0x41: // OUT (C), B
            DoOUT(Reg_B, Reg_C, Reg_B);
            break;
        case 0x49: // OUT (C), C
            DoOUT(Reg_B, Reg_C, Reg_C);
            break;
        case 0x51: // OUT (C), D
            DoOUT(Reg_B, Reg_C, Reg_D);
            break;
        case 0x59: // OUT (C), E
            DoOUT(Reg_B, Reg_C, Reg_E);
            break;
        case 0x61: // OUT (C), H
            DoOUT(Reg_B, Reg_C, Reg_H);
            break;
        case 0x69: // OUT (C), L
            DoOUT(Reg_B, Reg_C, Reg_L);
            break;
        case 0x79: // OUT (C), A
            DoOUT(Reg_B, Reg_C, Reg_A);
            break;

        // Interrupt modes
        case 0x46: // IM 0
            break;
        case 0x56: // IM 1
            break;
        case 0x5E: // IM 2
            break;

        // Return from interrupt call
        case 0x45: // RETN
            DoRETI();
            InterruptFinish();
            break;
        case 0x4D: // RETI
            DoRETI();
            InterruptFinish();
            break;

        // Copying 8-bit values
        case 0x47: // LD I, A
            Reg_I = Reg_A;
            break;
        case 0x4F: // LD R, A
            Reg_R = Reg_A;
            break;
        case 0x57: // LD A, I
            Reg_A = Reg_I;
            if (Reg_IFF2)
            {
                FlagPSet;
            }
            else
            {
                FlagPClr;
            }
            SetFlagsSZ(Reg_I);
            FlagHClr;
            FlagNClr;
            break;
        case 0x5F: // LD A, R
            Reg_A = Reg_R;
            if (Reg_IFF2)
            {
                FlagPSet;
            }
            else
            {
                FlagPClr;
            }
            SetFlagsSZ(Reg_R);
            FlagHClr;
            FlagNClr;
            break;

        // Copying 16-bit values
        case 0x43: // LD (NN), BC
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC),     Reg_C);
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1, Reg_B);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x53: // LD (NN), DE
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC),     Reg_E);
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1, Reg_D);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x63: // LD (NN), HL
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC),     Reg_L);
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1, Reg_H);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x73: // LD (NN), SP
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC),     Reg_SP & 255);
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1, Reg_SP >> 8);
            Reg_PC++;
            Reg_PC++;
            break;

        case 0x4B: // LD BC, (NN)
            Reg_C = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
            Reg_B = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x5B: // LD DE, (NN)
            Reg_E = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
            Reg_D = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x6B: // LD HL, (NN)
            Reg_L = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
            Reg_H = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x7B: // LD SP, (NN)
            Data1I = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
            Data2I = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1);
            Reg_SP = Data1I + (Data2I << 8);
            Reg_PC++;
            Reg_PC++;
            break;

        // Operations on accumulator
        case 0x44: // NEG
            Data1 = Reg_A;
            Reg_A = 0;
            DoSUB1(Data1, false);
            break;
        case 0x67: // RRD
            Data1 = (Reg_A & 0b11110000);
            Data2 = (Reg_A & 0b00001111);
            Data3 = (MemGet(Reg_H, Reg_L) & 0b11110000);
            Data4 = (MemGet(Reg_H, Reg_L) & 0b00001111);
            Reg_A = Data1 | Data4;
            MemSet(Reg_H, Reg_L, (Data2 << 4) | (Data3 >> 4));
            break;
        case 0x6F: // RLD
            Data1 = (Reg_A & 0b11110000);
            Data2 = (Reg_A & 0b00001111);
            Data3 = (MemGet(Reg_H, Reg_L) & 0b11110000);
            Data4 = (MemGet(Reg_H, Reg_L) & 0b00001111);
            Reg_A = Data1 | (Data3 >> 4);
            MemSet(Reg_H, Reg_L, (Data4 << 4) | Data2);
            break;

        // Adding on 16-bit values
        case 0x4A: // ADC HL, BC
            DoADD2_HL(Reg_B, Reg_C, true);
            break;
        case 0x5A: // ADC HL, DE
            DoADD2_HL(Reg_D, Reg_E, true);
            break;
        case 0x6A: // ADC HL, HL
            DoADD2_HL(Reg_H, Reg_L, true);
            break;
        case 0x7A: // ADC HL, SP
            DoADD2_HL(Reg_SP, true);
            break;

        // Subtracting on 16-bit values
        case 0x42: // SBC HL, BC
            DoSUB2(Reg_B, Reg_C, true);
            break;
        case 0x52: // SBC HL, DE
            DoSUB2(Reg_D, Reg_E, true);
            break;
        case 0x62: // SBC HL, HL
            DoSUB2(Reg_H, Reg_L, true);
            break;
        case 0x72: // SBC HL, SP
            DoSUB2(Reg_SP, true);
            break;

        // Block data loading
        case 0xA0: // LDI
            DoBlock_LD();
            Reg_E++;
            if (Reg_E == 0)
            {
                Reg_D++;
            }
            DoBlock2I();
            FlagHClr;
            if ((Reg_B) || (Reg_C)) { FlagPSet; } else { FlagPClr; }
            FlagNClr;
            break;
        case 0xA8: // LDD
            DoBlock_LD();
            Reg_E--;
            if (Reg_E == 255)
            {
                Reg_D--;
            }
            DoBlock2D();
            FlagHClr;
            if ((Reg_B) || (Reg_C)) { FlagPSet; } else { FlagPClr; }
            FlagNClr;
            break;
        case 0xB0: // LDIR
            DoBlock_LD();
            Reg_E++;
            if (Reg_E == 0)
            {
                Reg_D++;
            }
            DoBlock2IR(false);
            FlagHClr;
            FlagPClr;
            FlagNClr;
            break;
        case 0xB8: // LDDR
            DoBlock_LD();
            Reg_E--;
            if (Reg_E == 255)
            {
                Reg_D--;
            }
            DoBlock2DR(false);
            FlagHClr;
            FlagPClr;
            FlagNClr;
            break;

        // Block data comparison
        case 0xA1: // CPI
            DoBlock_CP();
            DoBlock2I();
            if ((Reg_B) || (Reg_C)) { FlagPSet; } else { FlagPClr; }
            FlagNSet;
            break;
        case 0xA9: // CPD
            DoBlock_CP();
            DoBlock2D();
            if ((Reg_B) || (Reg_C)) { FlagPSet; } else { FlagPClr; }
            FlagNSet;
            break;
        case 0xB1: // CPIR
            DoBlock_CP();
            DoBlock2IR(true);
            if ((Reg_B) || (Reg_C)) { FlagPSet; } else { FlagPClr; }
            FlagNSet;
            break;
        case 0xB9: // CPDR
            DoBlock_CP();
            DoBlock2DR(true);
            if ((Reg_B) || (Reg_C)) { FlagPSet; } else { FlagPClr; }
            FlagNSet;
            break;

        default:
            Reg_PC--;
            Reg_PC--;
            MemData[SwapPage] = 255;
            FeedbackData("E", MessagePrefix, "Unknown instruction at " + Hex::IntToHex16(Reg_PC) + ": " + Hex::IntToHex8(OpCode0) + " " + Hex::IntToHex8(OpCode1));
            break;
    }
}

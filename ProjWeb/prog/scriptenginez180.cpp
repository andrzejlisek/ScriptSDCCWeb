#include "scriptenginez180.h"

ScriptEngineZ180::ScriptEngineZ180()
{
    ScriptDecompile_ = new ScriptDecompileZ180();
}

ScriptEngineZ180::~ScriptEngineZ180()
{
    delete ScriptDecompile_;
}

void ScriptEngineZ180::DoCommand()
{
    if (InterruptIdle)
    {
        if (InterruptQueue.size() > 0)
        {
            int IntParam = InterruptStartMem();

            // Non-maskable interrupt
            if ((IntParam & 0x30000) == 0x10000)
            {
                InterruptIdle = false;

                // CALL 0x0066
                DoJumpAbs(0x0066, true);
            }

            // Maskable interrupt
            if ((IntParam & 0x30000) == 0x20000)
            {
                InterruptIdle = false;

                // RST 0x38
                DoJumpAbs(0x0038, true);
            }
        }
    }

    uchar OpCode0 = MemPrg(Reg_PC);;
    uchar Data1;
    uchar Data2;
    uchar Arg1;
    uchar Arg2;
    int Data1I;
    int Data2I;


    //cout << Hex::IntToHex16(Reg_PC) << ": " << Hex::IntToHex8(MemPrg(Reg_PC + 0)) << " " << Hex::IntToHex8(MemPrg(Reg_PC + 1)) << " " << Hex::IntToHex8(MemPrg(Reg_PC + 2)) << " " << Hex::IntToHex8(MemPrg(Reg_PC + 3));
    //cout << " " << Hex::IntToHex8(MemPrg(Reg_PC + 4)) << " " << Hex::IntToHex8(MemPrg(Reg_PC + 5)) << " " << Hex::IntToHex8(MemPrg(Reg_PC + 6)) << " " << Hex::IntToHex8(MemPrg(Reg_PC + 7)) << endl;


    Reg_PC++;
    switch (OpCode0)
    {

        // Additional instructions
        case 0x00: // NOP
            break;
        case 0x76: // HALT
            break;
        case 0x27: // DA A
            if ((Reg_A > 0x99) || FlagCGet)
            {
                Data1 = 0x60;
                FlagCSet;
            }
            else
            {
                Data1 = 0x00;
                FlagCClr;
            }
            if (((Reg_A & 0b00001111) > 0x09) || FlagHGet)
            {
                Data1 += 0x06;
            }
            if (FlagNGet)
            {
                Data2 = Reg_A - Data1;
            }
            else
            {
                Data2 = Reg_A + Data1;
            }
            if ((Reg_A & 0b00010000) == (Data2 & 0b00010000))
            {
                FlagHClr;
            }
            else
            {
                FlagHSet;
            }
            Reg_A = Data2;
            SetFlagsSZ(Reg_A);
            SetFlagsP(Reg_A);
            break;

        // Swapping primary and secondary registers
        case 0x08: // EX AF, AF'
            Data1 = Reg_A; Reg_A = Reg_A_; Reg_A_ = Data1;
#ifdef FlagsAsReg
            Data1 = Reg_F; Reg_F = Reg_F_; Reg_F_ = Data1;
#else
            Data1 = Reg_F0; Reg_F0 = Reg_F0_; Reg_F0_ = Data1;
            Data1 = Reg_F1; Reg_F1 = Reg_F1_; Reg_F1_ = Data1;
            Data1 = Reg_F2; Reg_F2 = Reg_F2_; Reg_F2_ = Data1;
            Data1 = Reg_F4; Reg_F4 = Reg_F4_; Reg_F4_ = Data1;
            Data1 = Reg_F6; Reg_F6 = Reg_F6_; Reg_F6_ = Data1;
            Data1 = Reg_F7; Reg_F7 = Reg_F7_; Reg_F7_ = Data1;
#endif
            break;
        case 0xD9: // EXX
            Data1 = Reg_B; Reg_B = Reg_B_; Reg_B_ = Data1;
            Data1 = Reg_C; Reg_C = Reg_C_; Reg_C_ = Data1;
            Data1 = Reg_D; Reg_D = Reg_D_; Reg_D_ = Data1;
            Data1 = Reg_E; Reg_E = Reg_E_; Reg_E_ = Data1;
            Data1 = Reg_H; Reg_H = Reg_H_; Reg_H_ = Data1;
            Data1 = Reg_L; Reg_L = Reg_L_; Reg_L_ = Data1;
            break;
        case 0xE3: // EX (SP), HL
            Reg_SP++;
            Data1 = MemGet(Reg_SP); MemSet(Reg_SP, Reg_H); Reg_H = Data1;
            Reg_SP--;
            Data1 = MemGet(Reg_SP); MemSet(Reg_SP, Reg_L); Reg_L = Data1;
            break;
        case 0xEB: // EX DE, HL
            Data1 = Reg_D; Reg_D = Reg_H; Reg_H = Data1;
            Data1 = Reg_E; Reg_E = Reg_L; Reg_L = Data1;
            break;

        // Enabling and disabling interrupts
        case 0xF3: // DI
            break;
        case 0xFB: // EI
            break;

        // Writing constant value
        case 0x01: // LD BC, NN
            Reg_C = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_B = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x11: // LD DE, NN
            Reg_E = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_D = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x21: // LD HL, NN
            Reg_L = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_H = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x31: // LD SP, NN
            Data1I = MemPrg(Reg_PC);
            Reg_PC++;
            Data2I = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_SP = (Data2I << 8) + Data1I;
            break;
        case 0x22: // LD (NN), HL
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC), Reg_L);
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1, Reg_H);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x02: // LD (BC), A
            MemSet(Reg_B, Reg_C, Reg_A);
            break;
        case 0x12: // LD (DE), A
            MemSet(Reg_D, Reg_E, Reg_A);
            break;
        case 0x32: // LD (NN), A
            MemSet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC), Reg_A);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x3A: // LD A, (NN)
            Reg_A = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x36: // LD (HL), N
            MemSet(Reg_H, Reg_L, MemPrg(Reg_PC));
            Reg_PC++;
            break;
        case 0x0A: // LD A, (BC)
            Reg_A = MemGet(Reg_B, Reg_C);
            break;
        case 0x1A: // LD A, (DE)
            Reg_A = MemGet(Reg_D, Reg_E);
            break;
        case 0x06: // LD B, N
            Reg_B = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x0E: // LD C, N
            Reg_C = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x16: // LD D, N
            Reg_D = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x1E: // LD E, N
            Reg_E = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x26: // LD H, N
            Reg_H = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x2A: // LD HL, (NN)
            Reg_L = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
            Reg_H = MemGet(MemPrg(Reg_PC + 1), MemPrg(Reg_PC) + 1);
            Reg_PC++;
            Reg_PC++;
            break;
        case 0x2E: // LD L, N
            Reg_L = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0x3E: // LD A, N
            Reg_A = MemPrg(Reg_PC);
            Reg_PC++;
            break;
        case 0xF9: // LD SP, HL
            Reg_SP = ((ushort)Reg_H << 8) + (ushort)Reg_L;
            break;

        // Bit shifting and rotating
        case 0x07: // RLC A
            DoRLC(Reg_A, false);
            break;
        case 0x0F: // RRC A
            DoRRC(Reg_A, false);
            break;
        case 0x17: // RL A
            DoRL(Reg_A, false);
            break;
        case 0x1F: // RR A
            DoRR(Reg_A, false);
            break;

        // Value incrementation and decrementation
        case 0x03: // INC BC
            Reg_C++;
            if (Reg_C == 0)
            {
                Reg_B++;
            }
            break;
        case 0x13: // INC DE
            Reg_E++;
            if (Reg_E == 0)
            {
                Reg_D++;
            }
            break;
        case 0x23: // INC HL
            Reg_L++;
            if (Reg_L == 0)
            {
                Reg_H++;
            }
            break;
        case 0x33: // INC SP
            Reg_SP++;
            break;
        case 0x0B: // DEC BC
            Reg_C--;
            if (Reg_C == 255)
            {
                Reg_B--;
            }
            break;
        case 0x1B: // DEC DE
            Reg_E--;
            if (Reg_E == 255)
            {
                Reg_D--;
            }
            break;
        case 0x2B: // DEC HL
            Reg_L--;
            if (Reg_L == 255)
            {
                Reg_H--;
            }
            break;
        case 0x3B: // DEC SP
            Reg_SP--;
            break;
        case 0x04: // INC B
            DoINC(Reg_B);
            break;
        case 0x05: // DEC B
            DoDEC(Reg_B);
            break;
        case 0x0C: // INC C
            DoINC(Reg_C);
            break;
        case 0x0D: // DEC C
            DoDEC(Reg_C);
            break;
        case 0x14: // INC D
            DoINC(Reg_D);
            break;
        case 0x15: // DEC D
            DoDEC(Reg_D);
            break;
        case 0x1C: // INC E
            DoINC(Reg_E);
            break;
        case 0x1D: // DEC E
            DoDEC(Reg_E);
            break;
        case 0x24: // INC H
            DoINC(Reg_H);
            break;
        case 0x25: // DEC H
            DoDEC(Reg_H);
            break;
        case 0x2C: // INC L
            DoINC(Reg_L);
            break;
        case 0x2D: // DEC L
            DoDEC(Reg_L);
            break;
        case 0x34: // INC (HL)
            Data1 = MemGet(Reg_H, Reg_L);
            DoINC(Data1);
            MemSet(Reg_H, Reg_L, Data1);
            break;
        case 0x35: // DEC (HL)
            Data1 = MemGet(Reg_H, Reg_L);
            DoDEC(Data1);
            MemSet(Reg_H, Reg_L, Data1);
            break;
        case 0x3C: // INC A
            DoINC(Reg_A);
            break;
        case 0x3D: // DEC A
            DoDEC(Reg_A);
            break;

        // Adding and subtracting
        case 0x09: // ADD HL, BC
            DoADD2_HL(Reg_B, Reg_C, false);
            break;
        case 0x19: // ADD HL, DE
            DoADD2_HL(Reg_D, Reg_E, false);
            break;
        case 0x29: // ADD HL, HL
            DoADD2_HL(Reg_H, Reg_L, false);
            break;
        case 0x39: // ADD HL, SP
            DoADD2_HL(Reg_SP, false);
            break;
        case 0xC6: // ADD A, N
            DoADD1(MemPrg(Reg_PC), false);
            Reg_PC++;
            break;
        case 0xCE: // ADC A, N
            DoADD1(MemPrg(Reg_PC), true);
            Reg_PC++;
            break;
        case 0xD6: // SUB N
            DoSUB1(MemPrg(Reg_PC), false);
            Reg_PC++;
            break;
        case 0xDE: // SBC A, N
            DoSUB1(MemPrg(Reg_PC), true);
            Reg_PC++;
            break;

        // Logical operations
        case 0x2F: // CPL
            Reg_A = ~Reg_A;
            FlagHSet;
            FlagNSet;
            break;
        case 0x37: // SCF
            FlagCSet;
            FlagHClr;
            FlagNClr;
            break;
        case 0x3F: // CCF
            if (FlagCGet)
            {
                FlagHSet;
                FlagCClr;
            }
            else
            {
                FlagHClr;
                FlagCSet;
            }
            FlagNClr;
            break;
        case 0xE6: // AND N
            DoAND(MemPrg(Reg_PC));
            Reg_PC++;
            break;
        case 0xEE: // XOR N
            DoXOR(MemPrg(Reg_PC));
            Reg_PC++;
            break;
        case 0xF6: // OR N
            DoOR(MemPrg(Reg_PC));
            Reg_PC++;
            break;
        case 0xFE: // CP N
            DoCP(MemPrg(Reg_PC));
            Reg_PC++;
            break;

        // Jumps
        case 0x10: // DJNZ N
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Reg_B--;
            if (Reg_B != 0)
            {
                DoJumpRel(Arg1, false);
            }
            break;
        case 0x18: // JR N
            DoJR(true);
            break;
        case 0x20: // JR NZ, N
            DoJR(!FlagZGet);
            break;
        case 0x28: // JR Z, N
            DoJR(FlagZGet);
            break;
        case 0x30: // JR NC, N
            DoJR(!FlagCGet);
            break;
        case 0x38: // JR C, N
            DoJR(FlagCGet);
            break;
        case 0xC3: // JP NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            DoJumpAbs(Arg2, Arg1, false);
            break;
        case 0xE9: // JP (HL)
            ScriptDecompile_->JumpVectorAddr(Reg_PC - 1, (((int)Reg_H) << 8) + ((int)Reg_L));
            DoJumpAbs(Reg_H, Reg_L, false);
            break;
        case 0xC2: // JP NZ, NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            if (!FlagZGet)
            {
                DoJumpAbs(Arg2, Arg1, false);
            }
            break;
        case 0xCA: // JP Z, NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            if (FlagZGet)
            {
                DoJumpAbs(Arg2, Arg1, false);
            }
            break;
        case 0xD2: // JP NC, NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            if (!FlagCGet)
            {
                DoJumpAbs(Arg2, Arg1, false);
            }
            break;
        case 0xDA: // JP C, NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            if (FlagCGet)
            {
                DoJumpAbs(Arg2, Arg1, false);
            }
            break;
        case 0xE2: // JP PO, NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            if (!FlagPGet)
            {
                DoJumpAbs(Arg2, Arg1, false);
            }
            break;
        case 0xEA: // JP PE, NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            if (FlagPGet)
            {
                DoJumpAbs(Arg2, Arg1, false);
            }
            break;
        case 0xF2: // JP P, NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            if (!FlagSGet)
            {
                DoJumpAbs(Arg2, Arg1, false);
            }
            break;
        case 0xFA: // JP M, NN
            Arg1 = MemPrg(Reg_PC);
            Reg_PC++;
            Arg2 = MemPrg(Reg_PC);
            Reg_PC++;
            if (FlagSGet)
            {
                DoJumpAbs(Arg2, Arg1, false);
            }
            break;

        // Instructions on standard registers - copying value
        case 0x40: // LD B, B
            //Reg_B = Reg_B;
            break;
        case 0x41: // LD B, C
            Reg_B = Reg_C;
            break;
        case 0x42: // LD B, D
            Reg_B = Reg_D;
            break;
        case 0x43: // LD B, E
            Reg_B = Reg_E;
            break;
        case 0x44: // LD B, H
            Reg_B = Reg_H;
            break;
        case 0x45: // LD B, L
            Reg_B = Reg_L;
            break;
        case 0x46: // LD B, (HL)
            Reg_B = MemGet(Reg_H, Reg_L);
            break;
        case 0x47: // LD B, A
            Reg_B = Reg_A;
            break;
        case 0x48: // LD C, B
            Reg_C = Reg_B;
            break;
        case 0x49: // LD C, C
            //Reg_C = Reg_C;
            break;
        case 0x4A: // LD C, D
            Reg_C = Reg_D;
            break;
        case 0x4B: // LD C, E
            Reg_C = Reg_E;
            break;
        case 0x4C: // LD C, H
            Reg_C = Reg_H;
            break;
        case 0x4D: // LD C, L
            Reg_C = Reg_L;
            break;
        case 0x4E: // LD C, (HL)
            Reg_C = MemGet(Reg_H, Reg_L);
            break;
        case 0x4F: // LD C, A
            Reg_C = Reg_A;
            break;
        case 0x50: // LD D, B
            Reg_D = Reg_B;
            break;
        case 0x51: // LD D, C
            Reg_D = Reg_C;
            break;
        case 0x52: // LD D, D
            //Reg_D = Reg_D;
            break;
        case 0x53: // LD D, E
            Reg_D = Reg_E;
            break;
        case 0x54: // LD D, H
            Reg_D = Reg_H;
            break;
        case 0x55: // LD D, L
            Reg_D = Reg_L;
            break;
        case 0x56: // LD D, (HL)
            Reg_D = MemGet(Reg_H, Reg_L);
            break;
        case 0x57: // LD D, A
            Reg_D = Reg_A;
            break;
        case 0x58: // LD E, B
            Reg_E = Reg_B;
            break;
        case 0x59: // LD E, C
            Reg_E = Reg_C;
            break;
        case 0x5A: // LD E, D
            Reg_E = Reg_D;
            break;
        case 0x5B: // LD E, E
            //Reg_E = Reg_E;
            break;
        case 0x5C: // LD E, H
            Reg_E = Reg_H;
            break;
        case 0x5D: // LD E, L
            Reg_E = Reg_L;
            break;
        case 0x5E: // LD E, (HL)
            Reg_E = MemGet(Reg_H, Reg_L);
            break;
        case 0x5F: // LD E, A
            Reg_E = Reg_A;
            break;
        case 0x60: // LD H, B
            Reg_H = Reg_B;
            break;
        case 0x61: // LD H, C
            Reg_H = Reg_C;
            break;
        case 0x62: // LD H, D
            Reg_H = Reg_D;
            break;
        case 0x63: // LD H, E
            Reg_H = Reg_E;
            break;
        case 0x64: // LD H, H
            //Reg_H = Reg_H;
            break;
        case 0x65: // LD H, L
            Reg_H = Reg_L;
            break;
        case 0x66: // LD H, (HL)
            Reg_H = MemGet(Reg_H, Reg_L);
            break;
        case 0x67: // LD H, A
            Reg_H = Reg_A;
            break;
        case 0x68: // LD L, B
            Reg_L = Reg_B;
            break;
        case 0x69: // LD L, C
            Reg_L = Reg_C;
            break;
        case 0x6A: // LD L, D
            Reg_L = Reg_D;
            break;
        case 0x6B: // LD L, E
            Reg_L = Reg_E;
            break;
        case 0x6C: // LD L, H
            Reg_L = Reg_H;
            break;
        case 0x6D: // LD L, L
            //Reg_L = Reg_L;
            break;
        case 0x6E: // LD L, (HL)
            Reg_L = MemGet(Reg_H, Reg_L);
            break;
        case 0x6F: // LD L, A
            Reg_L = Reg_A;
            break;
        case 0x70: // LD (HL), B
            MemSet(Reg_H, Reg_L, Reg_B);
            break;
        case 0x71: // LD (HL), C
            MemSet(Reg_H, Reg_L, Reg_C);
            break;
        case 0x72: // LD (HL), D
            MemSet(Reg_H, Reg_L, Reg_D);
            break;
        case 0x73: // LD (HL), E
            MemSet(Reg_H, Reg_L, Reg_E);
            break;
        case 0x74: // LD (HL), H
            MemSet(Reg_H, Reg_L, Reg_H);
            break;
        case 0x75: // LD (HL), L
            MemSet(Reg_H, Reg_L, Reg_L);
            break;
        case 0x77: // LD (HL), A
            MemSet(Reg_H, Reg_L, Reg_A);
            break;
        case 0x78: // LD A, B
            Reg_A = Reg_B;
            break;
        case 0x79: // LD A, C
            Reg_A = Reg_C;
            break;
        case 0x7A: // LD A, D
            Reg_A = Reg_D;
            break;
        case 0x7B: // LD A, E
            Reg_A = Reg_E;
            break;
        case 0x7C: // LD A, H
            Reg_A = Reg_H;
            break;
        case 0x7D: // LD A, L
            Reg_A = Reg_L;
            break;
        case 0x7E: // LD A, (HL)
            Reg_A = MemGet(Reg_H, Reg_L);
            break;
        case 0x7F: // LD A, A
            //Reg_A = Reg_A;
            break;

        // Instructions on standard registers - mathematical and logical operations
        case 0x80: // ADD A, B
            DoADD1(Reg_B, false);
            break;
        case 0x81: // ADD A, C
            DoADD1(Reg_C, false);
            break;
        case 0x82: // ADD A, D
            DoADD1(Reg_D, false);
            break;
        case 0x83: // ADD A, E
            DoADD1(Reg_E, false);
            break;
        case 0x84: // ADD A, H
            DoADD1(Reg_H, false);
            break;
        case 0x85: // ADD A, L
            DoADD1(Reg_L, false);
            break;
        case 0x86: // ADD A, (HL)
            DoADD1(MemGet(Reg_H, Reg_L), false);
            break;
        case 0x87: // ADD A, A
            DoADD1(Reg_A, false);
            break;
        case 0x88: // ADC A, B
            DoADD1(Reg_B, true);
            break;
        case 0x89: // ADC A, C
            DoADD1(Reg_C, true);
            break;
        case 0x8A: // ADC A, D
            DoADD1(Reg_D, true);
            break;
        case 0x8B: // ADC A, E
            DoADD1(Reg_E, true);
            break;
        case 0x8C: // ADC A, H
            DoADD1(Reg_H, true);
            break;
        case 0x8D: // ADC A, L
            DoADD1(Reg_L, true);
            break;
        case 0x8E: // ADC A, (HL)
            DoADD1(MemGet(Reg_H, Reg_L), true);
            break;
        case 0x8F: // ADC A, A
            DoADD1(Reg_A, true);
            break;
        case 0x90: // SUB B
            DoSUB1(Reg_B, false);
            break;
        case 0x91: // SUB C
            DoSUB1(Reg_C, false);
            break;
        case 0x92: // SUB D
            DoSUB1(Reg_D, false);
            break;
        case 0x93: // SUB E
            DoSUB1(Reg_E, false);
            break;
        case 0x94: // SUB H
            DoSUB1(Reg_H, false);
            break;
        case 0x95: // SUB L
            DoSUB1(Reg_L, false);
            break;
        case 0x96: // SUB (HL)
            DoSUB1(MemGet(Reg_H, Reg_L), false);
            break;
        case 0x97: // SUB A
            DoSUB1(Reg_A, false);
            break;
        case 0x98: // SBC A, B
            DoSUB1(Reg_B, true);
            break;
        case 0x99: // SBC A, C
            DoSUB1(Reg_C, true);
            break;
        case 0x9A: // SBC A, D
            DoSUB1(Reg_D, true);
            break;
        case 0x9B: // SBC A, E
            DoSUB1(Reg_E, true);
            break;
        case 0x9C: // SBC A, H
            DoSUB1(Reg_H, true);
            break;
        case 0x9D: // SBC A, L
            DoSUB1(Reg_L, true);
            break;
        case 0x9E: // SBC A, (HL)
            DoSUB1(MemGet(Reg_H, Reg_L), true);
            break;
        case 0x9F: // SBC A, A
            DoSUB1(Reg_A, true);
            break;
        case 0xA0: // AND B
            DoAND(Reg_B);
            break;
        case 0xA1: // AND C
            DoAND(Reg_C);
            break;
        case 0xA2: // AND D
            DoAND(Reg_D);
            break;
        case 0xA3: // AND E
            DoAND(Reg_E);
            break;
        case 0xA4: // AND H
            DoAND(Reg_H);
            break;
        case 0xA5: // AND L
            DoAND(Reg_L);
            break;
        case 0xA6: // AND (HL)
            DoAND(MemGet(Reg_H, Reg_L));
            break;
        case 0xA7: // AND A
            DoAND(Reg_A);
            break;
        case 0xA8: // XOR B
            DoXOR(Reg_B);
            break;
        case 0xA9: // XOR C
            DoXOR(Reg_C);
            break;
        case 0xAA: // XOR D
            DoXOR(Reg_D);
            break;
        case 0xAB: // XOR E
            DoXOR(Reg_E);
            break;
        case 0xAC: // XOR H
            DoXOR(Reg_H);
            break;
        case 0xAD: // XOR L
            DoXOR(Reg_L);
            break;
        case 0xAE: // XOR (HL)
            DoXOR(MemGet(Reg_H, Reg_L));
            break;
        case 0xAF: // XOR A
            DoXOR(Reg_A);
            break;
        case 0xB0: // OR B
            DoOR(Reg_B);
            break;
        case 0xB1: // OR C
            DoOR(Reg_C);
            break;
        case 0xB2: // OR D
            DoOR(Reg_D);
            break;
        case 0xB3: // OR E
            DoOR(Reg_E);
            break;
        case 0xB4: // OR H
            DoOR(Reg_H);
            break;
        case 0xB5: // OR L
            DoOR(Reg_L);
            break;
        case 0xB6: // OR (HL)
            DoOR(MemGet(Reg_H, Reg_L));
            break;
        case 0xB7: // OR A
            DoOR(Reg_A);
            break;
        case 0xB8: // CP B
            DoCP(Reg_B);
            break;
        case 0xB9: // CP C
            DoCP(Reg_C);
            break;
        case 0xBA: // CP D
            DoCP(Reg_D);
            break;
        case 0xBB: // CP E
            DoCP(Reg_E);
            break;
        case 0xBC: // CP H
            DoCP(Reg_H);
            break;
        case 0xBD: // CP L
            DoCP(Reg_L);
            break;
        case 0xBE: // CP (HL)
            DoCP(MemGet(Reg_H, Reg_L));
            break;
        case 0xBF: // CP A
            DoCP(Reg_A);
            break;


        // Stack instructions
        case 0xC1: // POP BC
            DoPOP(Reg_B, Reg_C);
            break;
        case 0xC5: // PUSH BC
            DoPUSH(Reg_B, Reg_C);
            break;
        case 0xD1: // POP DE
            DoPOP(Reg_D, Reg_E);
            break;
        case 0xD5: // PUSH DE
            DoPUSH(Reg_D, Reg_E);
            break;
        case 0xE1: // POP HL
            DoPOP(Reg_H, Reg_L);
            break;
        case 0xE5: // PUSH HL
            DoPUSH(Reg_H, Reg_L);
            break;
        case 0xF1: // POP AF
#ifdef FlagsAsReg
            DoPOP(Reg_A, Reg_F);
#else
            {
                uchar __Reg_F;
                DoPOP(Reg_A, __Reg_F);
                Reg_F_Set(__Reg_F);
            }
#endif
            break;
        case 0xF5: // PUSH AF
#ifdef FlagsAsReg
            DoPUSH(Reg_A, Reg_F);
#else
            {
                uchar __Reg_F = Reg_F_Get;
                DoPUSH(Reg_A, __Reg_F);
            }
#endif
            break;

        // Two-bytes calls
        case 0xCD: // CALL NN
            DoCALL(true);
            break;
        case 0xC4: // CALL NZ NN
            DoCALL(!FlagZGet);
            break;
        case 0xCC: // CALL Z, NN
            DoCALL(FlagZGet);
            break;
        case 0xD4: // CALL NC, NN
            DoCALL(!FlagCGet);
            break;
        case 0xDC: // CALL C, NN
            DoCALL(FlagCGet);
            break;
        case 0xE4: // CALL PO, NN
            DoCALL(!FlagPGet);
            break;
        case 0xEC: // CALL PE, NN
            DoCALL(FlagPGet);
            break;
        case 0xF4: // CALL P, NN
            DoCALL(!FlagSGet);
            break;
        case 0xFC: // CALL M, NN
            DoCALL(FlagSGet);
            break;

        // One-byte calls
        case 0xC7: // RST 00
            DoRST(0x00);
            break;
        case 0xCF: // RST 08
            DoRST(0x08);
            break;
        case 0xD7: // RST 10
            DoRST(0x10);
            break;
        case 0xDF: // RST 18
            DoRST(0x18);
            break;
        case 0xE7: // RST 20
            DoRST(0x20);
            break;
        case 0xEF: // RST 28
            DoRST(0x28);
            break;
        case 0xF7: // RST 30
            DoRST(0x30);
            break;
        case 0xFF: // RST 38
            DoRST(0x38);
            break;

        // Returns from call
        case 0xC9: // RET
            DoRETI();
            break;
        case 0xC0: // RET NZ
            DoRET(!FlagZGet);
            break;
        case 0xC8: // RET Z
            DoRET(FlagZGet);
            break;
        case 0xD0: // RET NC
            DoRET(!FlagCGet);
            break;
        case 0xD8: // RET C
            DoRET(FlagCGet);
            break;
        case 0xE0: // RET PO
            DoRET(!FlagPGet);
            break;
        case 0xE8: // RET PE
            DoRET(FlagPGet);
            break;
        case 0xF0: // RET P
            DoRET(!FlagSGet);
            break;
        case 0xF8: // RET M
            DoRET(FlagSGet);
            break;

        // Input and output
        case 0xD3: // OUT (N), A
            DoOUT(Reg_A, MemGet(Reg_PC), Reg_A);
            Reg_PC++;
            break;
        case 0xDB: // IN A, (N)
            DoIN(Reg_A, MemGet(Reg_PC), Reg_A, false);
            Reg_PC++;
            break;


        case 0xCB: // CB instruction serie - instructions on single register byte pointed by HL
            DoCommandExtCB(OpCode0);
            break;
        case 0xDD: // DD instruction serie - instructions using IX register
        case 0xFD: // FD instruction serie - instructions using IY register
            DoCommandExt_D(OpCode0);
            break;
        case 0xED: // ED instructions
            DoCommandExtED(OpCode0);
            break;

        default:
            Reg_PC--;
            MemData[SwapPage] = 255;
            FeedbackData("E", MessagePrefix, "Unknown instruction at " + Hex::IntToHex16(Reg_PC) + ": " + Hex::IntToHex8(OpCode0));
    }

    //if ((Reg_PC >= (0x1565)) && (Reg_PC <= (0x159B)))
    /*{
        cout << "PO:    A=" << Hex::IntToHex8(Reg_A) << " B=" << Hex::IntToHex8(Reg_B) << " C=" << Hex::IntToHex8(Reg_C) << " D=" << Hex::IntToHex8(Reg_D) << " E=" << Hex::IntToHex8(Reg_E);
        cout << "   IX=" << Hex::IntToHex16(Reg_IX) << " IY=" << Hex::IntToHex16(Reg_IY) ;
        cout << "   SP=" << Hex::IntToHex16(Reg_SP) << " H=" << Hex::IntToHex8(Reg_H) << " L=" << Hex::IntToHex8(Reg_L) << endl;
    }*/

}

void ScriptEngineZ180::DoReset()
{
    Reg_PC = 0;

    Reg_IFF1 = false;
    Reg_IFF2 = false;

    Reg_I = 0;

    Reg_A = 0;
    Reg_A_ = 0;
    Reg_F = 0;
    Reg_F0 = 0;
    Reg_F1 = 0;
    Reg_F2 = 0;
    Reg_F4 = 0;
    Reg_F6 = 0;
    Reg_F7 = 0;
    Reg_F_ = 0;
    Reg_F0_ = 0;
    Reg_F1_ = 0;
    Reg_F2_ = 0;
    Reg_F4_ = 0;
    Reg_F6_ = 0;
    Reg_F7_ = 0;

    Reg_B = 0;
    Reg_B_ = 0;
    Reg_C = 0;
    Reg_C_ = 0;
    Reg_D = 0;
    Reg_D_ = 0;
    Reg_E = 0;
    Reg_E_ = 0;
    Reg_H = 0;
    Reg_H_ = 0;
    Reg_L = 0;
    Reg_L_ = 0;

    Reg_IX = 0;
    Reg_IY = 0;
    Reg_SP = 0;

    Reg_R = 0;
}


std::string ScriptEngineZ180::GetEntryPoints()
{
    return "X0000X0066X0038X";
}

void ScriptEngineZ180::DoCALL(bool Condition)
{
    ushort AddrLo = MemPrg(Reg_PC);
    Reg_PC++;
    ushort AddrHi = MemPrg(Reg_PC);
    Reg_PC++;
    if (Condition)
    {
        DoJumpAbs((AddrHi << 8) + AddrLo, true);
    }
}

void ScriptEngineZ180::DoPUSH(uchar &ValH, uchar &ValL)
{
    Reg_SP--;
    MemSet(Reg_SP, ValH);
    Reg_SP--;
    MemSet(Reg_SP, ValL);
}

void ScriptEngineZ180::DoPOP(uchar &ValH, uchar &ValL)
{
    ValL = MemGet(Reg_SP);
    Reg_SP++;
    ValH = MemGet(Reg_SP);
    Reg_SP++;
}

void ScriptEngineZ180::DoRET(bool Condition)
{
    if (Condition)
    {
        uchar PCH;
        uchar PCL;
        DoPOP(PCH, PCL);
        Reg_PC = (((ushort)PCH) << 8) + ((ushort)PCL);
    }
}

void ScriptEngineZ180::DoRETI()
{
    uchar PCH;
    uchar PCL;
    DoPOP(PCH, PCL);
    Reg_PC = (((ushort)PCH) << 8) + ((ushort)PCL);
}

void ScriptEngineZ180::DoRST(int Addr)
{
    DoJumpAbs(Addr, true);
}

void ScriptEngineZ180::DoJR(bool Condition)
{
    uchar TempData = MemPrg(Reg_PC);
    Reg_PC++;
    if (Condition)
    {
        DoJumpRel(TempData, false);
    }
}

void ScriptEngineZ180::DoADD1(uchar Val, bool Carry)
{
    int C = Carry ? (FlagCGet ? 1 : 0) : 0;
    int A = Reg_A;
    int Res = A + Val + C;
    int ResX = ((int)((char)Reg_A)) + ((int)((char)Val)) + C;

    if ((ResX > 127) || (ResX < -128))
    {
        FlagPSet;
    }
    else
    {
        FlagPClr;
    }

    if (((A & 15) + (Val & 15) + C) > 15)
    {
        FlagHSet;
    }
    else
    {
        FlagHClr;
    }
    if (Res > 255)
    {
        FlagCSet;
        Res = Res - 256;
    }
    else
    {
        FlagCClr;
    }

    Reg_A = Res & 255;
    SetFlagsSZ(Reg_A);
    FlagNClr;
}

void ScriptEngineZ180::DoADD2_HL(int Val, bool Carry)
{
    int C = Carry ? (FlagCGet ? 1 : 0) : 0;

    int A = Reg_H;
    A = A << 8;
    A = A + Reg_L;

    int Res = A + Val + C;
    int ResX = ((int)((short)A)) + ((int)((short)Val)) + C;

    if ((ResX > 32767) || (ResX < -32768))
    {
        FlagPSet;
    }
    else
    {
        FlagPClr;
    }

    if (((A & 4095) + (Val & 4095) + C) > 4095)
    {
        FlagHSet;
    }
    else
    {
        FlagHClr;
    }
    if (Res > 65535)
    {
        FlagCSet;
        Res = Res - 65536;
    }
    else
    {
        FlagCClr;
    }

    A = Res & 65535;
    Reg_L = A & 255;
    A = A >> 8;
    Reg_H = A & 255;
    if (Carry)
    {
        SetFlagsSZ_(Reg_H, Reg_L);
    }
    FlagNClr;
}

void ScriptEngineZ180::DoADD2_HL(int ValH, int ValL, bool Carry)
{
    DoADD2_HL((ValH << 8) + ValL, Carry);
}

void ScriptEngineZ180::DoADD2_I_(int Val)
{
    int A = Reg_Idx;

    int Res = A + Val;

    if (((A & 4095) + (Val & 4095)) > 4095)
    {
        FlagHSet;
    }
    else
    {
        FlagHClr;
    }
    if (Res > 65535)
    {
        FlagCSet;
        Res = Res - 65536;
    }
    else
    {
        FlagCClr;
    }

    A = Res & 65535;
    Reg_Idx = A;
    FlagNClr;
}

void ScriptEngineZ180::DoADD2_I_(int ValH, int ValL)
{
    DoADD2_I_((ValH << 8) + ValL);
}

void ScriptEngineZ180::DoSUB1(uchar Val, bool Carry)
{
    int C = Carry ? (FlagCGet ? 1 : 0) : 0;
    int A = Reg_A;

    int Res = A - (Val + C);
    int ResX = ((int)((char)Reg_A)) - ((int)((char)Val)) - C;

    if ((ResX > 127) || (ResX < -128))
    {
        FlagPSet;
    }
    else
    {
        FlagPClr;
    }

    if (Res < 0)
    {
        FlagCSet;
        Res = Res + 256;
    }
    else
    {
        FlagCClr;
    }
    if (((Val + 1) & 15) > (A & 15))
    {
        FlagHSet;
    }
    else
    {
        FlagHClr;
    }

    Reg_A = Res & 255;
    SetFlagsSZ(Reg_A);
    FlagNSet;
}

void ScriptEngineZ180::DoSUB2(int Val, bool Carry)
{
    int C = Carry ? (FlagCGet ? 1 : 0) : 0;

    int A = Reg_H;
    A = A << 8;
    A = A + Reg_L;

    int Res = A - (Val + C);
    int ResX = ((int)((short)A)) - ((int)((short)Val)) - C;

    if ((ResX > 32767) || (ResX < -32768))
    {
        FlagPSet;
    }
    else
    {
        FlagPClr;
    }

    if (Res < 0)
    {
        FlagCSet;
        Res = Res + 65536;
    }
    else
    {
        FlagCClr;
    }
    if (((Val + 1) & 4095) > (A & 4095))
    {
        FlagHSet;
    }
    else
    {
        FlagHClr;
    }

    A = Res & 65535;
    Reg_L = A & 255;
    A = A >> 8;
    Reg_H = A & 255;
    SetFlagsSZ_(Reg_H, Reg_L);
    FlagNSet;
}

void ScriptEngineZ180::DoSUB2(int ValH, int ValL, bool Carry)
{
    DoSUB2((ValH << 8) + ValL, Carry);
}

void ScriptEngineZ180::DoCP(uchar Val)
{
    uchar TempA = Reg_A;
    DoSUB1(Val, false);
    Reg_A = TempA;
}

void ScriptEngineZ180::DoTST(uchar Val)
{
    uchar TempA = Reg_A & Val;
    SetFlagsSZ(TempA);
    SetFlagsP(TempA);
    FlagHSet;
    FlagNClr;
    FlagCClr;
}

void ScriptEngineZ180::DoTST(uchar Val0, uchar Val)
{
    uchar TempA = Val0 & Val;
    SetFlagsSZ(TempA);
    SetFlagsP(TempA);
    FlagHSet;
    FlagNClr;
    FlagCClr;
}

void ScriptEngineZ180::DoAND(uchar Val)
{
    Reg_A = Reg_A & Val;
    SetFlagsSZ(Reg_A);
    SetFlagsP(Reg_A);
    FlagHSet;
    FlagNClr;
    FlagCClr;
}

void ScriptEngineZ180::DoXOR(uchar Val)
{
    Reg_A = Reg_A ^ Val;
    SetFlagsSZ(Reg_A);
    SetFlagsP(Reg_A);
    FlagHClr;
    FlagNClr;
    FlagCClr;
}

void ScriptEngineZ180::DoOR(uchar Val)
{
    Reg_A = Reg_A | Val;
    SetFlagsSZ(Reg_A);
    SetFlagsP(Reg_A);
    FlagHClr;
    FlagNClr;
    FlagCClr;
}

void ScriptEngineZ180::DoINC(uchar &Reg)
{
    uchar Val1 = Reg + 1;
    if ((!(Val1 & 0b00001000)) && (Reg & 0b00001000))
    {
        FlagHSet;
    }
    else
    {
        FlagHClr;
    }
    if (Reg == 0x7F)
    {
        FlagPSet;
    }
    else
    {
        FlagPClr;
    }
    FlagNClr;
    Reg = Val1;
    SetFlagsSZ(Reg);
}

void ScriptEngineZ180::DoDEC(uchar &Reg)
{
    uchar Val1 = Reg - 1;
    if ((!(Reg & 0b00001000)) && (Val1 & 0b00001000))
    {
        FlagHSet;
    }
    else
    {
        FlagHClr;
    }
    if (Reg == 0x80)
    {
        FlagPSet;
    }
    else
    {
        FlagPClr;
    }
    FlagNSet;
    Reg = Val1;
    SetFlagsSZ(Reg);
}

void ScriptEngineZ180::DoRL(uchar &Reg, bool NoAcc)
{
    bool Carry = Reg & 0b10000000;
    Reg = Reg << 1;
    if (FlagCGet)
    {
        Reg++;
    }
    if (Carry)
    {
        FlagCSet;
    }
    else
    {
        FlagCClr;
    }
    FlagNClr;
    FlagHClr;

    if (NoAcc)
    {
        SetFlagsP(Reg);
        SetFlagsSZ(Reg);
    }
}

void ScriptEngineZ180::DoRR(uchar &Reg, bool NoAcc)
{
    bool Carry = Reg & 0b00000001;
    Reg = Reg >> 1;
    if (FlagCGet)
    {
        Reg += 128;
    }
    if (Carry)
    {
        FlagCSet;
    }
    else
    {
        FlagCClr;
    }
    FlagNClr;
    FlagHClr;

    if (NoAcc)
    {
        SetFlagsP(Reg);
        SetFlagsSZ(Reg);
    }
}

void ScriptEngineZ180::DoRLC(uchar &Reg, bool NoAcc)
{
    bool Carry = Reg & 0b10000000;
    Reg = Reg << 1;
    if (Carry)
    {
        FlagCSet;
        Reg++;
    }
    else
    {
        FlagCClr;
    }
    FlagNClr;
    FlagHClr;

    if (NoAcc)
    {
        SetFlagsP(Reg);
        SetFlagsSZ(Reg);
    }
}

void ScriptEngineZ180::DoRRC(uchar &Reg, bool NoAcc)
{
    bool Carry = Reg & 0b00000001;
    Reg = Reg >> 1;
    if (Carry)
    {
        FlagCSet;
        Reg += 128;
    }
    else
    {
        FlagCClr;
    }
    FlagNClr;
    FlagHClr;

    if (NoAcc)
    {
        SetFlagsP(Reg);
        SetFlagsSZ(Reg);
    }
}

void ScriptEngineZ180::DoSLA(uchar &Reg)
{
    if (Reg & 0b10000000)
    {
        FlagCSet;
    }
    else
    {
        FlagCClr;
    }
    Reg = Reg << 1;

    FlagNClr;
    FlagHClr;

    SetFlagsP(Reg);
    SetFlagsSZ(Reg);
}

void ScriptEngineZ180::DoSRA(uchar &Reg)
{
    uchar Carry = Reg & 0b10000000;
    if (Reg & 0b00000001)
    {
        FlagCSet;
    }
    else
    {
        FlagCClr;
    }
    Reg = Reg >> 1;
    Reg = Reg | Carry;

    FlagNClr;
    FlagHClr;

    SetFlagsP(Reg);
    SetFlagsSZ(Reg);
}

void ScriptEngineZ180::DoSLL(uchar &Reg)
{
    if (Reg & 0b10000000)
    {
        FlagCSet;
    }
    else
    {
        FlagCClr;
    }
    Reg = Reg << 1;
    Reg = Reg + 1;

    FlagNClr;
    FlagHClr;

    SetFlagsP(Reg);
    SetFlagsSZ(Reg);
}

void ScriptEngineZ180::DoSRL(uchar &Reg)
{
    if (Reg & 0b00000001)
    {
        FlagCSet;
    }
    else
    {
        FlagCClr;
    }
    Reg = Reg >> 1;

    FlagNClr;
    FlagHClr;

    SetFlagsP(Reg);
    SetFlagsSZ(Reg);
}

void ScriptEngineZ180::DoJumpAbs(int Addr, bool Call)
{
    if (Call)
    {
        uchar PCH = Reg_PC >> 8;
        uchar PCL = Reg_PC & 255;
        DoPUSH(PCH, PCL);
    }
    Reg_PC = Addr;
}

void ScriptEngineZ180::DoJumpAbs(int AddrH, int AddrL, bool Call)
{
    if (Call)
    {
        uchar PCH = Reg_PC >> 8;
        uchar PCL = Reg_PC & 255;
        DoPUSH(PCH, PCL);
    }
    Reg_PC = (AddrH << 8) + AddrL;
}

void ScriptEngineZ180::DoJumpRel(int Addr, bool Call)
{
    if (Call)
    {
        uchar PCH = Reg_PC >> 8;
        uchar PCL = Reg_PC & 255;
        DoPUSH(PCH, PCL);
    }
    Reg_PC = Reg_PC + Addr;
    if (Addr > 127)
    {
        Reg_PC -= 256;
    }
}

void ScriptEngineZ180::DoIN(uchar AddrH, uchar AddrL, uchar &Reg, bool Flags)
{
    Reg = 0x00;

    if (Flags)
    {
        SetFlagsSZ(Reg);
        SetFlagsP(Reg);
        FlagHClr;
        FlagNClr;
    }
}

void ScriptEngineZ180::DoOUT(uchar AddrH, uchar AddrL, uchar &Reg)
{
}

void ScriptEngineZ180::DoBlock1I()
{
    Reg_L++;
    if (Reg_L == 0) { Reg_H++; }
    if (Reg_B == 0)
    {
        FlagZSet;
    }
    else
    {
        FlagZClr;
    }
    FlagNSet;
}

void ScriptEngineZ180::DoBlock1D()
{
    Reg_L--;
    if (Reg_L == 255) { Reg_H--; }
    if (Reg_B == 0)
    {
        FlagZSet;
    }
    else
    {
        FlagZClr;
    }
    FlagNSet;
}

void ScriptEngineZ180::DoBlock1IR()
{
    Reg_L++;
    if (Reg_L == 0) { Reg_H++; }
    if (Reg_B != 0)
    {
        Reg_PC--;
        Reg_PC--;
    }
    FlagZSet;
    FlagNSet;
}

void ScriptEngineZ180::DoBlock1DR()
{
    Reg_L--;
    if (Reg_L == 255) { Reg_H--; }
    if (Reg_B != 0)
    {
        Reg_PC--;
        Reg_PC--;
    }
    FlagZSet;
    FlagNSet;
}

void ScriptEngineZ180::DoBlock2I()
{
    if (Reg_A == MemGet(Reg_H, Reg_L))
    {
        FlagZSet;
    }
    else
    {
        FlagZClr;
    }
    Reg_L++;
    if (Reg_L == 0)
    {
        Reg_H++;
    }
    Reg_C--;
    if (Reg_C == 255)
    {
        Reg_B--;
    }
    if ((Reg_B == 0) && (Reg_C == 0))
    {
        FlagPClr;
    }
    else
    {
        FlagPSet;
    }
}

void ScriptEngineZ180::DoBlock2D()
{
    if (Reg_A == MemGet(Reg_H, Reg_L))
    {
        FlagZSet;
    }
    else
    {
        FlagZClr;
    }
    Reg_L--;
    if (Reg_L == 255)
    {
        Reg_H--;
    }
    Reg_C--;
    if (Reg_C == 255)
    {
        Reg_B--;
    }
    if ((Reg_B == 0) && (Reg_C == 0))
    {
        FlagPClr;
    }
    else
    {
        FlagPSet;
    }
}

void ScriptEngineZ180::DoBlock2IR(bool CompareA)
{
    Reg_L++;
    if (Reg_L == 0)
    {
        Reg_H++;
    }
    Reg_C--;
    if (Reg_C == 255)
    {
        Reg_B--;
    }

    if (!(((Reg_B == 0) && (Reg_C == 0)) || (CompareA && (FlagZGet))))
    {
        Reg_PC--;
        Reg_PC--;
    }
}

void ScriptEngineZ180::DoBlock2DR(bool CompareA)
{
    Reg_L--;
    if (Reg_L == 255)
    {
        Reg_H--;
    }
    Reg_C--;
    if (Reg_C == 255)
    {
        Reg_B--;
    }

    if (!(((Reg_B == 0) && (Reg_C == 0)) || (CompareA && (FlagZGet))))
    {
        Reg_PC--;
        Reg_PC--;
    }
}

void ScriptEngineZ180::DoBlock_CP()
{
    bool C = FlagCGet;
    DoCP(MemGet(Reg_H, Reg_L));
    if (C)
    {
        FlagCSet;
    }
    else
    {
        FlagCClr;
    }
}

void ScriptEngineZ180::DoBlock_LD()
{
    MemSet(Reg_D, Reg_E, MemGet(Reg_H, Reg_L));
}

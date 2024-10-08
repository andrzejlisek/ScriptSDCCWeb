#include "scriptenginemcs51.h"

ScriptEngineMCS51::ScriptEngineMCS51()
{
    ScriptDecompile_ = new ScriptDecompileMCS51();
    for (int I = 0; I < 256; I++)
    {
        BitAddress1[I] = (((I) >> 3) + 32);
        BitAddress2[I] = (((I) >> 3) - 16);
        RegBankAddr[I] = ((I >> 3) & 3) << 3;
    }
}

ScriptEngineMCS51::~ScriptEngineMCS51()
{
    delete ScriptDecompile_;
}

void ScriptEngineMCS51::DoCommand()
{
    if (InterruptIdle)
    {
        if (InterruptQueue.size() > 0)
        {
            int IntParam = InterruptStartMem();

            if ((IntParam & 0x30000) == 0x10000)
            {
                InterruptIdle = false;

                RegSP++;
                IRAM[RegSP] = PC & 255;
                RegSP++;
                IRAM[RegSP] = PC >> 8;

                PC = 0x03;
            }
            if ((IntParam & 0x30000) == 0x20000)
            {
                InterruptIdle = false;

                RegSP++;
                IRAM[RegSP] = PC & 255;
                RegSP++;
                IRAM[RegSP] = PC >> 8;

                PC = 0x13;
            }

            // 0 - 0x03
            // 1 - 0x0B
            // 2 - 0x13
            // 3 - 0x1B
            // 4 - 0x23
            // 5 - 0x2B
        }
    }

    int OpCode = PrgRead(PC);
    int Data1, Data2;
    int Temp1, Temp2, Temp3, Temp4;
#ifdef ScriptMachineStatistics
    for (int I = 0; I < 256; I++)
    {
        InstructionStatistics[OpCode]++;
    }
#endif
    switch (OpCode)
    {
        // Additional instructions
        case 0x00: // NOP
            PC++;
            break;
        case 0xA5: // Undocumented instruction
            MemData[SwapPage] = 255;
            FeedbackData("E", MessagePrefix, "Unknown instruction at " + Hex::IntToHex16(PC) + ": " + Hex::IntToHex8(0xA5));
            break;

        // Subroutine calling
        case 0x11: // ACALL (P0)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoACALL(Data1, 0);
            break;
        case 0x31: // ACALL (P1)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoACALL(Data1, 256);
            break;
        case 0x51: // ACALL (P2)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoACALL(Data1, 512);
            break;
        case 0x71: // ACALL (P3)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoACALL(Data1, 768);
            break;
        case 0x91: // ACALL (P4)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoACALL(Data1, 1024);
            break;
        case 0xB1: // ACALL (P5)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoACALL(Data1, 1280);
            break;
        case 0xD1: // ACALL (P6)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoACALL(Data1, 1536);
            break;
        case 0xF1: // ACALL (P7)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoACALL(Data1, 1792);
            break;
        case 0x12: // LCALL addr16
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            RegSP++;
            IRAM[RegSP] = PC & 255;
            RegSP++;
            IRAM[RegSP] = PC >> 8;
            PC = (Data1 << 8) + Data2;
            break;

        // Return from subroutine or interrupt
        case 0x22: // RET
            Temp1 = IRAM[RegSP];
            RegSP--;
            Temp2 = IRAM[RegSP];
            RegSP--;
            PC = (Temp1 << 8) + Temp2;
            break;
        case 0x32: // RETI
            Temp1 = IRAM[RegSP];
            RegSP--;
            Temp2 = IRAM[RegSP];
            RegSP--;
            PC = (Temp1 << 8) + Temp2;
            InterruptFinish();
            break;

        // Unconditional jumps
        case 0x01: // AJMP (P0)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoAJMP(Data1, 0);
            break;
        case 0x21: // AJMP (P1)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoAJMP(Data1, 256);
            break;
        case 0x41: // AJMP (P2)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoAJMP(Data1, 512);
            break;
        case 0x61: // AJMP (P3)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoAJMP(Data1, 768);
            break;
        case 0x81: // AJMP (P4)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoAJMP(Data1, 1024);
            break;
        case 0xA1: // AJMP (P5)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoAJMP(Data1, 1280);
            break;
        case 0xC1: // AJMP (P6)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoAJMP(Data1, 1536);
            break;
        case 0xE1: // AJMP (P7)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoAJMP(Data1, 1792);
            break;
        case 0x02: // LJMP addr16
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC = (Data1 << 8) + Data2;
            break;
        case 0x73: // JMP @A+DPTR
            Temp1 = (RegDPH << 8) + RegDPL;
            Temp2 = MCS51_AccumulatorRead;
            ScriptDecompile_->JumpVectorAddr(PC, Temp1 + Temp2);
            PC = Temp1 + Temp2;
            break;
        case 0x80: // SJMP rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            PC = PC + CalcRel(Data1);
            break;

        // Conditional jumps based on bit value
        case 0x10: // JBC bit,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            if (BitRead(Data1))
            {
                BitWrite(Data1, false);
                PC = PC + CalcRel(Data2);
            }
            break;
        case 0x20: // JB bit,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            if (BitRead(Data1))
            {
                PC = PC + CalcRel(Data2);
            }
            break;
        case 0x30: // JNB bit,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            if (BitRead(Data1) != true)
            {
                PC = PC + CalcRel(Data2);
            }
            break;
        case 0x40: // JC rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (MCS51_PSW_CYGet)
            {
                PC = PC + CalcRel(Data1);
            }
            break;
        case 0x50: // JNC rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (!MCS51_PSW_CYGet)
            {
                PC = PC + CalcRel(Data1);
            }
            break;
        case 0x60: // JZ rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (MCS51_AccumulatorRead == 0)
            {
                PC = PC + CalcRel(Data1);
            }
            break;
        case 0x70: // JNZ rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (MCS51_AccumulatorRead != 0)
            {
                PC = PC + CalcRel(Data1);
            }
            break;

        // Conditional jumps with value comparison
        case 0xB4: // CJNE A,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xB5: // CJNE A,dir,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IBYTERead(Data1);
            DoCJNE(Temp1, Temp2, Data2);
            break;
        case 0xB6: // CJNE @R0,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = IRAM[RRead(0)];
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xB7: // CJNE @R1,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = IRAM[RRead(1)];
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xB8: // CJNE R0,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = RRead(0);
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xB9: // CJNE R1,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = RRead(1);
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xBA: // CJNE R2,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = RRead(2);
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xBB: // CJNE R3,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = RRead(3);
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xBC: // CJNE R4,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = RRead(4);
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xBD: // CJNE R5,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = RRead(5);
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xBE: // CJNE R6,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = RRead(6);
            DoCJNE(Temp1, Data1, Data2);
            break;
        case 0xBF: // CJNE R7,#data,rel (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = RRead(7);
            DoCJNE(Temp1, Data1, Data2);
            break;

        // Conditional jumps with value decrementation
        case 0xD5: // DJNZ dir,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            IBYTEWrite(Data1, Temp1);
            if (Temp1 != 0)
            {
                PC = PC + CalcRel(Data2);
            }
            break;
        case 0xD8: // DJNZ R0,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoDJNZ(0, Data1);
            break;
        case 0xD9: // DJNZ R1,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoDJNZ(1, Data1);
            break;
        case 0xDA: // DJNZ R2,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoDJNZ(2, Data1);
            break;
        case 0xDB: // DJNZ R3,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoDJNZ(3, Data1);
            break;
        case 0xDC: // DJNZ R4,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoDJNZ(4, Data1);
            break;
        case 0xDD: // DJNZ R5,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoDJNZ(5, Data1);
            break;
        case 0xDE: // DJNZ R6,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoDJNZ(6, Data1);
            break;
        case 0xDF: // DJNZ R7,rel
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoDJNZ(7, Data1);
            break;

        // Stack instructions
        case 0xC0: // PUSH dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            RegSP++;
            IRAM[RegSP] = Temp1;
            break;
        case 0xD0: // POP dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = IRAM[RegSP];
            RegSP--;
            IBYTEWrite(Data1, Temp1);
            break;

        // Operations on accumulator
        case 0x03: // RR A
            PC++;
            Temp1 = RegBitsX[0x0C] & 0x01;
            RegBitsX[0x0C] = RegBitsX[0x0C] >> 1;
            if (Temp1)
            {
                RegBitsX[0x0C] = RegBitsX[0x0C] | 0x80;
            }
            break;
        case 0x13: // RRC A (C)
            PC++;
            Temp1 = RegBitsX[0x0C] & 0x01;
            RegBitsX[0x0C] = RegBitsX[0x0C] >> 1;
            if (MCS51_PSW_CYGet)
            {
                RegBitsX[0x0C] = RegBitsX[0x0C] | 0x80;
            }
            if (Temp1)
            {
                MCS51_PSW_CYSet;
            }
            else
            {
                MCS51_PSW_CYClr;
            }
            //!!CheckParity();
            break;
        case 0x23: // RL A
            PC++;
            Temp1 = RegBitsX[0x0C] & 0x80;
            RegBitsX[0x0C] = (RegBitsX[0x0C] << 1) & 0xFF;
            if (Temp1)
            {
                RegBitsX[0x0C] = RegBitsX[0x0C] | 0x01;
            }
            break;
        case 0x33: // RLC A (C)
            PC++;
            Temp1 = RegBitsX[0x0C] & 0x80;
            RegBitsX[0x0C] = (RegBitsX[0x0C] << 1) & 0xFF;
            if (MCS51_PSW_CYGet)
            {
                RegBitsX[0x0C] = RegBitsX[0x0C] | 0x01;
            }
            if (Temp1)
            {
                MCS51_PSW_CYSet;
            }
            else
            {
                MCS51_PSW_CYClr;
            }
            //!!!CheckParity();
            break;
        case 0xC4: // SWAP A
            PC++;
            Temp1 = (RegBitsX[0x0C] & 0xF0) >> 4;
            RegBitsX[0x0C] = ((RegBitsX[0x0C] & 0x0F) << 4) + Temp1;
            break;
        case 0xD4: // DA A (C)
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            if (((Temp1 & 15) > 9) || (MCS51_PSW_ACGet))
            {
                Temp1 = Temp1 + 6;
                if (Temp1 > 255)
                {
                    Temp1 = Temp1 - 256;
                    MCS51_PSW_CYSet;
                }
            }
            if (((Temp1 >> 4) > 9) || (MCS51_PSW_CYGet))
            {
                Temp1 = Temp1 + 96;
                if (Temp1 > 255)
                {
                    Temp1 = Temp1 - 256;
                    MCS51_PSW_CYSet;
                }
            }
            MCS51_AccumulatorWrite(Temp1);
            break;
        case 0xE4: // CLR A
            PC++;
            RegBitsX[0x0C] = 0;
            //!!!CheckParity();
            break;
        case 0xF4: // CPL A
            PC++;
            RegBitsX[0x0C] = 255 - RegBitsX[0x0C];
            break;

        // Operations on single bit
        case 0xB2: // CPL bit
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            BitWrite(Data1, (!BitRead(Data1)));
            break;
        case 0xC2: // CLR bit
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            BitWrite(Data1, false);
            break;
        case 0xD2: // SETB bit
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            BitWrite(Data1, true);
            break;
        case 0xB3: // CPL C (C)
            PC++;
            if (MCS51_PSW_CYGet)
            {
                MCS51_PSW_CYClr;
            }
            else
            {
                MCS51_PSW_CYSet;
            }
            break;
        case 0xC3: // CLR C (C)
            PC++;
            MCS51_PSW_CYClr;
            break;
        case 0xD3: // SETB C (C)
            PC++;
            MCS51_PSW_CYSet;
            break;

        // Value incrementation
        case 0xA3: // INC DPTR
            PC++;
            Temp1 = (RegDPH << 8) + RegDPL;
            Temp1++;
            if (Temp1 == 65536) { Temp1 = 0; }
            RegDPH = (Temp1 >> 8);
            RegDPL = (Temp1 & 255);
            break;
        case 0x04: // INC A
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            MCS51_AccumulatorWrite(Temp1);
            break;
        case 0x05: // INC dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            IBYTEWrite(Data1, Temp1);
            break;
        case 0x06: // INC @R0
            PC++;
            Temp1 = IRAM[RRead(0)];
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            IRAM[RRead(0)] = Temp1;
            break;
        case 0x07: // INC @R1
            PC++;
            Temp1 = IRAM[RRead(1)];
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            IRAM[RRead(1)] = Temp1;
            break;
        case 0x08: // INC R0
            PC++;
            Temp1 = RRead(0);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            RWrite(0, Temp1);
            break;
        case 0x09: // INC R1
            PC++;
            Temp1 = RRead(1);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            RWrite(1, Temp1);
            break;
        case 0x0A: // INC R2
            PC++;
            Temp1 = RRead(2);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            RWrite(2, Temp1);
            break;
        case 0x0B: // INC R3
            PC++;
            Temp1 = RRead(3);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            RWrite(3, Temp1);
            break;
        case 0x0C: // INC R4
            PC++;
            Temp1 = RRead(4);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            RWrite(4, Temp1);
            break;
        case 0x0D: // INC R5
            PC++;
            Temp1 = RRead(5);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            RWrite(5, Temp1);
            break;
        case 0x0E: // INC R6
            PC++;
            Temp1 = RRead(6);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            RWrite(6, Temp1);
            break;
        case 0x0F: // INC R7
            PC++;
            Temp1 = RRead(7);
            Temp1++;
            if (Temp1 == 256) { Temp1 = 0; }
            RWrite(7, Temp1);
            break;

        // Value decrementation
        case 0x14: // DEC A
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            MCS51_AccumulatorWrite(Temp1);
            break;
        case 0x15: // DEC dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            IBYTEWrite(Data1, Temp1);
            break;
        case 0x16: // DEC @R0
            PC++;
            Temp1 = IRAM[RRead(0)];
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            IRAM[RRead(0)] = Temp1;
            break;
        case 0x17: // DEC @R1
            PC++;
            Temp1 = IRAM[RRead(1)];
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            IRAM[RRead(1)] = Temp1;
            break;
        case 0x18: // DEC R0
            PC++;
            Temp1 = RRead(0);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            RWrite(0, Temp1);
            break;
        case 0x19: // DEC R1
            PC++;
            Temp1 = RRead(1);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            RWrite(1, Temp1);
            break;
        case 0x1A: // DEC R2
            PC++;
            Temp1 = RRead(2);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            RWrite(2, Temp1);
            break;
        case 0x1B: // DEC R3
            PC++;
            Temp1 = RRead(3);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            RWrite(3, Temp1);
            break;
        case 0x1C: // DEC R4
            PC++;
            Temp1 = RRead(4);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            RWrite(4, Temp1);
            break;
        case 0x1D: // DEC R5
            PC++;
            Temp1 = RRead(5);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            RWrite(5, Temp1);
            break;
        case 0x1E: // DEC R6
            PC++;
            Temp1 = RRead(6);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            RWrite(6, Temp1);
            break;
        case 0x1F: // DEC R7
            PC++;
            Temp1 = RRead(7);
            Temp1--;
            if (Temp1 == -1) { Temp1 = 255; }
            RWrite(7, Temp1);
            break;

        // Multiplication and division
        case 0xA4: // MUL AB (C, OV)
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IBYTERead(0xF0);
            Temp3 = Temp1 * Temp2;
            if (Temp3 > 255)
            {
                Temp1 = Temp3 & 255;
                Temp2 = Temp3 >> 8;
                MCS51_PSW_OVSet;
            }
            else
            {
                Temp1 = Temp3;
                Temp2 = 0;
                MCS51_PSW_OVClr;
            }
            MCS51_AccumulatorWrite(Temp1);
            IBYTEWrite(0xF0, Temp2);
            MCS51_PSW_CYClr;
            break;
        case 0x84: // DIV AB (C, OV)
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IBYTERead(0xF0);
            if (Temp2 != 0)
            {
                Temp3 = Temp1 / Temp2;
                Temp4 = Temp1 % Temp2;
                MCS51_AccumulatorWrite(Temp3);
                IBYTEWrite(0xF0, Temp4);
                MCS51_PSW_OVClr;
            }
            else
            {
                MCS51_AccumulatorWrite(255);
                IBYTEWrite(0xF0, Temp1);
                MCS51_PSW_OVSet;
            }
            MCS51_PSW_CYClr;
            break;

        // Adding without carry
        case 0x24: // ADD A,#data (C, OV, AC)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoADD(Data1);
            break;
        case 0x25: // ADD A,dir (C, OV, AC)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoADD(IBYTERead(Data1));
            break;
        case 0x26: // ADD A,@R0 (C, OV, AC)
            PC++;
            DoADD(IRAM[RRead(0)]);
            break;
        case 0x27: // ADD A,@R1 (C, OV, AC)
            PC++;
            DoADD(IRAM[RRead(1)]);
            break;
        case 0x28: // ADD A,R0 (C, OV, AC)
            PC++;
            DoADD(RRead(0));
            break;
        case 0x29: // ADD A,R1 (C, OV, AC)
            PC++;
            DoADD(RRead(1));
            break;
        case 0x2A: // ADD A,R2 (C, OV, AC)
            PC++;
            DoADD(RRead(2));
            break;
        case 0x2B: // ADD A,R3 (C, OV, AC)
            PC++;
            DoADD(RRead(3));
            break;
        case 0x2C: // ADD A,R4 (C, OV, AC)
            PC++;
            DoADD(RRead(4));
            break;
        case 0x2D: // ADD A,R5 (C, OV, AC)
            PC++;
            DoADD(RRead(5));
            break;
        case 0x2E: // ADD A,R6 (C, OV, AC)
            PC++;
            DoADD(RRead(6));
            break;
        case 0x2F: // ADD A,R7 (C, OV, AC)
            PC++;
            DoADD(RRead(7));
            break;

        // Adding with carry
        case 0x34: // ADDC A,#data (C, OV, AC)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoADDC(Data1);
            break;
        case 0x35: // ADDC A,dir (C, OV, AC)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoADDC(IBYTERead(Data1));
            break;
        case 0x36: // ADDC A,@R0 (C, OV, AC)
            PC++;
            DoADDC(IRAM[RRead(0)]);
            break;
        case 0x37: // ADDC A,@R1 (C, OV, AC)
            PC++;
            DoADDC(IRAM[RRead(1)]);
            break;
        case 0x38: // ADDC A,R0 (C, OV, AC)
            PC++;
            DoADDC(RRead(0));
            break;
        case 0x39: // ADDC A,R1 (C, OV, AC)
            PC++;
            DoADDC(RRead(1));
            break;
        case 0x3A: // ADDC A,R2 (C, OV, AC)
            PC++;
            DoADDC(RRead(2));
            break;
        case 0x3B: // ADDC A,R3 (C, OV, AC)
            PC++;
            DoADDC(RRead(3));
            break;
        case 0x3C: // ADDC A,R4 (C, OV, AC)
            PC++;
            DoADDC(RRead(4));
            break;
        case 0x3D: // ADDC A,R5 (C, OV, AC)
            PC++;
            DoADDC(RRead(5));
            break;
        case 0x3E: // ADDC A,R6 (C, OV, AC)
            PC++;
            DoADDC(RRead(6));
            break;
        case 0x3F: // ADDC A,R7 (C, OV, AC)
            PC++;
            DoADDC(RRead(7));
            break;

        // Subtracting with carry
        case 0x94: // SUBB A,#data (C, OV, AC)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoSUBB(Data1);
            break;
        case 0x95: // SUBB A,dir (C, OV, AC)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            DoSUBB(IBYTERead(Data1));
            break;
        case 0x96: // SUBB A,@R0 (C, OV, AC)
            PC++;
            DoSUBB(IRAM[RRead(0)]);
            break;
        case 0x97: // SUBB A,@R1 (C, OV, AC)
            PC++;
            DoSUBB(IRAM[RRead(1)]);
            break;
        case 0x98: // SUBB A,R0 (C, OV, AC)
            PC++;
            DoSUBB(RRead(0));
            break;
        case 0x99: // SUBB A,R1 (C, OV, AC)
            PC++;
            DoSUBB(RRead(1));
            break;
        case 0x9A: // SUBB A,R2 (C, OV, AC)
            PC++;
            DoSUBB(RRead(2));
            break;
        case 0x9B: // SUBB A,R3 (C, OV, AC)
            PC++;
            DoSUBB(RRead(3));
            break;
        case 0x9C: // SUBB A,R4 (C, OV, AC)
            PC++;
            DoSUBB(RRead(4));
            break;
        case 0x9D: // SUBB A,R5 (C, OV, AC)
            PC++;
            DoSUBB(RRead(5));
            break;
        case 0x9E: // SUBB A,R6 (C, OV, AC)
            PC++;
            DoSUBB(RRead(6));
            break;
        case 0x9F: // SUBB A,R7 (C, OV, AC)
            PC++;
            DoSUBB(RRead(7));
            break;

        // Bitwise conjunction
        case 0x82: // ANL C,bit (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (MCS51_PSW_CYGet && BitRead(Data1))
            {
                MCS51_PSW_CYSet;
            }
            else
            {
                MCS51_PSW_CYClr;
            }
            break;
        case 0xB0: // ANL C,/bit (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (MCS51_PSW_CYGet && (!BitRead(Data1)))
            {
                MCS51_PSW_CYSet;
            }
            else
            {
                MCS51_PSW_CYClr;
            }
            break;
        case 0x52: // ANL dir,A
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            Temp2 = MCS51_AccumulatorRead;
            IBYTEWrite(Data1, Temp1 & Temp2);
            break;
        case 0x53: // ANL dir,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            IBYTEWrite(Data1, Temp1 & Data2);
            break;
        case 0x54: // ANL A,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            MCS51_AccumulatorWrite(Temp1 & Data1);
            break;
        case 0x55: // ANL A,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IBYTERead(Data1);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x56: // ANL A,@R0
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IRAM[RRead(0)];
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x57: // ANL A,@R1
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IRAM[RRead(1)];
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x58: // ANL A,R0
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(0);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x59: // ANL A,R1
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(1);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x5A: // ANL A,R2
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(2);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x5B: // ANL A,R3
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(3);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x5C: // ANL A,R4
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(4);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x5D: // ANL A,R5
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(5);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x5E: // ANL A,R6
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(6);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;
        case 0x5F: // ANL A,R7
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(7);
            MCS51_AccumulatorWrite(Temp1 & Temp2);
            break;

        // Bitwise disjunction
        case 0x72: // ORL C,bit (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (MCS51_PSW_CYGet || BitRead(Data1))
            {
                MCS51_PSW_CYSet;
            }
            else
            {
                MCS51_PSW_CYClr;
            }
            break;
        case 0xA0: // ORL C,/bit (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (MCS51_PSW_CYGet || (!BitRead(Data1)))
            {
                MCS51_PSW_CYSet;
            }
            else
            {
                MCS51_PSW_CYClr;
            }
            break;
        case 0x42: // ORL dir,A
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            Temp2 = MCS51_AccumulatorRead;
            IBYTEWrite(Data1, Temp1 | Temp2);
            break;
        case 0x43: // ORL dir,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            IBYTEWrite(Data1, Temp1 | Data2);
            break;
        case 0x44: // ORL A,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            MCS51_AccumulatorWrite(Temp1 | Data1);
            break;
        case 0x45: // ORL A,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IBYTERead(Data1);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x46: // ORL A,@R0
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IRAM[RRead(0)];
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x47: // ORL A,@R1
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IRAM[RRead(1)];
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x48: // ORL A,R0
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(0);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x49: // ORL A,R1
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(1);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x4A: // ORL A,R2
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(2);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x4B: // ORL A,R3
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(3);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x4C: // ORL A,R4
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(4);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x4D: // ORL A,R5
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(5);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x4E: // ORL A,R6
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(6);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;
        case 0x4F: // ORL A,R7
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(7);
            MCS51_AccumulatorWrite(Temp1 | Temp2);
            break;

        // Bitwise exclusive disjunction
        case 0x62: // XRL dir,A
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            Temp2 = MCS51_AccumulatorRead;
            IBYTEWrite(Data1, Temp1 ^ Temp2);
            break;
        case 0x63: // XRL dir,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            Temp1 = IBYTERead(Data1);
            IBYTEWrite(Data1, Temp1 ^ Data2);
            break;
        case 0x64: // XRL A,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            MCS51_AccumulatorWrite(Temp1 ^ Data1);
            break;
        case 0x65: // XRL A,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IBYTERead(Data1);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x66: // XRL A,@R0
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IRAM[RRead(0)];
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x67: // XRL A,@R1
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IRAM[RRead(1)];
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x68: // XRL A,R0
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(0);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x69: // XRL A,R1
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(1);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x6A: // XRL A,R2
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(2);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x6B: // XRL A,R3
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(3);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x6C: // XRL A,R4
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(4);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x6D: // XRL A,R5
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(5);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x6E: // XRL A,R6
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(6);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;
        case 0x6F: // XRL A,R7
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(7);
            MCS51_AccumulatorWrite(Temp1 ^ Temp2);
            break;

        // Swapping four least significant bits
        case 0xD6: // XCHD A,@R0
            PC++;
            Data1 = MCS51_AccumulatorRead;
            Data2 = IRAM[RRead(0)];
            Temp1 = (Data1 >> 4);
            Temp2 = (Data2 >> 4);
            Temp3 = (Data1 & 15);
            Temp4 = (Data2 & 15);
            Data1 = (Temp1 << 4) + Temp4;
            Data2 = (Temp2 << 4) + Temp3;
            MCS51_AccumulatorWrite(Data1);
            IRAM[RRead(0)] = Data2;
            break;
        case 0xD7: // XCHD A,@R1
            PC++;
            Data1 = MCS51_AccumulatorRead;
            Data2 = IRAM[RRead(1)];
            Temp1 = (Data1 >> 4);
            Temp2 = (Data2 >> 4);
            Temp3 = (Data1 & 15);
            Temp4 = (Data2 & 15);
            Data1 = (Temp1 << 4) + Temp4;
            Data2 = (Temp2 << 4) + Temp3;
            MCS51_AccumulatorWrite(Data1);
            IRAM[RRead(1)] = Data2;
            break;

        // Swapping accumulator with register
        case 0xC5: // XCH A,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IBYTERead(Data1);
            MCS51_AccumulatorWrite(Temp2);
            IBYTEWrite(Data1, Temp1);
            break;
        case 0xC6: // XCH A,@R0
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IRAM[RRead(0)];
            MCS51_AccumulatorWrite(Temp2);
            IRAM[RRead(0)] = Temp1;
            break;
        case 0xC7: // XCH A,@R1
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = IRAM[RRead(1)];
            MCS51_AccumulatorWrite(Temp2);
            IRAM[RRead(1)] = Temp1;
            break;
        case 0xC8: // XCH A,R0
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(0);
            MCS51_AccumulatorWrite(Temp2);
            RWrite(0, Temp1);
            break;
        case 0xC9: // XCH A,R1
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(1);
            MCS51_AccumulatorWrite(Temp2);
            RWrite(1, Temp1);
            break;
        case 0xCA: // XCH A,R2
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(2);
            MCS51_AccumulatorWrite(Temp2);
            RWrite(2, Temp1);
            break;
        case 0xCB: // XCH A,R3
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(3);
            MCS51_AccumulatorWrite(Temp2);
            RWrite(3, Temp1);
            break;
        case 0xCC: // XCH A,R4
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(4);
            MCS51_AccumulatorWrite(Temp2);
            RWrite(4, Temp1);
            break;
        case 0xCD: // XCH A,R5
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(5);
            MCS51_AccumulatorWrite(Temp2);
            RWrite(5, Temp1);
            break;
        case 0xCE: // XCH A,R6
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(6);
            MCS51_AccumulatorWrite(Temp2);
            RWrite(6, Temp1);
            break;
        case 0xCF: // XCH A,R7
            PC++;
            Temp1 = MCS51_AccumulatorRead;
            Temp2 = RRead(7);
            MCS51_AccumulatorWrite(Temp2);
            RWrite(7, Temp1);
            break;

        // Writing constant value
        case 0x74: // MOV A,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            MCS51_AccumulatorWrite(Data1);
            break;
        case 0x75: // MOV dir,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, Data2);
            break;
        case 0x76: // MOV @R0,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IRAM[RRead(0)] = Data1;
            break;
        case 0x77: // MOV @R1,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IRAM[RRead(1)] = Data1;
            break;
        case 0x78: // MOV R0,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(0, Data1);
            break;
        case 0x79: // MOV R1,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(1, Data1);
            break;
        case 0x7A: // MOV R2,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(2, Data1);
            break;
        case 0x7B: // MOV R3,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(3, Data1);
            break;
        case 0x7C: // MOV R4,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(4, Data1);
            break;
        case 0x7D: // MOV R5,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(5, Data1);
            break;
        case 0x7E: // MOV R6,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(6, Data1);
            break;
        case 0x7F: // MOV R7,#data
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(7, Data1);
            break;

        // Bit copying
        case 0x92: // MOV bit,C
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            BitWrite(Data1, MCS51_PSW_CYGet);
            break;
        case 0xA2: // MOV C,bit (C)
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            if (BitRead(Data1))
            {
                MCS51_PSW_CYSet;
            }
            else
            {
                MCS51_PSW_CYClr;
            }
            break;

        // Copying value in internal memory
        case 0x85: // MOV dir,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data2, IBYTERead(Data1));
            break;
        case 0x86: // MOV dir,@R0
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, IRAM[RRead(0)]);
            break;
        case 0x87: // MOV dir,@R1
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, IRAM[RRead(1)]);
            break;
        case 0x88: // MOV dir,R0
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, RRead(0));
            break;
        case 0x89: // MOV dir,R1
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, RRead(1));
            break;
        case 0x8A: // MOV dir,R2
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, RRead(2));
            break;
        case 0x8B: // MOV dir,R3
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, RRead(3));
            break;
        case 0x8C: // MOV dir,R4
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, RRead(4));
            break;
        case 0x8D: // MOV dir,R5
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, RRead(5));
            break;
        case 0x8E: // MOV dir,R6
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, RRead(6));
            break;
        case 0x8F: // MOV dir,R7
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, RRead(7));
            break;
        case 0xA6: // MOV @R0,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IRAM[RRead(0)] = IBYTERead(Data1);
            break;
        case 0xA7: // MOV @R1,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IRAM[RRead(1)] = IBYTERead(Data1);
            break;
        case 0xA8: // MOV R0,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(0, IBYTERead(Data1));
            break;
        case 0xA9: // MOV R1,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(1, IBYTERead(Data1));
            break;
        case 0xAA: // MOV R2,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(2, IBYTERead(Data1));
            break;
        case 0xAB: // MOV R3,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(3, IBYTERead(Data1));
            break;
        case 0xAC: // MOV R4,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(4, IBYTERead(Data1));
            break;
        case 0xAD: // MOV R5,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(5, IBYTERead(Data1));
            break;
        case 0xAE: // MOV R6,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(6, IBYTERead(Data1));
            break;
        case 0xAF: // MOV R7,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            RWrite(7, IBYTERead(Data1));
            break;
        case 0xE5: // MOV A,dir
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            MCS51_AccumulatorWrite(IBYTERead(Data1));
            break;
        case 0xE6: // MOV A,@R0
            PC++;
            MCS51_AccumulatorWrite(IRAM[RRead(0)]);
            break;
        case 0xE7: // MOV A,@R1
            PC++;
            MCS51_AccumulatorWrite(IRAM[RRead(1)]);
            break;
        case 0xE8: // MOV A,R0
            PC++;
            MCS51_AccumulatorWrite(RRead(0));
            break;
        case 0xE9: // MOV A,R1
            PC++;
            MCS51_AccumulatorWrite(RRead(1));
            break;
        case 0xEA: // MOV A,R2
            PC++;
            MCS51_AccumulatorWrite(RRead(2));
            break;
        case 0xEB: // MOV A,R3
            PC++;
            MCS51_AccumulatorWrite(RRead(3));
            break;
        case 0xEC: // MOV A,R4
            PC++;
            MCS51_AccumulatorWrite(RRead(4));
            break;
        case 0xED: // MOV A,R5
            PC++;
            MCS51_AccumulatorWrite(RRead(5));
            break;
        case 0xEE: // MOV A,R6
            PC++;
            MCS51_AccumulatorWrite(RRead(6));
            break;
        case 0xEF: // MOV A,R7
            PC++;
            MCS51_AccumulatorWrite(RRead(7));
            break;
        case 0xF5: // MOV dir,A
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            IBYTEWrite(Data1, MCS51_AccumulatorRead);
            break;
        case 0xF6: // MOV @R0,A
            PC++;
            IRAM[RRead(0)] = MCS51_AccumulatorRead;
            break;
        case 0xF7: // MOV @R1,A
            PC++;
            IRAM[RRead(1)] = MCS51_AccumulatorRead;
            break;
        case 0xF8: // MOV R0,A
            PC++;
            RWrite(0, MCS51_AccumulatorRead);
            break;
        case 0xF9: // MOV R1,A
            PC++;
            RWrite(1, MCS51_AccumulatorRead);
            break;
        case 0xFA: // MOV R2,A
            PC++;
            RWrite(2, MCS51_AccumulatorRead);
            break;
        case 0xFB: // MOV R3,A
            PC++;
            RWrite(3, MCS51_AccumulatorRead);
            break;
        case 0xFC: // MOV R4,A
            PC++;
            RWrite(4, MCS51_AccumulatorRead);
            break;
        case 0xFD: // MOV R5,A
            PC++;
            RWrite(5, MCS51_AccumulatorRead);
            break;
        case 0xFE: // MOV R6,A
            PC++;
            RWrite(6, MCS51_AccumulatorRead);
            break;
        case 0xFF: // MOV R7,A
            PC++;
            RWrite(7, MCS51_AccumulatorRead);
            break;

        // Reading code memory
        case 0x83: // MOVC A,@A+PC
            PC++;
            Temp1 = (MCS51_AccumulatorRead + PC) & 65535;
            MCS51_AccumulatorWrite(PrgRead(Temp1));
            break;
        case 0x93: // MOVC A,@A+DPTR
            PC++;
            Temp1 = (MCS51_AccumulatorRead + (RegDPH << 8) + RegDPL) & 65535;
            MCS51_AccumulatorWrite(PrgRead(Temp1));
            break;

        // Setting external address
        case 0x90: // MOV DPTR,#data16
            PC++;
            Data1 = PrgRead(PC);
            PC++;
            Data2 = PrgRead(PC);
            PC++;
            RegDPH = Data1;
            RegDPL = Data2;
            break;

        // Reading and writing external memory
        case 0xE0: // MOVX A,@DPTR
            PC++;
            MCS51_AccumulatorWrite(XBYTERead((RegDPH << 8) + RegDPL));
            break;
        case 0XE2: // MOVX A,@R0
            PC++;
            MCS51_AccumulatorWrite(XBYTERead((IBYTERead(160) << 8) + RRead(0)));
            break;
        case 0xE3: // MOVX A,@R1
            PC++;
            MCS51_AccumulatorWrite(XBYTERead((IBYTERead(160) << 8) + RRead(1)));
            break;
        case 0xF0: // MOVX @DPTR,A
            PC++;
            XBYTEWrite((RegDPH << 8) + RegDPL, MCS51_AccumulatorRead);
            break;
        case 0xF2: // MOVX @R0,A
            PC++;
            XBYTEWrite((IBYTERead(160) << 8) + RRead(0), MCS51_AccumulatorRead);
            break;
        case 0xF3: // MOVX @R1,A
            PC++;
            XBYTEWrite((IBYTERead(160) << 8) + RRead(1), MCS51_AccumulatorRead);
            break;
    }
}

void ScriptEngineMCS51::DoReset()
{
    PC = 0;
    RegSP = 7;
    RegDPH = 0;
    RegDPL = 0;
    for (int i = 0; i < 16; i++)
    {
        RegBitsX[i] = 0;
    }
}


std::string ScriptEngineMCS51::GetEntryPoints()
{
    return "X0000X0003X0013X";
    //return "X0000X0003X0013X0023X000BX001BX";
}

// AJMP working procedure
void ScriptEngineMCS51::DoAJMP(int Addr, int Offset)
{
    PC = (PC & 63488) + Addr + Offset;
}

// ACALL working procedure
void ScriptEngineMCS51::DoACALL(int Addr, int Offset)
{
    RegSP++;
    IRAM[RegSP] = PC & 255;
    RegSP++;
    IRAM[RegSP] = PC >> 8;
    PC = (PC & 63488) + Addr + Offset;
}

// CJNE working procedure
void ScriptEngineMCS51::DoCJNE(int Data1, int Data2, int Addr)
{
    if (Data1 != Data2)
    {
        PC = PC + CalcRel(Addr);
    }
    if (Data1 < Data2)
    {
        MCS51_PSW_CYSet;
    }
    else
    {
        MCS51_PSW_CYClr;
    }
}

// DJNZ working procedure
void ScriptEngineMCS51::DoDJNZ(int R, int Addr)
{
    int Temp1 = RRead(R);
    Temp1--;
    if (Temp1 == -1) { Temp1 = 255; }
    RWrite(R, (uchar)Temp1);
    if (Temp1 != 0)
    {
        PC = PC + CalcRel(Addr);
    }
}

// ADD working procedure
void ScriptEngineMCS51::DoADD(int Arg)
{
    int A = MCS51_AccumulatorRead;
    int Res = A + Arg;
    int A1c = A % 16;
    int A2c = Arg % 16;
    int A1ov = A % 128;
    int A2ov = Arg % 128;
    int Sumov = A1ov + A2ov;
    if ((A1c + A2c) > 15)
    {
        MCS51_PSW_ACSet;
    }
    else
    {
        MCS51_PSW_ACClr;
    }
    if (Res > 255)
    {
        MCS51_PSW_CYSet;
        if (Sumov < 128)
        {
            MCS51_PSW_OVSet;
        }
        else
        {
            MCS51_PSW_OVClr;
        }
        Res = Res - 256;
    }
    else
    {
        MCS51_PSW_CYClr;
        if (Sumov < 128)
        {
            MCS51_PSW_OVClr;
        }
        else
        {
            MCS51_PSW_OVSet;
        }
    }
    MCS51_AccumulatorWrite(Res);
}

// ADDC working procedure
void ScriptEngineMCS51::DoADDC(int Arg)
{
    int C = 0;
    if (MCS51_PSW_CYGet)
    {
        C = 1;
    }
    int A = MCS51_AccumulatorRead;
    int Res = A + Arg + C;
    int A1c = A % 16;
    int A2c = Arg % 16;
    int A1ov = A % 128;
    int A2ov = Arg % 128;
    int Sumov = A1ov + A2ov + C;
    if ((A1c + A2c + C) > 15)
    {
        MCS51_PSW_ACSet;
    }
    else
    {
        MCS51_PSW_ACClr;
    }
    if (Res > 255)
    {
        MCS51_PSW_CYSet;
        if (Sumov < 128)
        {
            MCS51_PSW_OVSet;
        }
        else
        {
            MCS51_PSW_OVClr;
        }
        Res = Res - 256;
    }
    else
    {
        MCS51_PSW_CYClr;
        if (Sumov < 128)
        {
            MCS51_PSW_OVClr;
        }
        else
        {
            MCS51_PSW_OVSet;
        }
    }
    MCS51_AccumulatorWrite(Res);
}

// SUBB working procedure
void ScriptEngineMCS51::DoSUBB(int Arg)
{
    int C = 0;
    if (MCS51_PSW_CYGet)
    {
        C = 1;
    }
    int A = MCS51_AccumulatorRead;
    int Res = A - (Arg + C);
    int A1ac = A % 16;
    int A2ac = (Arg + C) % 16;
    int A1ov = A % 128;
    int A2ov = (Arg + C) % 128;
    if (Res < 0)
    {
        MCS51_PSW_CYSet;
        if (A2ov > A1ov)
        {
            MCS51_PSW_OVClr;
        }
        else
        {
            MCS51_PSW_OVSet;
        }
        Res = Res + 256;
    }
    else
    {
        MCS51_PSW_CYClr;
        if (A2ov > A1ov)
        {
            MCS51_PSW_OVSet;
        }
        else
        {
            MCS51_PSW_OVClr;
        }
    }
    if (A2ac > A1ac)
    {
        MCS51_PSW_ACSet;
    }
    else
    {
        MCS51_PSW_ACClr;
    }
    MCS51_AccumulatorWrite(Res);
}

// Calculating relative address
inline int ScriptEngineMCS51::CalcRel(int Data)
{
    if (Data & 0b10000000)
    {
        return Data - 256;
    }
    else
    {
        return Data;
    }
}



// Register Rx reading
inline int ScriptEngineMCS51::RRead(int N)
{
    return IRAM[N | RegBankAddr[RegBitsX[0x0A]]];
}

// Register Rx writing
inline void ScriptEngineMCS51::RWrite(int N, int Data)
{
    IRAM[N | RegBankAddr[RegBitsX[0x0A]]] = (uchar)Data;
}

// Reading internal memory or SFR
int ScriptEngineMCS51::IBYTERead(int Addr)
{
    int Data = 0;
    if (Addr < 128)
    {
        Data = IRAM[Addr];
    }
    else
    {
        if ((Addr & 7) == 0)
        {
            Data = RegBitsX[BitAddress2[Addr]];
        }
        else
        {
            switch (Addr)
            {
                case 0x81:
                    Data = RegSP;
                    break;
                case 0x82:
                    Data = RegDPL;
                    break;
                case 0x83:
                    Data = RegDPH;
                    break;
            }
        }
    }
    return Data;
}

// Writing internal memory or SFR
void ScriptEngineMCS51::IBYTEWrite(int Addr, int Data)
{
    if (Addr < 128)
    {
        IRAM[Addr] = (uchar)Data;
    }
    else
    {
        if ((Addr & 7) == 0)
        {
            RegBitsX[BitAddress2[Addr]] = (Data); /*!!!!if (BitAddress2((int)(Addr)) == 0x0D) { CheckParity(); }*/
        }
        else
        {
            switch (Addr)
            {
                case 0x81:
                    RegSP = Data;
                    break;
                case 0x82:
                    RegDPL = Data;
                    break;
                case 0x83:
                    RegDPH = Data;
                    break;
            }
        }
    }
}


// Reading bit from address
bool ScriptEngineMCS51::BitRead(int Addr)
{
    if (Addr >= 128)
    {
        return ((RegBitsX[BitAddress2[Addr]] >> (Addr & 7)) & 1) == 1;
    }
    else
    {
        return ((IRAM[BitAddress1[Addr]] >> (Addr & 7)) & 1) == 1;
    }
}

// Writing bit to address
void ScriptEngineMCS51::BitWrite(int Addr, bool Val)
{
    if (Addr >= 128)
    {
        if (Val)
        {
            RegBitsX[BitAddress2[Addr]] = RegBitsX[BitAddress2[Addr]] | (1 << (Addr & 7));
        }
        else
        {
            RegBitsX[BitAddress2[Addr]] = RegBitsX[BitAddress2[Addr]] & (255 - (1 << (Addr & 7)));
        }
        /*!!!if (BitAddress2(Addr) == 0x0C)
        {
            CheckParity();
        }*/
    }
    else
    {
        if (Val)
        {
            IRAM[BitAddress1[Addr]] = IRAM[BitAddress1[Addr]] | (1 << (Addr & 7));
        }
        else
        {
            IRAM[BitAddress1[Addr]] = IRAM[BitAddress1[Addr]] & (255 - (1 << (Addr & 7)));
        }
    }
}

// Checking accumulator parity
/*inline void ScriptEngineMCS51::CheckParity()
{
    if (false)
    {
        bool ParityTest = true;
        if (RegBitsX[0x0C] & 128) { ParityTest = !ParityTest; }
        if (RegBitsX[0x0C] & 64) { ParityTest = !ParityTest; }
        if (RegBitsX[0x0C] & 32) { ParityTest = !ParityTest; }
        if (RegBitsX[0x0C] & 16) { ParityTest = !ParityTest; }
        if (RegBitsX[0x0C] & 8) { ParityTest = !ParityTest; }
        if (RegBitsX[0x0C] & 4) { ParityTest = !ParityTest; }
        if (RegBitsX[0x0C] & 2) { ParityTest = !ParityTest; }
        if (RegBitsX[0x0C] & 1) { ParityTest = !ParityTest; }
        if (ParityTest)
        {
            MCS51_PSW_P_Set;
        }
        else
        {
            MCS51_PSW_P_Clr;
        }
    }
}*/

#include "scriptdecompilemcs51.h"

ScriptDecompileMCS51::ScriptDecompileMCS51()
{

}

void ScriptDecompileMCS51::ProcessOpcode(int Thr)
{
    int Reg_PC = ProgramCounterThreads[Thr];
    uchar OpCode = MemProg[ProgramCounterThreads[Thr]];
    switch (OpCode)
    {
        // Additional instructions
        case 0x00: InstrPattern[Reg_PC] = "NOP";          ThreadNext(Thr, 1); break;
        case 0xA5: InstrPattern[Reg_PC] = "?";            ThreadNext(Thr, 0); break;

        // Subroutine calling
        case 0x11: InstrPattern[Reg_PC] = "ACALL (P0)";   ThreadNext(Thr, 2); ThreadAdd(CalcAJMP(Reg_PC,    0)); break;
        case 0x31: InstrPattern[Reg_PC] = "ACALL (P1)";   ThreadNext(Thr, 2); ThreadAdd(CalcAJMP(Reg_PC,  256)); break;
        case 0x51: InstrPattern[Reg_PC] = "ACALL (P2)";   ThreadNext(Thr, 2); ThreadAdd(CalcAJMP(Reg_PC,  512)); break;
        case 0x71: InstrPattern[Reg_PC] = "ACALL (P3)";   ThreadNext(Thr, 2); ThreadAdd(CalcAJMP(Reg_PC,  768)); break;
        case 0x91: InstrPattern[Reg_PC] = "ACALL (P4)";   ThreadNext(Thr, 2); ThreadAdd(CalcAJMP(Reg_PC, 1024)); break;
        case 0xB1: InstrPattern[Reg_PC] = "ACALL (P5)";   ThreadNext(Thr, 2); ThreadAdd(CalcAJMP(Reg_PC, 1280)); break;
        case 0xD1: InstrPattern[Reg_PC] = "ACALL (P6)";   ThreadNext(Thr, 2); ThreadAdd(CalcAJMP(Reg_PC, 1536)); break;
        case 0xF1: InstrPattern[Reg_PC] = "ACALL (P7)";   ThreadNext(Thr, 2); ThreadAdd(CalcAJMP(Reg_PC, 1792)); break;
        case 0x12: InstrPattern[Reg_PC] = "LCALL addr16"; ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;

        // Return from subroutine or interrupt
        case 0x22: InstrPattern[Reg_PC] = "RET";          ThreadNext(Thr, -1); break;
        case 0x32: InstrPattern[Reg_PC] = "RETI";         ThreadNext(Thr, -1); break;

        // Unconditional jumps
        case 0x01: InstrPattern[Reg_PC] = "AJMP (P0)";    ThreadNext(Thr, -2); ThreadAdd(CalcAJMP(Reg_PC,    0)); break;
        case 0x21: InstrPattern[Reg_PC] = "AJMP (P1)";    ThreadNext(Thr, -2); ThreadAdd(CalcAJMP(Reg_PC,  256)); break;
        case 0x41: InstrPattern[Reg_PC] = "AJMP (P2)";    ThreadNext(Thr, -2); ThreadAdd(CalcAJMP(Reg_PC,  512)); break;
        case 0x61: InstrPattern[Reg_PC] = "AJMP (P3)";    ThreadNext(Thr, -2); ThreadAdd(CalcAJMP(Reg_PC,  768)); break;
        case 0x81: InstrPattern[Reg_PC] = "AJMP (P4)";    ThreadNext(Thr, -2); ThreadAdd(CalcAJMP(Reg_PC, 1024)); break;
        case 0xA1: InstrPattern[Reg_PC] = "AJMP (P5)";    ThreadNext(Thr, -2); ThreadAdd(CalcAJMP(Reg_PC, 1280)); break;
        case 0xC1: InstrPattern[Reg_PC] = "AJMP (P6)";    ThreadNext(Thr, -2); ThreadAdd(CalcAJMP(Reg_PC, 1536)); break;
        case 0xE1: InstrPattern[Reg_PC] = "AJMP (P7)";    ThreadNext(Thr, -2); ThreadAdd(CalcAJMP(Reg_PC, 1792)); break;
        case 0x02: InstrPattern[Reg_PC] = "LJMP addr16";  ThreadNext(Thr, -3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0x73: InstrPattern[Reg_PC] = "JMP @A+DPTR";  ThreadNext(Thr, -1); ThreadAddVector(Reg_PC);
        case 0x80: InstrPattern[Reg_PC] = "SJMP rel1";    ThreadNext(Thr, -2); ThreadAdd(CalcRel(Reg_PC + 1)); break;

        // Conditional jumps based on bit value
        case 0x10: InstrPattern[Reg_PC] = "JBC bit,rel2"; ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0x20: InstrPattern[Reg_PC] = "JB bit,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0x30: InstrPattern[Reg_PC] = "JNB bit,rel2"; ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0x40: InstrPattern[Reg_PC] = "JC rel1";      ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0x50: InstrPattern[Reg_PC] = "JNC rel1";     ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0x60: InstrPattern[Reg_PC] = "JZ rel1";      ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0x70: InstrPattern[Reg_PC] = "JNZ rel1";     ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;

        // Conditional jumps with value comparison
        case 0xB4: InstrPattern[Reg_PC] = "CJNE A,#data,rel2";   ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xB5: InstrPattern[Reg_PC] = "CJNE A,dir,rel2";     ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xB6: InstrPattern[Reg_PC] = "CJNE @R0,#data,rel2"; ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xB7: InstrPattern[Reg_PC] = "CJNE @R1,#data,rel2"; ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xB8: InstrPattern[Reg_PC] = "CJNE R0,#data,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xB9: InstrPattern[Reg_PC] = "CJNE R1,#data,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xBA: InstrPattern[Reg_PC] = "CJNE R2,#data,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xBB: InstrPattern[Reg_PC] = "CJNE R3,#data,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xBC: InstrPattern[Reg_PC] = "CJNE R4,#data,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xBD: InstrPattern[Reg_PC] = "CJNE R5,#data,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xBE: InstrPattern[Reg_PC] = "CJNE R6,#data,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xBF: InstrPattern[Reg_PC] = "CJNE R7,#data,rel2";  ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;

        // Conditional jumps with value decrementation
        case 0xD5: InstrPattern[Reg_PC] = "DJNZ dir,rel2"; ThreadNext(Thr, 3); ThreadAdd(CalcRel(Reg_PC + 2)); break;
        case 0xD8: InstrPattern[Reg_PC] = "DJNZ R0,rel1";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0xD9: InstrPattern[Reg_PC] = "DJNZ R1,rel1";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0xDA: InstrPattern[Reg_PC] = "DJNZ R2,rel1";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0xDB: InstrPattern[Reg_PC] = "DJNZ R3,rel1";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0xDC: InstrPattern[Reg_PC] = "DJNZ R4,rel1";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0xDD: InstrPattern[Reg_PC] = "DJNZ R5,rel1";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0xDE: InstrPattern[Reg_PC] = "DJNZ R6,rel1";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;
        case 0xDF: InstrPattern[Reg_PC] = "DJNZ R7,rel1";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC + 1)); break;

        // Stack instructions
        case 0xC0: InstrPattern[Reg_PC] = "PUSH dir";     ThreadNext(Thr, 2); break;
        case 0xD0: InstrPattern[Reg_PC] = "POP dir";      ThreadNext(Thr, 2); break;

        // Operations on accumulator
        case 0x03: InstrPattern[Reg_PC] = "RR A";         ThreadNext(Thr, 1); break;
        case 0x13: InstrPattern[Reg_PC] = "RRC A";        ThreadNext(Thr, 1); break;
        case 0x23: InstrPattern[Reg_PC] = "RL A";         ThreadNext(Thr, 1); break;
        case 0x33: InstrPattern[Reg_PC] = "RLC A";        ThreadNext(Thr, 1); break;
        case 0xC4: InstrPattern[Reg_PC] = "SWAP A";       ThreadNext(Thr, 1); break;
        case 0xD4: InstrPattern[Reg_PC] = "DA A";         ThreadNext(Thr, 1); break;
        case 0xE4: InstrPattern[Reg_PC] = "CLR A";        ThreadNext(Thr, 1); break;
        case 0xF4: InstrPattern[Reg_PC] = "CPL A";        ThreadNext(Thr, 1); break;

        // Operations on single bit
        case 0xB2: InstrPattern[Reg_PC] = "CPL bit";      ThreadNext(Thr, 2); break;
        case 0xC2: InstrPattern[Reg_PC] = "CLR bit";      ThreadNext(Thr, 2); break;
        case 0xD2: InstrPattern[Reg_PC] = "SETB bit";     ThreadNext(Thr, 2); break;
        case 0xB3: InstrPattern[Reg_PC] = "CPL C";        ThreadNext(Thr, 1); break;
        case 0xC3: InstrPattern[Reg_PC] = "CLR C";        ThreadNext(Thr, 1); break;
        case 0xD3: InstrPattern[Reg_PC] = "SETB C";       ThreadNext(Thr, 1); break;

        // Value incrementation
        case 0xA3: InstrPattern[Reg_PC] = "INC DPTR";     ThreadNext(Thr, 1); break;
        case 0x04: InstrPattern[Reg_PC] = "INC A";        ThreadNext(Thr, 1); break;
        case 0x05: InstrPattern[Reg_PC] = "INC dir";      ThreadNext(Thr, 2); break;
        case 0x06: InstrPattern[Reg_PC] = "INC @R0";      ThreadNext(Thr, 1); break;
        case 0x07: InstrPattern[Reg_PC] = "INC @R1";      ThreadNext(Thr, 1); break;
        case 0x08: InstrPattern[Reg_PC] = "INC R0";       ThreadNext(Thr, 1); break;
        case 0x09: InstrPattern[Reg_PC] = "INC R1";       ThreadNext(Thr, 1); break;
        case 0x0A: InstrPattern[Reg_PC] = "INC R2";       ThreadNext(Thr, 1); break;
        case 0x0B: InstrPattern[Reg_PC] = "INC R3";       ThreadNext(Thr, 1); break;
        case 0x0C: InstrPattern[Reg_PC] = "INC R4";       ThreadNext(Thr, 1); break;
        case 0x0D: InstrPattern[Reg_PC] = "INC R5";       ThreadNext(Thr, 1); break;
        case 0x0E: InstrPattern[Reg_PC] = "INC R6";       ThreadNext(Thr, 1); break;
        case 0x0F: InstrPattern[Reg_PC] = "INC R7";       ThreadNext(Thr, 1); break;

        // Value decrementation
        case 0x14: InstrPattern[Reg_PC] = "DEC A";        ThreadNext(Thr, 1); break;
        case 0x15: InstrPattern[Reg_PC] = "DEC dir";      ThreadNext(Thr, 2); break;
        case 0x16: InstrPattern[Reg_PC] = "DEC @R0";      ThreadNext(Thr, 1); break;
        case 0x17: InstrPattern[Reg_PC] = "DEC @R1";      ThreadNext(Thr, 1); break;
        case 0x18: InstrPattern[Reg_PC] = "DEC R0";       ThreadNext(Thr, 1); break;
        case 0x19: InstrPattern[Reg_PC] = "DEC R1";       ThreadNext(Thr, 1); break;
        case 0x1A: InstrPattern[Reg_PC] = "DEC R2";       ThreadNext(Thr, 1); break;
        case 0x1B: InstrPattern[Reg_PC] = "DEC R3";       ThreadNext(Thr, 1); break;
        case 0x1C: InstrPattern[Reg_PC] = "DEC R4";       ThreadNext(Thr, 1); break;
        case 0x1D: InstrPattern[Reg_PC] = "DEC R5";       ThreadNext(Thr, 1); break;
        case 0x1E: InstrPattern[Reg_PC] = "DEC R6";       ThreadNext(Thr, 1); break;
        case 0x1F: InstrPattern[Reg_PC] = "DEC R7";       ThreadNext(Thr, 1); break;

        // Multiplication and division
        case 0xA4: InstrPattern[Reg_PC] = "MUL AB";       ThreadNext(Thr, 1); break;
        case 0x84: InstrPattern[Reg_PC] = "DIV AB";       ThreadNext(Thr, 1); break;

        // Adding without carry
        case 0x24: InstrPattern[Reg_PC] = "ADD A,#data";  ThreadNext(Thr, 2); break;
        case 0x25: InstrPattern[Reg_PC] = "ADD A,dir";    ThreadNext(Thr, 2); break;
        case 0x26: InstrPattern[Reg_PC] = "ADD A,@R0";    ThreadNext(Thr, 1); break;
        case 0x27: InstrPattern[Reg_PC] = "ADD A,@R1";    ThreadNext(Thr, 1); break;
        case 0x28: InstrPattern[Reg_PC] = "ADD A,R0";     ThreadNext(Thr, 1); break;
        case 0x29: InstrPattern[Reg_PC] = "ADD A,R1";     ThreadNext(Thr, 1); break;
        case 0x2A: InstrPattern[Reg_PC] = "ADD A,R2";     ThreadNext(Thr, 1); break;
        case 0x2B: InstrPattern[Reg_PC] = "ADD A,R3";     ThreadNext(Thr, 1); break;
        case 0x2C: InstrPattern[Reg_PC] = "ADD A,R4";     ThreadNext(Thr, 1); break;
        case 0x2D: InstrPattern[Reg_PC] = "ADD A,R5";     ThreadNext(Thr, 1); break;
        case 0x2E: InstrPattern[Reg_PC] = "ADD A,R6";     ThreadNext(Thr, 1); break;
        case 0x2F: InstrPattern[Reg_PC] = "ADD A,R7";     ThreadNext(Thr, 1); break;

        // Adding with carry
        case 0x34: InstrPattern[Reg_PC] = "ADDC A,#data"; ThreadNext(Thr, 2); break;
        case 0x35: InstrPattern[Reg_PC] = "ADDC A,dir";   ThreadNext(Thr, 2); break;
        case 0x36: InstrPattern[Reg_PC] = "ADDC A,@R0";   ThreadNext(Thr, 1); break;
        case 0x37: InstrPattern[Reg_PC] = "ADDC A,@R1";   ThreadNext(Thr, 1); break;
        case 0x38: InstrPattern[Reg_PC] = "ADDC A,R0";    ThreadNext(Thr, 1); break;
        case 0x39: InstrPattern[Reg_PC] = "ADDC A,R1";    ThreadNext(Thr, 1); break;
        case 0x3A: InstrPattern[Reg_PC] = "ADDC A,R2";    ThreadNext(Thr, 1); break;
        case 0x3B: InstrPattern[Reg_PC] = "ADDC A,R3";    ThreadNext(Thr, 1); break;
        case 0x3C: InstrPattern[Reg_PC] = "ADDC A,R4";    ThreadNext(Thr, 1); break;
        case 0x3D: InstrPattern[Reg_PC] = "ADDC A,R5";    ThreadNext(Thr, 1); break;
        case 0x3E: InstrPattern[Reg_PC] = "ADDC A,R6";    ThreadNext(Thr, 1); break;
        case 0x3F: InstrPattern[Reg_PC] = "ADDC A,R7";    ThreadNext(Thr, 1); break;

        // Subtracting with carry
        case 0x94: InstrPattern[Reg_PC] = "SUBB A,#data"; ThreadNext(Thr, 2); break;
        case 0x95: InstrPattern[Reg_PC] = "SUBB A,dir";   ThreadNext(Thr, 2); break;
        case 0x96: InstrPattern[Reg_PC] = "SUBB A,@R0";   ThreadNext(Thr, 1); break;
        case 0x97: InstrPattern[Reg_PC] = "SUBB A,@R1";   ThreadNext(Thr, 1); break;
        case 0x98: InstrPattern[Reg_PC] = "SUBB A,R0";    ThreadNext(Thr, 1); break;
        case 0x99: InstrPattern[Reg_PC] = "SUBB A,R1";    ThreadNext(Thr, 1); break;
        case 0x9A: InstrPattern[Reg_PC] = "SUBB A,R2";    ThreadNext(Thr, 1); break;
        case 0x9B: InstrPattern[Reg_PC] = "SUBB A,R3";    ThreadNext(Thr, 1); break;
        case 0x9C: InstrPattern[Reg_PC] = "SUBB A,R4";    ThreadNext(Thr, 1); break;
        case 0x9D: InstrPattern[Reg_PC] = "SUBB A,R5";    ThreadNext(Thr, 1); break;
        case 0x9E: InstrPattern[Reg_PC] = "SUBB A,R6";    ThreadNext(Thr, 1); break;
        case 0x9F: InstrPattern[Reg_PC] = "SUBB A,R7";    ThreadNext(Thr, 1); break;

        // Bitwise conjunction
        case 0x82: InstrPattern[Reg_PC] = "ANL C,bit";    ThreadNext(Thr, 2); break;
        case 0xB0: InstrPattern[Reg_PC] = "ANL C,/bit";   ThreadNext(Thr, 2); break;
        case 0x52: InstrPattern[Reg_PC] = "ANL dir,A";    ThreadNext(Thr, 2); break;
        case 0x53: InstrPattern[Reg_PC] = "ANL dir,#dat2"; ThreadNext(Thr, 3); break;
        case 0x54: InstrPattern[Reg_PC] = "ANL A,#data";  ThreadNext(Thr, 2); break;
        case 0x55: InstrPattern[Reg_PC] = "ANL A,dir";    ThreadNext(Thr, 2); break;
        case 0x56: InstrPattern[Reg_PC] = "ANL A,@R0";    ThreadNext(Thr, 1); break;
        case 0x57: InstrPattern[Reg_PC] = "ANL A,@R1";    ThreadNext(Thr, 1); break;
        case 0x58: InstrPattern[Reg_PC] = "ANL A,R0";     ThreadNext(Thr, 1); break;
        case 0x59: InstrPattern[Reg_PC] = "ANL A,R1";     ThreadNext(Thr, 1); break;
        case 0x5A: InstrPattern[Reg_PC] = "ANL A,R2";     ThreadNext(Thr, 1); break;
        case 0x5B: InstrPattern[Reg_PC] = "ANL A,R3";     ThreadNext(Thr, 1); break;
        case 0x5C: InstrPattern[Reg_PC] = "ANL A,R4";     ThreadNext(Thr, 1); break;
        case 0x5D: InstrPattern[Reg_PC] = "ANL A,R5";     ThreadNext(Thr, 1); break;
        case 0x5E: InstrPattern[Reg_PC] = "ANL A,R6";     ThreadNext(Thr, 1); break;
        case 0x5F: InstrPattern[Reg_PC] = "ANL A,R7";     ThreadNext(Thr, 1); break;

        // Bitwise disjunction
        case 0x72: InstrPattern[Reg_PC] = "ORL C,bit";    ThreadNext(Thr, 2); break;
        case 0xA0: InstrPattern[Reg_PC] = "ORL C,/bit";   ThreadNext(Thr, 2); break;
        case 0x42: InstrPattern[Reg_PC] = "ORL dir,A";    ThreadNext(Thr, 2); break;
        case 0x43: InstrPattern[Reg_PC] = "ORL dir,#dat2"; ThreadNext(Thr, 3); break;
        case 0x44: InstrPattern[Reg_PC] = "ORL A,#data";  ThreadNext(Thr, 2); break;
        case 0x45: InstrPattern[Reg_PC] = "ORL A,dir";    ThreadNext(Thr, 2); break;
        case 0x46: InstrPattern[Reg_PC] = "ORL A,@R0";    ThreadNext(Thr, 1); break;
        case 0x47: InstrPattern[Reg_PC] = "ORL A,@R1";    ThreadNext(Thr, 1); break;
        case 0x48: InstrPattern[Reg_PC] = "ORL A,R0";     ThreadNext(Thr, 1); break;
        case 0x49: InstrPattern[Reg_PC] = "ORL A,R1";     ThreadNext(Thr, 1); break;
        case 0x4A: InstrPattern[Reg_PC] = "ORL A,R2";     ThreadNext(Thr, 1); break;
        case 0x4B: InstrPattern[Reg_PC] = "ORL A,R3";     ThreadNext(Thr, 1); break;
        case 0x4C: InstrPattern[Reg_PC] = "ORL A,R4";     ThreadNext(Thr, 1); break;
        case 0x4D: InstrPattern[Reg_PC] = "ORL A,R5";     ThreadNext(Thr, 1); break;
        case 0x4E: InstrPattern[Reg_PC] = "ORL A,R6";     ThreadNext(Thr, 1); break;
        case 0x4F: InstrPattern[Reg_PC] = "ORL A,R7";     ThreadNext(Thr, 1); break;

        // Bitwise exclusive disjunction
        case 0x62: InstrPattern[Reg_PC] = "XRL dir,A";    ThreadNext(Thr, 2); break;
        case 0x63: InstrPattern[Reg_PC] = "XRL dir,#dat2"; ThreadNext(Thr, 3); break;
        case 0x64: InstrPattern[Reg_PC] = "XRL A,#data";  ThreadNext(Thr, 2); break;
        case 0x65: InstrPattern[Reg_PC] = "XRL A,dir";    ThreadNext(Thr, 2); break;
        case 0x66: InstrPattern[Reg_PC] = "XRL A,@R0";    ThreadNext(Thr, 1); break;
        case 0x67: InstrPattern[Reg_PC] = "XRL A,@R1";    ThreadNext(Thr, 1); break;
        case 0x68: InstrPattern[Reg_PC] = "XRL A,R0";     ThreadNext(Thr, 1); break;
        case 0x69: InstrPattern[Reg_PC] = "XRL A,R1";     ThreadNext(Thr, 1); break;
        case 0x6A: InstrPattern[Reg_PC] = "XRL A,R2";     ThreadNext(Thr, 1); break;
        case 0x6B: InstrPattern[Reg_PC] = "XRL A,R3";     ThreadNext(Thr, 1); break;
        case 0x6C: InstrPattern[Reg_PC] = "XRL A,R4";     ThreadNext(Thr, 1); break;
        case 0x6D: InstrPattern[Reg_PC] = "XRL A,R5";     ThreadNext(Thr, 1); break;
        case 0x6E: InstrPattern[Reg_PC] = "XRL A,R6";     ThreadNext(Thr, 1); break;
        case 0x6F: InstrPattern[Reg_PC] = "XRL A,R7";     ThreadNext(Thr, 1); break;

        // Swapping four least significant bits
        case 0xD6: InstrPattern[Reg_PC] = "XCHD A,@R0";   ThreadNext(Thr, 1); break;
        case 0xD7: InstrPattern[Reg_PC] = "XCHD A,@R1";   ThreadNext(Thr, 1); break;

        // Swapping accumulator with register
        case 0xC5: InstrPattern[Reg_PC] = "XCH A,dir";    ThreadNext(Thr, 2); break;
        case 0xC6: InstrPattern[Reg_PC] = "XCH A,@R0";    ThreadNext(Thr, 1); break;
        case 0xC7: InstrPattern[Reg_PC] = "XCH A,@R1";    ThreadNext(Thr, 1); break;
        case 0xC8: InstrPattern[Reg_PC] = "XCH A,R0";     ThreadNext(Thr, 1); break;
        case 0xC9: InstrPattern[Reg_PC] = "XCH A,R1";     ThreadNext(Thr, 1); break;
        case 0xCA: InstrPattern[Reg_PC] = "XCH A,R2";     ThreadNext(Thr, 1); break;
        case 0xCB: InstrPattern[Reg_PC] = "XCH A,R3";     ThreadNext(Thr, 1); break;
        case 0xCC: InstrPattern[Reg_PC] = "XCH A,R4";     ThreadNext(Thr, 1); break;
        case 0xCD: InstrPattern[Reg_PC] = "XCH A,R5";     ThreadNext(Thr, 1); break;
        case 0xCE: InstrPattern[Reg_PC] = "XCH A,R6";     ThreadNext(Thr, 1); break;
        case 0xCF: InstrPattern[Reg_PC] = "XCH A,R7";     ThreadNext(Thr, 1); break;

        // Writing constant value
        case 0x74: InstrPattern[Reg_PC] = "MOV A,#data";  ThreadNext(Thr, 2); break;
        case 0x75: InstrPattern[Reg_PC] = "MOV dir,#dat2"; ThreadNext(Thr, 3); break;
        case 0x76: InstrPattern[Reg_PC] = "MOV @R0,#data"; ThreadNext(Thr, 2); break;
        case 0x77: InstrPattern[Reg_PC] = "MOV @R1,#data"; ThreadNext(Thr, 2); break;
        case 0x78: InstrPattern[Reg_PC] = "MOV R0,#data"; ThreadNext(Thr, 2); break;
        case 0x79: InstrPattern[Reg_PC] = "MOV R1,#data"; ThreadNext(Thr, 2); break;
        case 0x7A: InstrPattern[Reg_PC] = "MOV R2,#data"; ThreadNext(Thr, 2); break;
        case 0x7B: InstrPattern[Reg_PC] = "MOV R3,#data"; ThreadNext(Thr, 2); break;
        case 0x7C: InstrPattern[Reg_PC] = "MOV R4,#data"; ThreadNext(Thr, 2); break;
        case 0x7D: InstrPattern[Reg_PC] = "MOV R5,#data"; ThreadNext(Thr, 2); break;
        case 0x7E: InstrPattern[Reg_PC] = "MOV R6,#data"; ThreadNext(Thr, 2); break;
        case 0x7F: InstrPattern[Reg_PC] = "MOV R7,#data"; ThreadNext(Thr, 2); break;

        // Bit copying
        case 0x92: InstrPattern[Reg_PC] = "MOV bit,C";    ThreadNext(Thr, 2); break;
        case 0xA2: InstrPattern[Reg_PC] = "MOV C,bit";    ThreadNext(Thr, 2); break;

        // Copying value in internal memory
        case 0x85: InstrPattern[Reg_PC] = "MOV dir,dir2"; ThreadNext(Thr, 3); break;
        case 0x86: InstrPattern[Reg_PC] = "MOV dir,@R0";  ThreadNext(Thr, 2); break;
        case 0x87: InstrPattern[Reg_PC] = "MOV dir,@R1";  ThreadNext(Thr, 2); break;
        case 0x88: InstrPattern[Reg_PC] = "MOV dir,R0";   ThreadNext(Thr, 2); break;
        case 0x89: InstrPattern[Reg_PC] = "MOV dir,R1";   ThreadNext(Thr, 2); break;
        case 0x8A: InstrPattern[Reg_PC] = "MOV dir,R2";   ThreadNext(Thr, 2); break;
        case 0x8B: InstrPattern[Reg_PC] = "MOV dir,R3";   ThreadNext(Thr, 2); break;
        case 0x8C: InstrPattern[Reg_PC] = "MOV dir,R4";   ThreadNext(Thr, 2); break;
        case 0x8D: InstrPattern[Reg_PC] = "MOV dir,R5";   ThreadNext(Thr, 2); break;
        case 0x8E: InstrPattern[Reg_PC] = "MOV dir,R6";   ThreadNext(Thr, 2); break;
        case 0x8F: InstrPattern[Reg_PC] = "MOV dir,R7";   ThreadNext(Thr, 2); break;
        case 0xA6: InstrPattern[Reg_PC] = "MOV @R0,dir";  ThreadNext(Thr, 2); break;
        case 0xA7: InstrPattern[Reg_PC] = "MOV @R1,dir";  ThreadNext(Thr, 2); break;
        case 0xA8: InstrPattern[Reg_PC] = "MOV R0,dir";   ThreadNext(Thr, 2); break;
        case 0xA9: InstrPattern[Reg_PC] = "MOV R1,dir";   ThreadNext(Thr, 2); break;
        case 0xAA: InstrPattern[Reg_PC] = "MOV R2,dir";   ThreadNext(Thr, 2); break;
        case 0xAB: InstrPattern[Reg_PC] = "MOV R3,dir";   ThreadNext(Thr, 2); break;
        case 0xAC: InstrPattern[Reg_PC] = "MOV R4,dir";   ThreadNext(Thr, 2); break;
        case 0xAD: InstrPattern[Reg_PC] = "MOV R5,dir";   ThreadNext(Thr, 2); break;
        case 0xAE: InstrPattern[Reg_PC] = "MOV R6,dir";   ThreadNext(Thr, 2); break;
        case 0xAF: InstrPattern[Reg_PC] = "MOV R7,dir";   ThreadNext(Thr, 2); break;
        case 0xE5: InstrPattern[Reg_PC] = "MOV A,dir";    ThreadNext(Thr, 2); break;
        case 0xE6: InstrPattern[Reg_PC] = "MOV A,@R0";    ThreadNext(Thr, 1); break;
        case 0xE7: InstrPattern[Reg_PC] = "MOV A,@R1";    ThreadNext(Thr, 1); break;
        case 0xE8: InstrPattern[Reg_PC] = "MOV A,R0";     ThreadNext(Thr, 1); break;
        case 0xE9: InstrPattern[Reg_PC] = "MOV A,R1";     ThreadNext(Thr, 1); break;
        case 0xEA: InstrPattern[Reg_PC] = "MOV A,R2";     ThreadNext(Thr, 1); break;
        case 0xEB: InstrPattern[Reg_PC] = "MOV A,R3";     ThreadNext(Thr, 1); break;
        case 0xEC: InstrPattern[Reg_PC] = "MOV A,R4";     ThreadNext(Thr, 1); break;
        case 0xED: InstrPattern[Reg_PC] = "MOV A,R5";     ThreadNext(Thr, 1); break;
        case 0xEE: InstrPattern[Reg_PC] = "MOV A,R6";     ThreadNext(Thr, 1); break;
        case 0xEF: InstrPattern[Reg_PC] = "MOV A,R7";     ThreadNext(Thr, 1); break;
        case 0xF5: InstrPattern[Reg_PC] = "MOV dir,A";    ThreadNext(Thr, 2); break;
        case 0xF6: InstrPattern[Reg_PC] = "MOV @R0,A";    ThreadNext(Thr, 1); break;
        case 0xF7: InstrPattern[Reg_PC] = "MOV @R1,A";    ThreadNext(Thr, 1); break;
        case 0xF8: InstrPattern[Reg_PC] = "MOV R0,A";     ThreadNext(Thr, 1); break;
        case 0xF9: InstrPattern[Reg_PC] = "MOV R1,A";     ThreadNext(Thr, 1); break;
        case 0xFA: InstrPattern[Reg_PC] = "MOV R2,A";     ThreadNext(Thr, 1); break;
        case 0xFB: InstrPattern[Reg_PC] = "MOV R3,A";     ThreadNext(Thr, 1); break;
        case 0xFC: InstrPattern[Reg_PC] = "MOV R4,A";     ThreadNext(Thr, 1); break;
        case 0xFD: InstrPattern[Reg_PC] = "MOV R5,A";     ThreadNext(Thr, 1); break;
        case 0xFE: InstrPattern[Reg_PC] = "MOV R6,A";     ThreadNext(Thr, 1); break;
        case 0xFF: InstrPattern[Reg_PC] = "MOV R7,A";     ThreadNext(Thr, 1); break;

        // Reading code memory
        case 0x83: InstrPattern[Reg_PC] = "MOVC A,@A+PC"; ThreadNext(Thr, 1); break;
        case 0x93: InstrPattern[Reg_PC] = "MOVC A,@A+DPTR"; ThreadNext(Thr, 1); break;

        // Setting external address
        case 0x90: InstrPattern[Reg_PC] = "MOV DPTR,#data16"; ThreadNext(Thr, 3); break;

        // Reading and writing external memory
        case 0xE0: InstrPattern[Reg_PC] = "MOVX A,@DPTR"; ThreadNext(Thr, 1); break;
        case 0XE2: InstrPattern[Reg_PC] = "MOVX A,@R0";   ThreadNext(Thr, 1); break;
        case 0xE3: InstrPattern[Reg_PC] = "MOVX A,@R1";   ThreadNext(Thr, 1); break;
        case 0xF0: InstrPattern[Reg_PC] = "MOVX @DPTR,A"; ThreadNext(Thr, 1); break;
        case 0xF2: InstrPattern[Reg_PC] = "MOVX @R0,A";   ThreadNext(Thr, 1); break;
        case 0xF3: InstrPattern[Reg_PC] = "MOVX @R1,A";   ThreadNext(Thr, 1); break;
    }
}

int ScriptDecompileMCS51::CalcAJMP(int Reg_PC, int Offset)
{
    Reg_PC++;
    int Addr = MemProg[Reg_PC];
    return (Reg_PC & 63488) + Addr + Offset;
}

int ScriptDecompileMCS51::CalcAddr(int Reg_PC)
{
    int AddrH = MemProg[Reg_PC + 1];
    int AddrL = MemProg[Reg_PC + 2];
    return (AddrH << 8) + AddrL;
}

int ScriptDecompileMCS51::CalcRel(int Reg_PC)
{
    int Data = MemProg[Reg_PC];
    if (Data & 0b10000000)
    {
        return Reg_PC + Data - 256 + 1;
    }
    else
    {
        return Reg_PC + Data + 1;
    }
}

std::string ScriptDecompileMCS51::InstructionName(int Addr)
{
    std::string Name = InstrPattern[Addr];
    Name = StringFindReplace(Name, "rel1", LabelPrefix + Hex::IntToHex16(CalcRel(Addr + 1)));
    Name = StringFindReplace(Name, "rel2", LabelPrefix + Hex::IntToHex16(CalcRel(Addr + 2)));
    Name = StringFindReplace(Name, "addr16", LabelPrefix + Hex::IntToHex16(CalcAddr(Addr)));
    Name = StringFindReplace(Name, "#data16", "#" + Hex::IntToHex16(CalcAddr(Addr)) + "h");
    Name = StringFindReplace(Name, "#dat2", "#" + Hex::IntToHex8(MemProg[Addr + 2]) + "h");
    Name = StringFindReplace(Name, "#data", "#" + Hex::IntToHex8(MemProg[Addr + 1]) + "h");
    Name = StringFindReplace(Name, "bit", Hex::IntToHex8(MemProg[Addr + 1]) + "h");
    Name = StringFindReplace(Name, "dir2", Hex::IntToHex8(MemProg[Addr + 2]) + "h");
    Name = StringFindReplace(Name, "dir", Hex::IntToHex8(MemProg[Addr + 1]) + "h");

    Name = StringFindReplace(Name, "(P0)", LabelPrefix + Hex::IntToHex16(CalcAJMP(Addr,    0)));
    Name = StringFindReplace(Name, "(P1)", LabelPrefix + Hex::IntToHex16(CalcAJMP(Addr,  256)));
    Name = StringFindReplace(Name, "(P2)", LabelPrefix + Hex::IntToHex16(CalcAJMP(Addr,  512)));
    Name = StringFindReplace(Name, "(P3)", LabelPrefix + Hex::IntToHex16(CalcAJMP(Addr,  768)));
    Name = StringFindReplace(Name, "(P4)", LabelPrefix + Hex::IntToHex16(CalcAJMP(Addr, 1024)));
    Name = StringFindReplace(Name, "(P5)", LabelPrefix + Hex::IntToHex16(CalcAJMP(Addr, 1280)));
    Name = StringFindReplace(Name, "(P6)", LabelPrefix + Hex::IntToHex16(CalcAJMP(Addr, 1536)));
    Name = StringFindReplace(Name, "(P7)", LabelPrefix + Hex::IntToHex16(CalcAJMP(Addr, 1792)));

    return Name;
}

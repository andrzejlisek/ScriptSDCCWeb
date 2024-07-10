#include "scriptdecompilez180.h"

ScriptDecompileZ180::ScriptDecompileZ180()
{

}

void ScriptDecompileZ180::ProcessOpcode(int Thr)
{
    int Reg_PC = ProgramCounterThreads[Thr];
    uchar OpCode = MemProg[ProgramCounterThreads[Thr]];
    switch (OpCode)
    {
        // Additional instructions
        case 0x00: InstrPattern[Reg_PC] = "NOP";         ThreadNext(Thr, 1); break;
        case 0x76: InstrPattern[Reg_PC] = "HALT";        ThreadNext(Thr, 1); break;
        case 0x27: InstrPattern[Reg_PC] = "DA A";        ThreadNext(Thr, 1); break;

        // Swapping primary and secondary registers
        case 0x08: InstrPattern[Reg_PC] = "EX AF, AF'";  ThreadNext(Thr, 1); break;
        case 0xD9: InstrPattern[Reg_PC] = "EXX";         ThreadNext(Thr, 1); break;
        case 0xE3: InstrPattern[Reg_PC] = "EX (SP), HL"; ThreadNext(Thr, 1); break;
        case 0xEB: InstrPattern[Reg_PC] = "EX DE, HL";   ThreadNext(Thr, 1); break;

        // Enabling and disabling interrupts
        case 0xF3: InstrPattern[Reg_PC] = "DI";          ThreadNext(Thr, 1); break;
        case 0xFB: InstrPattern[Reg_PC] = "EI";          ThreadNext(Thr, 1); break;

        // Writing constant value
        case 0x01: InstrPattern[Reg_PC] = "LD BC, NN";   ThreadNext(Thr, 3); break;
        case 0x11: InstrPattern[Reg_PC] = "LD DE, NN";   ThreadNext(Thr, 3); break;
        case 0x21: InstrPattern[Reg_PC] = "LD HL, NN";   ThreadNext(Thr, 3); break;
        case 0x31: InstrPattern[Reg_PC] = "LD SP, NN";   ThreadNext(Thr, 3); break;
        case 0x22: InstrPattern[Reg_PC] = "LD (NN), HL"; ThreadNext(Thr, 3); break;
        case 0x02: InstrPattern[Reg_PC] = "LD (BC), A";  ThreadNext(Thr, 1); break;
        case 0x12: InstrPattern[Reg_PC] = "LD (DE), A";  ThreadNext(Thr, 1); break;
        case 0x32: InstrPattern[Reg_PC] = "LD (NN), A";  ThreadNext(Thr, 3); break;
        case 0x3A: InstrPattern[Reg_PC] = "LD A, (NN)";  ThreadNext(Thr, 3); break;
        case 0x36: InstrPattern[Reg_PC] = "LD (HL), n";  ThreadNext(Thr, 2); break;
        case 0x0A: InstrPattern[Reg_PC] = "LD A, (BC)";  ThreadNext(Thr, 1); break;
        case 0x1A: InstrPattern[Reg_PC] = "LD A, (DE)";  ThreadNext(Thr, 1); break;
        case 0x06: InstrPattern[Reg_PC] = "LD B, n";     ThreadNext(Thr, 2); break;
        case 0x0E: InstrPattern[Reg_PC] = "LD C, n";     ThreadNext(Thr, 2); break;
        case 0x16: InstrPattern[Reg_PC] = "LD D, n";     ThreadNext(Thr, 2); break;
        case 0x1E: InstrPattern[Reg_PC] = "LD E, n";     ThreadNext(Thr, 2); break;
        case 0x26: InstrPattern[Reg_PC] = "LD H, n";     ThreadNext(Thr, 2); break;
        case 0x2A: InstrPattern[Reg_PC] = "LD HL, (NN)"; ThreadNext(Thr, 3); break;
        case 0x2E: InstrPattern[Reg_PC] = "LD L, n";     ThreadNext(Thr, 2); break;
        case 0x3E: InstrPattern[Reg_PC] = "LD A, n";     ThreadNext(Thr, 2); break;
        case 0xF9: InstrPattern[Reg_PC] = "LD SP, HL";   ThreadNext(Thr, 1); break;

        // Bit shifting and rotating
        case 0x07: InstrPattern[Reg_PC] = "RLC A";       ThreadNext(Thr, 1); break;
        case 0x0F: InstrPattern[Reg_PC] = "RRC A";       ThreadNext(Thr, 1); break;
        case 0x17: InstrPattern[Reg_PC] = "RL A";        ThreadNext(Thr, 1); break;
        case 0x1F: InstrPattern[Reg_PC] = "RR A";        ThreadNext(Thr, 1); break;

        // Value incrementation and decrementation
        case 0x03: InstrPattern[Reg_PC] = "INC BC";      ThreadNext(Thr, 1); break;
        case 0x13: InstrPattern[Reg_PC] = "INC DE";      ThreadNext(Thr, 1); break;
        case 0x23: InstrPattern[Reg_PC] = "INC HL";      ThreadNext(Thr, 1); break;
        case 0x33: InstrPattern[Reg_PC] = "INC SP";      ThreadNext(Thr, 1); break;
        case 0x0B: InstrPattern[Reg_PC] = "DEC BC";      ThreadNext(Thr, 1); break;
        case 0x1B: InstrPattern[Reg_PC] = "DEC DE";      ThreadNext(Thr, 1); break;
        case 0x2B: InstrPattern[Reg_PC] = "DEC HL";      ThreadNext(Thr, 1); break;
        case 0x3B: InstrPattern[Reg_PC] = "DEC SP";      ThreadNext(Thr, 1); break;
        case 0x04: InstrPattern[Reg_PC] = "INC B";       ThreadNext(Thr, 1); break;
        case 0x05: InstrPattern[Reg_PC] = "DEC B";       ThreadNext(Thr, 1); break;
        case 0x0C: InstrPattern[Reg_PC] = "INC C";       ThreadNext(Thr, 1); break;
        case 0x0D: InstrPattern[Reg_PC] = "DEC C";       ThreadNext(Thr, 1); break;
        case 0x14: InstrPattern[Reg_PC] = "INC D";       ThreadNext(Thr, 1); break;
        case 0x15: InstrPattern[Reg_PC] = "DEC D";       ThreadNext(Thr, 1); break;
        case 0x1C: InstrPattern[Reg_PC] = "INC E";       ThreadNext(Thr, 1); break;
        case 0x1D: InstrPattern[Reg_PC] = "DEC E";       ThreadNext(Thr, 1); break;
        case 0x24: InstrPattern[Reg_PC] = "INC H";       ThreadNext(Thr, 1); break;
        case 0x25: InstrPattern[Reg_PC] = "DEC H";       ThreadNext(Thr, 1); break;
        case 0x2C: InstrPattern[Reg_PC] = "INC L";       ThreadNext(Thr, 1); break;
        case 0x2D: InstrPattern[Reg_PC] = "DEC L";       ThreadNext(Thr, 1); break;
        case 0x34: InstrPattern[Reg_PC] = "INC (HL)";    ThreadNext(Thr, 1); break;
        case 0x35: InstrPattern[Reg_PC] = "DEC (HL)";    ThreadNext(Thr, 1); break;
        case 0x3C: InstrPattern[Reg_PC] = "INC A";       ThreadNext(Thr, 1); break;
        case 0x3D: InstrPattern[Reg_PC] = "DEC A";       ThreadNext(Thr, 1); break;

        // Adding and subtracting
        case 0x09: InstrPattern[Reg_PC] = "ADD HL, BC";  ThreadNext(Thr, 1); break;
        case 0x19: InstrPattern[Reg_PC] = "ADD HL, DE";  ThreadNext(Thr, 1); break;
        case 0x29: InstrPattern[Reg_PC] = "ADD HL, HL";  ThreadNext(Thr, 1); break;
        case 0x39: InstrPattern[Reg_PC] = "ADD HL, SP";  ThreadNext(Thr, 1); break;
        case 0xC6: InstrPattern[Reg_PC] = "ADD A, n";    ThreadNext(Thr, 2); break;
        case 0xCE: InstrPattern[Reg_PC] = "ADC A, n";    ThreadNext(Thr, 2); break;
        case 0xD6: InstrPattern[Reg_PC] = "SUB n";       ThreadNext(Thr, 2); break;
        case 0xDE: InstrPattern[Reg_PC] = "SBC A, n";    ThreadNext(Thr, 2); break;

        // Logical operations
        case 0x2F: InstrPattern[Reg_PC] = "CPL";         ThreadNext(Thr, 1); break;
        case 0x37: InstrPattern[Reg_PC] = "SCF";         ThreadNext(Thr, 1); break;
        case 0x3F: InstrPattern[Reg_PC] = "CCF";         ThreadNext(Thr, 1); break;
        case 0xE6: InstrPattern[Reg_PC] = "AND n";       ThreadNext(Thr, 2); break;
        case 0xEE: InstrPattern[Reg_PC] = "XOR n";       ThreadNext(Thr, 2); break;
        case 0xF6: InstrPattern[Reg_PC] = "OR n";        ThreadNext(Thr, 2); break;
        case 0xFE: InstrPattern[Reg_PC] = "CP n";        ThreadNext(Thr, 2); break;

        // Jumps
        case 0x10: InstrPattern[Reg_PC] = "DJNZ RelN";   ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC)); break;
        case 0x18: InstrPattern[Reg_PC] = "JR RelN";     ThreadNext(Thr, -2); ThreadAdd(CalcRel(Reg_PC)); break;
        case 0x20: InstrPattern[Reg_PC] = "JR NZ, RelN"; ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC)); break;
        case 0x28: InstrPattern[Reg_PC] = "JR Z, RelN";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC)); break;
        case 0x30: InstrPattern[Reg_PC] = "JR NC, RelN"; ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC)); break;
        case 0x38: InstrPattern[Reg_PC] = "JR C, RelN";  ThreadNext(Thr, 2); ThreadAdd(CalcRel(Reg_PC)); break;
        case 0xC3: InstrPattern[Reg_PC] = "JP NN_";      ThreadNext(Thr, -3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xE9: InstrPattern[Reg_PC] = "JP (HL)";     ThreadNext(Thr, -1); ThreadAddVector(Reg_PC); break;
        case 0xC2: InstrPattern[Reg_PC] = "JP NZ, NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xCA: InstrPattern[Reg_PC] = "JP Z, NN_";   ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xD2: InstrPattern[Reg_PC] = "JP NC, NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xDA: InstrPattern[Reg_PC] = "JP C, NN_";   ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xE2: InstrPattern[Reg_PC] = "JP PO, NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xEA: InstrPattern[Reg_PC] = "JP PE, NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xF2: InstrPattern[Reg_PC] = "JP P, NN_";   ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xFA: InstrPattern[Reg_PC] = "JP M, NN_";   ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;

        // Instructions on standard registers - copying value
        case 0x40: InstrPattern[Reg_PC] = "LD B, B";     ThreadNext(Thr, 1); break;
        case 0x41: InstrPattern[Reg_PC] = "LD B, C";     ThreadNext(Thr, 1); break;
        case 0x42: InstrPattern[Reg_PC] = "LD B, D";     ThreadNext(Thr, 1); break;
        case 0x43: InstrPattern[Reg_PC] = "LD B, E";     ThreadNext(Thr, 1); break;
        case 0x44: InstrPattern[Reg_PC] = "LD B, H";     ThreadNext(Thr, 1); break;
        case 0x45: InstrPattern[Reg_PC] = "LD B, L";     ThreadNext(Thr, 1); break;
        case 0x46: InstrPattern[Reg_PC] = "LD B, (HL)";  ThreadNext(Thr, 1); break;
        case 0x47: InstrPattern[Reg_PC] = "LD B, A";     ThreadNext(Thr, 1); break;
        case 0x48: InstrPattern[Reg_PC] = "LD C, B";     ThreadNext(Thr, 1); break;
        case 0x49: InstrPattern[Reg_PC] = "LD C, C";     ThreadNext(Thr, 1); break;
        case 0x4A: InstrPattern[Reg_PC] = "LD C, D";     ThreadNext(Thr, 1); break;
        case 0x4B: InstrPattern[Reg_PC] = "LD C, E";     ThreadNext(Thr, 1); break;
        case 0x4C: InstrPattern[Reg_PC] = "LD C, H";     ThreadNext(Thr, 1); break;
        case 0x4D: InstrPattern[Reg_PC] = "LD C, L";     ThreadNext(Thr, 1); break;
        case 0x4E: InstrPattern[Reg_PC] = "LD C, (HL)";  ThreadNext(Thr, 1); break;
        case 0x4F: InstrPattern[Reg_PC] = "LD C, A";     ThreadNext(Thr, 1); break;
        case 0x50: InstrPattern[Reg_PC] = "LD D, B";     ThreadNext(Thr, 1); break;
        case 0x51: InstrPattern[Reg_PC] = "LD D, C";     ThreadNext(Thr, 1); break;
        case 0x52: InstrPattern[Reg_PC] = "LD D, D";     ThreadNext(Thr, 1); break;
        case 0x53: InstrPattern[Reg_PC] = "LD D, E";     ThreadNext(Thr, 1); break;
        case 0x54: InstrPattern[Reg_PC] = "LD D, H";     ThreadNext(Thr, 1); break;
        case 0x55: InstrPattern[Reg_PC] = "LD D, L";     ThreadNext(Thr, 1); break;
        case 0x56: InstrPattern[Reg_PC] = "LD D, (HL)";  ThreadNext(Thr, 1); break;
        case 0x57: InstrPattern[Reg_PC] = "LD D, A";     ThreadNext(Thr, 1); break;
        case 0x58: InstrPattern[Reg_PC] = "LD E, B";     ThreadNext(Thr, 1); break;
        case 0x59: InstrPattern[Reg_PC] = "LD E, C";     ThreadNext(Thr, 1); break;
        case 0x5A: InstrPattern[Reg_PC] = "LD E, D";     ThreadNext(Thr, 1); break;
        case 0x5B: InstrPattern[Reg_PC] = "LD E, E";     ThreadNext(Thr, 1); break;
        case 0x5C: InstrPattern[Reg_PC] = "LD E, H";     ThreadNext(Thr, 1); break;
        case 0x5D: InstrPattern[Reg_PC] = "LD E, L";     ThreadNext(Thr, 1); break;
        case 0x5E: InstrPattern[Reg_PC] = "LD E, (HL)";  ThreadNext(Thr, 1); break;
        case 0x5F: InstrPattern[Reg_PC] = "LD E, A";     ThreadNext(Thr, 1); break;
        case 0x60: InstrPattern[Reg_PC] = "LD H, B";     ThreadNext(Thr, 1); break;
        case 0x61: InstrPattern[Reg_PC] = "LD H, C";     ThreadNext(Thr, 1); break;
        case 0x62: InstrPattern[Reg_PC] = "LD H, D";     ThreadNext(Thr, 1); break;
        case 0x63: InstrPattern[Reg_PC] = "LD H, E";     ThreadNext(Thr, 1); break;
        case 0x64: InstrPattern[Reg_PC] = "LD H, H";     ThreadNext(Thr, 1); break;
        case 0x65: InstrPattern[Reg_PC] = "LD H, L";     ThreadNext(Thr, 1); break;
        case 0x66: InstrPattern[Reg_PC] = "LD H, (HL)";  ThreadNext(Thr, 1); break;
        case 0x67: InstrPattern[Reg_PC] = "LD H, A";     ThreadNext(Thr, 1); break;
        case 0x68: InstrPattern[Reg_PC] = "LD L, B";     ThreadNext(Thr, 1); break;
        case 0x69: InstrPattern[Reg_PC] = "LD L, C";     ThreadNext(Thr, 1); break;
        case 0x6A: InstrPattern[Reg_PC] = "LD L, D";     ThreadNext(Thr, 1); break;
        case 0x6B: InstrPattern[Reg_PC] = "LD L, E";     ThreadNext(Thr, 1); break;
        case 0x6C: InstrPattern[Reg_PC] = "LD L, H";     ThreadNext(Thr, 1); break;
        case 0x6D: InstrPattern[Reg_PC] = "LD L, L";     ThreadNext(Thr, 1); break;
        case 0x6E: InstrPattern[Reg_PC] = "LD L, (HL)";  ThreadNext(Thr, 1); break;
        case 0x6F: InstrPattern[Reg_PC] = "LD L, A";     ThreadNext(Thr, 1); break;
        case 0x70: InstrPattern[Reg_PC] = "LD (HL), B";  ThreadNext(Thr, 1); break;
        case 0x71: InstrPattern[Reg_PC] = "LD (HL), C";  ThreadNext(Thr, 1); break;
        case 0x72: InstrPattern[Reg_PC] = "LD (HL), D";  ThreadNext(Thr, 1); break;
        case 0x73: InstrPattern[Reg_PC] = "LD (HL), E";  ThreadNext(Thr, 1); break;
        case 0x74: InstrPattern[Reg_PC] = "LD (HL), H";  ThreadNext(Thr, 1); break;
        case 0x75: InstrPattern[Reg_PC] = "LD (HL), L";  ThreadNext(Thr, 1); break;
        case 0x77: InstrPattern[Reg_PC] = "LD (HL), A";  ThreadNext(Thr, 1); break;
        case 0x78: InstrPattern[Reg_PC] = "LD A, B";     ThreadNext(Thr, 1); break;
        case 0x79: InstrPattern[Reg_PC] = "LD A, C";     ThreadNext(Thr, 1); break;
        case 0x7A: InstrPattern[Reg_PC] = "LD A, D";     ThreadNext(Thr, 1); break;
        case 0x7B: InstrPattern[Reg_PC] = "LD A, E";     ThreadNext(Thr, 1); break;
        case 0x7C: InstrPattern[Reg_PC] = "LD A, H";     ThreadNext(Thr, 1); break;
        case 0x7D: InstrPattern[Reg_PC] = "LD A, L";     ThreadNext(Thr, 1); break;
        case 0x7E: InstrPattern[Reg_PC] = "LD A, (HL)";  ThreadNext(Thr, 1); break;
        case 0x7F: InstrPattern[Reg_PC] = "LD A, A";     ThreadNext(Thr, 1); break;

        // Instructions on standard registers - mathematical and logical operations
        case 0x80: InstrPattern[Reg_PC] = "ADD A, B";    ThreadNext(Thr, 1); break;
        case 0x81: InstrPattern[Reg_PC] = "ADD A, C";    ThreadNext(Thr, 1); break;
        case 0x82: InstrPattern[Reg_PC] = "ADD A, D";    ThreadNext(Thr, 1); break;
        case 0x83: InstrPattern[Reg_PC] = "ADD A, E";    ThreadNext(Thr, 1); break;
        case 0x84: InstrPattern[Reg_PC] = "ADD A, H";    ThreadNext(Thr, 1); break;
        case 0x85: InstrPattern[Reg_PC] = "ADD A, L";    ThreadNext(Thr, 1); break;
        case 0x86: InstrPattern[Reg_PC] = "ADD A, (HL)"; ThreadNext(Thr, 1); break;
        case 0x87: InstrPattern[Reg_PC] = "ADD A, A";    ThreadNext(Thr, 1); break;
        case 0x88: InstrPattern[Reg_PC] = "ADC A, B";    ThreadNext(Thr, 1); break;
        case 0x89: InstrPattern[Reg_PC] = "ADC A, C";    ThreadNext(Thr, 1); break;
        case 0x8A: InstrPattern[Reg_PC] = "ADC A, D";    ThreadNext(Thr, 1); break;
        case 0x8B: InstrPattern[Reg_PC] = "ADC A, E";    ThreadNext(Thr, 1); break;
        case 0x8C: InstrPattern[Reg_PC] = "ADC A, H";    ThreadNext(Thr, 1); break;
        case 0x8D: InstrPattern[Reg_PC] = "ADC A, L";    ThreadNext(Thr, 1); break;
        case 0x8E: InstrPattern[Reg_PC] = "ADC A, (HL)"; ThreadNext(Thr, 1); break;
        case 0x8F: InstrPattern[Reg_PC] = "ADC A, A";    ThreadNext(Thr, 1); break;
        case 0x90: InstrPattern[Reg_PC] = "SUB B";       ThreadNext(Thr, 1); break;
        case 0x91: InstrPattern[Reg_PC] = "SUB C";       ThreadNext(Thr, 1); break;
        case 0x92: InstrPattern[Reg_PC] = "SUB D";       ThreadNext(Thr, 1); break;
        case 0x93: InstrPattern[Reg_PC] = "SUB E";       ThreadNext(Thr, 1); break;
        case 0x94: InstrPattern[Reg_PC] = "SUB H";       ThreadNext(Thr, 1); break;
        case 0x95: InstrPattern[Reg_PC] = "SUB L";       ThreadNext(Thr, 1); break;
        case 0x96: InstrPattern[Reg_PC] = "SUB (HL)";    ThreadNext(Thr, 1); break;
        case 0x97: InstrPattern[Reg_PC] = "SUB A";       ThreadNext(Thr, 1); break;
        case 0x98: InstrPattern[Reg_PC] = "SBC A, B";    ThreadNext(Thr, 1); break;
        case 0x99: InstrPattern[Reg_PC] = "SBC A, C";    ThreadNext(Thr, 1); break;
        case 0x9A: InstrPattern[Reg_PC] = "SBC A, D";    ThreadNext(Thr, 1); break;
        case 0x9B: InstrPattern[Reg_PC] = "SBC A, E";    ThreadNext(Thr, 1); break;
        case 0x9C: InstrPattern[Reg_PC] = "SBC A, H";    ThreadNext(Thr, 1); break;
        case 0x9D: InstrPattern[Reg_PC] = "SBC A, L";    ThreadNext(Thr, 1); break;
        case 0x9E: InstrPattern[Reg_PC] = "SBC A, (HL)"; ThreadNext(Thr, 1); break;
        case 0x9F: InstrPattern[Reg_PC] = "SBC A, A";    ThreadNext(Thr, 1); break;
        case 0xA0: InstrPattern[Reg_PC] = "AND B";       ThreadNext(Thr, 1); break;
        case 0xA1: InstrPattern[Reg_PC] = "AND C";       ThreadNext(Thr, 1); break;
        case 0xA2: InstrPattern[Reg_PC] = "AND D";       ThreadNext(Thr, 1); break;
        case 0xA3: InstrPattern[Reg_PC] = "AND E";       ThreadNext(Thr, 1); break;
        case 0xA4: InstrPattern[Reg_PC] = "AND H";       ThreadNext(Thr, 1); break;
        case 0xA5: InstrPattern[Reg_PC] = "AND L";       ThreadNext(Thr, 1); break;
        case 0xA6: InstrPattern[Reg_PC] = "AND (HL)";    ThreadNext(Thr, 1); break;
        case 0xA7: InstrPattern[Reg_PC] = "AND A";       ThreadNext(Thr, 1); break;
        case 0xA8: InstrPattern[Reg_PC] = "XOR B";       ThreadNext(Thr, 1); break;
        case 0xA9: InstrPattern[Reg_PC] = "XOR C";       ThreadNext(Thr, 1); break;
        case 0xAA: InstrPattern[Reg_PC] = "XOR D";       ThreadNext(Thr, 1); break;
        case 0xAB: InstrPattern[Reg_PC] = "XOR E";       ThreadNext(Thr, 1); break;
        case 0xAC: InstrPattern[Reg_PC] = "XOR H";       ThreadNext(Thr, 1); break;
        case 0xAD: InstrPattern[Reg_PC] = "XOR L";       ThreadNext(Thr, 1); break;
        case 0xAE: InstrPattern[Reg_PC] = "XOR (HL)";    ThreadNext(Thr, 1); break;
        case 0xAF: InstrPattern[Reg_PC] = "XOR A";       ThreadNext(Thr, 1); break;
        case 0xB0: InstrPattern[Reg_PC] = "OR B";        ThreadNext(Thr, 1); break;
        case 0xB1: InstrPattern[Reg_PC] = "OR C";        ThreadNext(Thr, 1); break;
        case 0xB2: InstrPattern[Reg_PC] = "OR D";        ThreadNext(Thr, 1); break;
        case 0xB3: InstrPattern[Reg_PC] = "OR E";        ThreadNext(Thr, 1); break;
        case 0xB4: InstrPattern[Reg_PC] = "OR H";        ThreadNext(Thr, 1); break;
        case 0xB5: InstrPattern[Reg_PC] = "OR L";        ThreadNext(Thr, 1); break;
        case 0xB6: InstrPattern[Reg_PC] = "OR (HL)";     ThreadNext(Thr, 1); break;
        case 0xB7: InstrPattern[Reg_PC] = "OR A";        ThreadNext(Thr, 1); break;
        case 0xB8: InstrPattern[Reg_PC] = "CP B";        ThreadNext(Thr, 1); break;
        case 0xB9: InstrPattern[Reg_PC] = "CP C";        ThreadNext(Thr, 1); break;
        case 0xBA: InstrPattern[Reg_PC] = "CP D";        ThreadNext(Thr, 1); break;
        case 0xBB: InstrPattern[Reg_PC] = "CP E";        ThreadNext(Thr, 1); break;
        case 0xBC: InstrPattern[Reg_PC] = "CP H";        ThreadNext(Thr, 1); break;
        case 0xBD: InstrPattern[Reg_PC] = "CP L";        ThreadNext(Thr, 1); break;
        case 0xBE: InstrPattern[Reg_PC] = "CP (HL)";     ThreadNext(Thr, 1); break;
        case 0xBF: InstrPattern[Reg_PC] = "CP A";        ThreadNext(Thr, 1); break;


        // Stack instructions
        case 0xC1: InstrPattern[Reg_PC] = "POP BC";      ThreadNext(Thr, 1); break;
        case 0xC5: InstrPattern[Reg_PC] = "PUSH BC";     ThreadNext(Thr, 1); break;
        case 0xD1: InstrPattern[Reg_PC] = "POP DE";      ThreadNext(Thr, 1); break;
        case 0xD5: InstrPattern[Reg_PC] = "PUSH DE";     ThreadNext(Thr, 1); break;
        case 0xE1: InstrPattern[Reg_PC] = "POP HL";      ThreadNext(Thr, 1); break;
        case 0xE5: InstrPattern[Reg_PC] = "PUSH HL";     ThreadNext(Thr, 1); break;
        case 0xF1: InstrPattern[Reg_PC] = "POP AF";      ThreadNext(Thr, 1); break;
        case 0xF5: InstrPattern[Reg_PC] = "PUSH AF";     ThreadNext(Thr, 1); break;

        // Two-bytes calls
        case 0xCD: InstrPattern[Reg_PC] = "CALL NN_";     ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xC4: InstrPattern[Reg_PC] = "CALL NZ NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xCC: InstrPattern[Reg_PC] = "CALL Z, NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xD4: InstrPattern[Reg_PC] = "CALL NC, NN_"; ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xDC: InstrPattern[Reg_PC] = "CALL C, NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xE4: InstrPattern[Reg_PC] = "CALL PO, NN_"; ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xEC: InstrPattern[Reg_PC] = "CALL PE, NN_"; ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xF4: InstrPattern[Reg_PC] = "CALL P, NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0xFC: InstrPattern[Reg_PC] = "CALL M, NN_";  ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;

        // One-byte calls
        case 0xC7: InstrPattern[Reg_PC] = "RST 00";      ThreadNext(Thr, 1); ThreadAdd(0x00); break;
        case 0xCF: InstrPattern[Reg_PC] = "RST 08";      ThreadNext(Thr, 1); ThreadAdd(0x08); break;
        case 0xD7: InstrPattern[Reg_PC] = "RST 10";      ThreadNext(Thr, 1); ThreadAdd(0x10); break;
        case 0xDF: InstrPattern[Reg_PC] = "RST 18";      ThreadNext(Thr, 1); ThreadAdd(0x18); break;
        case 0xE7: InstrPattern[Reg_PC] = "RST 20";      ThreadNext(Thr, 1); ThreadAdd(0x20); break;
        case 0xEF: InstrPattern[Reg_PC] = "RST 28";      ThreadNext(Thr, 1); ThreadAdd(0x28); break;
        case 0xF7: InstrPattern[Reg_PC] = "RST 30";      ThreadNext(Thr, 1); ThreadAdd(0x30); break;
        case 0xFF: InstrPattern[Reg_PC] = "RST 38";      ThreadNext(Thr, 1); ThreadAdd(0x38); break;

        // Returns from call
        case 0xC9: InstrPattern[Reg_PC] = "RET";         ThreadNext(Thr, -1); break;
        case 0xC0: InstrPattern[Reg_PC] = "RET NZ";      ThreadNext(Thr, 1); break;
        case 0xC8: InstrPattern[Reg_PC] = "RET Z";       ThreadNext(Thr, 1); break;
        case 0xD0: InstrPattern[Reg_PC] = "RET NC";      ThreadNext(Thr, 1); break;
        case 0xD8: InstrPattern[Reg_PC] = "RET C";       ThreadNext(Thr, 1); break;
        case 0xE0: InstrPattern[Reg_PC] = "RET PO";      ThreadNext(Thr, 1); break;
        case 0xE8: InstrPattern[Reg_PC] = "RET PE";      ThreadNext(Thr, 1); break;
        case 0xF0: InstrPattern[Reg_PC] = "RET P";       ThreadNext(Thr, 1); break;
        case 0xF8: InstrPattern[Reg_PC] = "RET M";       ThreadNext(Thr, 1); break;

        // Input and output
        case 0xD3: InstrPattern[Reg_PC] = "OUT (n), A";  ThreadNext(Thr, 2); break;
        case 0xDB: InstrPattern[Reg_PC] = "IN A, (n)";   ThreadNext(Thr, 2); break;


        case 0xCB: // CB instruction serie - instructions on single register byte pointed by HL
            ProcessOpcodeExtCB(Thr);
            break;
        case 0xDD: // DD instruction serie - instructions using IX register
        case 0xFD: // FD instruction serie - instructions using IY register
            ProcessOpcodeExt_D(Thr);
            break;
        case 0xED: // ED instructions
            ProcessOpcodeExtED(Thr);
            break;

        default:
            InstrPattern[Reg_PC] = "?";
            ThreadNext(Thr, 0);
            break;
    }
}

void ScriptDecompileZ180::ProcessOpcodeExtCB(int Thr)
{
    int Reg_PC = ProgramCounterThreads[Thr];
    uchar OpCode1 = MemProg[Reg_PC + 1];

    std::string RegName = "";

    switch (OpCode1 & 0b00000111)
    {
        case 0: RegName = "B"; break;
        case 1: RegName = "C"; break;
        case 2: RegName = "D"; break;
        case 3: RegName = "E"; break;
        case 4: RegName = "H"; break;
        case 5: RegName = "L"; break;
        case 6: RegName = "(HL)"; break;
        case 7: RegName = "A"; break;
    }

    // Performing operation
    switch (OpCode1 & 0b11111000)
    {
        case 0x00: InstrPattern[Reg_PC] = "RLC "    + RegName;  ThreadNext(Thr, 2); break;
        case 0x08: InstrPattern[Reg_PC] = "RRC "    + RegName;  ThreadNext(Thr, 2); break;
        case 0x10: InstrPattern[Reg_PC] = "RL "     + RegName;  ThreadNext(Thr, 2); break;
        case 0x18: InstrPattern[Reg_PC] = "RR "     + RegName;  ThreadNext(Thr, 2); break;
        case 0x20: InstrPattern[Reg_PC] = "SLA "    + RegName;  ThreadNext(Thr, 2); break;
        case 0x28: InstrPattern[Reg_PC] = "SRA "    + RegName;  ThreadNext(Thr, 2); break;
        case 0x30: InstrPattern[Reg_PC] = "SLL "    + RegName;  ThreadNext(Thr, 2); break;
        case 0x38: InstrPattern[Reg_PC] = "SRL "    + RegName;  ThreadNext(Thr, 2); break;
        case 0x40: InstrPattern[Reg_PC] = "BIT 0, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x48: InstrPattern[Reg_PC] = "BIT 1, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x50: InstrPattern[Reg_PC] = "BIT 2, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x58: InstrPattern[Reg_PC] = "BIT 3, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x60: InstrPattern[Reg_PC] = "BIT 4, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x68: InstrPattern[Reg_PC] = "BIT 5, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x70: InstrPattern[Reg_PC] = "BIT 6, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x78: InstrPattern[Reg_PC] = "BIT 7, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x80: InstrPattern[Reg_PC] = "RES 0, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x88: InstrPattern[Reg_PC] = "RES 1, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x90: InstrPattern[Reg_PC] = "RES 2, " + RegName;  ThreadNext(Thr, 2); break;
        case 0x98: InstrPattern[Reg_PC] = "RES 3, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xA0: InstrPattern[Reg_PC] = "RES 4, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xA8: InstrPattern[Reg_PC] = "RES 5, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xB0: InstrPattern[Reg_PC] = "RES 6, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xB8: InstrPattern[Reg_PC] = "RES 7, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xC0: InstrPattern[Reg_PC] = "SET 0, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xC8: InstrPattern[Reg_PC] = "SET 1, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xD0: InstrPattern[Reg_PC] = "SET 2, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xD8: InstrPattern[Reg_PC] = "SET 3, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xE0: InstrPattern[Reg_PC] = "SET 4, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xE8: InstrPattern[Reg_PC] = "SET 5, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xF0: InstrPattern[Reg_PC] = "SET 6, " + RegName;  ThreadNext(Thr, 2); break;
        case 0xF8: InstrPattern[Reg_PC] = "SET 7, " + RegName;  ThreadNext(Thr, 2); break;
        default:
            InstrPattern[Reg_PC] = "?";
            ThreadNext(Thr, 0);
            break;
    }
}

void ScriptDecompileZ180::ProcessOpcodeExt_D(int Thr)
{
    int Reg_PC = ProgramCounterThreads[Thr];
    uchar OpCode1 = MemProg[Reg_PC + 1];

    std::string RegName = "";

    // Register name IX/IY
    if (MemProg[Reg_PC] == 0xDD)
    {
        RegName = "IX";
    }
    else
    {
        RegName = "IY";
    }

    uchar OpCode2;

    // Performing instruction
    switch (OpCode1)
    {
        case 0x09: InstrPattern[Reg_PC] = "ADD " + RegName + ", BC";     ThreadNext(Thr, 2); break;
        case 0x19: InstrPattern[Reg_PC] = "ADD " + RegName + ", DE";     ThreadNext(Thr, 2); break;
        case 0x29: InstrPattern[Reg_PC] = "ADD " + RegName + ", " + RegName + "";     ThreadNext(Thr, 2); break;
        case 0x39: InstrPattern[Reg_PC] = "ADD " + RegName + ", SP";     ThreadNext(Thr, 2); break;
        case 0x23: InstrPattern[Reg_PC] = "INC " + RegName + "";         ThreadNext(Thr, 2); break;
        case 0x2B: InstrPattern[Reg_PC] = "DEC " + RegName + "";         ThreadNext(Thr, 2); break;
        case 0x34: InstrPattern[Reg_PC] = "INC (" + RegName + " + d)";   ThreadNext(Thr, 3); break;
        case 0x35: InstrPattern[Reg_PC] = "DEC (" + RegName + " + d)";   ThreadNext(Thr, 3); break;

        case 0x21: InstrPattern[Reg_PC] = "LD " + RegName + ", NN2";     ThreadNext(Thr, 4); break;
        case 0x22: InstrPattern[Reg_PC] = "LD (NN2), " + RegName + "";   ThreadNext(Thr, 4); break;
        case 0x2A: InstrPattern[Reg_PC] = "LD " + RegName + ", (NN2)";   ThreadNext(Thr, 4); break;
        case 0xF9: InstrPattern[Reg_PC] = "LD SP, " + RegName + "";      ThreadNext(Thr, 2); break;
        case 0x36: InstrPattern[Reg_PC] = "LD (" + RegName + " + d), n4"; ThreadNext(Thr, 4); break;

        case 0x46: InstrPattern[Reg_PC] = "LD B, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0x4E: InstrPattern[Reg_PC] = "LD C, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0x56: InstrPattern[Reg_PC] = "LD D, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0x5E: InstrPattern[Reg_PC] = "LD E, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0x66: InstrPattern[Reg_PC] = "LD H, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0x6E: InstrPattern[Reg_PC] = "LD L, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0x7E: InstrPattern[Reg_PC] = "LD A, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;

        case 0x70: InstrPattern[Reg_PC] = "LD (" + RegName + " + d), B"; ThreadNext(Thr, 3); break;
        case 0x71: InstrPattern[Reg_PC] = "LD (" + RegName + " + d), C"; ThreadNext(Thr, 3); break;
        case 0x72: InstrPattern[Reg_PC] = "LD (" + RegName + " + d), D"; ThreadNext(Thr, 3); break;
        case 0x73: InstrPattern[Reg_PC] = "LD (" + RegName + " + d), E"; ThreadNext(Thr, 3); break;
        case 0x74: InstrPattern[Reg_PC] = "LD (" + RegName + " + d), H"; ThreadNext(Thr, 3); break;
        case 0x75: InstrPattern[Reg_PC] = "LD (" + RegName + " + d), L"; ThreadNext(Thr, 3); break;
        case 0x77: InstrPattern[Reg_PC] = "LD (" + RegName + " + d), A"; ThreadNext(Thr, 3); break;

        case 0x86: InstrPattern[Reg_PC] = "ADD A, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0x8E: InstrPattern[Reg_PC] = "ADC A, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0x96: InstrPattern[Reg_PC] = "SUB, (" + RegName + " + d)";   ThreadNext(Thr, 3); break;
        case 0x9E: InstrPattern[Reg_PC] = "SBC A, (" + RegName + " + d)"; ThreadNext(Thr, 3); break;
        case 0xA6: InstrPattern[Reg_PC] = "AND, (" + RegName + " + d)";   ThreadNext(Thr, 3); break;
        case 0xAE: InstrPattern[Reg_PC] = "XOR, (" + RegName + " + d)";   ThreadNext(Thr, 3); break;
        case 0xB6: InstrPattern[Reg_PC] = "OR, (" + RegName + " + d)";    ThreadNext(Thr, 3); break;
        case 0xBE: InstrPattern[Reg_PC] = "CP, (" + RegName + " + d)";    ThreadNext(Thr, 3); break;

        case 0xE3: InstrPattern[Reg_PC] = "EX (SP), " + RegName + "";    ThreadNext(Thr, 2); break;
        case 0xE1: InstrPattern[Reg_PC] = "POP " + RegName + "";         ThreadNext(Thr, 2); break;
        case 0xE5: InstrPattern[Reg_PC] = "PUSH " + RegName + "";        ThreadNext(Thr, 2); break;
        case 0xE9: InstrPattern[Reg_PC] = "JP (" + RegName + ")";        ThreadNext(Thr, -2); ThreadAddVector(Reg_PC); break;

        case 0xCB: // CB instructions
            OpCode2 = MemProg[Reg_PC + 3];
            switch (OpCode2)
            {
                case 0x06: InstrPattern[Reg_PC] = "RLC (" + RegName + " + d)";    ThreadNext(Thr, 4); break;
                case 0x0E: InstrPattern[Reg_PC] = "RRC (" + RegName + " + d)";    ThreadNext(Thr, 4); break;
                case 0x16: InstrPattern[Reg_PC] = "RL ("  + RegName + " + d)";    ThreadNext(Thr, 4); break;
                case 0x1E: InstrPattern[Reg_PC] = "RR ("  + RegName + " + d)";    ThreadNext(Thr, 4); break;

                case 0x26: InstrPattern[Reg_PC] = "SLA (" + RegName + " + d)";    ThreadNext(Thr, 4); break;
                case 0x2E: InstrPattern[Reg_PC] = "SRA (" + RegName + " + d)";    ThreadNext(Thr, 4); break;
                case 0x36: InstrPattern[Reg_PC] = "SLL (" + RegName + " + d)";    ThreadNext(Thr, 4); break;
                case 0x3E: InstrPattern[Reg_PC] = "SRL (" + RegName + " + d)";    ThreadNext(Thr, 4); break;

                case 0x46: InstrPattern[Reg_PC] = "BIT 0, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x4E: InstrPattern[Reg_PC] = "BIT 1, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x56: InstrPattern[Reg_PC] = "BIT 2, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x5E: InstrPattern[Reg_PC] = "BIT 3, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x66: InstrPattern[Reg_PC] = "BIT 4, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x6E: InstrPattern[Reg_PC] = "BIT 5, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x76: InstrPattern[Reg_PC] = "BIT 6, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x7E: InstrPattern[Reg_PC] = "BIT 7, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;

                case 0x86: InstrPattern[Reg_PC] = "RES 0, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x8E: InstrPattern[Reg_PC] = "RES 1, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x96: InstrPattern[Reg_PC] = "RES 2, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0x9E: InstrPattern[Reg_PC] = "RES 3, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xA6: InstrPattern[Reg_PC] = "RES 4, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xAE: InstrPattern[Reg_PC] = "RES 5, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xB6: InstrPattern[Reg_PC] = "RES 6, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xBE: InstrPattern[Reg_PC] = "RES 7, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;

                case 0xC6: InstrPattern[Reg_PC] = "SET 0, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xCE: InstrPattern[Reg_PC] = "SET 1, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xD6: InstrPattern[Reg_PC] = "SET 2, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xDE: InstrPattern[Reg_PC] = "SET 3, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xE6: InstrPattern[Reg_PC] = "SET 4, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xEE: InstrPattern[Reg_PC] = "SET 5, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xF6: InstrPattern[Reg_PC] = "SET 6, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;
                case 0xFE: InstrPattern[Reg_PC] = "SET 7, (" + RegName + " + d)"; ThreadNext(Thr, 4); break;

                default:
                    InstrPattern[Reg_PC] = "?";
                    ThreadNext(Thr, 0);
                    break;
            }
            break;

        default:
            InstrPattern[Reg_PC] = "?";
            ThreadNext(Thr, 0);
            break;
    }
}

void ScriptDecompileZ180::ProcessOpcodeExtED(int Thr)
{
    int Reg_PC = ProgramCounterThreads[Thr];
    uchar OpCode1 = MemProg[Reg_PC + 1];

    switch (OpCode1)
    {
        // Multiplication - Z180
        case 0x4C: InstrPattern[Reg_PC] = "MLT BC"; ThreadNext(Thr, 2); break;
        case 0x5C: InstrPattern[Reg_PC] = "MLT DE"; ThreadNext(Thr, 2); break;
        case 0x6C: InstrPattern[Reg_PC] = "MLT HL"; ThreadNext(Thr, 2); break;
        case 0x7C: InstrPattern[Reg_PC] = "MLT SP"; ThreadNext(Thr, 2); break;

        // Checking conjunction parity - Z180
        case 0x04: InstrPattern[Reg_PC] = "TST B"; ThreadNext(Thr, 2); break;
        case 0x0C: InstrPattern[Reg_PC] = "TST C"; ThreadNext(Thr, 2); break;
        case 0x14: InstrPattern[Reg_PC] = "TST D"; ThreadNext(Thr, 2); break;
        case 0x1C: InstrPattern[Reg_PC] = "TST E"; ThreadNext(Thr, 2); break;
        case 0x24: InstrPattern[Reg_PC] = "TST H"; ThreadNext(Thr, 2); break;
        case 0x2C: InstrPattern[Reg_PC] = "TST L"; ThreadNext(Thr, 2); break;
        case 0x34: InstrPattern[Reg_PC] = "TST (HL)"; ThreadNext(Thr, 2); break;
        case 0x3C: InstrPattern[Reg_PC] = "TST A"; ThreadNext(Thr, 2); break;
        case 0x64: InstrPattern[Reg_PC] = "TST n3"; ThreadNext(Thr, 3); break;

            /*
        case 0x00: InstrPattern[Reg_PC] = "IN0 B, (n)"; ThreadNext(Thr, 3); break;
        case 0x08: InstrPattern[Reg_PC] = "IN0 C, (n)"; ThreadNext(Thr, 3); break;
        case 0x10: InstrPattern[Reg_PC] = "IN0 D, (n)"; ThreadNext(Thr, 3); break;
        case 0x18: InstrPattern[Reg_PC] = "IN0 E, (n)"; ThreadNext(Thr, 3); break;
        case 0x20: InstrPattern[Reg_PC] = "IN0 H, (n)"; ThreadNext(Thr, 3); break;
        case 0x28: InstrPattern[Reg_PC] = "IN0 L, (n)"; ThreadNext(Thr, 3); break;
        case 0x30: InstrPattern[Reg_PC] = "IN0 F, (n)"; ThreadNext(Thr, 3); break;
        case 0x38: InstrPattern[Reg_PC] = "IN0 A, (n)"; ThreadNext(Thr, 3); break;

        case 0x01: InstrPattern[Reg_PC] = "OUT0 (n), B"; ThreadNext(Thr, 3); break;
        case 0x09: InstrPattern[Reg_PC] = "OUT0 (n), C"; ThreadNext(Thr, 3); break;
        case 0x11: InstrPattern[Reg_PC] = "OUT0 (n), D"; ThreadNext(Thr, 3); break;
        case 0x19: InstrPattern[Reg_PC] = "OUT0 (n), E"; ThreadNext(Thr, 3); break;
        case 0x21: InstrPattern[Reg_PC] = "OUT0 (n), H"; ThreadNext(Thr, 3); break;
        case 0x29: InstrPattern[Reg_PC] = "OUT0 (n), L"; ThreadNext(Thr, 3); break;
        case 0x39: InstrPattern[Reg_PC] = "OUT0 (n), A"; ThreadNext(Thr, 3); break;

        case 0x74: InstrPattern[Reg_PC] = "TSTIO N"; ThreadNext(Thr, 3); break;

        case 0x76: InstrPattern[Reg_PC] = "SLP"; ThreadNext(Thr, 2); break;

        case 0x83: InstrPattern[Reg_PC] = "OTIM"; ThreadNext(Thr, 2); break;
        case 0x8B: InstrPattern[Reg_PC] = "OTDM"; ThreadNext(Thr, 2); break;
        case 0x93: InstrPattern[Reg_PC] = "OTIMR"; ThreadNext(Thr, 2); break;
        case 0x9B: InstrPattern[Reg_PC] = "OTDMR"; ThreadNext(Thr, 2); break;

        case 0xA2: InstrPattern[Reg_PC] = "INI"; ThreadNext(Thr, 2); break;
        case 0xA3: InstrPattern[Reg_PC] = "OTI"; ThreadNext(Thr, 2); break;
        case 0xAA: InstrPattern[Reg_PC] = "IND"; ThreadNext(Thr, 2); break;
        case 0xAB: InstrPattern[Reg_PC] = "OTD"; ThreadNext(Thr, 2); break;
        case 0xB2: InstrPattern[Reg_PC] = "INIR"; ThreadNext(Thr, 2); break;
        case 0xB3: InstrPattern[Reg_PC] = "OTIR"; ThreadNext(Thr, 2); break;
        case 0xBA: InstrPattern[Reg_PC] = "INDR"; ThreadNext(Thr, 2); break;
        case 0xBB: InstrPattern[Reg_PC] = "OTDR"; ThreadNext(Thr, 2); break;
            */

        // ########################################################

        // Receiving from external device
        case 0x40: InstrPattern[Reg_PC] = "IN B, (C)"; ThreadNext(Thr, 2); break;
        case 0x48: InstrPattern[Reg_PC] = "IN C, (C)"; ThreadNext(Thr, 2); break;
        case 0x50: InstrPattern[Reg_PC] = "IN D, (C)"; ThreadNext(Thr, 2); break;
        case 0x58: InstrPattern[Reg_PC] = "IN E, (C)"; ThreadNext(Thr, 2); break;
        case 0x60: InstrPattern[Reg_PC] = "IN H, (C)"; ThreadNext(Thr, 2); break;
        case 0x68: InstrPattern[Reg_PC] = "IN L, (C)"; ThreadNext(Thr, 2); break;
        case 0x78: InstrPattern[Reg_PC] = "IN A, (C)"; ThreadNext(Thr, 2); break;

        // Sending to external device
        case 0x41: InstrPattern[Reg_PC] = "OUT (C), B"; ThreadNext(Thr, 2); break;
        case 0x49: InstrPattern[Reg_PC] = "OUT (C), C"; ThreadNext(Thr, 2); break;
        case 0x51: InstrPattern[Reg_PC] = "OUT (C), D"; ThreadNext(Thr, 2); break;
        case 0x59: InstrPattern[Reg_PC] = "OUT (C), E"; ThreadNext(Thr, 2); break;
        case 0x61: InstrPattern[Reg_PC] = "OUT (C), H"; ThreadNext(Thr, 2); break;
        case 0x69: InstrPattern[Reg_PC] = "OUT (C), L"; ThreadNext(Thr, 2); break;
        case 0x79: InstrPattern[Reg_PC] = "OUT (C), A"; ThreadNext(Thr, 2); break;

        // Interrupt modes
        case 0x46: InstrPattern[Reg_PC] = "IM 0"; ThreadNext(Thr, 2); break;
        case 0x56: InstrPattern[Reg_PC] = "IM 1"; ThreadNext(Thr, 2); break;
        case 0x5E: InstrPattern[Reg_PC] = "IM 2"; ThreadNext(Thr, 2); break;

        // Return from interrupt call
        case 0x45: InstrPattern[Reg_PC] = "RETN"; ThreadNext(Thr, -2); break;
        case 0x4D: InstrPattern[Reg_PC] = "RETI"; ThreadNext(Thr, -2); break;

        // Copying 8-bit values
        case 0x47: InstrPattern[Reg_PC] = "LD I, A"; ThreadNext(Thr, 2); break;
        case 0x4F: InstrPattern[Reg_PC] = "LD R, A"; ThreadNext(Thr, 2); break;
        case 0x57: InstrPattern[Reg_PC] = "LD A, I"; ThreadNext(Thr, 2); break;
        case 0x5F: InstrPattern[Reg_PC] = "LD A, R"; ThreadNext(Thr, 2); break;

        // Copying 16-bit values
        case 0x43: InstrPattern[Reg_PC] = "LD (NN2), BC"; ThreadNext(Thr, 4); break;
        case 0x53: InstrPattern[Reg_PC] = "LD (NN2), DE"; ThreadNext(Thr, 4); break;
        case 0x63: InstrPattern[Reg_PC] = "LD (NN2), HL"; ThreadNext(Thr, 4); break;
        case 0x73: InstrPattern[Reg_PC] = "LD (NN2), SP"; ThreadNext(Thr, 4); break;

        case 0x4B: InstrPattern[Reg_PC] = "LD BC, (NN2)"; ThreadNext(Thr, 4); break;
        case 0x5B: InstrPattern[Reg_PC] = "LD DE, (NN2)"; ThreadNext(Thr, 4); break;
        case 0x6B: InstrPattern[Reg_PC] = "LD HL, (NN2)"; ThreadNext(Thr, 4); break;
        case 0x7B: InstrPattern[Reg_PC] = "LD SP, (NN2)"; ThreadNext(Thr, 4); break;

        // Operations on accumulator
        case 0x44: InstrPattern[Reg_PC] = "NEG"; ThreadNext(Thr, 2); break;
        case 0x67: InstrPattern[Reg_PC] = "RRD"; ThreadNext(Thr, 2); break;
        case 0x6F: InstrPattern[Reg_PC] = "RLD"; ThreadNext(Thr, 2); break;

        // Adding on 16-bit values
        case 0x4A: InstrPattern[Reg_PC] = "ADC HL, BC"; ThreadNext(Thr, 2); break;
        case 0x5A: InstrPattern[Reg_PC] = "ADC HL, DE"; ThreadNext(Thr, 2); break;
        case 0x6A: InstrPattern[Reg_PC] = "ADC HL, HL"; ThreadNext(Thr, 2); break;
        case 0x7A: InstrPattern[Reg_PC] = "ADC HL, SP"; ThreadNext(Thr, 2); break;

        // Subtracting on 16-bit values
        case 0x42: InstrPattern[Reg_PC] = "SBC HL, BC"; ThreadNext(Thr, 2); break;
        case 0x52: InstrPattern[Reg_PC] = "SBC HL, DE"; ThreadNext(Thr, 2); break;
        case 0x62: InstrPattern[Reg_PC] = "SBC HL, HL"; ThreadNext(Thr, 2); break;
        case 0x72: InstrPattern[Reg_PC] = "SBC HL, SP"; ThreadNext(Thr, 2); break;

        // Block data loading
        case 0xA0: InstrPattern[Reg_PC] = "LDI"; ThreadNext(Thr, 2); break;
        case 0xA8: InstrPattern[Reg_PC] = "LDD"; ThreadNext(Thr, 2); break;
        case 0xB0: InstrPattern[Reg_PC] = "LDIR"; ThreadNext(Thr, 2); break;
        case 0xB8: InstrPattern[Reg_PC] = "LDDR"; ThreadNext(Thr, 2); break;

        // Block data comparison
        case 0xA1: InstrPattern[Reg_PC] = "CPI"; ThreadNext(Thr, 2); break;
        case 0xA9: InstrPattern[Reg_PC] = "CPD"; ThreadNext(Thr, 2); break;
        case 0xB1: InstrPattern[Reg_PC] = "CPIR"; ThreadNext(Thr, 2); break;
        case 0xB9: InstrPattern[Reg_PC] = "CPDR"; ThreadNext(Thr, 2); break;

        default:
            InstrPattern[Reg_PC] = "?";
            ThreadNext(Thr, 0);
            break;
    }
}


int ScriptDecompileZ180::CalcAddr(int Reg_PC)
{
    int AddrH = MemProg[Reg_PC + 2];
    int AddrL = MemProg[Reg_PC + 1];
    return (AddrH << 8) + AddrL;
}

int ScriptDecompileZ180::CalcRel(int Reg_PC)
{
    Reg_PC++;
    int Addr = MemProg[Reg_PC];
    Reg_PC = Reg_PC + Addr;
    if (Addr > 127)
    {
        Reg_PC -= 256;
    }
    return Reg_PC + 1;
}


std::string ScriptDecompileZ180::InstructionName(int Addr)
{
    std::string Name = InstrPattern[Addr];
    Name = StringFindReplace(Name, "NN2", Hex::IntToHex16(CalcAddr(Addr + 1)) + "h");
    Name = StringFindReplace(Name, "NN_", LabelPrefix + Hex::IntToHex16(CalcAddr(Addr)));
    Name = StringFindReplace(Name, "NN", Hex::IntToHex16(CalcAddr(Addr)) + "h");
    Name = StringFindReplace(Name, "RelN", LabelPrefix + Hex::IntToHex16(CalcRel(Addr)));

    Name = StringFindReplace(Name, "n4", Hex::IntToHex8(MemProg[Addr + 3]) + "h");
    Name = StringFindReplace(Name, "n3", Hex::IntToHex8(MemProg[Addr + 2]) + "h");
    Name = StringFindReplace(Name, "n", Hex::IntToHex8(MemProg[Addr + 1]) + "h");

    if ((Addr + 2) < 65536)
    {
        if (MemProg[Addr + 2] < 128)
        {
            Name = StringFindReplace(Name, "+ d", "+ " + Hex::IntToHex8(MemProg[Addr + 2]) + "h");
        }
        else
        {
            Name = StringFindReplace(Name, "+ d", "- " + Hex::IntToHex8(0 - ((int)MemProg[Addr + 2] - 256)) + "h");
        }
    }
    return Name;
}

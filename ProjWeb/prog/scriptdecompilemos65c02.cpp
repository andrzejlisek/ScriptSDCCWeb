#include "scriptdecompilemos65c02.h"

ScriptDecompileMOS65C02::ScriptDecompileMOS65C02()
{

}

void ScriptDecompileMOS65C02::ProcessOpcode(int Thr)
{
    int Reg_PC = ProgramCounterThreads[Thr];
    uchar OpCode = MemProg[ProgramCounterThreads[Thr]];
    switch (OpCode)
    {
        case 0xA9: InstrPattern[Reg_PC] = "LDA #$nn";    ThreadNext(Thr, 2); break;
        case 0xAD: InstrPattern[Reg_PC] = "LDA $nnnn"  ; ThreadNext(Thr, 3); break;
        case 0xBD: InstrPattern[Reg_PC] = "LDA $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0xB9: InstrPattern[Reg_PC] = "LDA $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0xA5: InstrPattern[Reg_PC] = "LDA $nn";     ThreadNext(Thr, 2); break;
        case 0xB5: InstrPattern[Reg_PC] = "LDA $nn,X";   ThreadNext(Thr, 2); break;
        case 0xB2: InstrPattern[Reg_PC] = "LDA ($nn)";   ThreadNext(Thr, 2); break;
        case 0xA1: InstrPattern[Reg_PC] = "LDA ($nn,X)"; ThreadNext(Thr, 2); break;
        case 0xB1: InstrPattern[Reg_PC] = "LDA ($nn),Y"; ThreadNext(Thr, 2); break;

        case 0xA2: InstrPattern[Reg_PC] = "LDX #$nn";    ThreadNext(Thr, 2); break;
        case 0xAE: InstrPattern[Reg_PC] = "LDX $nnnn";   ThreadNext(Thr, 3); break;
        case 0xBE: InstrPattern[Reg_PC] = "LDX $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0xA6: InstrPattern[Reg_PC] = "LDX $nn";     ThreadNext(Thr, 2); break;
        case 0xB6: InstrPattern[Reg_PC] = "LDX $nn,Y";   ThreadNext(Thr, 2); break;

        case 0xA0: InstrPattern[Reg_PC] = "LDY #$nn";    ThreadNext(Thr, 2); break;
        case 0xAC: InstrPattern[Reg_PC] = "LDY $nnnn";   ThreadNext(Thr, 3); break;
        case 0xBC: InstrPattern[Reg_PC] = "$nnnn,X";     ThreadNext(Thr, 3); break;
        case 0xA4: InstrPattern[Reg_PC] = "LDY $nn";     ThreadNext(Thr, 2); break;
        case 0xB4: InstrPattern[Reg_PC] = "LDY $nn,X";   ThreadNext(Thr, 2); break;

        case 0x8D: InstrPattern[Reg_PC] = "STA $nnnn";   ThreadNext(Thr, 3); break;
        case 0x9D: InstrPattern[Reg_PC] = "STA $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x99: InstrPattern[Reg_PC] = "STA $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0x85: InstrPattern[Reg_PC] = "STA $nn";     ThreadNext(Thr, 2); break;
        case 0x95: InstrPattern[Reg_PC] = "STA $nn,X";   ThreadNext(Thr, 2); break;
        case 0x92: InstrPattern[Reg_PC] = "STA ($nn)";   ThreadNext(Thr, 2); break;
        case 0x81: InstrPattern[Reg_PC] = "STA ($nn,X)"; ThreadNext(Thr, 2); break;
        case 0x91: InstrPattern[Reg_PC] = "STA ($nn),Y"; ThreadNext(Thr, 2); break;

        case 0x8E: InstrPattern[Reg_PC] = "STX $nnnn";   ThreadNext(Thr, 3); break;
        case 0x86: InstrPattern[Reg_PC] = "STX $nn";     ThreadNext(Thr, 2); break;
        case 0x96: InstrPattern[Reg_PC] = "STX $nn,Y";   ThreadNext(Thr, 2); break;

        case 0x8C: InstrPattern[Reg_PC] = "STY $nnnn";   ThreadNext(Thr, 3); break;
        case 0x84: InstrPattern[Reg_PC] = "STY $nn";     ThreadNext(Thr, 2); break;
        case 0x94: InstrPattern[Reg_PC] = "STY $nn,Y";   ThreadNext(Thr, 2); break;


        case 0xAA: InstrPattern[Reg_PC] = "TAX";         ThreadNext(Thr, 1); break;
        case 0xA8: InstrPattern[Reg_PC] = "TAY";         ThreadNext(Thr, 1); break;
        case 0xBA: InstrPattern[Reg_PC] = "TSX";         ThreadNext(Thr, 1); break;
        case 0x8A: InstrPattern[Reg_PC] = "TXA";         ThreadNext(Thr, 1); break;
        case 0x9A: InstrPattern[Reg_PC] = "TXS";         ThreadNext(Thr, 1); break;
        case 0x98: InstrPattern[Reg_PC] = "TYA";         ThreadNext(Thr, 1); break;


        case 0x48: InstrPattern[Reg_PC] = "PHA";         ThreadNext(Thr, 1); break;
        case 0x08: InstrPattern[Reg_PC] = "PHP";         ThreadNext(Thr, 1); break;
        case 0xDA: InstrPattern[Reg_PC] = "PHX";         ThreadNext(Thr, 1); break;
        case 0x5A: InstrPattern[Reg_PC] = "PHY";         ThreadNext(Thr, 1); break;
        case 0x68: InstrPattern[Reg_PC] = "PLA";         ThreadNext(Thr, 1); break;
        case 0x28: InstrPattern[Reg_PC] = "PLP";         ThreadNext(Thr, 1); break;
        case 0xFA: InstrPattern[Reg_PC] = "PLX";         ThreadNext(Thr, 1); break;
        case 0x7A: InstrPattern[Reg_PC] = "PLY";         ThreadNext(Thr, 1); break;


        case 0x0A: InstrPattern[Reg_PC] = "ASL A";       ThreadNext(Thr, 1); break;
        case 0x0E: InstrPattern[Reg_PC] = "ASL $nnnn";   ThreadNext(Thr, 3); break;
        case 0x1E: InstrPattern[Reg_PC] = "ASL $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x06: InstrPattern[Reg_PC] = "ASL $nn";     ThreadNext(Thr, 2); break;
        case 0x16: InstrPattern[Reg_PC] = "ASL $nn,X";   ThreadNext(Thr, 2); break;

        case 0x4A: InstrPattern[Reg_PC] = "LSR A";       ThreadNext(Thr, 1); break;
        case 0x4E: InstrPattern[Reg_PC] = "LSR $nnnn";   ThreadNext(Thr, 3); break;
        case 0x5E: InstrPattern[Reg_PC] = "LSR $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x46: InstrPattern[Reg_PC] = "LSR $nn";     ThreadNext(Thr, 2); break;
        case 0x56: InstrPattern[Reg_PC] = "LSR $nn,X";   ThreadNext(Thr, 2); break;

        case 0x2A: InstrPattern[Reg_PC] = "ROL A";       ThreadNext(Thr, 1); break;
        case 0x2E: InstrPattern[Reg_PC] = "ROL $nnnn";   ThreadNext(Thr, 3); break;
        case 0x3E: InstrPattern[Reg_PC] = "ROL $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x26: InstrPattern[Reg_PC] = "ROL $nn";     ThreadNext(Thr, 2); break;
        case 0x36: InstrPattern[Reg_PC] = "ROL $nn,X";   ThreadNext(Thr, 2); break;

        case 0x6A: InstrPattern[Reg_PC] = "ROR A";       ThreadNext(Thr, 1); break;
        case 0x6E: InstrPattern[Reg_PC] = "ROR $nnnn";   ThreadNext(Thr, 3); break;
        case 0x7E: InstrPattern[Reg_PC] = "ROR $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x66: InstrPattern[Reg_PC] = "ROR $nn";     ThreadNext(Thr, 2); break;
        case 0x76: InstrPattern[Reg_PC] = "ROR $nn,X";   ThreadNext(Thr, 2); break;


        case 0x89: InstrPattern[Reg_PC] = "BIT #$nn";    ThreadNext(Thr, 2); break;
        case 0x2C: InstrPattern[Reg_PC] = "BIT $nnnn";   ThreadNext(Thr, 3); break;
        case 0x3C: InstrPattern[Reg_PC] = "BIT $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x24: InstrPattern[Reg_PC] = "BIT $nn";     ThreadNext(Thr, 2); break;
        case 0x34: InstrPattern[Reg_PC] = "BIT $nn,X";   ThreadNext(Thr, 2); break;

        case 0x29: InstrPattern[Reg_PC] = "AND #$nn";    ThreadNext(Thr, 2); break;
        case 0x2D: InstrPattern[Reg_PC] = "AND $nnnn";   ThreadNext(Thr, 3); break;
        case 0x3D: InstrPattern[Reg_PC] = "AND $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x39: InstrPattern[Reg_PC] = "AND $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0x25: InstrPattern[Reg_PC] = "AND $nn";     ThreadNext(Thr, 2); break;
        case 0x35: InstrPattern[Reg_PC] = "AND $nn,X";   ThreadNext(Thr, 2); break;
        case 0x32: InstrPattern[Reg_PC] = "AND ($nn)";   ThreadNext(Thr, 2); break;
        case 0x21: InstrPattern[Reg_PC] = "AND ($nn,X)"; ThreadNext(Thr, 2); break;
        case 0x31: InstrPattern[Reg_PC] = "AND ($nn),Y"; ThreadNext(Thr, 2); break;

        case 0x49: InstrPattern[Reg_PC] = "EOR #$nn";    ThreadNext(Thr, 2); break;
        case 0x4D: InstrPattern[Reg_PC] = "EOR $nnnn";   ThreadNext(Thr, 3); break;
        case 0x5D: InstrPattern[Reg_PC] = "EOR $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x59: InstrPattern[Reg_PC] = "EOR $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0x45: InstrPattern[Reg_PC] = "EOR $nn";     ThreadNext(Thr, 2); break;
        case 0x55: InstrPattern[Reg_PC] = "EOR $nn,X";   ThreadNext(Thr, 2); break;
        case 0x52: InstrPattern[Reg_PC] = "EOR ($nn)";   ThreadNext(Thr, 2); break;
        case 0x41: InstrPattern[Reg_PC] = "EOR ($nn,X)"; ThreadNext(Thr, 2); break;
        case 0x51: InstrPattern[Reg_PC] = "EOR ($nn),Y"; ThreadNext(Thr, 2); break;

        case 0x09: InstrPattern[Reg_PC] = "ORA #$nn";    ThreadNext(Thr, 2); break;
        case 0x0D: InstrPattern[Reg_PC] = "ORA $nnnn";   ThreadNext(Thr, 3); break;
        case 0x1D: InstrPattern[Reg_PC] = "ORA $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x19: InstrPattern[Reg_PC] = "ORA $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0x05: InstrPattern[Reg_PC] = "ORA $nn";     ThreadNext(Thr, 2); break;
        case 0x15: InstrPattern[Reg_PC] = "ORA $nn,X";   ThreadNext(Thr, 2); break;
        case 0x12: InstrPattern[Reg_PC] = "ORA ($nn)";   ThreadNext(Thr, 2); break;
        case 0x01: InstrPattern[Reg_PC] = "ORA ($nn,X)"; ThreadNext(Thr, 2); break;
        case 0x11: InstrPattern[Reg_PC] = "ORA ($nn),Y"; ThreadNext(Thr, 2); break;


        case 0x69: InstrPattern[Reg_PC] = "ADC #$nn";    ThreadNext(Thr, 2); break;
        case 0x6D: InstrPattern[Reg_PC] = "ADC $nnnn";   ThreadNext(Thr, 3); break;
        case 0x7D: InstrPattern[Reg_PC] = "ADC $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x79: InstrPattern[Reg_PC] = "ADC $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0x65: InstrPattern[Reg_PC] = "ADC $nn";     ThreadNext(Thr, 2); break;
        case 0x75: InstrPattern[Reg_PC] = "ADC $nn,X";   ThreadNext(Thr, 2); break;
        case 0x72: InstrPattern[Reg_PC] = "ADC ($nn)";   ThreadNext(Thr, 2); break;
        case 0x61: InstrPattern[Reg_PC] = "ADC ($nn,X)"; ThreadNext(Thr, 2); break;
        case 0x71: InstrPattern[Reg_PC] = "ADC ($nn),Y"; ThreadNext(Thr, 2); break;

        case 0xE9: InstrPattern[Reg_PC] = "SBC #$nn";    ThreadNext(Thr, 2); break;
        case 0xED: InstrPattern[Reg_PC] = "SBC $nnnn";   ThreadNext(Thr, 3); break;
        case 0xFD: InstrPattern[Reg_PC] = "SBC $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0xF9: InstrPattern[Reg_PC] = "SBC $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0xE5: InstrPattern[Reg_PC] = "SBC $nn";     ThreadNext(Thr, 2); break;
        case 0xF5: InstrPattern[Reg_PC] = "SBC $nn,X";   ThreadNext(Thr, 2); break;
        case 0xF2: InstrPattern[Reg_PC] = "SBC ($nn)";   ThreadNext(Thr, 2); break;
        case 0xE1: InstrPattern[Reg_PC] = "SBC ($nn,X)"; ThreadNext(Thr, 2); break;
        case 0xF1: InstrPattern[Reg_PC] = "SBC ($nn),Y"; ThreadNext(Thr, 2); break;

        case 0xC9: InstrPattern[Reg_PC] = "CMP #$nn";    ThreadNext(Thr, 2); break;
        case 0xCD: InstrPattern[Reg_PC] = "CMP $nnnn";   ThreadNext(Thr, 3); break;
        case 0xDD: InstrPattern[Reg_PC] = "CMP $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0xD9: InstrPattern[Reg_PC] = "CMP $nnnn,Y"; ThreadNext(Thr, 3); break;
        case 0xC5: InstrPattern[Reg_PC] = "CMP $nn";     ThreadNext(Thr, 2); break;
        case 0xD5: InstrPattern[Reg_PC] = "CMP $nn,X";   ThreadNext(Thr, 2); break;
        case 0xD2: InstrPattern[Reg_PC] = "CMP ($nn)";   ThreadNext(Thr, 2); break;
        case 0xC1: InstrPattern[Reg_PC] = "CMP ($nn,X)"; ThreadNext(Thr, 2); break;
        case 0xD1: InstrPattern[Reg_PC] = "CMP ($nn),Y"; ThreadNext(Thr, 2); break;

        case 0xE0: InstrPattern[Reg_PC] = "CPX #$nn";    ThreadNext(Thr, 2); break;
        case 0xEC: InstrPattern[Reg_PC] = "CPX $nnnn";   ThreadNext(Thr, 3); break;
        case 0xE4: InstrPattern[Reg_PC] = "CPX $nn"  ;   ThreadNext(Thr, 2); break;

        case 0xC0: InstrPattern[Reg_PC] = "CPY #$nn";    ThreadNext(Thr, 2); break;
        case 0xCC: InstrPattern[Reg_PC] = "CPY $nnnn";   ThreadNext(Thr, 3); break;
        case 0xC4: InstrPattern[Reg_PC] = "CPY $nn";     ThreadNext(Thr, 2); break;


        case 0x3A: InstrPattern[Reg_PC] = "DEC A";       ThreadNext(Thr, 1); break;
        case 0xCE: InstrPattern[Reg_PC] = "DEC $nnnn";   ThreadNext(Thr, 3); break;
        case 0xDE: InstrPattern[Reg_PC] = "DEC $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0xC6: InstrPattern[Reg_PC] = "DEC $nn";     ThreadNext(Thr, 2); break;
        case 0xD6: InstrPattern[Reg_PC] = "DEC $nn,X";   ThreadNext(Thr, 2); break;
        case 0xCA: InstrPattern[Reg_PC] = "DEX";         ThreadNext(Thr, 1); break;
        case 0x88: InstrPattern[Reg_PC] = "DEY";         ThreadNext(Thr, 1); break;

        case 0x1A: InstrPattern[Reg_PC] = "INC A";       ThreadNext(Thr, 1); break;
        case 0xEE: InstrPattern[Reg_PC] = "INC $nnnn";   ThreadNext(Thr, 3); break;
        case 0xFE: InstrPattern[Reg_PC] = "INC $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0xE6: InstrPattern[Reg_PC] = "INC $nn";     ThreadNext(Thr, 2); break;
        case 0xF6: InstrPattern[Reg_PC] = "INC $nn,X";   ThreadNext(Thr, 2); break;
        case 0xE8: InstrPattern[Reg_PC] = "INX";         ThreadNext(Thr, 1); break;
        case 0xC8: InstrPattern[Reg_PC] = "INY";         ThreadNext(Thr, 1); break;


        case 0x4C: InstrPattern[Reg_PC] = "JMP !nnnn";   ThreadNext(Thr, -3); ThreadAdd(CalcAddr(Reg_PC)); break;
        case 0x6C: InstrPattern[Reg_PC] = "JMP ($nnnn)"; ThreadNext(Thr, -3); ThreadAddVector(Reg_PC); break;
        case 0x7C: InstrPattern[Reg_PC] = "JMP ($nnnn,X)"; ThreadNext(Thr, -3); ThreadAddVector(Reg_PC); break;
        case 0x20: InstrPattern[Reg_PC] = "JSR !nnnn";   ThreadNext(Thr, 3); ThreadAdd(CalcAddr(Reg_PC)); break;

        case 0x40: InstrPattern[Reg_PC] = "RTI";         ThreadNext(Thr, -1); break;
        case 0x60: InstrPattern[Reg_PC] = "RTS";         ThreadNext(Thr, -1); break;


        case 0x90: InstrPattern[Reg_PC] = "BCC ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;
        case 0xB0: InstrPattern[Reg_PC] = "BCS ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;
        case 0xD0: InstrPattern[Reg_PC] = "BNE ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;
        case 0xF0: InstrPattern[Reg_PC] = "BEQ ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;
        case 0x10: InstrPattern[Reg_PC] = "BPL ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;
        case 0x30: InstrPattern[Reg_PC] = "BMI ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;
        case 0x50: InstrPattern[Reg_PC] = "BVC ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;
        case 0x70: InstrPattern[Reg_PC] = "BVS ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;


        case 0x18: InstrPattern[Reg_PC] = "CLC";         ThreadNext(Thr, 1); break;
        case 0xD8: InstrPattern[Reg_PC] = "CLD";         ThreadNext(Thr, 1); break;
        case 0x58: InstrPattern[Reg_PC] = "CLI";         ThreadNext(Thr, 1); break;
        case 0xB8: InstrPattern[Reg_PC] = "CLV";         ThreadNext(Thr, 1); break;

        case 0x38: InstrPattern[Reg_PC] = "SEC";         ThreadNext(Thr, 1); break;
        case 0xF8: InstrPattern[Reg_PC] = "SED";         ThreadNext(Thr, 1); break;
        case 0x78: InstrPattern[Reg_PC] = "SEI";         ThreadNext(Thr, 1); break;

        default:
            ProcessOpcodeExt(Thr);
            break;
    }
}

void ScriptDecompileMOS65C02::ProcessOpcodeExt(int Thr)
{
    int Reg_PC = ProgramCounterThreads[Thr];
    uchar OpCode = MemProg[ProgramCounterThreads[Thr]];
    switch (OpCode)
    {
        default:
            InstrPattern[Reg_PC] = "?";
            ThreadNext(Thr, 0);
            break;

        case 0xEA: InstrPattern[Reg_PC] = "NOP";         ThreadNext(Thr, 1); break;
            break;

        case 0x80: InstrPattern[Reg_PC] = "BRA ~nnnn";   ThreadNext(Thr, 2); ThreadAdd(CalcBranch(Reg_PC)); break;

        case 0x1C: InstrPattern[Reg_PC] = "TRB $nnnn";   ThreadNext(Thr, 3); break;
        case 0x14: InstrPattern[Reg_PC] = "TRB $nn";     ThreadNext(Thr, 2); break;
        case 0x0C: InstrPattern[Reg_PC] = "TSB $nnnn";   ThreadNext(Thr, 3); break;
        case 0x04: InstrPattern[Reg_PC] = "TSB $nn";     ThreadNext(Thr, 2); break;

        case 0x9C: InstrPattern[Reg_PC] = "STZ $nnnn";   ThreadNext(Thr, 3); break;
        case 0x9E: InstrPattern[Reg_PC] = "STZ $nnnn,X"; ThreadNext(Thr, 3); break;
        case 0x64: InstrPattern[Reg_PC] = "STZ $nn";     ThreadNext(Thr, 2); break;
        case 0x74: InstrPattern[Reg_PC] = "STZ $nn,Y";   ThreadNext(Thr, 2); break;


        case 0x07: InstrPattern[Reg_PC] = "RMB0 $nn";    ThreadNext(Thr, 2); break;
        case 0x17: InstrPattern[Reg_PC] = "RMB1 $nn";    ThreadNext(Thr, 2); break;
        case 0x27: InstrPattern[Reg_PC] = "RMB2 $nn";    ThreadNext(Thr, 2); break;
        case 0x37: InstrPattern[Reg_PC] = "RMB3 $nn";    ThreadNext(Thr, 2); break;
        case 0x47: InstrPattern[Reg_PC] = "RMB4 $nn";    ThreadNext(Thr, 2); break;
        case 0x57: InstrPattern[Reg_PC] = "RMB5 $nn";    ThreadNext(Thr, 2); break;
        case 0x67: InstrPattern[Reg_PC] = "RMB6 $nn";    ThreadNext(Thr, 2); break;
        case 0x77: InstrPattern[Reg_PC] = "RMB7 $nn";    ThreadNext(Thr, 2); break;

        case 0x87: InstrPattern[Reg_PC] = "SMB0 $nn";    ThreadNext(Thr, 2); break;
        case 0x97: InstrPattern[Reg_PC] = "SMB1 $nn";    ThreadNext(Thr, 2); break;
        case 0xA7: InstrPattern[Reg_PC] = "SMB2 $nn";    ThreadNext(Thr, 2); break;
        case 0xB7: InstrPattern[Reg_PC] = "SMB3 $nn";    ThreadNext(Thr, 2); break;
        case 0xC7: InstrPattern[Reg_PC] = "SMB4 $nn";    ThreadNext(Thr, 2); break;
        case 0xD7: InstrPattern[Reg_PC] = "SMB5 $nn";    ThreadNext(Thr, 2); break;
        case 0xE7: InstrPattern[Reg_PC] = "SMB6 $nn";    ThreadNext(Thr, 2); break;
        case 0xF7: InstrPattern[Reg_PC] = "SMB7 $nn";    ThreadNext(Thr, 2); break;


        case 0x0F: InstrPattern[Reg_PC] = "BBR0 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0x1F: InstrPattern[Reg_PC] = "BBR1 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0x2F: InstrPattern[Reg_PC] = "BBR2 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0x3F: InstrPattern[Reg_PC] = "BBR3 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0x4F: InstrPattern[Reg_PC] = "BBR4 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0x5F: InstrPattern[Reg_PC] = "BBR5 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0x6F: InstrPattern[Reg_PC] = "BBR6 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0x7F: InstrPattern[Reg_PC] = "BBR7 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;

        case 0x8F: InstrPattern[Reg_PC] = "BBS0 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0x9F: InstrPattern[Reg_PC] = "BBS1 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0xAF: InstrPattern[Reg_PC] = "BBS2 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0xBF: InstrPattern[Reg_PC] = "BBS3 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0xCF: InstrPattern[Reg_PC] = "BBS4 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0xDF: InstrPattern[Reg_PC] = "BBS5 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0xEF: InstrPattern[Reg_PC] = "BBS6 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
        case 0xFF: InstrPattern[Reg_PC] = "BBS7 $nn,~~nnnn"; ThreadNext(Thr, 3); ThreadAdd(CalcBranch1(Reg_PC)); break;
    }
}

int ScriptDecompileMOS65C02::CalcAddr(int Reg_PC)
{
    int AddrH = MemProg[Reg_PC + 2];
    int AddrL = MemProg[Reg_PC + 1];
    return (AddrH << 8) + AddrL;
}

int ScriptDecompileMOS65C02::CalcBranch(int Reg_PC)
{
    Reg_PC++;
    int Offset = MemProg[Reg_PC];
    if (Offset < 128)
    {
        return Reg_PC + Offset + 1;
    }
    else
    {
        return Reg_PC + Offset - 255;
    }
}

int ScriptDecompileMOS65C02::CalcBranch1(int Reg_PC)
{
    Reg_PC++;
    Reg_PC++;
    ushort Offset = MemProg[Reg_PC];
    if (Offset < 128)
    {
        return Reg_PC + Offset + 1;
    }
    else
    {
        return Reg_PC + Offset - 255;
    }
}

std::string ScriptDecompileMOS65C02::InstructionName(int Addr)
{
    std::string Name = InstrPattern[Addr];
    Name = StringFindReplace(Name, "~~nnnn", LabelPrefix + Hex::IntToHex16(CalcBranch1(Addr)));
    Name = StringFindReplace(Name, "~nnnn", LabelPrefix + Hex::IntToHex16(CalcBranch(Addr)));
    Name = StringFindReplace(Name, "!nnnn", LabelPrefix + Hex::IntToHex16(CalcAddr(Addr)));
    Name = StringFindReplace(Name, "$nnnn", "$" + Hex::IntToHex8(MemProg[Addr + 2]) + Hex::IntToHex8(MemProg[Addr + 1]));
    Name = StringFindReplace(Name, "$nn", "$" + Hex::IntToHex8(MemProg[Addr + 1]));
    return Name;
}

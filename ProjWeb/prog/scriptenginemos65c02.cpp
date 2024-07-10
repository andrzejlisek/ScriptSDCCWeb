#include "scriptenginemos65c02.h"

ScriptEngineMOS65C02::ScriptEngineMOS65C02()
{
    ScriptDecompile_ = new ScriptDecompileMOS65C02();
}

ScriptEngineMOS65C02::~ScriptEngineMOS65C02()
{
    delete ScriptDecompile_;
}

void ScriptEngineMOS65C02::DoCommand()
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

                DoPush((Reg_PC) >> 8);
                DoPush((Reg_PC) & 255);
#ifdef MOS6502_FlagsAsReg
                DoPush(Reg_F);
#else
                uchar Temp_uchar0 = Reg_F_Get;
                DoPush(Temp_uchar0);
#endif
                Reg_PC = MemoryAddress(MemPrg(0xFFFB), MemPrg(0xFFFA));
            }

            // Maskable interrupt
            if ((IntParam & 0x30000) == 0x20000)
            {
                InterruptIdle = false;

                DoPush((Reg_PC) >> 8);
                DoPush((Reg_PC) & 255);
#ifdef MOS6502_FlagsAsReg
                DoPush(Reg_F);
#else
                uchar Temp_uchar0 = Reg_F_Get;
                DoPush(Temp_uchar0);
#endif
                Reg_PC = MemoryAddress(MemPrg(0xFFFF), MemPrg(0xFFFE));
            }
        }
    }

    int OpCode = MemPrg(Reg_PC);

    //DebugTrace();

    Reg_PC++;
    uchar Temp_uchar;
    switch (OpCode)
    {
        case 0xA9: // LDA #$nn
            Reg_A = MemPrg(Reg_PC);
            Reg_PC += 1;
            SetFlagsNZ(Reg_A);
            break;
        case 0xAD: // LDA $nnnn
            Reg_A = AddrGetAbsolute();
            Reg_PC += 2;
            SetFlagsNZ(Reg_A);
            break;
        case 0xBD: // LDA $nnnn,X
            Reg_A = AddrGetXIndexedAbsolute();
            Reg_PC += 2;
            SetFlagsNZ(Reg_A);
            break;
        case 0xB9: // LDA $nnnn,Y
            Reg_A = AddrGetYIndexedAbsolute();
            Reg_PC += 2;
            SetFlagsNZ(Reg_A);
            break;
        case 0xA5: // LDA $nn
            Reg_A = AddrGetZeroPage();
            Reg_PC += 1;
            SetFlagsNZ(Reg_A);
            break;
        case 0xB5: // LDA $nn,X
            Reg_A = AddrGetXIndexedZeroPage();
            Reg_PC += 1;
            SetFlagsNZ(Reg_A);
            break;
        case 0xB2: // LDA ($nn)
            Reg_A = AddrGetZeroPageIndirect();
            Reg_PC += 1;
            SetFlagsNZ(Reg_A);
            break;
        case 0xA1: // LDA ($nn,X)
            Reg_A = AddrGetXIndexedZeroPageIndirect();
            Reg_PC += 1;
            SetFlagsNZ(Reg_A);
            break;
        case 0xB1: // LDA ($nn),Y
            Reg_A = AddrGetZeroPageIndirectYIndexed();
            Reg_PC += 1;
            SetFlagsNZ(Reg_A);
            break;

        case 0xA2: // LDX #$nn
            Reg_X = MemPrg(Reg_PC);
            Reg_PC += 1;
            SetFlagsNZ(Reg_X);
            break;
        case 0xAE: // LDX $nnnn
            Reg_X = AddrGetAbsolute();
            Reg_PC += 2;
            SetFlagsNZ(Reg_X);
            break;
        case 0xBE: // LDX $nnnn,Y
            Reg_X = AddrGetXIndexedAbsolute();
            Reg_PC += 2;
            SetFlagsNZ(Reg_X);
            break;
        case 0xA6: // LDX $nn
            Reg_X = AddrGetZeroPage();
            Reg_PC += 1;
            SetFlagsNZ(Reg_X);
            break;
        case 0xB6: // LDX $nn,Y
            Reg_X = AddrGetYIndexedZeroPage();
            Reg_PC += 1;
            SetFlagsNZ(Reg_X);
            break;

        case 0xA0: // LDY #$nn
            Reg_Y = MemPrg(Reg_PC);
            Reg_PC += 1;
            SetFlagsNZ(Reg_Y);
            break;
        case 0xAC: // LDY $nnnn
            Reg_Y = AddrGetAbsolute();
            Reg_PC += 2;
            SetFlagsNZ(Reg_Y);
            break;
        case 0xBC: // LDY $nnnn,X
            Reg_Y = AddrGetXIndexedAbsolute();
            Reg_PC += 2;
            SetFlagsNZ(Reg_Y);
            break;
        case 0xA4: // LDY $nn
            Reg_Y = AddrGetZeroPage();
            Reg_PC += 1;
            SetFlagsNZ(Reg_Y);
            break;
        case 0xB4: // LDY $nn,X
            Reg_Y = AddrGetXIndexedZeroPage();
            Reg_PC += 1;
            SetFlagsNZ(Reg_Y);
            break;

        case 0x8D: // STA $nnnn
            AddrSetAbsolute(Reg_A);
            Reg_PC += 2;
            break;
        case 0x9D: // STA $nnnn,X
            AddrSetXIndexedAbsolute(Reg_A);
            Reg_PC += 2;
            break;
        case 0x99: // STA $nnnn,Y
            AddrSetYIndexedAbsolute(Reg_A);
            Reg_PC += 2;
            break;
        case 0x85: // STA $nn
            AddrSetZeroPage(Reg_A);
            Reg_PC += 1;
            break;
        case 0x95: // STA $nn,X
            AddrSetXIndexedZeroPage(Reg_A);
            Reg_PC += 1;
            break;
        case 0x92: // STA ($nn)
            AddrSetZeroPageIndirect(Reg_A);
            Reg_PC += 1;
            break;
        case 0x81: // STA ($nn,X)
            AddrSetXIndexedZeroPageIndirect(Reg_A);
            Reg_PC += 1;
            break;
        case 0x91: // STA ($nn),Y
            AddrSetZeroPageIndirectYIndexed(Reg_A);
            Reg_PC += 1;
            break;

        case 0x8E: // STX $nnnn
            AddrSetAbsolute(Reg_X);
            Reg_PC += 2;
            break;
        case 0x86: // STX $nn
            AddrSetZeroPage(Reg_X);
            Reg_PC += 1;
            break;
        case 0x96: // STX $nn,Y
            AddrSetYIndexedZeroPage(Reg_X);
            Reg_PC += 1;
            break;

        case 0x8C: // STY $nnnn
            AddrSetAbsolute(Reg_Y);
            Reg_PC += 2;
            break;
        case 0x84: // STY $nn
            AddrSetZeroPage(Reg_Y);
            Reg_PC += 1;
            break;
        case 0x94: // STY $nn,Y
            AddrSetXIndexedZeroPage(Reg_Y);
            Reg_PC += 1;
            break;


        case 0xAA: // TAX
            Reg_X = Reg_A;
            SetFlagsNZ(Reg_X);
            break;
        case 0xA8: // TAY
            Reg_Y = Reg_A;
            SetFlagsNZ(Reg_Y);
            break;
        case 0xBA: // TSX
            Reg_X = Reg_SP;
            SetFlagsNZ(Reg_X);
            break;
        case 0x8A: // TXA
            Reg_A = Reg_X;
            SetFlagsNZ(Reg_A);
            break;
        case 0x9A: // TXS
            Reg_SP = Reg_X;
            SetFlagsNZ(Reg_SP);
            break;
        case 0x98: // TYA
            Reg_A = Reg_Y;
            SetFlagsNZ(Reg_A);
            break;


        case 0x48: // PHA
            DoPush(Reg_A);
            break;
        case 0x08: // PHP
#ifdef MOS6502_FlagsAsReg
            DoPush(Reg_F);
#else
            Temp_uchar = Reg_F_Get;
            DoPush(Temp_uchar);
#endif
            break;
        case 0xDA: // PHX
            DoPush(Reg_X);
            break;
        case 0x5A: // PHY
            DoPush(Reg_Y);
            break;
        case 0x68: // PLA
            Reg_A = DoPop();
            SetFlagsNZ(Reg_A);
            break;
        case 0x28: // PLP
#ifdef MOS6502_FlagsAsReg
            Reg_F = DoPop();
#else
            Temp_uchar = DoPop();
            Reg_F_Set(Temp_uchar);
#endif
            break;
        case 0xFA: // PLX
            Reg_X = DoPop();
            SetFlagsNZ(Reg_X);
            break;
        case 0x7A: // PLY
            Reg_Y = DoPop();
            SetFlagsNZ(Reg_Y);
            break;


        case 0x0A: // ASL A
            Reg_A = DoShiftL(Reg_A, false);
            break;
        case 0x0E: // ASL $nnnn
            AddrSetAbsolute(DoShiftL(AddrGetAbsolute(), false));
            Reg_PC += 2;
            break;
        case 0x1E: // ASL $nnnn,X
            AddrSetXIndexedAbsolute(DoShiftL(AddrGetXIndexedAbsolute(), false));
            Reg_PC += 2;
            break;
        case 0x06: // ASL $nn
            AddrSetZeroPage(DoShiftL(AddrGetZeroPage(), false));
            Reg_PC += 1;
            break;
        case 0x16: // ASL $nn,X
            AddrSetXIndexedZeroPage(DoShiftL(AddrGetXIndexedZeroPage(), false));
            Reg_PC += 1;
            break;

        case 0x4A: // LSR A
            Reg_A = DoShiftR(Reg_A, false);
            break;
        case 0x4E: // LSR $nnnn
            AddrSetAbsolute(DoShiftR(AddrGetAbsolute(), false));
            Reg_PC += 2;
            break;
        case 0x5E: // LSR $nnnn,X
            AddrSetXIndexedAbsolute(DoShiftR(AddrGetXIndexedAbsolute(), false));
            Reg_PC += 2;
            break;
        case 0x46: // LSR $nn
            AddrSetZeroPage(DoShiftR(AddrGetZeroPage(), false));
            Reg_PC += 1;
            break;
        case 0x56: // LSR $nn,X
            AddrSetXIndexedZeroPage(DoShiftR(AddrGetXIndexedZeroPage(), false));
            Reg_PC += 1;
            break;

        case 0x2A: // ROL A
            Reg_A = DoShiftL(Reg_A, true);
            break;
        case 0x2E: // ROL $nnnn
            AddrSetAbsolute(DoShiftL(AddrGetAbsolute(), true));
            Reg_PC += 2;
            break;
        case 0x3E: // ROL $nnnn,X
            AddrSetXIndexedAbsolute(DoShiftL(AddrGetXIndexedAbsolute(), true));
            Reg_PC += 2;
            break;
        case 0x26: // ROL $nn
            AddrSetZeroPage(DoShiftL(AddrGetZeroPage(), true));
            Reg_PC += 1;
            break;
        case 0x36: // ROL $nn,X
            AddrSetXIndexedZeroPage(DoShiftL(AddrGetXIndexedZeroPage(), true));
            Reg_PC += 1;
            break;

        case 0x6A: // ROR A
            Reg_A = DoShiftR(Reg_A, true);
            break;
        case 0x6E: // ROR $nnnn
            AddrSetAbsolute(DoShiftR(AddrGetAbsolute(), true));
            Reg_PC += 2;
            break;
        case 0x7E: // ROR $nnnn,X
            AddrSetXIndexedAbsolute(DoShiftR(AddrGetXIndexedAbsolute(), true));
            Reg_PC += 2;
            break;
        case 0x66: // ROR $nn
            AddrSetZeroPage(DoShiftR(AddrGetZeroPage(), true));
            Reg_PC += 1;
            break;
        case 0x76: // ROR $nn,X
            AddrSetXIndexedZeroPage(DoShiftR(AddrGetXIndexedZeroPage(), true));
            Reg_PC += 1;
            break;


        case 0x89: // BIT #$nn
            Temp_uchar = Reg_A & MemPrg(Reg_PC);
            MOS6502_FlagNVal(Temp_uchar & 0b10000000);
            MOS6502_FlagVVal(Temp_uchar & 0b01000000);
            MOS6502_FlagZVal(Temp_uchar == 0);
            Reg_PC += 1;
            break;
        case 0x2C: // BIT $nnnn
            Temp_uchar = Reg_A & AddrGetAbsolute();
            MOS6502_FlagNVal(Temp_uchar & 0b10000000);
            MOS6502_FlagVVal(Temp_uchar & 0b01000000);
            MOS6502_FlagZVal(Temp_uchar == 0);
            Reg_PC += 2;
            break;
        case 0x3C: // BIT $nnnn,X
            Temp_uchar = Reg_A & AddrGetXIndexedAbsolute();
            MOS6502_FlagNVal(Temp_uchar & 0b10000000);
            MOS6502_FlagVVal(Temp_uchar & 0b01000000);
            MOS6502_FlagZVal(Temp_uchar == 0);
            Reg_PC += 2;
            break;
        case 0x24: // BIT $nn
            Temp_uchar = Reg_A & AddrGetZeroPage();
            MOS6502_FlagNVal(Temp_uchar & 0b10000000);
            MOS6502_FlagVVal(Temp_uchar & 0b01000000);
            MOS6502_FlagZVal(Temp_uchar == 0);
            Reg_PC += 1;
            break;
        case 0x34: // BIT $nn,X
            Temp_uchar = Reg_A & AddrGetXIndexedZeroPage();
            MOS6502_FlagNVal(Temp_uchar & 0b10000000);
            MOS6502_FlagVVal(Temp_uchar & 0b01000000);
            MOS6502_FlagZVal(Temp_uchar == 0);
            Reg_PC += 1;
            break;

        case 0x29: // AND #$nn
            Reg_A = Reg_A & MemPrg(Reg_PC);
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x2D: // AND $nnnn
            Reg_A = Reg_A & AddrGetAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x3D: // AND $nnnn,X
            Reg_A = Reg_A & AddrGetXIndexedAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x39: // AND $nnnn,Y
            Reg_A = Reg_A & AddrGetYIndexedAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x25: // AND $nn
            Reg_A = Reg_A & AddrGetZeroPage();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x35: // AND $nn,X
            Reg_A = Reg_A & AddrGetXIndexedZeroPage();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x32: // AND ($nn)
            Reg_A = Reg_A & AddrGetZeroPageIndirect();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x21: // AND ($nn,X)
            Reg_A = Reg_A & AddrGetXIndexedZeroPageIndirect();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x31: // AND ($nn),Y
            Reg_A = Reg_A & AddrGetZeroPageIndirectYIndexed();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;

        case 0x49: // EOR #$nn
            Reg_A = Reg_A ^ MemPrg(Reg_PC);
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x4D: // EOR $nnnn
            Reg_A = Reg_A ^ AddrGetAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x5D: // EOR $nnnn,X
            Reg_A = Reg_A ^ AddrGetXIndexedAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x59: // EOR $nnnn,Y
            Reg_A = Reg_A ^ AddrGetYIndexedAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x45: // EOR $nn
            Reg_A = Reg_A ^ AddrGetZeroPage();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x55: // EOR $nn,X
            Reg_A = Reg_A ^ AddrGetXIndexedZeroPage();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x52: // EOR ($nn)
            Reg_A = Reg_A ^ AddrGetZeroPageIndirect();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x41: // EOR ($nn,X)
            Reg_A = Reg_A ^ AddrGetXIndexedZeroPageIndirect();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x51: // EOR ($nn),Y
            Reg_A = Reg_A ^ AddrGetZeroPageIndirectYIndexed();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;

        case 0x09: // ORA #$nn
            Reg_A = Reg_A | MemPrg(Reg_PC);
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x0D: // ORA $nnnn
            Reg_A = Reg_A | AddrGetAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x1D: // ORA $nnnn,X
            Reg_A = Reg_A | AddrGetXIndexedAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x19: // ORA $nnnn,Y
            Reg_A = Reg_A | AddrGetYIndexedAbsolute();
            SetFlagsNZ(Reg_A);
            Reg_PC += 2;
            break;
        case 0x05: // ORA $nn
            Reg_A = Reg_A | AddrGetZeroPage();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x15: // ORA $nn,X
            Reg_A = Reg_A | AddrGetXIndexedZeroPage();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x12: // ORA ($nn)
            Reg_A = Reg_A | AddrGetZeroPageIndirect();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x01: // ORA ($nn,X)
            Reg_A = Reg_A | AddrGetXIndexedZeroPageIndirect();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;
        case 0x11: // ORA ($nn),Y
            Reg_A = Reg_A | AddrGetZeroPageIndirectYIndexed();
            SetFlagsNZ(Reg_A);
            Reg_PC += 1;
            break;


        case 0x69: // ADC #$nn
            Reg_A = DoADC(Reg_A, MemPrg(Reg_PC));
            Reg_PC += 1;
            break;
        case 0x6D: // ADC $nnnn
            Reg_A = DoADC(Reg_A, AddrGetAbsolute());
            Reg_PC += 2;
            break;
        case 0x7D: // ADC $nnnn,X
            Reg_A = DoADC(Reg_A, AddrGetXIndexedAbsolute());
            Reg_PC += 2;
            break;
        case 0x79: // ADC $nnnn,Y
            Reg_A = DoADC(Reg_A, AddrGetYIndexedAbsolute());
            Reg_PC += 2;
            break;
        case 0x65: // ADC $nn
            Reg_A = DoADC(Reg_A, AddrGetZeroPage());
            Reg_PC += 1;
            break;
        case 0x75: // ADC $nn,X
            Reg_A = DoADC(Reg_A, AddrGetXIndexedZeroPage());
            Reg_PC += 1;
            break;
        case 0x72: // ADC ($nn)
            Reg_A = DoADC(Reg_A, AddrGetZeroPageIndirect());
            Reg_PC += 1;
            break;
        case 0x61: // ADC ($nn,X)
            Reg_A = DoADC(Reg_A, AddrGetXIndexedZeroPageIndirect());
            Reg_PC += 1;
            break;
        case 0x71: // ADC ($nn),Y
            Reg_A = DoADC(Reg_A, AddrGetZeroPageIndirectYIndexed());
            Reg_PC += 1;
            break;

        case 0xE9: // SBC #$nn
            Reg_A = DoSUB(Reg_A, MemPrg(Reg_PC));
            Reg_PC += 1;
            break;
        case 0xED: // SBC $nnnn
            Reg_A = DoSUB(Reg_A, AddrGetAbsolute());
            Reg_PC += 2;
            break;
        case 0xFD: // SBC $nnnn,X
            Reg_A = DoSUB(Reg_A, AddrGetXIndexedAbsolute());
            Reg_PC += 2;
            break;
        case 0xF9: // SBC $nnnn,Y
            Reg_A = DoSUB(Reg_A, AddrGetYIndexedAbsolute());
            Reg_PC += 2;
            break;
        case 0xE5: // SBC $nn
            Reg_A = DoSUB(Reg_A, AddrGetZeroPage());
            Reg_PC += 1;
            break;
        case 0xF5: // SBC $nn,X
            Reg_A = DoSUB(Reg_A, AddrGetXIndexedZeroPage());
            Reg_PC += 1;
            break;
        case 0xF2: // SBC ($nn)
            Reg_A = DoSUB(Reg_A, AddrGetZeroPageIndirect());
            Reg_PC += 1;
            break;
        case 0xE1: // SBC ($nn,X)
            Reg_A = DoSUB(Reg_A, AddrGetXIndexedZeroPageIndirect());
            Reg_PC += 1;
            break;
        case 0xF1: // SBC ($nn),Y
            Reg_A = DoSUB(Reg_A, AddrGetZeroPageIndirectYIndexed());
            Reg_PC += 1;
            break;

        case 0xC9: // CMP #$nn
            DoCMP(Reg_A, MemPrg(Reg_PC));
            Reg_PC += 1;
            break;
        case 0xCD: // CMP $nnnn
            DoCMP(Reg_A, AddrGetAbsolute());
            Reg_PC += 2;
            break;
        case 0xDD: // CMP $nnnn,X
            DoCMP(Reg_A, AddrGetXIndexedAbsolute());
            Reg_PC += 2;
            break;
        case 0xD9: // CMP $nnnn,Y
            DoCMP(Reg_A, AddrGetYIndexedAbsolute());
            Reg_PC += 2;
            break;
        case 0xC5: // CMP $nn
            DoCMP(Reg_A, AddrGetZeroPage());
            Reg_PC += 1;
            break;
        case 0xD5: // CMP $nn,X
            DoCMP(Reg_A, AddrGetXIndexedZeroPage());
            Reg_PC += 1;
            break;
        case 0xD2: // CMP ($nn)
            DoCMP(Reg_A, AddrGetZeroPageIndirect());
            Reg_PC += 1;
            break;
        case 0xC1: // CMP ($nn,X)
            DoCMP(Reg_A, AddrGetXIndexedZeroPageIndirect());
            Reg_PC += 1;
            break;
        case 0xD1: // CMP ($nn),Y
            DoCMP(Reg_A, AddrGetZeroPageIndirectYIndexed());
            Reg_PC += 1;
            break;

        case 0xE0: // CPX #$nn
            DoCMP(Reg_X, MemPrg(Reg_PC));
            Reg_PC += 1;
            break;
        case 0xEC: // CPX $nnnn
            DoCMP(Reg_X, AddrGetAbsolute());
            Reg_PC += 2;
            break;
        case 0xE4: // CPX $nn
            DoCMP(Reg_X, AddrGetZeroPage());
            Reg_PC += 1;
            break;

        case 0xC0: // CPY #$nn
            DoCMP(Reg_Y, MemPrg(Reg_PC));
            Reg_PC += 1;
            break;
        case 0xCC: // CPY $nnnn
            DoCMP(Reg_Y, AddrGetAbsolute());
            Reg_PC += 2;
            break;
        case 0xC4: // CPY $nn
            DoCMP(Reg_Y, AddrGetZeroPage());
            Reg_PC += 1;
            break;


        case 0x3A: // DEC A
            Reg_A = DoDEC(Reg_A);
            break;
        case 0xCE: // DEC $nnnn
            AddrSetAbsolute(DoDEC(AddrGetAbsolute()));
            Reg_PC += 2;
            break;
        case 0xDE: // DEC $nnnn,X
            AddrSetXIndexedAbsolute(DoDEC(AddrGetXIndexedAbsolute()));
            Reg_PC += 2;
            break;
        case 0xC6: // DEC $nn
            AddrSetZeroPage(DoDEC(AddrGetZeroPage()));
            Reg_PC += 1;
            break;
        case 0xD6: // DEC $nn,X
            AddrSetXIndexedZeroPage(DoDEC(AddrGetXIndexedZeroPage()));
            Reg_PC += 1;
            break;
        case 0xCA: // DEX
            Reg_X = DoDEC(Reg_X);
            break;
        case 0x88: // DEY
            Reg_Y = DoDEC(Reg_Y);
            break;

        case 0x1A: // INC A
            Reg_A = DoINC(Reg_A);
            break;
        case 0xEE: // INC $nnnn
            AddrSetAbsolute(DoINC(AddrGetAbsolute()));
            Reg_PC += 2;
            break;
        case 0xFE: // INC $nnnn,X
            AddrSetXIndexedAbsolute(DoINC(AddrGetXIndexedAbsolute()));
            Reg_PC += 2;
            break;
        case 0xE6: // INC $nn
            AddrSetZeroPage(DoINC(AddrGetZeroPage()));
            Reg_PC += 1;
            break;
        case 0xF6: // INC $nn,X
            AddrSetXIndexedZeroPage(DoINC(AddrGetXIndexedZeroPage()));
            Reg_PC += 1;
            break;
        case 0xE8: // INX
            Reg_X = DoINC(Reg_X);
            break;
        case 0xC8: // INY
            Reg_Y = DoINC(Reg_Y);
            break;


        case 0x4C: // JMP $nnnn
            Reg_PC = MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
            break;
        case 0x6C: // JMP ($nnnn)
            {
                int Addr = MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
                int Addr_ = MemoryAddress(MemGet(Addr + 1), MemGet(Addr));
                ScriptDecompile_->JumpVectorAddr(Reg_PC - 1, Addr_);
                Reg_PC = Addr_;
            }
            break;
        case 0x7C: // JMP ($nnnn,X)
            {
                int Addr = MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC)) + Reg_X;
                int Addr_ = MemoryAddress(MemGet(Addr + 1), MemGet(Addr));
                ScriptDecompile_->JumpVectorAddr(Reg_PC - 1, Addr_);
                Reg_PC = Addr_;
            }
            break;
        case 0x20: // JSR $nnnn
            DoPush((Reg_PC + 1) >> 8);
            DoPush((Reg_PC + 1) & 255);
            Reg_PC = MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
            break;

        case 0x40: // RTI
#ifdef MOS6502_FlagsAsReg
            Reg_F = DoPop();
#else
            Temp_uchar = DoPop();
            Reg_F_Set(Temp_uchar);
#endif
            Reg_PC = 0;
            Reg_PC = (int)DoPop();
            Reg_PC = Reg_PC + ((int)DoPop() << 8);
            InterruptFinish();
            break;
        case 0x60: // RTS
            Reg_PC = 0;
            Reg_PC = (int)DoPop();
            Reg_PC = Reg_PC + ((int)DoPop() << 8);
            Reg_PC++;
            break;


        case 0x90: // BCC $nnnn
            if (MOS6502_FlagCGet) { Reg_PC++; } else { DoBranch(); }
            break;
        case 0xB0: // BCS $nnnn
            if (MOS6502_FlagCGet) { DoBranch(); } else { Reg_PC++; }
            break;
        case 0xD0: // BNE $nnnn
            if (MOS6502_FlagZGet) { Reg_PC++; } else { DoBranch(); }
            break;
        case 0xF0: // BEQ $nnnn
            if (MOS6502_FlagZGet) { DoBranch(); } else { Reg_PC++; }
            break;
        case 0x10: // BPL $nnnn
            if (MOS6502_FlagNGet) { Reg_PC++; } else { DoBranch(); }
            break;
        case 0x30: // BMI $nnnn
            if (MOS6502_FlagNGet) { DoBranch(); } else { Reg_PC++; }
            break;
        case 0x50: // BVC $nnnn
            if (MOS6502_FlagVGet) { Reg_PC++; } else { DoBranch(); }
            break;
        case 0x70: // BVS $nnnn
            if (MOS6502_FlagVGet) { DoBranch(); } else { Reg_PC++; }
            break;


        case 0x18: // CLC
            MOS6502_FlagCClr;
            break;
        case 0xD8: // CLD
            MOS6502_FlagDClr;
            break;
        case 0x58: // CLI
            MOS6502_FlagIClr;
            break;
        case 0xB8: // CLV
            MOS6502_FlagVClr;
            break;

        case 0x38: // SEC
            MOS6502_FlagCSet;
            break;
        case 0xF8: // SED
            MOS6502_FlagDSet;
            break;
        case 0x78: // SEI
            MOS6502_FlagISet;
            break;

        default:
            DoCommandExt(OpCode);
            break;
    }
}

void ScriptEngineMOS65C02::DoReset()
{
    Reg_A = 0;
    Reg_X = 0;
    Reg_Y = 0;
    Reg_SP = 255;
    Reg_PC = MemoryAddress(MemPrg(0xFFFD), MemPrg(0xFFFC));
#ifdef MOS6502_FlagsAsReg
    Reg_F = 0b00110000;
#else
    Reg_F_Set(0b00110000);
#endif
}

std::string ScriptEngineMOS65C02::GetEntryPoints()
{
    return "X" + Hex::IntToHex16(MemoryAddress(MemPrg(0xFFFD), MemPrg(0xFFFC))) + "X" + Hex::IntToHex16(MemoryAddress(MemPrg(0xFFFB), MemPrg(0xFFFA))) + "X" + Hex::IntToHex16(MemoryAddress(MemPrg(0xFFFF), MemPrg(0xFFFE))) + "X";
}

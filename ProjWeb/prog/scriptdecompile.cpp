#include "scriptdecompile.h"

ScriptDecompile::ScriptDecompile()
{

}

ScriptDecompile::~ScriptDecompile()
{

}

void ScriptDecompile::DecompilePrepare(uchar * MemProg_, uchar * MemMapP_, uchar * MemMapC_)
{
    for (int I = 0; I < 65536; I++)
    {
        DecompiledOpcodes[I] = 0;
        DecompiledLabels[I] = 0;
        InstrPattern[I] = "";
    }
    MemProg = MemProg_;
    MemMapP = MemMapP_;
    MemMapC = MemMapC_;
    JumpVector1.clear();
    JumpVector2.clear();
}

void ScriptDecompile::InitDecompile(int EntryPoint)
{
    ProgramCounterThreads.clear();
    ThreadAdd(EntryPoint);
}

void ScriptDecompile::ThreadAdd(int Addr)
{
    DecompiledLabels[Addr] = 1;
    for (int I = 0; I < ProgramCounterThreads.size(); I++)
    {
        if (ProgramCounterThreads[I] == Addr)
        {
            return;
        }
    }
    ProgramCounterThreads.push_back(Addr);
}

void ScriptDecompile::JumpVectorAddr(int Reg_PC, int Addr)
{
    for (int I = 0; I < JumpVector1.size(); I++)
    {
        if (JumpVector1[I] == Reg_PC)
        {
            if (JumpVector2[I] == Addr)
            {
                return;
            }
        }
    }
    JumpVector1.push_back(Reg_PC);
    JumpVector2.push_back(Addr);
}

void ScriptDecompile::ThreadAddVector(int Reg_PC)
{
    for (int I = 0; I < JumpVector1.size(); I++)
    {
        if (JumpVector1[I] == Reg_PC)
        {
            ThreadAdd(JumpVector2[I]);
        }
    }
}

void ScriptDecompile::ThreadNext(int Thr, int Step)
{
    int MemAddr = ProgramCounterThreads[Thr];
    int MapIndicate = 8; //ScriptEngineMemMapC;

    MemMapC[MemAddr] = MapIndicate;
    if (Step > 0)
    {
        for (int I = 0; I < Step; I++)
        {
            MemMapC[MemAddr + I] = MapIndicate;
            DecompiledOpcodes[MemAddr + I] = Step;
        }
        DecompiledOpcodes[MemAddr] = Step + 16;
        ProgramCounterThreads[Thr] += Step;
    }
    else
    {
        for (int I = 0; I < (0 - Step); I++)
        {
            MemMapC[MemAddr + I] = MapIndicate;
            DecompiledOpcodes[MemAddr + I] = 0 - Step;
        }
        DecompiledOpcodes[MemAddr] = (0 - Step) + 16;
        ProgramCounterThreads[Thr] = -1;
    }
}
bool ScriptDecompile::DoIterate()
{
    bool DebugThreads = false;
    bool Iterated = false;
    if (DebugThreads)
    {
        for (int I = 0; I < ProgramCounterThreads.size(); I++)
        {
            std::cout << Hex::IntToHex16(ProgramCounterThreads[I]) << "    ";
        }
        std::cout << std::endl;
    }
    int ThrL = ProgramCounterThreads.size();
    for (int I = 0; I < ThrL; I++)
    {
        if (ProgramCounterThreads[I] >= 0)
        {
            if (DecompiledOpcodes[ProgramCounterThreads[I]] == 0)
            {
                ProcessOpcode(I);
                Iterated = true;
            }
            else
            {
                ProgramCounterThreads[I] = -1;
            }
        }
    }
    if (!DebugThreads)
    {
        for (int I = 0; I < ProgramCounterThreads.size(); I++)
        {
            if (ProgramCounterThreads[I] < 0)
            {
                ProgramCounterThreads.erase(ProgramCounterThreads.begin() + I);
                I--;
            }
        }
    }
    return Iterated;
}

std::string ScriptDecompile::StringFindReplace(std::string S, std::string From, std::string To)
{
    int FromLen = From.length();
    int FromPos = S.find(From);
    while (FromPos != std::string::npos)
    {
        S.replace(FromPos, FromLen, To);
        FromPos = S.find(From);
    }
    return S;
}

void ScriptDecompile::GetInfoReset()
{
    InfoState = 0;
    InfoStateLabel = false;
}

std::string ScriptDecompile::GetInfo()
{
    if (InfoState >= 65536)
    {
        return "";
    }

    while (1)
    {
        if (MemMapP[InfoState] > 0)
        {
            std::string Msg = (DecompiledLabels[InfoState] ? "*" : " ") + Hex::IntToHex16(InfoState) + ":";

            if (DecompiledOpcodes[InfoState] >= 16)
            {
                for (int I = 0; I < 4; I++)
                {
                    if (I < (DecompiledOpcodes[InfoState] - 16))
                    {
                        Msg = Msg + " " + Hex::IntToHex8(MemProg[InfoState + I]);
                    }
                    else
                    {
                        Msg = Msg + "   ";
                    }
                }
                Msg = Msg + "            ";
                Msg = Msg + InstructionName(InfoState);
                InfoState = InfoState + (DecompiledOpcodes[InfoState] - 16);
            }
            else
            {
                int SizeMax0 = 4;
                int SizeMax = SizeMax0;
                while ((InfoState + SizeMax) > 65536)
                {
                    SizeMax--;
                }
                for (int I = 0; I < SizeMax; I++)
                {
                    if (((DecompiledOpcodes[InfoState + I]) >= 16) || (MemMapP[InfoState + I] == 0) || (DecompiledLabels[InfoState + I]))
                    {
                        SizeMax = I;
                    }
                }
                for (int I = 0; I < SizeMax0; I++)
                {
                    if (I < SizeMax)
                    {
                        Msg = Msg + " " + Hex::IntToHex8(MemProg[InfoState + I]);
                    }
                    else
                    {
                        Msg = Msg + "   ";
                    }
                }
                InfoState += SizeMax;
            }
            return Msg;
        }
        else
        {
            InfoState++;
        }
        if (InfoState >= 65536)
        {
            return "";
        }
    }
}

std::string ScriptDecompile::GetInfoMem(int Offset, int Length)
{
    std::string Msg = Hex::IntToHex16(Offset) + ":";
    for (int I = 0; I < Length; I++)
    {
        Msg = Msg + " ";
        if (MemMapP[I + Offset])
        {
            Msg = Msg + Hex::IntToHex8(MemProg[I + Offset]);
        }
        else
        {
            Msg = Msg + "__";
        }
    }
    return Msg;
}

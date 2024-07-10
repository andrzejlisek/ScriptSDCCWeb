#include "filehandle.h"

FileHandle::FileHandle()
{
    TempBuf = new char[65536];
    TempOpX = new char[65536];
    for (int I = 0; I < FileHandleCount; I++)
    {
        //F[I] = NULL;
        FileInfo[I] = "";
    }
    for (int I = 0; I < 65536; I++)
    {
        TempOpX[I] = 1;
    }
}

FileHandle::~FileHandle()
{
    for (int I = 0; I < FileHandleCount; I++)
    {
        FileClose(I);
    }
    delete[] TempBuf;
    delete[] TempOpX;
}

bool FileHandle::FileOpen(uchar N, std::string FileName, char AccessMode)
{
    return true;
    /*FileClose(N);
    FN[N] = FileName;
    FA[N] = AccessMode;
    switch (AccessMode)
    {
        case 1: F[N] = NEW(fstream, fstream(FileName, ios::binary | ios::out)); break;
        case 2: F[N] = NEW(fstream, fstream(FileName, ios::binary | ios::in));  break;
        case 3: F[N] = NEW(fstream, fstream(FileName, ios::binary | ios::in | ios::out));  break;
    }
    if (F[N]->is_open())
    {
        FileInfo[N] = "File " + to_string(N);
        switch (FA[N])
        {
            case 1: FileInfo[N] = FileInfo[N] + " (W): "; break;
            case 2: FileInfo[N] = FileInfo[N] + " (R): "; break;
            case 3: FileInfo[N] = FileInfo[N] + " (R&W): "; break;
        }
        FileInfo[N] = FileInfo[N] + FN[N];
        return true;
    }
    else
    {
        DEL(fstream, F[N]);
        F[N] = NULL;
        FileInfo[N] = "";
        return false;
    }*/
}

bool FileHandle::FileClose(uchar N)
{
    return true;
    /*if (F[N] != NULL)
    {
        F[N]->close();
        DEL(fstream, F[N]);
        F[N] = NULL;
        FileInfo[N] = "";
        return true;
    }
    else
    {
        return false;
    }*/
}

uint FileHandle::FileSize(uchar N)
{
    /*if (F[N] != NULL)
    {
        uint X = 0;
        uint S = 0;
        switch (FA[N])
        {
            case 1:
                X = F[N]->tellp();
                F[N]->seekp(0, ios_base::end);
                S = F[N]->tellp();
                F[N]->seekp(X);
            break;
            case 2:
            case 3:
                X = F[N]->tellg();
                F[N]->seekg(0, ios_base::end);
                S = F[N]->tellg();
                F[N]->seekg(X);
            break;
        }
        return S;
    }*/
    return 0;
}

bool FileHandle::FileSetPos(uchar N, uint Pos)
{
    /*if (F[N] != NULL)
    {
        if ((FA[N] == 1) || (FA[N] == 3))
        {
            F[N]->seekp(Pos);
        }
        if ((FA[N] == 2) || (FA[N] == 3))
        {
            F[N]->seekg(Pos);
        }
        return true;
    }*/
    return false;
}

uint FileHandle::FileGetPos(uchar N)
{
    return 0;
    /*uint S = 0;
    if (F[N] != NULL)
    {
        if ((FA[N] == 2) || (FA[N] == 3))
        {
            S = F[N]->tellg();
        }
        else
        {
            S = F[N]->tellp();
        }
        return true;
    }
    return S;*/
}

bool FileHandle::DataPut(uchar N, uchar * DataBuf, uchar * DataBufX, uint DataAddr, uint DataSize)
{
    /*if ((DataAddr + DataSize <= 65536) && (F[N] != NULL))
    {
        memcpy(DataBufX + DataAddr, TempOpX, DataSize);
        memcpy(TempBuf, DataBuf + DataAddr, DataSize);
        F[N]->write(TempBuf, DataSize);
        if (FA[N] == 3)
        {
            F[N]->seekg(F[N]->tellp());
        }
        return true;
    }*/
    return false;
}

bool FileHandle::DataGet(uchar N, uchar * DataBuf, uchar * DataBufX, uint DataAddr, uint DataSize)
{
    /*if ((DataAddr + DataSize <= 65536) && (F[N] != NULL))
    {
        F[N]->read(TempBuf, DataSize);
        memcpy(DataBufX + DataAddr, TempOpX, DataSize);
        memcpy(DataBuf + DataAddr, TempBuf, DataSize);
        if (FA[N] == 3)
        {
            F[N]->seekp(F[N]->tellg());
        }
        return true;
    }*/
    return false;
}

std::string FileHandle::Info()
{
    std::stringstream SS;
    for (int N = 0; N < FileHandleCount; N++)
    {
        //if (F[N] != NULL)
        {
            SS << FileInfo[N] << std::endl;
        }
    }
    return SS.str();
}

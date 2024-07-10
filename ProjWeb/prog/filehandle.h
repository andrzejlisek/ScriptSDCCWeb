#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include "valuetypes.h"
#include <iostream>

class FileHandle
{
    #define FileHandleCount 256
public:
    FileHandle();
    ~FileHandle();
    bool FileOpen(uchar N, std::string FileName, char AccessMode);
    bool FileClose(uchar N);
    uint FileSize(uchar N);
    bool FileSetPos(uchar N, uint Pos);
    uint FileGetPos(uchar N);
    bool DataPut(uchar N, uchar * DataBuf, uchar * DataBufX, uint DataAddr, uint DataSize);
    bool DataGet(uchar N, uchar * DataBuf, uchar * DataBufX, uint DataAddr, uint DataSize);
    std::string Info();
private:
    //fstream * F[FileHandleCount];
    char FA[FileHandleCount];
    char * TempBuf;
    char * TempOpX;
    std::string FN[FileHandleCount];
    std::string FileInfo[FileHandleCount];
};

#endif // FILEHANDLE_H

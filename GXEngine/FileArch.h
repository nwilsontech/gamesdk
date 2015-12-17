/*
#pragma once
#pragma message "Compiling " __FILE__ "..."
*/
#ifndef FILEARCH_H_INCLUDED
#define FILEARCH_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdarg>
#include <cstdio> //exit, free
#include "types.h"

using std::vector;
using std::string;


namespace FARC
{
#define FARC_MAX_FILE_LENGTH 32
enum __OPEN_ENUM
{
    FA_OPEN_READ  = 0,
    FA_OPEN_WRITE
};
enum __FLAGS_ENUM
{
    FA_LOAD_NON  = 0,
    FA_LOAD_AUTO = 1
};
//BaseHeader
#pragma pack(1)
typedef struct _Header
{
    char  ID[6];//arc67
    DWORD files;
} THeader;
//#pragma pop(1)
/*
 *begin modular headers
*/
typedef struct __Header_Mod01
{
    //Awesome Stuff Here
}THeaderMod01;

/*
 *end modular headers
*/
typedef struct _pzfile
{
  char   fn[FARC_MAX_FILE_LENGTH];//Max File Length
  DWORD  fileSize;
  unsigned int crc;
} TFileBlk;
///Stream Struct
typedef struct
{
    unsigned char *buffer;
    size_t  size;
} FAstream;


/*Added 10.14.13*/
bool   StrEqual( const char* s1, const char* s2 );
int    FindLastDelimiter(string Text);
int    FindLastPoint(string Text);
string FindPrevDir(string Text);
int    hasDotDot(string input);
string ExtractFileName(string Input);
string ExtractPathName(string Input);
string ExtractExtName(string Input);
/*
*/


///
typedef vector<string> TStringList;
typedef vector<TFileBlk> TFileBlkList;
class FArchieve;//predefine

class FSetStream
{
public:
    FSetStream(string fname="",string furl="",FArchieve *farch = NULL)
    {
        fileName = fname;
        fileURL  = furl;
        if (farch!=NULL)
        {
            fileOriginType = 0x01;
            __Arc = farch;
        } else
        {
            __Arc = NULL;
            fileOriginType = 0x00;
        }
    }
    ~FSetStream(){}
    string &GetName() {return fileName;}
    string &GetURL()  {return fileURL; }
    FArchieve &GetArc() {return (*__Arc); }
public:
    BYTE      fileOriginType;
    string    fileName;
    string    fileURL;
    FArchieve *__Arc;
};

typedef vector<FSetStream > FSetStrList;

class FArchieve
{
  public:
        FArchieve();
        ~FArchieve();
        bool Open(char *fn,__OPEN_ENUM ot,__FLAGS_ENUM ft=FA_LOAD_NON);//Need to add error checking
        bool ReOpen(char *fn,__OPEN_ENUM ot,__FLAGS_ENUM ft=FA_LOAD_NON);
        bool Close(void);
        bool LoadInfo(void);
        bool LoadFileIntoBuf(UCHAR *dest,size_t s,char *fn);
        bool IsOpen();
        int  LookUpFileSize(char *fn);
        int  LookUpFileLoc(char *fn);
        int  updateFileC(void);
        THeader ReadHeader(FILE *fn);
        void AddFile(string fn);
        void SaveArchieve(void);
        bool ExtractToFile(char *fn,char *sn);
        void SaveFileToBuffer(char *fn,FAstream &fs);

  protected:
        void Destroy();
        /*
  public:commented out 10.9.13
        TStringList &filezList() {return fileList;}
        */
  public:
        TStringList fileList; //moved to public 10.9.13
  private:
        FILE * pFile;//Archieve to save or read from
        int   tFiles;

        TFileBlkList __fblock;
        THeader __h;
  protected:
        TStringList readInFList(FILE *fn);
        void  genBlockList(void);
  private://Functions
        long lmin(long a,long b);
        DWORD64 d64min(DWORD64 a,DWORD64 b);
        bool WriteHeader(void);
        bool WriteFileBlocks(void);
        bool WriteFileData(void);
        char VerifyBlk[64];
        char RequestBk[64];
        //
        void MoveToDataLoc(int dl);
  private://Variables
        bool __hasbeenloaded;
        DWORD64 DataLoc;
};
}
#endif // FILEARCH_H_INCLUDED

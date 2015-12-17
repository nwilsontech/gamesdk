#include <cstdarg>
#include <cstdlib>
#include <cstdio> //exit, free
#include "FileArch.h"
//#include "crc32.h"
//Usefull Functions
namespace  FARC
{

bool StrEqual( const char* s1, const char* s2 )
{
    return ( s1 && s2 && strcmp( s1, s2 ) == 0 );
}


int FindLastDelimiter(string Text)
{
#ifdef PLATFORM_WINDOWS
    return Text.find_last_of('\\', Text.length());
#else //LINUX
    return Text.find_last_of('/', Text.length());
#endif
}
int FindLastPoint(string Text)
{
   // printf("lp %d , %d\n",Text.find_last_of('.', Text.length()),Text.length());
    return Text.find_last_of('.', Text.length());

}
string FindPrevDir(string Text)
{
    string ___o = Text.substr(0,FindLastDelimiter(Text)-1);
    return Text.substr(0,FindLastDelimiter(___o)+1);
}
int hasDotDot(string input)
{
    return input.find_first_of("..",input.length());
}

string ExtractFileName(string Input)
{
    return Input.substr(FindLastDelimiter(Input)+1,Input.length()-FindLastDelimiter(Input)-1);
}
string ExtractPathName(string Input)
{
    return Input.substr(0,FindLastDelimiter(Input)+1);
}
string ExtractExtName(string Input)
{
    if (FindLastDelimiter(Input)<FindLastPoint(Input))
    {
        return Input.substr(FindLastPoint(Input)+1,Input.length()-FindLastPoint(Input));
    }
    else return "";
}


long FArchieve::lmin(long a,long b)
{
    if (a>b)
        return b;
    else return a;
}
DWORD64 FArchieve::d64min(DWORD64 a,DWORD64 b)
{
    if (a>b)
        return b;
    else return a;
}
FArchieve::FArchieve()
{
   /*
   :pFile(NULL),
          __hasbeenloaded(false),
          tFiles(0)
   */
   pFile = NULL;
   __hasbeenloaded = false;
   updateFileC();
   DataLoc=0x00;
}
FArchieve::~FArchieve()
{
    if (__hasbeenloaded)
        Close();
}
void FArchieve::Destroy()
{
    delete pFile;
}
TStringList FArchieve::readInFList(FILE *fn)
{

}
//Main Archieve Functions
bool FArchieve::Open(char *fn,__OPEN_ENUM ot,__FLAGS_ENUM ft)
{

    char *__ot;
    switch (ot)
    {
        case FA_OPEN_READ:
            {
                __ot = "r+bt";
                break;
            }
        case FA_OPEN_WRITE:
            {
                __ot = "w+bt";
                break;
            }
        default:
            {
                printf("unknown open enum\n");
                return false;
                break;
            }
    }
    if (__hasbeenloaded)
        return false;
    pFile = fopen (fn,__ot);

    if (pFile==NULL)
    {
        printf("<0x7> does not exist\n");
        return false;
        exit(0x88);

    }
    __hasbeenloaded = true;

    if (ft==FA_LOAD_AUTO)
    {
        if (!LoadInfo())//if it fails to load return
            return false;
    }
    return true;

}
bool FArchieve::ReOpen(char *fn,__OPEN_ENUM ot,__FLAGS_ENUM ft)
{
    if(IsOpen())
        Close();
    fileList.empty();
    fileList.clear();
    return Open(fn,ot,ft);
}

bool FArchieve::Close(void)
{
    fclose(pFile);
    //Destroy();creates error discovered 10.9.13
    __hasbeenloaded = false;
    fileList.empty();
    fileList.clear();
    __fblock.empty();
    __fblock.clear();

    tFiles = 0;
}
int FArchieve::updateFileC(void)
{
     tFiles = (int)fileList.size();
     return 0;
}
void  FArchieve::genBlockList(void)
{
     updateFileC();
     if (tFiles==0)
     {
         printf("no files to gen\n");
         return;
     }
     TFileBlk FileB;
     FILE *iFile;
     char *b;
     int  s=0;
     for (int i = 0; i < tFiles; i++)
     {
         printf("Openging\n");
          iFile = fopen (fileList.at(i).data(),"rbt");
          sprintf(FileB.fn,"%s",ExtractFileName(fileList.at(i)).data());
          fseek  (iFile , 0 , SEEK_END );
          s = ftell  (iFile);//Set Header File Size
          FileB.fileSize = s;
          fseek  (iFile, 0,SEEK_SET);
          b = new char[s];
          fread(b,1,s,iFile);
          FileB.crc = 0;//crc32(b,s);
          fclose ( iFile );
          free(b);
          __fblock.push_back(FileB);
     }
     printf("exiting GenBlock\n");
     //delete iFile; //Error 10.16.13
}
void FArchieve::AddFile(string fn)
{
    if (!__hasbeenloaded)
        return;
    fileList.push_back(fn);
    updateFileC();

}
bool FArchieve::WriteHeader(void)
{
    if (!__hasbeenloaded)
        return false;
    THeader Header;
    //Header.ID = "ARC67a";
    printf("mocho\n");
    //sprintf(Header.ID,"%s\0","ARC67");//causes error if ARC67 dont know why
    memcpy(Header.ID,"ARC67a",sizeof(Header.ID));
    //strcpy(Header.ID,"ARC67a");
    //strncpy(Header.ID, "ARC67a\0",6);//6 /*sizeof(name)-1*/);
    //Header.ID="ARC67";
    Header.files = (DWORD)tFiles;
//    printf("header save data: %ld,%ld,%s\n",Header.files,Header.sizeofList,Header.ID);
    fwrite(&Header,1,sizeof(THeader),pFile);
    return true;
}
bool FArchieve::WriteFileBlocks(void)
{
    FILE *iFile;
    for(int numOblk = 0; numOblk < tFiles; numOblk++)
    {
      iFile = fopen ((char *)fileList.at(numOblk).data(),"rbt");
      if (iFile==NULL)
          exit(475);
      fwrite (&__fblock.at(numOblk),1,sizeof(TFileBlk),pFile);
      fclose ( iFile );
    }
    //delete iFile; Error
    return true;
}
bool FArchieve::WriteFileData(void)
{
    //char buffer[8192];
    UCHAR *buffer;
    long bytes;
    FILE *iFile;
    DataLoc = ftell(pFile);
    //printf("Data Location %ld\n",DataLoc);
    for(int numOblk = 0; numOblk < tFiles; numOblk++)
    {
      iFile = fopen ((char *)fileList.at(numOblk).data(),"rbt");
      if (iFile==NULL)
          exit(375);
      bytes = __fblock.at(numOblk).fileSize;
//      do
//      {
//
//         printf("writing file s:%ld\n",lmin(bytes,8192));
//         fread(&buffer,1,lmin(bytes,8192),iFile);
//         fwrite(&buffer,1,lmin(bytes,8192),pFile);
//         bytes-=lmin(bytes,8192);
//
//      }while (bytes!=0);
     // fseek(iFile,0,SEEK_SET);
      buffer = new UCHAR [bytes];
      fread(buffer,1,bytes,iFile);
      fwrite(buffer,1,bytes,pFile);

      fclose ( iFile );
    }
    //delete [] buffer;
    return true;
}
void FArchieve::SaveArchieve(void)
{
     if (!__hasbeenloaded)
        {
            printf("file has not been loaded\n");
            return;
        }
        printf("generating blocks\n");
        genBlockList();
        printf("writing headers\n");
        WriteHeader();
        printf("writing blocks\n");
        WriteFileBlocks();
        printf("writing Data\n");
        WriteFileData();
        printf("All Finished\n");
        //printf("%ld file pos\n",ftell(pFile));
}
void FArchieve::SaveFileToBuffer(char *fn,FAstream &fs)
{
    fs.size = LookUpFileSize(fn);
    fs.buffer =(UCHAR *) realloc (NULL, fs.size * sizeof(UCHAR));//new UCHAR[bufferSize];
    LoadFileIntoBuf(fs.buffer,fs.size,fn);
    return;
}
bool FArchieve::LoadInfo(void)
{
  long tbytes = 0;
  if (!__hasbeenloaded)
  {
    printf("archieve has not been properly loaded\n");
    return false;
  }
  TFileBlk tfb;
  fread(&__h,1,sizeof(THeader),pFile);
  printf("data: %s\n",__h.ID);
  int readFB = (int)__h.files;
  for(int i=0;i<readFB;i++)
  {
        tbytes = fread(&tfb,1,sizeof(TFileBlk),pFile);
        fileList.push_back(tfb.fn);
        if (tbytes != sizeof(TFileBlk)) {fputs ("Reading error",stderr); exit (3);}
        __fblock.push_back(tfb);
  }
  updateFileC();
  DataLoc = ftell(pFile);
  return true;

}
int  FArchieve::LookUpFileLoc(char *fn)
{
    if (!__hasbeenloaded)
    {
        printf("has not been loaded yet\n");
        return -1;
    }
    tFiles = __fblock.size();

    int loc = -1;
    //printf("tfile:%d\n",tFiles);

    for (int i = 0; i < tFiles; i++)
    {

        if (strcmp(__fblock.at(i).fn,fn)==0)
        {
            loc = i;
            break;
        }
        else
        {
            //printf("file: %s \tfile: %s\n",__fblock.at(i).fn,fn);
        }
    }
    return loc;
}
int  FArchieve::LookUpFileSize(char *fn)
{
    if (!__hasbeenloaded)
    {
        printf("has not been loaded yet\n");
        return -1;
    }
    fseek(pFile,0,SEEK_SET);//FILE Begining
    updateFileC();
    int i = LookUpFileLoc(fn);
    //printf("iiii   %d\n",i);
    if (i==-1)
        return -1;
    //printf("file size:%ld\n",__fblock.at(i).fileSize);
    return __fblock.at(i).fileSize;
}
bool FArchieve::LoadFileIntoBuf(UCHAR *dest,size_t s,char *fn)
{
    if (!__hasbeenloaded)
    {
        printf("has not been loaded yet\n");
        return -1;
    }
    int fp  = LookUpFileLoc(fn);
    long ds = (long)__fblock.at(fp).fileSize;

    MoveToDataLoc(fp);
    fread(dest,1,s,pFile);//Read File Data into stream
    return true;

}
void FArchieve::MoveToDataLoc(int dl)
{
    fseek(pFile,DataLoc,SEEK_SET);//Set Data to Data block
    int ___t;
    long tDistance;
    ___t = dl - 0;
    tDistance = 0;
    for (int a = 0; a <= ___t; a++)
    {
        switch (a)
        {
            case 0:
                {
                    tDistance = 0;
                    break;
                }
            default:
                {
                    tDistance += __fblock.at(a-1).fileSize;
                    break;
                }
        }
    }
    fseek(pFile,tDistance,SEEK_CUR);
}
bool FArchieve::ExtractToFile(char *fn,char *savename)
{

    FILE *SaveToFile;
    UCHAR *buffer;
    long bufferSize;
    printf("<extracting>\n");
    SaveToFile = fopen(savename,"wb");
    if (SaveToFile==NULL)
    {
        printf("failed to save");
        return false;
    }
    fseek(SaveToFile,0,SEEK_SET);
    bufferSize = LookUpFileSize(fn);
    if (bufferSize==-1)
    {
        printf("file not found\n");
        return false;
    }
    buffer = (UCHAR*) malloc ( bufferSize);
    LoadFileIntoBuf(buffer,bufferSize,fn);
    fwrite(buffer,1,bufferSize,SaveToFile);

    fclose(SaveToFile);
    delete []buffer;
}
bool FArchieve::IsOpen()
{
    return __hasbeenloaded;
}
}

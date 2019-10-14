//---------------------------------------------------------------------------

#ifndef U72312ChipH
#define U72312ChipH
//---------------------------------------------------------------------------
#include "U72310Device.h"
//#include ".\72312_reg_map\72312map.h"
//using namespace map312;

class Dev_72312_Chip : public Dev_72310
{
    private:
       // static unsigned char * regmap_312[];
    public:
        Dev_72312_Chip(AnsiString str);

        virtual void SetBoard(int b);
        virtual void SetBoard(AnsiString sb);
        virtual GetBoard();

        virtual int GetPageNumber();
        virtual int GetBoardNumber();

        virtual bool GetPageExist(int b, int p);
        virtual void ChangePageList(int i);
        virtual void ChangePageList(int * PL);



        virtual bool AllWriteByte(unsigned int Address, Byte WriteByte);
        virtual bool AllReadByte(unsigned int Address, Byte &ReadByte);
        virtual bool AllWriteDWord(unsigned int Address, unsigned int WriteDWord);
        virtual bool AllReadDWord(unsigned int Address, unsigned int &ReadDWord);


        virtual bool Start();

};

#endif
 
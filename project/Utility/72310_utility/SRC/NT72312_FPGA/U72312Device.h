//---------------------------------------------------------------------------

#ifndef U72312DeviceH
#define U72312DeviceH
//---------------------------------------------------------------------------

#include "U72310Device.h"

enum boards{Board_A, Board_B, Board_C, Board_ALL};
class Dev_72312_FPGA : public Dev_72310
{
    private:
        boards Board;
        int * PageList;
    public:
        static unsigned char * regmap_312[];
        
    public:
        Dev_72312_FPGA(AnsiString str);
        
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
 
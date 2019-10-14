//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_Image.h"
#include "UForm_Bitmap.h"
#include <Math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCFrame"
#pragma link "RegCheckBox"
#pragma link "RegScrollBar"
#pragma resource "*.dfm"
TFrame_Image *Frame_Image;

int csc_coef[3][4] =
{
    {4096,  0,      6450,   -806},
    {4096,  -767,   -1917,   336},
    {4096,  7601,   0,      -950},
};

//{coef00, coef01, coef02, const0} = { 15'd871 ,  15'd2929,  15'd296 , 12'd0  };
//{coef10, coef11, coef12, const1} = {-15'd469 , -15'd1579,  15'd2048, 12'd512};
//{coef20, coef21, coef22, const2} = { 15'd2048, -15'd1860, -15'd188 , 12'd512};
int csc_coefR2Y[3][4] =
{
    {871,   2929,   296,    0},
    {-469,  -1579,  2048,   512},
    {2048,  -1860,  -188,    512},
};
//---------------------------------------------------------------------------
__fastcall TFrame_Image::TFrame_Image(TComponent* Owner)
    : TMEMCFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Image::Button6Click(TObject *Sender)
{
    int block_top,block_left,block_width,block_height;
    unsigned int startAddr, blockStart;
    Graphics::TBitmap * pBitmap;
    //TForm * Form_Bitmap;
    Byte block_H, block_V;
    Byte ** y_buf;

    DWORD Time0, Time;

    Time0 = GetTickCount();
    pBitmap = new Graphics::TBitmap;  

    Form_Bitmap = new TForm_Bitmap(this);
    try
    {
        block_top = LE_bTop->Text.ToInt();
        block_left = LE_bLeft->Text.ToInt();
        block_width = LE_bWidth->Text.ToInt();
        block_height = LE_bHeight->Text.ToInt();
    }
    catch(...)
    {
    }

    if(!GetDevice()->ReadDWord(0xE0000A08,startAddr))//read y buffer0 address
    {
        return;
    }
    startAddr = ((startAddr & 0x0000FFFF)<<12) | 0x80000000;

    GetDevice()->ReadByte(0xE0000A00, block_H);
    GetDevice()->ReadByte(0xE0000A01, block_V);

    //if(block_top>block_V)   return;
    //if(block_left>block_H)   return;
    //if(block_left+block_width>block_H)  return;
    //if(block_top+block_height>block_V)   return;
    
    PB->Max = 16*block_height*block_width;
    PB->Position = 0;
    blockStart = startAddr + (block_top*block_H+block_left)*16;
    y_buf = (Byte **)malloc(block_height*sizeof(Byte *));
    for(int i=0;i<block_height;i++)
    {
        y_buf[i] = ReadBlockLine(blockStart,block_width);
        blockStart += block_H*16;
    }
    Time = GetTickCount()- Time0;
    Memo1->Lines->Clear();
    Memo1->Lines->Add(Time);
    MakeBlockImage(block_width,block_height,pBitmap,y_buf);
    //Form_Bitmap->Canvas->Draw(0,0, pBitmap);
    Form_Bitmap->pBitmap = pBitmap;
    Form_Bitmap->ShowModal();
    delete pBitmap;

}
//---------------------------------------------------------------------------
Byte * __fastcall TFrame_Image::ReadBlockLine(unsigned int LineStart,int width)
{
    Byte * LineBuffer;
    Byte * Line;
    unsigned int dwReadData;
    Byte bReadData;
    bool bFalse = false;

    bFalse = !CB_Burst->Checked;
    LineBuffer = (Byte *)malloc(width*16*sizeof(Byte));
    Line = LineBuffer;
    if(bFalse)
    {
        for(int i=0;i<width*16;i+=4)
        {
            if(!GetDevice()->ReadDWord(LineStart+i, dwReadData))
            {
                return NULL;
            }

            for(int j=0;j<4;j++)
            {
                bReadData = (dwReadData >> (j*8)) & 0xFF;
                * LineBuffer = bReadData;
                LineBuffer++;
                PB->Position++;
            }
        }
    }
    else
    {
        int count = width * 16;
        for(int i=0;i<count;i+=256)
        {
            if(count-i >= 256)
            {
                GetDevice()->BurstReadByte(LineStart+i,256,LineBuffer);
                LineBuffer += 256;
                PB->Position += 256;
            }
            else //if(count -i != 0)
            {
                GetDevice()->BurstReadByte(LineStart+i, count-i, LineBuffer);
                LineBuffer += count-i;
                PB->Position += count-i;
            }
        }
    }
    return Line;
}
void __fastcall TFrame_Image::MakeBlockImage(int width,int height, Graphics::TBitmap * pBitmap, Byte ** y_buf)
{
    int R_data, G_data, B_data;
    pBitmap->Width = width*4;
    pBitmap->Height = height*4;
    pBitmap->PixelFormat = pf32bit;
    pBitmap->IgnorePalette = true;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            for(int m=0;m<4;m++)
            {
                for(int n=0;n<4;n++)
                {
                    R_data = y_buf[i][j*16+m*4+n];
                    G_data = y_buf[i][j*16+m*4+n];
                    B_data = y_buf[i][j*16+m*4+n];


                    pBitmap->Canvas->Pixels[j*4+n][i*4+m]=(TColor) R_data |(G_data<<8) | (B_data<<16);
                }
            }
        }
    }
    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }
}
void __fastcall TFrame_Image::CheckBox1Click(TObject *Sender)
{
    Byte value;
    TCheckBox * cb;
    
    cb = (TCheckBox *)Sender;

    GetDevice()->ReadByte(0xE0000A04, value);
    value &= 0x7F;
    if(cb->Checked)
    {
        value |= 0x80;
    }
    GetDevice()->WriteByte(0xE0000A04, value);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Image::CheckBox2Click(TObject *Sender)
{
    Byte value;
    TCheckBox * cb;
    
    cb = (TCheckBox *)Sender;

    GetDevice()->ReadByte(0xE0000A06, value);
    value &= 0xFB;
    if(cb->Checked)
    {
        value |= 0x04;
    }
    GetDevice()->WriteByte(0xE0000A06, value);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Image::CheckBox3Click(TObject *Sender)
{
    Byte value;
    TCheckBox * cb;
    
    cb = (TCheckBox *)Sender;

    GetDevice()->ReadByte(0xE0000A07, value);
    value &= 0xEF;
    if(cb->Checked)
    {
        value |= 0x10;
    }
    GetDevice()->WriteByte(0xE0000A07, value);
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Image::CheckBox4Click(TObject *Sender)
{
    Byte value;
    TCheckBox * cb;
    
    cb = (TCheckBox *)Sender;

    GetDevice()->ReadByte(0xE0000A0D, value);
    value &= 0x7F;
    if(cb->Checked)
    {
        value |= 0x80;
    }
    GetDevice()->WriteByte(0xE0000A0D, value);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Image::ScrollBar1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    if(ScrollCode==scEndScroll)
    {
        //
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TFrame_Image::Button5Click(TObject *Sender)
{
    Graphics::TBitmap * pBitmap;
    pBitmap = new Graphics::TBitmap;
    try
    {
        if(LE_top->Text != "")
        {
            buf_top = LE_top->Text.ToInt();
        }
        if(LE_left->Text != "")
        {
            buf_left = LE_left->Text.ToInt();
        } 
    }
    catch(...)
    {

    }
    if(SaveBitmap->Execute())
    {
        pBitmap->LoadFromFile(SaveBitmap->FileName);
        //Form_Bitmap->Is8bit = RB_8bit->Checked;
        Is8bit = RB_8bit->Checked;
        //Form_Bitmap->IsRGB = RB_RGB->Checked;
        IsRGB = RB_RGB->Checked;
        IsYCbCr422 = RB_YCbCr422->Checked;
        //Form_Bitmap->m_cNT72310Slave = m_cNT72310Slave ;
        WriteBitmapToDDR(pBitmap);
    }

    delete pBitmap;
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Image::Button4Click(TObject *Sender)
{
    Graphics::TBitmap * pBitmap;

    pBitmap = new Graphics::TBitmap;

    Form_Bitmap = new TForm_Bitmap(this);

    Is8bit = RB_8bit->Checked;
    IsRGB = RB_RGB->Checked;
    IsYCbCr422 = RB_YCbCr422->Checked;

    try
    {
        if(LE_top->Text != "")
        {
            buf_top = LE_top->Text.ToInt();
        }
        if(LE_left->Text != "")
        {
            buf_left = LE_left->Text.ToInt();
        }
        if(LE_width->Text != "")
        {
            buf_width = LE_width->Text.ToInt();
        }
        if(LE_height->Text != "")
        {
            buf_height = LE_height->Text.ToInt();
        }
        /*if(buf_start->Text != "")
        {

        }
        if(buf_end->Text != "")
        {

        } */
        y_buf = (Word **)malloc(buf_height*sizeof(Word *));//(Word **) calloc(buf_height, sizeof(Word));
        Cb_buf = (Word **)malloc(buf_height*sizeof(Word *));//(Word **) calloc(buf_height, sizeof(Word));
        Cr_buf = (Word **)malloc(buf_height*sizeof(Word *));
        Form_Bitmap->pBitmap = pBitmap;
    }
    catch(...)
    {

    }
    
    ReadImageBuf();
    if(Is8bit)
    {
        if(IsRGB)
        {
            Make8BitRGBBitmap(pBitmap);
        }
        else if(IsYCbCr422)
        {
            Make8BitYUV422Bitmap(pBitmap);
        }
        else
        {
            Make8BitYUVBitmap(pBitmap);
        }
    }
    else
    {
        if(IsRGB)
        {
            Make10BitRGBBitmap(pBitmap);
        }
        else if(IsYCbCr422)
        {
            Make10BitYUV422Bitmap(pBitmap);
        }
        else
        {
            Make10BitYUVBitmap(pBitmap);
        }
    }
    Form_Bitmap->ShowModal();
    delete pBitmap;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFrame_Image::ReadImageBuf()
{
    unsigned int buf_start, buf_end, y_start, Cb_start, Cr_start;
    int col, row;
    Word * LineBuffer;

    float unitby32;
    int RowBytes;

    RowCount = 1920;

    if(!GetDevice()->WriteByte(0xE000015B,0x07)) //stop 72310 write buffer;
    {
        return;
    }

    if(!GetDevice()->ReadDWord(0xE0000000,buf_start))//read y buffer0 address
    {
        return;
    }
    y_start = ((buf_start & 0x0000FFFF)<<12) | 0x80000000;
    //y_start = (((buf_start >>16)& 0x0000FFFF)<<12) | 0x80000000;

    if(!GetDevice()->ReadDWord(0xE000000C,buf_start))//read Cb buffer0 address
    {
        return;
    }
    Cb_start = ((buf_start & 0x0000FFFF)<<12) | 0x80000000;
    //Cb_start = (((buf_start >>16)& 0x0000FFFF)<<12) | 0x80000000;

    if(!GetDevice()->ReadDWord(0xE0000018,buf_start))//read Cr buffer0 address
    {
        return;
    }
    Cr_start = ((buf_start & 0x0000FFFF)<<12) | 0x80000000;
    //Cr_start = (((buf_start >>16)& 0x0000FFFF)<<12) | 0x80000000;



    if(Is8bit)
    {
        unitby32 = (double)RowCount/32;
        RowBytes = ceil(unitby32)*32;
        y_start += buf_top*RowBytes+buf_left;
        Cb_start += buf_top*RowBytes+buf_left;
        Cr_start += buf_top*RowBytes+buf_left;
    }
    else
    {
        RowBytes = ceil((double)RowCount*10 / 8);
        unitby32 = (double)RowBytes/32;
        RowBytes = ceil(unitby32)*32;
        y_start += buf_top*RowBytes+buf_left*10/8;
        Cb_start += buf_top*RowBytes+buf_left*10/8;
        Cr_start += buf_top*RowBytes+buf_left*10/8;
    }

    PB->Position = 0;
    if(Is8bit)
    {
        PB->Max = buf_width*buf_height;
    }
    else
    {
        PB->Max = ceil((double)(buf_width)*10/8)*buf_height;
    }

    PB->Visible = true;


    for(int i=0;i<buf_height;i++)
    {
        LineBuffer = ReadLine(y_start);
        if(Is8bit)
        {
            y_buf[i] = LineBuffer;
        }
        else
        {
            
            y_buf[i] = TransferTo10Bit(LineBuffer);
        }

        LineBuffer = ReadLine(Cb_start);
        if(Is8bit)
        {
            Cb_buf[i] = LineBuffer;
        }
        else
        {
            Cb_buf[i] = TransferTo10Bit(LineBuffer);
        }
        if(!IsYCbCr422)
        {
            LineBuffer = ReadLine(Cr_start);
            if(Is8bit)
            {
                Cr_buf[i] = LineBuffer;
            }
            else
            {
                Cr_buf[i] = TransferTo10Bit(LineBuffer);
            }
        }

        y_start += RowBytes;
        Cb_start += RowBytes;
        Cr_start += RowBytes;

    }
}
//---------------------------------------------------------------------------

Word * __fastcall TFrame_Image::ReadLine(unsigned int LineStart)
{
    Word * LineBuffer, * Line;
    unsigned int LineStartRead, LineEndRead;
    Byte bReadData;
    unsigned int dwReadData;
    int left_width;                     
    int modby4, modby4end, readlength;

    if(Is8bit)
    {
        left_width = buf_width;
    }
    else
    {
        left_width = ceil((double)(buf_width)*10/8);
    }

    LineBuffer = (Word *) malloc(left_width*sizeof(Word));
    Line = LineBuffer;

    modby4 = LineStart % 4;

    modby4end = (LineStart+left_width) % 4;
    LineEndRead = LineStart + left_width  - modby4end;

    if(modby4 !=0 )
    {
        for(int i=0;i<(4-modby4);i++)
        {
            if(!GetDevice()->ReadByte(LineStart+i,bReadData))
            {
                return NULL;
            }
            * LineBuffer = (Word)bReadData;
            LineBuffer++;
            PB->Position ++;
        }
        LineStartRead = LineStart +4-modby4;
    }
    else
    {
        LineStartRead = LineStart;
    }

    readlength = LineEndRead - LineStartRead;
    
    if(!CB_Burst->Checked)
    {
        for (int i=0; i<readlength; i+=4)
        {
            if(!GetDevice()->ReadDWord(LineStartRead+i, dwReadData))
            {
                return NULL;
            }

            for(int j=0;j<4;j++)
            {
                bReadData = (dwReadData >> (j*8)) & 0xFF;
                * LineBuffer = (Word)bReadData;
                LineBuffer++;
                PB->Position ++;
            }
        }
    }
    else
    {
        for(int i=0; i < readlength; i+=256)
        {
            if(readlength-i >= 256)
            {
                GetDevice()->BurstReadByte(LineStartRead+i, 256, (Byte *)LineBuffer);
                LineBuffer += 256;
            }
            else //if(readlength -i != 0)
            {
                GetDevice()->BurstReadByte(LineStartRead+i, readlength-i, (Byte *)LineBuffer);
                LineBuffer += readlength-i;
            }
        }
    }


    for(int i = modby4end-1; i>=0; i--)
    {
        if(!GetDevice()->ReadByte(LineEndRead-i,bReadData))
        {
            return NULL;
        }
        * LineBuffer = (Word)bReadData;
        LineBuffer++;
        PB->Position ++;
    }          

    return Line;
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Image::Make8BitRGBBitmap(Graphics::TBitmap * pBitmap)
{
    pBitmap->Width = buf_width;
    pBitmap->Height = buf_height;
    pBitmap->PixelFormat = pf32bit;
    pBitmap->IgnorePalette = true;
    for(int i=0; i<buf_height; i++)
    {
        for(int j=0; j<buf_width; j++)
        {
            pBitmap->Canvas->Pixels[j][i]=(TColor)( (Byte)(y_buf[i][j]) |(((Byte)(Cb_buf[i][j]))<<8) | (((Byte)(Cr_buf[i][j]))<<16));
        }
    }

    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Image::Make8BitYUVBitmap(Graphics::TBitmap * pBitmap)
{
    int R_data, G_data, B_data;

    pBitmap->Width = buf_width;
    pBitmap->Height = buf_height;
    pBitmap->PixelFormat = pf32bit;
    pBitmap->IgnorePalette = true;


    for(int i=0; i<buf_height; i++)
    {
        for(int j=0; j<buf_width; j++)
        {
            R_data = ((int)y_buf[i][j]*csc_coef[0][0]+(int)Cb_buf[i][j]*csc_coef[0][1]+(int)Cr_buf[i][j]*csc_coef[0][2]+csc_coef[0][3]*4096/4)/4096;
            G_data = ((int)y_buf[i][j]*csc_coef[1][0]+(int)Cb_buf[i][j]*csc_coef[1][1]+(int)Cr_buf[i][j]*csc_coef[1][2]+csc_coef[1][3]*4096/4)/4096;
            B_data = ((int)y_buf[i][j]*csc_coef[2][0]+(int)Cb_buf[i][j]*csc_coef[2][1]+(int)Cr_buf[i][j]*csc_coef[2][2]+csc_coef[2][3]*4096/4)/4096;

            if(R_data < 0)   R_data = 0;
            if(R_data > 255)   R_data = 255;
            if(G_data < 0)   G_data = 0;
            if(G_data > 255)   G_data = 255;
            if(B_data < 0)   B_data = 0;
            if(B_data > 255)   B_data = 255;

            pBitmap->Canvas->Pixels[j][i]=(TColor)( R_data |(G_data<<8) | (B_data<<16));
        }
    }

    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }
}

void __fastcall TFrame_Image::Make10BitRGBBitmap(Graphics::TBitmap * pBitmap)
{
    Byte y_data, Cb_data, Cr_data;

    //buf_width = 1024;
    //buf_height = 256;

    pBitmap->Width = buf_width;
    pBitmap->Height = buf_height;
    pBitmap->PixelFormat = pf32bit;
    pBitmap->IgnorePalette = true;

    for(int i=0; i<buf_height; i++)
    {
        for(int j=0; j<buf_width; j++)
        {
            //y_data = data/4;//y_buf[i][j]/4;
            //Cb_data = data/4;//Cb_buf[i][j]/4;
            //Cr_data = data/4;//Cr_buf[i][j]/4;
            y_data = y_buf[i][j]/4;
            Cb_data = Cb_buf[i][j]/4;
            Cr_data = Cr_buf[i][j]/4;
            pBitmap->Canvas->Pixels[j][i]=(TColor)( y_data | (Cb_data<<8) | (Cr_data<<16));
        }
    }

    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }
}

void __fastcall TFrame_Image::Make10BitYUVBitmap(Graphics::TBitmap * pBitmap)
{
    int wR_data, wG_data, wB_data;
    Byte R_data, G_data, B_data;

    pBitmap->Width = buf_width;
    pBitmap->Height = buf_height;
    pBitmap->PixelFormat = pf32bit;
    pBitmap->IgnorePalette = true;


    for(int i=0; i<buf_height; i++)
    {
        for(int j=0; j<buf_width; j++)
        {
            wR_data = (y_buf[i][j]*csc_coef[0][0]+Cb_buf[i][j]*csc_coef[0][1]+Cr_buf[i][j]*csc_coef[0][2]+csc_coef[0][3]*4096)/4096;
            wG_data = (y_buf[i][j]*csc_coef[1][0]+Cb_buf[i][j]*csc_coef[1][1]+Cr_buf[i][j]*csc_coef[1][2]+csc_coef[1][3]*4096)/4096;
            wB_data = (y_buf[i][j]*csc_coef[2][0]+Cb_buf[i][j]*csc_coef[2][1]+Cr_buf[i][j]*csc_coef[2][2]+csc_coef[2][3]*4096)/4096;

            if(((int)wR_data < 0))   wR_data = 0;
            if(((int)wR_data > 1023))   wR_data = 1023;
            if(((int)wG_data < 0))   wG_data = 0;
            if(((int)wG_data > 1023))   wG_data = 1023;
            if(((int)wB_data < 0))   wB_data = 0;
            if(((int)wB_data > 1023))   wB_data = 1023;

            R_data = wR_data / 4;
            G_data = wG_data / 4;
            B_data = wB_data / 4;

            pBitmap->Canvas->Pixels[j][i]=(TColor)( R_data |(G_data<<8) | (B_data<<16));
        }
    }

    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }
}

Word * __fastcall TFrame_Image::TransferTo10Bit( Word * LineBuffer)
{
    Word  * Line;
    int startShift;
    int Rshift, FFRshift, d_i;

    startShift = ((buf_left*10)%8);

    Line  = (Word *) malloc(buf_width*sizeof(Word));
    //////////////////////////////////////////////////////////////////////////////////////////////
    // if startShift = 0 then
    //    Line[i]       LSB                               MSB
    //                               Rshift                          0xFF & FFRshift
    //   Line[0]  =  LineBuffer[0]>>   0   +    ((LineBuffer[1] &        0x03         ) << 8)
    //   Line[1]  =  LineBuffer[1]>>   2   +    ((LineBuffer[2] &        0x0F         ) << 6)
    //   Line[2]  =  LineBuffer[2]>>   4   +    ((LineBuffer[3] &        0x3F         ) << 4)
    //   Line[3]  =  LineBuffer[3]>>   6   +    ((LineBuffer[4] &        0xFF         ) << 2)
    //   Line[4]  =  LineBuffer[5]>>   0   +    ((LineBuffer[6] &        0x03         ) << 8)
    //   Line[5]  =  LineBuffer[6]>>   2   +    ((LineBuffer[7] &        0x0F         ) << 6)
    //   Line[6]  =  LineBuffer[7]>>   4   +    ((LineBuffer[8] &        0x3F         ) << 4)
    //   Line[7]  =  LineBuffer[8]>>   6   +    ((LineBuffer[9] &        0xFF         ) << 2)
    //   Line[8]  =  LineBuffer[10]>>  0   +    ((LineBuffer[11]&        0x03         ) << 8)
    //   Line[9]  =  LineBuffer[11]>>  2   +    ((LineBuffer[12]&        0x0F         ) << 6)
    //////////////////////////////////////////////////////////////////////////////////////////////
    for(int i=0;i<buf_width;i++)
    {
        Rshift = ((i%4)*2+startShift);
        d_i = i/4;
        FFRshift = 8 - (((i%4)+1)*2 );
        FFRshift = (FFRshift + 8 - startShift) % 8 ;

        Line[i] = (LineBuffer[i+d_i] >> Rshift) | ((LineBuffer[i+d_i+1] & (0xFF>>FFRshift))<<(8-Rshift));
    }      
    return Line;    
}

void __fastcall TFrame_Image::Make8BitYUV422Bitmap(Graphics::TBitmap * pBitmap)
{
    int R_data, G_data, B_data;

    pBitmap->Width = buf_width;
    pBitmap->Height = buf_height;
    pBitmap->PixelFormat = pf32bit;
    pBitmap->IgnorePalette = true;


    for(int i=0; i<buf_height; i++)
    {
        for(int j=0; j<buf_width; j++)
        {
            //R_data = ((int)y_buf[i][j]*csc_coef[0][0]+(int)Cb_buf[i][(j/2)*2]*csc_coef[0][1]+(int)Cb_buf[i][(j/2)*2+1]*csc_coef[0][2]+csc_coef[0][3]*4096/4)/4096;
            //G_data = ((int)y_buf[i][j]*csc_coef[1][0]+(int)Cb_buf[i][(j/2)*2]*csc_coef[1][1]+(int)Cb_buf[i][(j/2)*2+1]*csc_coef[1][2]+csc_coef[1][3]*4096/4)/4096;
            //B_data = ((int)y_buf[i][j]*csc_coef[2][0]+(int)Cb_buf[i][(j/2)*2]*csc_coef[2][1]+(int)Cb_buf[i][(j/2)*2+1]*csc_coef[2][2]+csc_coef[2][3]*4096/4)/4096;
            R_data = ((int)y_buf[i][j]*csc_coef[0][0]+(int)Cb_buf[i][(j/2)*2+1]*csc_coef[0][1]+(int)Cb_buf[i][(j/2)*2]*csc_coef[0][2]+csc_coef[0][3]*4096/4)/4096;
            G_data = ((int)y_buf[i][j]*csc_coef[1][0]+(int)Cb_buf[i][(j/2)*2+1]*csc_coef[1][1]+(int)Cb_buf[i][(j/2)*2]*csc_coef[1][2]+csc_coef[1][3]*4096/4)/4096;
            B_data = ((int)y_buf[i][j]*csc_coef[2][0]+(int)Cb_buf[i][(j/2)*2+1]*csc_coef[2][1]+(int)Cb_buf[i][(j/2)*2]*csc_coef[2][2]+csc_coef[2][3]*4096/4)/4096;
            if(R_data < 0)   R_data = 0;
            if(R_data > 255)   R_data = 255;
            if(G_data < 0)   G_data = 0;
            if(G_data > 255)   G_data = 255;
            if(B_data < 0)   B_data = 0;
            if(B_data > 255)   B_data = 255;

            pBitmap->Canvas->Pixels[j][i]=(TColor)( R_data |(G_data<<8) | (B_data<<16));
        }
    }

    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }
}

void __fastcall TFrame_Image::Make10BitYUV422Bitmap(Graphics::TBitmap * pBitmap)
{
    int wR_data, wG_data, wB_data;
    Byte R_data, G_data, B_data;

    pBitmap->Width = buf_width;
    pBitmap->Height = buf_height;
    pBitmap->PixelFormat = pf32bit;
    pBitmap->IgnorePalette = true;


    for(int i=0; i<buf_height; i++)
    {
        for(int j=0; j<buf_width; j++)
        {
            //wR_data = (y_buf[i][j]*csc_coef[0][0]+Cb_buf[i][(j/2)*2]*csc_coef[0][1]+Cb_buf[i][(j/2)*2+1]*csc_coef[0][2]+csc_coef[0][3]*4096)/4096;
            //wG_data = (y_buf[i][j]*csc_coef[1][0]+Cb_buf[i][(j/2)*2]*csc_coef[1][1]+Cb_buf[i][(j/2)*2+1]*csc_coef[1][2]+csc_coef[1][3]*4096)/4096;
            //wB_data = (y_buf[i][j]*csc_coef[2][0]+Cb_buf[i][(j/2)*2]*csc_coef[2][1]+Cb_buf[i][(j/2)*2+1]*csc_coef[2][2]+csc_coef[2][3]*4096)/4096;
            wR_data = (y_buf[i][j]*csc_coef[0][0]+Cb_buf[i][(j/2)*2+1]*csc_coef[0][1]+Cb_buf[i][(j/2)*2]*csc_coef[0][2]+csc_coef[0][3]*4096)/4096;
            wG_data = (y_buf[i][j]*csc_coef[1][0]+Cb_buf[i][(j/2)*2+1]*csc_coef[1][1]+Cb_buf[i][(j/2)*2]*csc_coef[1][2]+csc_coef[1][3]*4096)/4096;
            wB_data = (y_buf[i][j]*csc_coef[2][0]+Cb_buf[i][(j/2)*2+1]*csc_coef[2][1]+Cb_buf[i][(j/2)*2]*csc_coef[2][2]+csc_coef[2][3]*4096)/4096;

            if(((int)wR_data < 0))   wR_data = 0;
            if(((int)wR_data > 1023))   wR_data = 1023;
            if(((int)wG_data < 0))   wG_data = 0;
            if(((int)wG_data > 1023))   wG_data = 1023;
            if(((int)wB_data < 0))   wB_data = 0;
            if(((int)wB_data > 1023))   wB_data = 1023;

            R_data = wR_data / 4;
            G_data = wG_data / 4;
            B_data = wB_data / 4;

            pBitmap->Canvas->Pixels[j][i]=(TColor)( R_data |(G_data<<8) | (B_data<<16));
        }
    }

    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }    
}


void __fastcall TFrame_Image::WriteBitmapToDDR(Graphics::TBitmap * pBitmap)
{
    Byte R_data, G_data, B_data;
    int wR_data, wG_data, wB_data;
    unsigned int y_start, cb_start, cr_start;
    unsigned int y_add, cb_add, cr_add;
    unsigned char SubAddr, data;
    unsigned char oldslave;
    unsigned int buf_start;
    float unitby32;
    int RowBytes, RowCount;
    Word * LineBuffer;


    RowCount = 1366;
    
    y_buf = (Word **)malloc(pBitmap->Height*sizeof(Word *));
    Cb_buf = (Word **)malloc(pBitmap->Height*sizeof(Word *));
    Cr_buf = (Word **)malloc(pBitmap->Height*sizeof(Word *));
    for(int i=0; i<pBitmap->Height; i++)
    {
        y_buf[i] = (Word *)malloc(pBitmap->Width*sizeof(Word));
        Cb_buf[i] = (Word *)malloc(pBitmap->Width*sizeof(Word));
        Cr_buf[i] = (Word *)malloc(pBitmap->Width*sizeof(Word));
        
        for(int j=0; j<pBitmap->Width; j++)
        {
            R_data = pBitmap->Canvas->Pixels[j][i];
            G_data = pBitmap->Canvas->Pixels[j][i]>>8;
            B_data = pBitmap->Canvas->Pixels[j][i]>>16;
            if(Is8bit)
            {
                if(IsRGB)
                {
                    y_buf[i][j] = R_data;
                    Cb_buf[i][j] = G_data;
                    Cr_buf[i][j] = B_data;
                }
                else if(IsYCbCr422)
                {
                    wR_data = (R_data*csc_coefR2Y[0][0] + G_data*csc_coefR2Y[0][1] + B_data*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096/4)/4096;
                    wG_data = (R_data*csc_coefR2Y[0][0] + G_data*csc_coefR2Y[0][1] + B_data*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096/4)/4096;
                    wB_data = (R_data*csc_coefR2Y[0][0] + G_data*csc_coefR2Y[0][1] + B_data*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096/4)/4096;

                    if((wR_data < 0))   wR_data = 0;
                    if((wR_data > 1023))   wR_data = 255;
                    if((wG_data < 0))   wG_data = 0;
                    if((wG_data > 1023))   wG_data = 255;
                    if((wB_data < 0))   wB_data = 0;
                    if((wB_data > 1023))   wB_data = 255;

                    y_buf[i][j] = wR_data;
                    Cb_buf[i][(j/2)*2+1] = wG_data;
                    Cb_buf[i][(j/2)*2] = wB_data;
                }
                else
                {
                    wR_data = (R_data*csc_coefR2Y[0][0] + G_data*csc_coefR2Y[0][1] + B_data*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096/4)/4096;
                    wG_data = (R_data*csc_coefR2Y[0][0] + G_data*csc_coefR2Y[0][1] + B_data*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096/4)/4096;
                    wB_data = (R_data*csc_coefR2Y[0][0] + G_data*csc_coefR2Y[0][1] + B_data*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096/4)/4096;

                    if((wR_data < 0))   wR_data = 0;
                    if((wR_data > 1023))   wR_data = 255;
                    if((wG_data < 0))   wG_data = 0;
                    if((wG_data > 1023))   wG_data = 255;
                    if((wB_data < 0))   wB_data = 0;
                    if((wB_data > 1023))   wB_data = 255;

                    y_buf[i][j] = wR_data;
                    Cb_buf[i][j] = wG_data;
                    Cr_buf[i][j] = wB_data;
                }
            }
            else
            {
                if(IsRGB)
                {
                    y_buf[i][j] = R_data*4;
                    Cb_buf[i][j] = G_data*4;
                    Cr_buf[i][j] = B_data*4;
                }
                else if(IsYCbCr422)
                {
                    wR_data = (R_data*4*csc_coefR2Y[0][0] + G_data*4*csc_coefR2Y[0][1] + B_data*4*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096)/4096;
                    wG_data = (R_data*4*csc_coefR2Y[0][0] + G_data*4*csc_coefR2Y[0][1] + B_data*4*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096)/4096;
                    wB_data = (R_data*4*csc_coefR2Y[0][0] + G_data*4*csc_coefR2Y[0][1] + B_data*4*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096)/4096;

                    if((wR_data < 0))   wR_data = 0;
                    if((wR_data > 1023))   wR_data = 1023;
                    if((wG_data < 0))   wG_data = 0;
                    if((wG_data > 1023))   wG_data = 1023;
                    if((wB_data < 0))   wB_data = 0;
                    if((wB_data > 1023))   wB_data = 1023;

                    y_buf[i][j] = wR_data;
                    Cb_buf[i][(j/2)*2+1] = wG_data;
                    Cb_buf[i][(j/2)*2] = wB_data;
                }
                else
                {
                    wR_data = (R_data*4*csc_coefR2Y[0][0] + G_data*4*csc_coefR2Y[0][1] + B_data*4*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096)/4096;
                    wG_data = (R_data*4*csc_coefR2Y[0][0] + G_data*4*csc_coefR2Y[0][1] + B_data*4*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096)/4096;
                    wB_data = (R_data*4*csc_coefR2Y[0][0] + G_data*4*csc_coefR2Y[0][1] + B_data*4*csc_coefR2Y[0][2] +csc_coefR2Y[0][3]*4096)/4096;

                    if((wR_data < 0))   wR_data = 0;
                    if((wR_data > 1023))   wR_data = 1023;
                    if((wG_data < 0))   wG_data = 0;
                    if((wG_data > 1023))   wG_data = 1023;
                    if((wB_data < 0))   wB_data = 0;
                    if((wB_data > 1023))   wB_data = 1023;

                    y_buf[i][j] = wR_data;
                    Cb_buf[i][j] = wG_data;
                    Cb_buf[i][j] = wB_data;
                }
            }
        }
    }

    if(!GetDevice()->WriteByte(0xE000015B,0x00)) //stop 72310 write buffer;
    {
        return;
    }

    //if(!WriteByte(0xE000015B,0x07)) //stop 72310 write buffer;
    //{
        //m_cNT72310Slave = oldslave;
        //return;
    //}

    if(!GetDevice()->ReadDWord(0xE0000000,buf_start))//Read y buffer0 address
    {
        return;
    }
    y_start = ((buf_start & 0x0000FFFF)<<12) | 0x80000000;
    y_add = ((buf_start & 0x0000FFFF) << 16) | (buf_start & 0x0000FFFF);
    if(!GetDevice()->ReadDWord(0xE000000C,buf_start))//Read cb buffer0 address
    {
        return;
    }
    cb_start = ((buf_start & 0x0000FFFF)<<12) | 0x80000000;
    cb_add = ((buf_start & 0x0000FFFF) << 16) | (buf_start & 0x0000FFFF);
    if(!GetDevice()->ReadDWord(0xE0000018,buf_start))//Read cr buffer0 address
    {
        return;
    }
    cr_start = ((buf_start & 0x0000FFFF)<<12) | 0x80000000;
    cr_add = ((buf_start & 0x0000FFFF) << 16) | (buf_start & 0x0000FFFF);

    for(int i=0; i<3; i++)
    {
        if(!GetDevice()->WriteDWord(0xE0000000+i*4,y_add))//Write y buffer address
        {
            return;
        }

        if(!GetDevice()->WriteDWord(0xE000000C+i*4,cb_add))//Write Cb buffer address
        {
            return;
        }

        if(!GetDevice()->WriteDWord(0xE0000018+i*4,cr_add))//Write Cr buffer address
        {
            return;
        }
    }

    if(!GetDevice()->WriteByte(0xE000015B,0x07)) //stop 72310 write buffer;
    {
        return;
    }

    if(Is8bit)
    {
        unitby32 = (double)RowCount/32;
        RowBytes = ceil(unitby32)*32;
        y_start += buf_top*RowBytes+buf_left;
        cb_start += buf_top*RowBytes+buf_left;
        cr_start += buf_top*RowBytes+buf_left;
    }
    else
    {
        RowBytes = ceil((double)RowCount*10 / 8);
        unitby32 = (double)RowBytes/32;
        RowBytes = ceil(unitby32)*32;
        y_start += buf_top*RowBytes+buf_left*10/8;
        cb_start += buf_top*RowBytes+buf_left*10/8;
        cr_start += buf_top*RowBytes+buf_left*10/8;
    }

    PB->Position = 0;
    if(Is8bit)
    {
        PB->Max = buf_width*buf_height;
    }
    else
    {
        PB->Max = ceil((double)(buf_width)*10/8)*buf_height;
    }

    PB->Visible = true;


    for(int i=0;i<pBitmap->Height;i++)
    {
        LineBuffer = TransferTo8Bit(y_buf[i],(pBitmap->Width*10/8+1));
        WriteLine(y_start, LineBuffer, pBitmap);
        LineBuffer = TransferTo8Bit(Cb_buf[i],(pBitmap->Width*10/8+1));
        WriteLine(cb_start, LineBuffer, pBitmap);
        LineBuffer = TransferTo8Bit(Cr_buf[i],(pBitmap->Width*10/8+1));
        WriteLine(cr_start, LineBuffer, pBitmap);
        y_start += RowBytes;
        cb_start += RowBytes;
        cr_start += RowBytes;
    }
}

void __fastcall TFrame_Image::WriteLine(unsigned int start_add, Word * LineBuffer, Graphics::TBitmap * pBitmap)
{
     //Word * LineBuffer, * Line;
    unsigned int LineStartWrite, LineEndWrite;
    Byte bWriteData;
    unsigned int dwWriteData;
    int left_width;                     
    int modby4, modby4end, writelength;

    if(Is8bit)
    {
        left_width = pBitmap->Width;
    }
    else
    {
        left_width = ceil((double)(pBitmap->Width)*10/8);
    }

    //LineBuffer = (Word *) malloc(left_width*sizeof(Word));
    //Line = LineBuffer;

    modby4 = start_add % 4;

    modby4end = (start_add+left_width) % 4;
    LineEndWrite = start_add + left_width  - modby4end;

    if(modby4 !=0 )
    {
        for(int i=0;i<(4-modby4);i++)
        {
            bWriteData = (* LineBuffer);
            if(!GetDevice()->WriteByte(start_add+i,bWriteData))
            {
                return;
            }

            LineBuffer++;
            PB->Position ++;
        }
        LineStartWrite = start_add +4-modby4;
    }
    else
    {
        LineStartWrite = start_add;
    }

    writelength = LineEndWrite - LineStartWrite;
    
    if(!CB_Burst->Checked)
    {
        for (int i=0; i<writelength; i+=4)
        {
            dwWriteData = 0;
            for(int j=0;j<4;j++)
            {
                bWriteData  = * LineBuffer;
                dwWriteData = (dwWriteData<<(j*8))+ bWriteData;
                LineBuffer++;
                PB->Position ++;
            }
            if(!GetDevice()->WriteDWord(LineStartWrite+i, dwWriteData))
            {
                return;
            }
        }
    }
    else
    {
        for(int i=0; i < writelength; i+=256)
        {
            if(writelength-i >= 256)
            {
                GetDevice()->BurstWriteByte(LineStartWrite+i, 256, (Byte *)LineBuffer);
                LineBuffer += 256;
            }
            else //if(readlength -i != 0)
            {
                GetDevice()->BurstWriteByte(LineStartWrite+i, writelength-i, (Byte *)LineBuffer);
                LineBuffer += writelength-i;
            }
        }
    }


    for(int i = modby4end-1; i>=0; i--)
    {
        bWriteData = * LineBuffer;
        LineBuffer++;
        PB->Position ++;
        if(!GetDevice()->WriteByte(LineEndWrite-i,bWriteData))
        {
            return ;
        }

    }

}

Word * __fastcall TFrame_Image::TransferTo8Bit(Word * LineBuffer, int ByteCount)
{
    Word * Line;
    int startShift, d_i,d_shift;

    if(Is8bit)
    {
        return LineBuffer;
    }

    Line = (Word *)malloc(ByteCount*sizeof(Word));

    startShift = buf_left*10/8;
    startShift = startShift % 5;
    //Memo1->Clear();

    for(int i=0;i<ByteCount;i++)
    {
        d_i = (i+startShift) / 5;
        d_shift = (i+startShift) % 5;

        if(i==d_i)
        {
            Line[i] =  ((LineBuffer[i-d_i] & (0x00FF>> d_shift*2))<<(d_shift*2));
        }
        else
        {
            Line[i] = ((LineBuffer[i-d_i] & (0x00FF>> d_shift*2))<<(d_shift*2)) | ((LineBuffer[i-d_i-1] >> ((5-d_shift)*2)) & 0x00FF);
        }
        Memo1->Lines->Add(IntToStr(i-d_i)+"  "+IntToStr(i)+"  LineBuffer:"+IntToHex(LineBuffer[i-d_i],4)+"    Line:"+IntToHex(Line[i],4));
    }
    return Line;
}

void __fastcall TFrame_Image::Button9Click(TObject *Sender)
{
    Graphics::TBitmap * pBitmap;
    pBitmap = new Graphics::TBitmap;

    Form_Bitmap = new TForm_Bitmap(this);

    Is8bit = RB_8bit->Checked;
    IsRGB = RB_RGB->Checked;
    IsYCbCr422 = RB_YCbCr422->Checked;
    try
    {
        if(LE_top->Text != "")
        {
            buf_top = LE_top->Text.ToInt();
        }
        if(LE_left->Text != "")
        {
            buf_left = LE_left->Text.ToInt();
        }
        if(LE_width->Text != "")
        {
            buf_width = LE_width->Text.ToInt();
        }
        if(LE_height->Text != "")
        {
            buf_height = LE_height->Text.ToInt();
        }
        /*if(buf_start->Text != "")
        {

        }
        if(buf_end->Text != "")
        {

        } */
        y_buf = (Word **)malloc(buf_height*sizeof(Word *));//(Word **) calloc(buf_height, sizeof(Word));
        Form_Bitmap->pBitmap = pBitmap;
    }
    catch(...)
    {
        
    }
    
    ReadMEYImageBuf();
    MakeMEYBitmap(pBitmap);
    Form_Bitmap->ShowModal();
    delete pBitmap;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Image::ReadMEYImageBuf()
{
    unsigned int buf_start, buf_end, y_start;
    int col, row;
    Word * LineBuffer;

    float unitby32;
    int RowBytes;

    RowCount = 960;

    if(!GetDevice()->WriteByte(0xE000015B,0x07)) //stop 72310 write buffer;
    {
        return;
    }

    if(!GetDevice()->ReadDWord(0xE0000018,buf_start))//read y buffer0 address
    {
        return;
    }
    y_start = ((buf_start & 0x0000FFFF)<<12) | 0x80000000;
    //y_start = (((buf_start >>16)& 0x0000FFFF)<<12) | 0x80000000;

    unitby32 = (double)RowCount/32;
    RowBytes = ceil(unitby32)*32;
    y_start += buf_top*RowBytes+buf_left;

    PB->Position = 0;
    PB->Max = buf_width*buf_height;
    PB->Visible = true;


    for(int i=0;i<buf_height;i++)
    {
        LineBuffer = ReadLine(y_start);
        y_buf[i] = LineBuffer;
        y_start += RowBytes;
    }
}

void __fastcall TFrame_Image::MakeMEYBitmap(Graphics::TBitmap * pBitmap)
{
    pBitmap->Width = buf_width;
    pBitmap->Height = buf_height;
    pBitmap->PixelFormat = pf32bit;
    pBitmap->IgnorePalette = true;
    for(int i=0; i<buf_height; i++)
    {
        for(int j=0; j<buf_width; j++)
        {
            pBitmap->Canvas->Pixels[j][i]=(TColor)( (Byte)(y_buf[i][j]) |(((Byte)(y_buf[i][j]))<<8) | (((Byte)(y_buf[i][j]))<<16));
        }
    }

    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Image::ScrollBar5Change(TObject *Sender)
{
    TRegScrollBar * sb;
    TLabel * lb;

    sb = (TRegScrollBar *)Sender;

    lb = (TLabel *)FindComponent("Label"+IntToStr(sb->Tag));
    lb->Caption = IntToStr(sb->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Image::Button1Click(TObject *Sender)
{
    TRegCheckBox * rcb;
    TRegScrollBar * rle;

    for(int i=0; i<this->ComponentCount; i++)
    {
        if(this->Components[i]->ClassNameIs("TRegScrollBar"))
        {
            rle = (TRegScrollBar *)this->Components[i];
            rle->Refresh();
        }
        if(this->Components[i]->ClassNameIs("TRegCheckBox"))
        {
            rcb = (TRegCheckBox *)this->Components[i];
            rcb->Refresh();
        }
    }    
}
//---------------------------------------------------------------------------


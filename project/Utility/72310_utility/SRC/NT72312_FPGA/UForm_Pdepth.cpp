//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_Pdepth.h"
#include "UForm_Bitmap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"
TForm_Pdepth *Form_Pdepth;
int _csc_coef_[3][4] =
{
    {4096,  0,      6450,   -806},
    {4096,  -767,   -1917,   336},
    {4096,  7601,   0,      -950},
};
//---------------------------------------------------------------------------
__fastcall TForm_Pdepth::TForm_Pdepth(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Pdepth::Button4Click(TObject *Sender)
{
    Graphics::TBitmap * pBitmap;

    pBitmap = new Graphics::TBitmap;

    Form_Bitmap = new TForm_Bitmap(this);

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
        data_buf = (Byte **)malloc(buf_height*sizeof(Byte *));
        Form_Bitmap->pBitmap = pBitmap;
    }
    catch(...)
    {

    }
    
    ReadImageBuf();
    MakeYUVBitmap(pBitmap);
    /*if(Is8bit)
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
    }      */
    Form_Bitmap->ShowModal();
    delete pBitmap;    
}
//---------------------------------------------------------------------------

void __fastcall TForm_Pdepth::ReadImageBuf()
{
    unsigned int buf_start, buf_ends;
    int col, row;
    Byte * LineBuffer;

    float unitby32;
    int RowBytes;
    GetDevice()->AllReadDWord(0xE0000094, (unsigned int)RowBytes);
    RowBytes &= 0x0000FFFF;
    RowBytes = RowBytes*2*3;

    if(!GetDevice()->AllReadDWord(0xE00000AC,buf_start))//read y buffer0 address
    {
        return;
    }
    buf_start = ((buf_start & 0x000000FF)<<20) | 0x00000000;

    buf_start += buf_top*RowBytes+buf_left;

    PB->Position = 0;
    PB->Max = buf_width*buf_height;
    PB->Visible = true;

    for(int i=0;i<buf_height;i++)
    {
        LineBuffer = ReadLine(buf_start);
        data_buf[i] = LineBuffer;

        buf_start += RowBytes;
    }
}
//---------------------------------------------------------------------------
Byte * __fastcall TForm_Pdepth::ReadLine(unsigned int LineStart)
{
    Byte * LineBuffer, * Line;
    unsigned int LineStartRead, LineEndRead;
    Byte bReadData;
    unsigned int dwReadData;
    int left_width;                     
    int modby4, modby4end, readlength;

    left_width = buf_width*3;

    LineBuffer = (Byte *) malloc(left_width*sizeof(Byte));
    Line = LineBuffer;

    modby4 = LineStart % 4;
    LineStartRead = LineStart - modby4;

    modby4end = (LineStart+left_width) % 4;
    LineEndRead = LineStart + left_width  - modby4end;

    if(modby4 !=0 )
    {
        if(!GetDevice()->ReadDWord(LineStartRead, dwReadData))
        {
            return NULL;
        }

        switch(modby4)
        {
            case 3:
                * LineBuffer = (Byte)(dwReadData >> 24);
                LineBuffer ++;
                PB->Position ++;
            break;
            case 2:
                * LineBuffer = (Byte)(dwReadData >> 16);
                * (LineBuffer+1) = (Byte)(dwReadData >> 24);
                LineBuffer += 2;
                PB->Position += 2;
            break;
            case 1:
                * LineBuffer =  (Byte)(dwReadData >> 8);
                * (LineBuffer+1) = (Byte)(dwReadData >> 16);
                * (LineBuffer+2) = (Byte)(dwReadData >> 24);
                LineBuffer += 3;
                PB->Position += 3;
            break;
        }
        LineStartRead += 4;
    }
    

    readlength = LineEndRead - LineStartRead;

    for (int i=0; i<readlength; i+=4)
    {
        if(!GetDevice()->ReadDWord(LineStartRead+i, dwReadData))
        {
            return NULL;
        }

        for(int j=0;j<4;j++)
        {
            bReadData = (dwReadData >> (j*8)) & 0xFF;
            * LineBuffer = bReadData;
            LineBuffer++;
            PB->Position ++;
        }
    }

    if(modby4end != 0)
    {
        if(!GetDevice()->ReadDWord(LineEndRead, dwReadData))
        {
            return NULL;
        }
        switch(modby4)
        {
            case 1:
                * LineBuffer = (Byte)(dwReadData);
                LineBuffer ++;
                PB->Position ++;
            break;
            case 2:
                * LineBuffer = (Byte)(dwReadData);
                * (LineBuffer+1) = (Byte)(dwReadData >> 8);
                LineBuffer += 2;
                PB->Position += 2;
            break;
            case 3:
                * LineBuffer =  (Byte)(dwReadData);
                * (LineBuffer+1) = (Byte)(dwReadData >> 8);
                * (LineBuffer+2) = (Byte)(dwReadData >> 16);
                LineBuffer += 3;
                PB->Position += 3;
            break;
        }
    }          

    return Line;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Pdepth::MakeYUVBitmap(Graphics::TBitmap * pBitmap)
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
            R_data = data_buf[i][j*3];
            G_data = data_buf[i][j*3+1];
            B_data = data_buf[i][j*3+2];
            pBitmap->Canvas->Pixels[j][i]=(TColor)( R_data |(G_data<<8) | (B_data<<16));
        }
    }

    if(SaveBitmap->Execute())
    {
        pBitmap->SaveToFile(SaveBitmap->FileName);
    }


    for(int i=0; i<buf_height; i++)
    {
        for(int j=0; j<buf_width; j++)
        {
            R_data = ((int)data_buf[i][j*3]*_csc_coef_[0][0]+(int)data_buf[i][j*3+1]*_csc_coef_[0][1]+(int)data_buf[i][j*3+2]*_csc_coef_[0][2]+_csc_coef_[0][3]*4096/4)/4096;
            G_data = ((int)data_buf[i][j*3]*_csc_coef_[1][0]+(int)data_buf[i][j*3+1]*_csc_coef_[1][1]+(int)data_buf[i][j*3+2]*_csc_coef_[1][2]+_csc_coef_[1][3]*4096/4)/4096;
            B_data = ((int)data_buf[i][j*3]*_csc_coef_[2][0]+(int)data_buf[i][j*3+1]*_csc_coef_[2][1]+(int)data_buf[i][j*3+2]*_csc_coef_[2][2]+_csc_coef_[2][3]*4096/4)/4096;

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
//---------------------------------------------------------------------------

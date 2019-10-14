//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.hpp>
#include <math.h>
#pragma hdrstop

#include "UForm_Gauss.h"
//#include "Peripheral.h"
//#include "I2C.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"

//extern CI2C I2C_Channel;

TForm_gauss *Form_gauss;
//---------------------------------------------------------------------------
__fastcall TForm_gauss::TForm_gauss(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
double __fastcall TForm_gauss::Gauss(double x, double sigma)
{
    double val;

    val =  -(pow(x,2))/(2*(pow(sigma,2)));
    val = exp(val);

    return val;
}
int * __fastcall TForm_gauss::GetCoff(int W, double sigma, double * data)
{
    double * y;
    int * coff;
    double sum;
    int i_sum;

    int nor;

    if (W==16)
    {
        nor = 4096;
    }
    else
    {
        nor = 1024;
    }

    y = (double *)malloc((2*W+1)*sizeof(double));
    coff = (int *)malloc((2*W+1)*sizeof(int));
    sum = 0;
    for(int i=-W; i<=W; i++)
    {
        y[i+W] = Gauss(i,sigma);
        sum += y[i+W];
    }

    i_sum = 0;
    for(int i=-W; i<=W; i++)
    {
        y[i+W] = y[i+W]/sum;
        y[i+W] = y[i+W] * nor;
        coff[i+W] = Round(y[i+W]);
        if(data != NULL)
        {
            data[i+W] = y[i+W];
        }
        i_sum += coff[i+W];
    }
    i_sum = nor-i_sum;
    if(i_sum>=0)
    {
        coff[W] += i_sum;
    }
    else
    {
        i_sum = -i_sum;
        if(i_sum % 2 == 1)
        {
            for(int i=0;i<=W;i++)
            {
                if(coff[i]==0) continue;
                else if(coff[i]>=((i_sum+1)/2))
                {
                    coff[i] -= (i_sum+1)/2;
                    coff[2*W-i] -= (i_sum+1)/2;
                    coff[W] += 1;
                    break;
                }
                else
                {
                    i_sum -= 2*coff[i];
                    coff[i] = 0;
                    coff[2*W-i] = 0;
                }

            }

        }
        else
        {
            for(int i=0;i<=W;i++)
            {
                if(coff[i]==0) continue;
                else if(coff[i]>=(i_sum/2))
                {
                    coff[i] -= i_sum/2;
                    coff[2*W-i] -= i_sum/2;
                    break;
                }
                else
                {
                    i_sum -= 2*coff[i];
                    coff[i] = 0;
                    coff[2*W-1] = 0;
                }

            }
        }
    }

    free( y);
    
    return coff;

}
//---------------------------------------------------------------------------

void __fastcall TForm_gauss::Button1Click(TObject *Sender)
{
    double * datay;
    double sigma;
    AnsiString str;
    
    datay = (double *)malloc((2*Y_W+1)*sizeof(double));
    sigma = Edit1->Text.ToDouble();

    coff_y =  GetCoff(Y_W, sigma, datay);
    Chart1->Series[0]->Clear();
    Chart1->Series[1]->Clear();
    str = "";
    Memo1->Lines->Clear();
    for(int i=0;i<=2*Y_W;i++)
    {
        str += FloatToStr(coff_y[i])+"    ";
        Chart1->Series[0]->AddXY(i-Y_W,coff_y[i],"",clRed);
        Chart1->Series[1]->AddXY(i-Y_W,datay[i],"",clBlue);
    }
    Memo1->Lines->Add(str);
    free(datay);
}
//---------------------------------------------------------------------------
int __fastcall TForm_gauss::Round(double x)
{
    int y;
    y = x*10 - Floor(x)*10;
    y = y/5;
    if(y>0)
    {
        y = Ceil(x);
    }
    else
    {
        y = Floor(x);
    }
    return y;
}
//---------------------------------------------------------------------------
void __fastcall TForm_gauss::Button2Click(TObject *Sender)
{
    double * datax;
    double sigma;
    TLineSeries * Ser1;
    TLineSeries * Ser2;
    double sum;
    AnsiString str;
    

    //Ser1 = new TLineSeries(Chart2);
    //Ser2 = new TLineSeries(Chart2);

    datax = (double *)malloc((2*X_W+1)*sizeof(double));

    sigma = Edit2->Text.ToDouble();

    coff_x =  GetCoff(X_W, sigma, datax);
    sum = 0;
    str = "";
    Memo2->Lines->Clear();
    for(int i=0;i<2*X_W;i+=4)
    {
        coff_x1[i] = (coff_x[i] /4) *4;
        coff_x1[i+1] = coff_x[i]+(double)((double)((coff_x[i+4]/4)*4-(coff_x[i]/4)*4)*0.25);
        coff_x1[i+2] = coff_x[i]+(double)((double)((coff_x[i+4]/4)*4-(coff_x[i]/4)*4)*0.5);
        coff_x1[i+3] = coff_x[i]+(double)((double)((coff_x[i+4]/4)*4-(coff_x[i]/4)*4)*0.75);
        sum += coff_x1[i]+coff_x1[i+1]+coff_x1[i+2]+coff_x1[i+3];
    }
    coff_x1[2*X_W] = (coff_x[2*X_W]/4)*4;
    sum += coff_x1[2*X_W];

    offset = 4096 - sum;

    Chart2->Series[0]->Clear();
    Chart2->Series[1]->Clear();
    for(int j=0;j<=2*X_W;j++)
    {
        str += FloatToStr(coff_x1[j])+"    ";
        Chart2->Series[0]->AddXY(j-X_W,coff_x[j],"",clBlue);
        Chart2->Series[1]->AddXY(j-X_W,coff_x1[j],"",clRed);
    }
    Memo2->Lines->Add(str);
    free( datax);
}
//---------------------------------------------------------------------------

void __fastcall TForm_gauss::FormCreate(TObject *Sender)
{
    coff_x1 = (double *)malloc((2*X_W+1)*sizeof(double));    
}
//---------------------------------------------------------------------------

void __fastcall TForm_gauss::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    if(coff_x1!=NULL)  free(coff_x1);
    if(coff_y!=NULL)  free(coff_y);
    if(coff_x!=NULL)  free(coff_x);
    Action = caFree;    
}
//---------------------------------------------------------------------------
#define Y_FilterStart 0xE0001332

void __fastcall TForm_gauss::Button3Click(TObject *Sender)
{
    Byte val,val1;

    GetDevice()->ReadByte(Y_FilterStart+Y_W+2, val1);
    val = 0;
    for(int i=0;i<Y_W+1;i++)
    {
        GetDevice()->WriteByte(Y_FilterStart+i, coff_y[i+Y_W] & 0x000000FF);
        if(coff_y[i+Y_W]>255)
        {
            if(Y_W != i)
            {
                val |= (0x01<<(Y_W-1-i));
            }
            else
            {
                val1 &= 0x7F;
                val1 |= 0x80;
            }
        }
    }

    GetDevice()->WriteByte(Y_FilterStart+Y_W+1, val);
    GetDevice()->WriteByte(Y_FilterStart+Y_W+2, val1);
}
//---------------------------------------------------------------------------

#define X_FilterStart 0xE0001340
void __fastcall TForm_gauss::Button4Click(TObject *Sender)
{
    Byte val,val1;
    int coff;


    //Form_Peripheral->ReadByte(Y_FilterStart+Y_W+1, val);
    GetDevice()->ReadByte(X_FilterStart+X_W/4+2, val1);
    val = 0;
    for(int i=0;i<X_W/4+1;i++)
    {
        coff = coff_x1[i*4+X_W]/4;
        GetDevice()->WriteByte(X_FilterStart+i, coff & 0x000000FF);
        if(coff>255)
        {
            if(X_W/4 != i)
            {
                val |= (((coff>>8)& 0xFF)<<(X_W/4-1-i));
            }
            else
            {
                val1 &= 0x3F;
                val1 |= ((coff>>8)&0xFF)<<6;
            }
        }
    }

    GetDevice()->WriteByte(X_FilterStart+X_W/4+1, val);
    GetDevice()->WriteByte(X_FilterStart+X_W/4+2, val1);
    GetDevice()->WriteByte(X_FilterStart+X_W/4+3, offset);
}
//---------------------------------------------------------------------------
/*bool __fastcall TForm_gauss::NT72310_AHBSelAddr(unsigned int Address)
{
    unsigned char SubAddress;
    unsigned char Data;
    unsigned int i;

    for(i = 0 ; i < 4 ; i++)
    {
        Data = (Address>>(i*8)) & 0xFF;
        SubAddress = i;
        if(I2C_Channel.I2CWrite(m_cNT72310Slave , &SubAddress , &Data) == false)
        {
            MessageBox(NULL , "I2C Access Fail !" , "Error" , MB_OK);
            return false;
        }
     }
     return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm_gauss::NT72310_AHBGetData(unsigned int &ReadData)
{
    unsigned char SubAddress;
    unsigned char Data;
    unsigned int i , count;
    ReadData = 0;

    // Read Enable
    SubAddress = 0x0C;
    Data = 0x02;
    if(I2C_Channel.I2CWrite(m_cNT72310Slave , &SubAddress , &Data) == false)
    {
            MessageBox(NULL , "I2C Access Fail !" , "Error" , MB_OK);
            return false;
    }

    Data = 0xFF;
    count = 0;
    while((Data!=0) || (count > 1500))
    {
        if(I2C_Channel.I2CRead(m_cNT72310Slave , &SubAddress , &Data) == false)
        {
            MessageBox(NULL , "I2C Access Fail !" , "Error" , MB_OK);
            return false;
        }
        count++;
    }

    if(count >= 1500)
    {
        MessageBox(NULL , "Timeout" , "Error" , MB_OK);
        return false;
    }

    // Read Data
    for(i = 0 ; i < 4 ; i++)
    {
        SubAddress = i+8;
        if(I2C_Channel.I2CRead(m_cNT72310Slave , &SubAddress , &Data) == false)
        {
            MessageBox(NULL , "I2C Access Fail !" , "Error" , MB_OK);
            return false;
        }
        ReadData |= (Data<<(i*8));
     }
     return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm_gauss::NT72310_AHBSetData(unsigned int WriteData)
{
    unsigned char SubAddress;
    unsigned char Data;
    unsigned int i , count;

    // Write Data
    for(i = 0 ; i < 4 ; i++)
    {
        Data = (WriteData>>(i*8)) & 0xFF;
        SubAddress = i+4;
        if(I2C_Channel.I2CWrite(m_cNT72310Slave , &SubAddress , &Data) == false)
        {
            MessageBox(NULL , "I2C Access Fail !" , "Error" , MB_OK);
            return false;
        }
     }
     
     // Write Enable
    SubAddress = 0x0C;
    Data = 0x01;
    if(I2C_Channel.I2CWrite(m_cNT72310Slave , &SubAddress , &Data) == false)
    {
            MessageBox(NULL , "I2C Access Fail !" , "Error" , MB_OK);
            return false;
    }

    Data = 0xFF;
    count = 0;
    while((Data!=0) || (count > 1500))
    {
        if(I2C_Channel.I2CRead(m_cNT72310Slave , &SubAddress , &Data) == false)
        {
            MessageBox(NULL , "I2C Access Fail !" , "Error" , MB_OK);
            return false;
        }
        count++;
    }

    if(count >= 1500)
    {
        MessageBox(NULL , "Timeout" , "Error" , MB_OK);
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm_gauss::ReadByte(unsigned int Address, Byte &ReadByte)
{
	int modby4;
	unsigned int ReadData;

	modby4 = Address % 4;
	Address -= modby4;
	if(!NT72310_AHBSelAddr(Address))
	{
		return false;
	}
	if(!NT72310_AHBGetData(ReadData) )
	{
		return false;
	}
	ReadByte = (ReadData >> (modby4*8)) & 0xFF;
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm_gauss::WriteByte(unsigned int Address, Byte WriteByte)
{
	int modby4;
	unsigned int ReadData;

	modby4 = Address %4;
	Address -= modby4;

	if(!ReadDWord(Address, ReadData))
	{
		return false;
	}

	ReadData = ReadData & (0xFFFFFFFF-(0xFF<<(modby4*8)));
	ReadData = ReadData + (WriteByte<<(modby4*8));

	if(!NT72310_AHBSelAddr(Address))
	{
		return false;
	}
	if(!NT72310_AHBSetData(ReadData))
	{
		return false;
	}
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm_gauss::ReadDWord(unsigned int Address, unsigned int &ReadDWord)
{
	if(!NT72310_AHBSelAddr(Address))
	{
		return false;
	}
	if(!NT72310_AHBGetData(ReadDWord) )
	{
		return false;
	}
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm_gauss::WriteDWord(unsigned int Address, unsigned int WriteDWord)
{
	if(!NT72310_AHBSelAddr(Address))
	{
		return false;
	}
	if(!NT72310_AHBSetData(WriteDWord))
	{
		return false;
	}
    return true;
}         */
//---------------------------------------------------------------------------

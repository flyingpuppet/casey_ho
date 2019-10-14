//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_BWData.h"
#include "UMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"
TForm_BWData *Form_BWData;
//---------------------------------------------------------------------------
__fastcall TForm_BWData::TForm_BWData(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_BWData::SetSeries(int s, int p, double ** b)
{
    seriesCount = s;
    points = p;
    pbuf = b;
}
void __fastcall TForm_BWData::SetLines(int l)
{
    lines = l;
}
void __fastcall TForm_BWData::FormShow(TObject *Sender)
{

    TLineSeries * Lines;
    AnsiString str;
    TTabSheet * n_page;
    TChart * chart;
    int pageCount;
    TColor c_color[4] = {clRed, clGreen, clBlue, clYellow};


    //Chart1->Series[0]->FillSampleValues(random(100));
    isAuto = (bool *)malloc(seriesCount*sizeof(bool));//new bool[seriesCount];
    for(int i=0;i<seriesCount;i++)
    {
        isAuto[i] = false;
    }

    if (pbuf == NULL) return;

    SG_Data->ColCount = points+1;
    SG_Data->RowCount = seriesCount+1;
    SG_Data->Cells[0][0]= "";
    SG_Data->DefaultColWidth = 50;
    for(int i=1;i<SG_Data->ColCount;i++)
    {
        SG_Data->Cells[i][0]= IntToStr(i);
    }
    for(int i=1;i<SG_Data->RowCount;i++)
    {
        SG_Data->Cells[0][i]= IntToStr(i);
    }
    for(int i=0;i<SG_Data->RowCount-1;i++)
    {
        for(int j=0;j<SG_Data->ColCount-1;j++)
        {
            str.printf("%.2f",pbuf[i][j]);
            SG_Data->Cells[j+1][i+1] = str;//IntToStr(pbuf[i][j]);
        }
    }

    
    pageCount = (seriesCount % 4 == 0)?(seriesCount /4)-1:seriesCount / 4;
    for(int i=0; i<=pageCount; i++)
    {
        n_page = new TTabSheet(ChartPage);
        n_page->PageControl = ChartPage;
        //ShowMessage(ChartPage->PageCount);
        n_page->Align = alClient;
        n_page->Caption = IntToStr(i);
        ChartPage->ActivePageIndex = 0;
        for(int j=0;j<4;j++)
        {
            if((i*4+j)>=seriesCount)
            {
                break;
            }
            chart = new TChart(n_page);
            chart->Parent = n_page;
            chart->Align = alTop;
            chart->Title->Text->Add((i*4+j));
            chart->View3D = false;
            chart->AllowPanning = pmBoth;
            chart->AllowZoom = true;
            chart->OnClickBackground = ClickBackground;
            chart->Tag = i*4+j;
            if(i == (seriesCount / 4))
            {
                chart->Height = n_page->Height/(seriesCount%4);
            }
            else
            {
                chart->Height = n_page->Height/4;
            }
            Lines = new TLineSeries(chart);
            Lines->Clear();

            for(int m=0;m<points;m++)
            {
                chart->LeftAxis->Minimum = 0;
                if(lines>8)
                {
                    chart->LeftAxis->Maximum = 2000;
                }
                else if(lines>6)
                {
                    chart->LeftAxis->Maximum = 1000;
                }
                else if(lines>4)
                {
                    chart->LeftAxis->Maximum = 500;
                }
                else
                {
                    chart->LeftAxis->Maximum = 200;
                }
                chart->LeftAxis->Automatic = false;
                //Lines->Pointer->Visible = true;

                Lines->AddY((double)(pbuf[i*4+j][m]),IntToStr(m),c_color[j]);
            }
            chart->AddSeries(Lines); 
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_BWData::ClickBackground(TCustomChart *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    isAuto[Sender->Tag] = !isAuto[Sender->Tag];
    Sender->LeftAxis->AutomaticMaximum = isAuto[Sender->Tag];
    if(isAuto)
    {
        if(lines>8)
        {
            Sender->LeftAxis->Maximum = 1000;
        }
        else if(lines>4)
        {
            Sender->LeftAxis->Maximum = 400;
        }
        else if(lines>0)
        {
            Sender->LeftAxis->Maximum = 200;
        }
        else
        {
            Sender->LeftAxis->Maximum = 200;
        }
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------




void __fastcall TForm_BWData::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    free(isAuto);
    for(int i=0;i<seriesCount;i++)
    {
        if(pbuf[i] != NULL)
        {
            free(pbuf[i]);
        }
    }
    free(pbuf);
    Action = caFree;    
}
//---------------------------------------------------------------------------


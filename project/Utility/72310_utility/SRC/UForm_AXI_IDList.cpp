//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_AXI_IDList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_AXI_IDList *Form_AXI_IDList;
//---------------------------------------------------------------------------
__fastcall TForm_AXI_IDList::TForm_AXI_IDList(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_AXI_IDList::BitBtn1Click(TObject *Sender)
{
    Count = 0;
    AgentNames = "";
    for(int i=0;i<clb_axi_agents->Items->Count;i++)
    {
        if(clb_axi_agents->Checked[i])
        {
            Count++;
            AgentNames += clb_axi_agents->Items->Strings[i]+", ";
        }
    }
    if(Count > 0)
    {
        Agents = (int *)malloc(Count*sizeof(int));
        Count = 0;
        for(int i=0;i<clb_axi_agents->Items->Count;i++)
        {
            if(clb_axi_agents->Checked[i])
            {
                Agents[Count] = i;
                Count++;
            }
        }
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm_AXI_IDList::FormShow(TObject *Sender)
{
    for(int i=0;i<clb_axi_agents->Items->Count;i++)
    {
        clb_axi_agents->Checked[i] =  false;
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#ifndef UForm_AXI_IDListH
#define UForm_AXI_IDListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TForm_AXI_IDList : public TForm
{
__published:	// IDE-managed Components
    TCheckListBox *clb_axi_agents;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    int * Agents;
    AnsiString AgentNames;
    int Count;
    __fastcall TForm_AXI_IDList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_AXI_IDList *Form_AXI_IDList;
//---------------------------------------------------------------------------
#endif

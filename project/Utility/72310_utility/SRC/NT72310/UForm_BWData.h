//---------------------------------------------------------------------------

#ifndef UForm_BWDataH
#define UForm_BWDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm_BWData : public TMEMCForm
{
__published:	// IDE-managed Components
    TPageControl *ChartPage;
    TPanel *panelStr;
    TStringGrid *SG_Data;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


private:	// User declarations
    int seriesCount;
    int points;
    double ** pbuf;
    bool *isAuto;
    int lines;
public:		// User declarations
    __fastcall TForm_BWData(TComponent* Owner);
    void __fastcall SetSeries(int s, int p, double ** b);
    void __fastcall ClickBackground(TCustomChart *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall SetLines(int l);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_BWData *Form_BWData;
//---------------------------------------------------------------------------
#endif

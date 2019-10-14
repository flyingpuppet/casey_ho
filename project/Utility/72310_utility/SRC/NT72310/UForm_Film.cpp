//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_Film.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TForm_Film *Form_Film;
//---------------------------------------------------------------------------

AnsiString FilmRegEditInfo[] =
{
	"0xE00004",
	"film_quit_th",     	"02",   "0",    "8",
	"film_prd_th",      	"03",   "0",    "8",
	"film_det_en",      	"04",   "0",    "9",
	"film_r_h0",        	"08",	"0",	"10",
	"film_r_v0",			"0A",	"0",	"10",
	"film_r_h1",			"0C",	"0",	"10",
	"film_r_v1",			"0E",	"0",	"10",
	"film_r_h0_c",     		"10",	"0",	"10",
	"film_r_v0_c",			"12",	"0",	"10",
	"film_r_h1_c",			"14",	"0",	"10",
	"film_r_v1_c",			"16",	"0",	"10",
	"film_diff_th_c",		"21",	"0",	"16",
	"film_diff_c_lsb",		"23",	"0",	"8",
	"film_dyn_w1_c",		"20",	"4",	"4",
	"film_dyn_w2_c",		"20",	"0",	"4",
	"dyn_th_sel_22",		"2E",	"0",	"2",
	"dyn_th_sel_32",		"2E",	"2",	"2",
	"dyn_th_sel_3223",		"2E",	"3",	"2",
	"dyn_th_sel_2224",		"2E",	"6",	"2",
	"dyn_th_sel_32322",		"2F",	"0",	"2",
	"dyn_th_sel_1123",		"2F",	"2",	"2",
	"dyn_th_sel_55",		"2F",	"4",	"2",
	"dyn_th_sel_6487",		"2F",	"6",	"2",
	"film_cad_num_22",		"3C",	"0",	"4",
	"film_cad_num_32",		"3C",	"4",	"4",
    "film_cad_num_3223",	"3D",	"0",	"4",
    "film_cad_num_2224",	"3D",	"4",	"4",
    "film_cad_num_32322",	"3E",	"0",	"4",
    "film_cad_num_1123",	"3E",	"4",	"4",
    "film_cad_num_55",		"3F",	"0",	"4",
    "film_cad_num_64",		"3F",	"4",	"4",
    "film_cad_num_87",		"40",	"0",	"4",
    "film_quit_diff_th_a",	"24",	"0",	"16",
    "film_quit_diff_th_b",	"26",	"0",	"16",
    "film_quit_diff_th_c",	"28",	"0",	"16",
    "film_quit_diff_th_d",	"2A",	"0",	"16",
    "film_quit_diff_th_e",	"2C",	"0",	"16",
    "rb_apl",				"8E",	"0",	"8",
    "rb_glb_mot_a",			"90",	"0",	"24",
    "rb_glb_mot_b",			"93",	"0",	"24",
    "rb_glb_mot_c",			"96",	"0",	"24",
    "rb_glb_mot_d",			"99",	"0",	"24",
    "rb_glb_mot_e",			"9C",	"0",	"24",
    "rb_glb_mot_r",			"9F",	"0",	"24",
    "rb_glb_mot_all",		"A2",	"0",	"24",
    "rb_glb_mot_all_film",  "A5",   "0",    "24",
    "rb_y_hstgm_max",		"EC",	"0",	"16",
    "rb_y_hstgm_max2",		"EE",	"0",	"16",
    "rb_y_hstgm_min",		"F0",	"0",	"16",
    "rb_y_hstgm_max_idx",	"F2",	"0",	"5",
    "rb_y_hstgm_max2_idx",	"F2",	"5",	"5",
    "rb_y_hstgm_min_idx",	"F3",	"2",	"5",    
    "EOF",
};
__fastcall TForm_Film::TForm_Film(TComponent* Owner)
    : TMEMCForm(Owner)
{
    
}
//---------------------------------------------------------------------------
void __fastcall TForm_Film::btn_RefreshClick(TObject *Sender)
{
    TRegLabeledEdit * ed;
    TRegCheckBox * cb;
    AnsiString conName;
    for(int i=0;i<ComponentCount;i++)
    {
        conName = Components[i]->ClassName();
        if(conName == "TRegLabeledEdit")
        {
            ed = (TRegLabeledEdit *)Components[i];
            ed->Refresh();
        }
        if(conName == "TRegCheckBox")
        {
            cb = (TRegCheckBox *)Components[i];
            cb->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Film::FormCreate(TObject *Sender)
{
    LoadRegEditInfo(FilmRegEditInfo);    
}
//---------------------------------------------------------------------------


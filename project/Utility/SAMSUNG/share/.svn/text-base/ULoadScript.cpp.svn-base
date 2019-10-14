//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ULoadScript.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"
TForm_LoadScript *Form_LoadScript;
//---------------------------------------------------------------------------
__fastcall TForm_LoadScript::TForm_LoadScript(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm_LoadScript::Button1Click(TObject *Sender)
{
    if(OpenScript->Execute())
    {
        MemoScript->Lines->Clear();
        MemoScript->Lines->LoadFromFile(OpenScript->FileName);

    }
}
//---------------------------------------------------------------------------
bool __fastcall TForm_LoadScript::IsComment(AnsiString str)
{
    if(str.SubString(1,1) == "#")
    {
        return true;
    }
    else
    {
        return false;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TForm_LoadScript::ExecuteScript(AnsiString str)
{
    char c_command[32];
    AnsiString command;
    unsigned int address;
    unsigned int data;
    
    if(!IsComment(str))
    {
        sscanf(str.c_str(), "%s %x %x", &c_command, &address, &data);
        command.printf("%s", c_command);

        if((command == "wmem")||(command == "WMEM"))
        {
            return GetDevice()->WriteDWord(address, data);
        }
        else
        {
            return false;   
        }
    }
    else
    {
        return true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_LoadScript::Button2Click(TObject *Sender)
{
    for(int i=0; i<MemoScript->Lines->Count; i++)
    {
        if(Trim(MemoScript->Lines->Strings[i]) == "")
        {
            continue;
        }
        else if(IsComment(MemoScript->Lines->Strings[i]))
        {
            continue;    
        }
        else
        {
            ExecuteScript(MemoScript->Lines->Strings[i]);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_LoadScript::Button3Click(TObject *Sender)
{
    if(SaveScript->Execute())
    {
        MemoScript->Lines->SaveToFile(SaveScript->FileName);

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_LoadScript::Button4Click(TObject *Sender)
{
    MemoScript->Lines->Clear();        
}
//---------------------------------------------------------------------------


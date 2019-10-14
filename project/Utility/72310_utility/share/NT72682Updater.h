//---------------------------------------------------------------------------

#ifndef NT72682UpdaterH
#define NT72682UpdaterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <stdio.h>

#include "elf_header.h"		//torres100813
#include <vector.h>
//---------------------------------------------------------------------------
class TForm_NT72682Updater : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl_Container;
    TOpenDialog *OpenDialog;
    TProgressBar *ProgressBar_Complete;
    TSaveDialog *SaveDialog;
    TTabSheet *TabSheet_codeDmp310;
    TGroupBox *GroupBox_codeDmp310_input;
    TLabeledEdit *LabeledEdit_310_subProgram;
    TLabeledEdit *LabeledEdit_310_subProgramDDR;
    TLabeledEdit *LabeledEdit_310_FRCmain;
    TLabeledEdit *LabeledEdit_310_dataSRAM;
    TButton *Button_310_subProgramDDR;
    TButton *Button_310_dataSRAM;
    TLabeledEdit *LabeledEdit_310_subProgram_offset;
    TLabeledEdit *LabeledEdit_310_subProgramDDR_offset;
    TLabeledEdit *LabeledEdit_310_dataSRAM_offset;
    TButton *Button_310_subProgram;
    TLabeledEdit *LabeledEdit_310_FRCmain_offset;
    TLabeledEdit *LabeledEdit_310_startAddr;
    TLabeledEdit *LabeledEdit_310_FRC;
    TButton *Button_310_FRC;
    TLabeledEdit *LabeledEdit_310_FRC_offset;
    TLabeledEdit *LabeledEdit_310_FRCstartAddr;
    TLabeledEdit *LabeledEdit_310_splitOffset;
    TMemo *Memo_310_dbg;
    TButton *Button_310_dmp;
    TLabeledEdit *LabeledEdit_310_pSize;
    TLabeledEdit *LabeledEdit_310_dSize;
    TTabSheet *TabSheet_312parser;
    TButton *Button_310_cpy;
    TButton *Button_310_FRCmain;
    TMemo *Memo_310_tmp;
    TMemo *Memo_72310_dbg;
    TLabeledEdit *LabeledEdit_310_unlock;
    /*void __fastcall Button_VGAEDIDOpenClick(TObject *Sender);
    void __fastcall Button_HDCPOpenClick(TObject *Sender);
    void __fastcall RadioGroup_FileFormatClick(TObject *Sender);
    void __fastcall Button_HDMIEDIDOpenClick(TObject *Sender);
    void __fastcall Button_Open_8051FWClick(TObject *Sender);
    void __fastcall Button_Open_MIPSBootLoaderClick(TObject *Sender);
    void __fastcall Button_Open_MIPSKernelClick(TObject *Sender);
    void __fastcall Button_Open_MIPSRamdiskClick(TObject *Sender);
    void __fastcall Button_Open_HDMIEDIDClick(TObject *Sender);
    void __fastcall Button_Open_VGAEDIDClick(TObject *Sender);
    void __fastcall Button_Open_HDCPKeyClick(TObject *Sender);
    void __fastcall CheckBox_8051FWClick(TObject *Sender);
    void __fastcall CheckBox_MIPSBootLoaderClick(TObject *Sender);
    void __fastcall CheckBox_MIPSKernelClick(TObject *Sender);
    void __fastcall CheckBox_MIPSRamdiskClick(TObject *Sender);
    void __fastcall CheckBox_HDMIEDIDClick(TObject *Sender);
    void __fastcall CheckBox_VGAEDIDClick(TObject *Sender);
    void __fastcall CheckBox_HDCPKeyClick(TObject *Sender);
    void __fastcall FC_CreateFlashImageBtnClick(TObject *Sender);
    void __fastcall Button_DRMKeyOpenClick(TObject *Sender);
    void __fastcall Button_fileClick(TObject *Sender);
	void __fastcall Button_freeBurnWriteClick(TObject *Sender);
    void __fastcall Button_72310_subProgramClick(TObject *Sender);
    void __fastcall Button_72310_parseClick(TObject *Sender);
    void __fastcall Button_72310_i2cWriteClick(TObject *Sender);*/
    void __fastcall Button_310_subProgramClick(TObject *Sender);
    void __fastcall Button_310_dmpClick(TObject *Sender);
    void __fastcall Button_310_cpyClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
		
private:	// User declarations
    HANDLE m_hComm;
    AnsiString Flasher_File , firmware_File , DDRTable_File;
    AnsiString VGAEDID_File , HDCP_File , HDMIEDID_File;
    bool __fastcall DownloadData(AnsiString strFileName , unsigned char ucCommand);
    bool __fastcall ParsingIni(AnsiString strFileName);
    bool __fastcall SendCommand(unsigned char ucCommand, const int delay_time = 3000);
    bool __fastcall SendLength(unsigned short usLength);
    bool __fastcall SendData(unsigned short usLength , FILE* infile);
    bool __fastcall SendForceEnd();
    bool __fastcall CreateKeyGroupFile(AnsiString *NewFilePath);
    void __fastcall SaveIni();
    AnsiString __fastcall GetFlashCodeVersion(const AnsiString &file_name);
    AnsiString __fastcall Get8051FWVersion(const AnsiString &file_name);
	TCheckBox *checkboxFile[6];	//100528
	TEdit *editFile[6];
	TButton *btnFile[6];
	TEdit *editFileOffset[6];
	TEdit *editFileLen[6];

	TLabeledEdit *lbledit72310[4];
	TButton *btn72310[5];
		
    // Flash Creator
    UINT8 *FlashData_8051FW;
    UINT8 *FlashData_MIPSBootLoader;
    UINT8 *FlashData_MIPSKernel;
    UINT8 *FlashData_MIPSRamdisk;
    UINT8 *FlashData_HDMIEDID;
    UINT8 *FlashData_VGAEDID;
    UINT8 *FlashData_HDCPKey;

    UINT32 DataSize_8051FW;
    UINT32 DataSize_MIPSBootLoader;
    UINT32 DataSize_MIPSKernel;
    UINT32 DataSize_MIPSRamdisk;
    UINT32 DataSize_HDMIEDID;
    UINT32 DataSize_VGAEDID;
    UINT32 DataSize_HDCPKey;

	typedef unsigned int uint32_t;		//torres100531 
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	
	#define WRITE_PROTECT	0x55
	#define NON_WRITE_PROTECT	0xAA
	void __fastcall SaveINIFileT(AnsiString inputFileName);	//100527 test
    void __fastcall FlashCreator_Initialize();
    bool __fastcall FlashCreator_EraseWholeFlash();
    void __fastcall FlashCreator_Encryption(UINT8 *Data, const UINT32 &DataSize);
    void __fastcall FlashCreator_EraseArray(UINT8 **FlashData, UINT32 *DataSize);
    unsigned long __fastcall FlashCreator_GetFlashSize();
    bool __fastcall FlashCreator_OpenFile(TEdit *Edit_FilePath, UINT8 **Data, UINT32 *DataSize);
    AnsiString __fastcall FlashCreator_CreateAddressRangeString(const UINT32 &StartAddr, const UINT32 &DataSize);
    void __fastcall FlashCreator_SwitchControls(const bool Checked, TLabel *Label_Addr, TLabel *Label_0x,
													TEdit *Edit_Addr, TLabel *Label_AddrRange, TLabel *Label_RangeValue,
													TLabel *Label_File, TEdit *Edit_FilePath, TButton *Button_Open);
	bool __fastcall CMD_SwitchBase(unsigned char B2, unsigned char B1);
	bool __fastcall LoadDataToBuffer//(unsigned char *FileData, 
										//TEdit *Edit_File, TEdit *Edit_FileOffset, TEdit *Edit_FileLen);
								(unsigned char *FileData, AnsiString fileName, 
															unsigned int fileOffset, unsigned int fileLen);		
	bool CMD_GetBaseAddress(unsigned int *pulBaseAddr);
	bool CMD_SwitchBaseAddress(unsigned int ulBaseAddr);
	bool CMD_SetWriteProtect(bool bProtect);
	bool CMD_Read256B(uint32_t ulAddr, uint8_t *pucDataBuf);
	bool CMD_Write256B(uint32_t ulAddr, uint8_t *pucDataBuf);
	bool CMD_Erase4KB_withSize(uint32_t ulAddr, uint32_t ulSize);
	bool CMD_Read4KB(uint32_t ulAddr, uint8_t *pu8Buf4KB);
	bool CMD_Write4KB(uint32_t ulAddr, uint8_t *pu8Buf4KB);
	bool CMD_Erase4KB(uint32_t ulAddr);
	void __fastcall BurnCodeFromFile(uint32_t ulAddr, uint32_t ulSize, AnsiString inputFilePath);
	bool CheckOffsetOrder(int *blkNum, int blkCnt);
	bool MergeFiles(unsigned int &totalFileLen, int filesCnt);
	class BurningFile
	{
		public:
			unsigned int fileOffset, fileLen;
			int startBlkNum;
			AnsiString fileName;
	} *burningFiles;

    _Endian endian;
	Elf32_Ehdr elf_hdr;
	Elf32_Phdr ph_array[10];
	Elf32_Shdr sh_array[256], *sh_strTable;
	
	class BurningHeader72310
	{
		public:
			unsigned int startAddr;
			unsigned int endAddr;
			unsigned int CRC;
			unsigned char index;
			unsigned char fileIndex;
			unsigned char type;	//0: text, 1: data, 2: textN, 3: dataN
			
	} *brnHdr;
	
	class BurningHeader72310_short
	{
		public:
			unsigned int startAddr;
			unsigned int endAddr;
			unsigned int CRC;
	}headerTable, FRCtable, totalHdr;
	
	vector<BurningHeader72310> vec_72310header;
	vector<BurningHeader72310_short> vec_72310header_short;
	vector<BurningHeader72310_short> vec_72310TotalHeader;
	
	unsigned int currentOffset, splitOffset;
	TLabeledEdit *lblEdit_72310_file[5];
	TLabeledEdit *lblEdit_72310_fileOffset[5];
	
	TLabeledEdit *lblEdit_310_file[5];
	TLabeledEdit *lblEdit_310_fileOffset[5];
	TButton *btn310[5];
	unsigned int currentOffset310, splitOffset310;
	unsigned char m_cNT72310Slave;
	unsigned int totalHdr_CRC, totalHdr_Size;

	int program_header_check(Elf32_Phdr& p_elf_hdr, int flag);
	int section_header_check(Elf32_Shdr& sec_hdr, int flag);
	int elf_header_check(Elf32_Ehdr* p_elf_hdr, int flag);
	int parser(const Elf32_Shdr& sec_hdr, FILE* in_file, int sh_num, char* name, int flag);
	int readStrTable(Elf32_Ehdr* elf_hdr, Elf32_Shdr *sh_hdr, Elf32_Shdr *sh_strTable, FILE* in_file,
						char* outBuf);
	//bool I2C72310_burn256Bytes(unsigned int address, unsigned int length, unsigned char* buf);
	//bool I2C72310_burnCode(unsigned int startAddr, AnsiString input_fileName);
	//bool __fastcall AHBSelAddr_NT72310(unsigned int Address);
	//bool __fastcall AHBGetData_NT72310(unsigned int &ReadData);
	//bool __fastcall AHBSetData_NT72310(unsigned int WriteData);
	//bool __fastcall I2C72310_write(uint32_t addr, uint32_t data);
	//bool __fastcall I2C72310_read(uint32_t addr, uint32_t &data);
	
	/*bool I2C_burnCode_72310_single(unsigned int address, unsigned int length, unsigned char buf[256]); */
	void reOrderBlock(unsigned char fleIdx);
	void reOrderBlock310(unsigned char fleIdx);
	bool __fastcall Write_SubProgram(unsigned int startAddr);
	void parse_FRCfile(AnsiString inputFile, AnsiString outputFile);
	void copy_vecHeader(vector<BurningHeader72310_short> &dest, 
								vector<BurningHeader72310> &src, int index);
	void __fastcall Cal_totalHeader(const AnsiString &inputFile);
	
public:		// User declarations
    __fastcall TForm_NT72682Updater(TComponent* Owner);
    typedef void __fastcall (__closure *PreCloseCallBack)(AnsiString FormCaption);
    typedef void __fastcall (__closure *ActiveForm)(AnsiString FormCaption);
    PreCloseCallBack PreClose;
    ActiveForm CurForm;
    long __fastcall GLOBAL_GetFileSize(const AnsiString &file_path);
    bool __fastcall GLOBAL_CopyFile(AnsiString &dest_filePath, AnsiString &src_filePath, bool appendMode = true);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_NT72682Updater *Form_NT72682Updater;
//---------------------------------------------------------------------------
#endif

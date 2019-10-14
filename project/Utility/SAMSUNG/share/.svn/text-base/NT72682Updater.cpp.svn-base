//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <IniFiles.hpp>
#include <dos.h>

#include "NT72682Updater.h"
#include "math.h"		//torres100817
#include "I2C.h"		//torres100901

#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_NT72682Updater *Form_NT72682Updater;

unsigned char *pu8SPIBuf = NULL;
unsigned int SPIBufSize = 0;
unsigned char *pu8SPITags = NULL;
unsigned int u8SPITagSize = 0;
unsigned int g_u32startAddr, g_u32hdrAddr;
bool g_bAlign4 = false;
bool g_bShowMsg = false;
unsigned int g_u32totalOffset;

unsigned char fileIdx, blockCnt[4];	//used to count data & text sections.
extern CI2C I2C_Channel;

const UINT8 FLASHER_ACK = 0xA5;
const UINT8 FLASHER_NACK = 0x5A;
const UINT8 FLASHER_CMD_UPDATE_KEY_GROUP = 0x81;        // update VGA EDID
const UINT8 FLASHER_CMD_ERASE_ALL        = 0x82;        // erase whole flash
const UINT8 FLASHER_CMD_UPDATE_8051_FW   = 0x85;        // update STBC FW
const UINT8 FLASHER_CMD_UPDATE_DDR_TABLE = 0x87;        // update DDR Table
const UINT8 FLASHER_CMD_DOWNLOAD_FLASHER = 0x89;        // download flasher
//---------------------------------------------------------------------------
const int BURNING_TIME_OUT = 15;
//---------------------------------------------------------------------------
//int elf_header_check(Elf32_Ehdr* p_elf_hdr, int flag);

unsigned int Cal_ChkSum(unsigned int u32Value1, unsigned int u32Value2);
//unsigned int ChangeEndian(unsigned int u32input);
void ChangeEndian(void *input, unsigned int length, unsigned char *ans);
unsigned int Cal_ChkSumF(void *input, unsigned int ByteLength);
int Cal_ChkSum_File(AnsiString &fileName);

__fastcall TForm_NT72682Updater::TForm_NT72682Updater(TComponent* Owner)
    : TForm(Owner)
{
    btn310[0] = Button_310_subProgram;
	btn310[1] = Button_310_subProgramDDR;
	btn310[2] = Button_310_dataSRAM;
	btn310[3] = Button_310_FRCmain;
	btn310[4] = Button_310_FRC;

    lblEdit_310_file[0] = LabeledEdit_310_subProgram;
	lblEdit_310_file[1] = LabeledEdit_310_subProgramDDR;
	lblEdit_310_file[2] = LabeledEdit_310_dataSRAM;
	lblEdit_310_file[3] = LabeledEdit_310_FRCmain;
	lblEdit_310_file[4] = LabeledEdit_310_FRC;

	lblEdit_310_fileOffset[0] = LabeledEdit_310_subProgram_offset;
	lblEdit_310_fileOffset[1] = LabeledEdit_310_subProgramDDR_offset;
	lblEdit_310_fileOffset[2] = LabeledEdit_310_dataSRAM_offset;
	lblEdit_310_fileOffset[3] = LabeledEdit_310_FRCmain_offset;
	lblEdit_310_fileOffset[4] = LabeledEdit_310_FRC_offset;
}
//---------------------------------------------------------------------------
int TForm_NT72682Updater::elf_header_check(Elf32_Ehdr* p_elf_hdr, int flag)
{
	Elf32_Ehdr elf_hdr = *p_elf_hdr;
	unsigned long temp, temp_word;
	unsigned short temp_half;
	FILE* log;

	if(LOG(flag) )
		log = fopen("log", "w");

	// e_ident ---------------------------
	if(elf_hdr.e_ident[0] != 0x7F || elf_hdr.e_ident[1] != 'E' || elf_hdr.e_ident[2] != 'L' || elf_hdr.e_ident[3] != 'F')
	{
		//if(INFO(flag) )
				 //printf("Not ELF format!\n");
		if(LOG(flag) )
				fprintf(log, "Not ELF format!\n");
		return 1;
	}

	if(elf_hdr.e_ident[4] != 1)
	{
		//if(INFO(flag) )			{	printf("Invalid or not supported class!!!\n");		    }
		if(LOG(flag) )
			fprintf(log, "Invalid or not supported class!!!\n");
		
		return 1;
	}

	if(elf_hdr.e_ident[5] == 0x02)
	{
		//if(INFO(flag) )  	{	printf("Big Endian\n"); 	        }
		if(LOG(flag) )
			fprintf(log, "Big Endian\n");
		
		endian = big;
	}
	else if(elf_hdr.e_ident[5] == 0x01)
	{
		//if(INFO(flag) )  	{	printf("Little Endian\n");	        }
		if(LOG(flag) )
			fprintf(log, "Little Endian\n");
		
		endian = little;
	}
	else
	{
		if(INFO(flag))		{	printf("Invalid data encoding!!!\n");		}
		if(LOG(flag))		{	fprintf(log, "Invalid data encoding!!!\n");	}
		return 1;
	}


    // e_type ---------------------------
    temp_half = elf_hdr.e_type;
    elf_hdr.e_type = (endian==big) ? ((temp_half&0x00ff)<<8) + ((temp_half&0xff00)>>8) : temp_half;
    
 	if(elf_hdr.e_type != 0x0002)
    {
        if(INFO(flag))	{	printf("Not excutable file!!!\n");		    }
        if(LOG(flag)) 	{	fprintf(log, "Not excutable file!!!\n");    }
		return 1;
    }
    
    // e_machine ---------------------------
    temp_half = elf_hdr.e_machine;
    elf_hdr.e_machine = (endian==big) ? ((temp_half&0x00ff)<<8) + ((temp_half&0xff00)>>8): temp_half;
    
    // e_version ---------------------------
    temp_word = elf_hdr.e_version;
    elf_hdr.e_version = (endian==big) ? ((temp_word>>24)&0xff) | ((temp_word>>8)&0xff00) | ((temp_word<<24)&0xff000000) | ((temp_word<<8)&0xff0000)
                      : temp_word;
   	if(elf_hdr.e_version != 0x00000001)
   	{
   		if(INFO(flag))	{	printf("Invalid version!!!\n");		    }
   		if(LOG(flag))	{	fprintf(log, "Invalid version!!!\n");	}
   		return 1;
   	}


    // e_entry ---------------------------
	if(endian == big)
	{
		temp = elf_hdr.e_entry;
		elf_hdr.e_entry = ((temp >> 24)&0xff) | ((temp >> 8)&0xff00) | ((temp << 24)&0xff000000) | ((temp << 8)&0xff0000);
	}
	if(INFO(flag))	{	printf("Starting address of physical memory: 0x%X\n", elf_hdr.e_entry);	        }
	if(LOG(flag))	{	fprintf(log, "Starting address of physical memory: 0x%X\n", elf_hdr.e_entry);	}

    // e_phoff ---------------------------
	if(endian == big)
	{
		temp = elf_hdr.e_phoff;
		elf_hdr.e_phoff = ((temp >> 24)&0xff) | ((temp >> 8)&0xff00) | ((temp << 24)&0xff000000) | ((temp << 8)&0xff0000);
	}
	if(INFO(flag))	{	printf("Program header offset: 0x%08X\n", elf_hdr.e_phoff);     	}
	if(LOG(flag))	{	fprintf(log, "Program header offset: 0x%08X\n", elf_hdr.e_phoff);	}

    // e_shoff ---------------------------
	if(endian == big)
	{
		temp = elf_hdr.e_shoff;
		elf_hdr.e_shoff = ((temp >> 24)&0xff) | ((temp >> 8)&0xff00) | ((temp << 24)&0xff000000) | ((temp << 8)&0xff0000);
	}
	if(INFO(flag))	{	printf("Section header offset: 0x%08X\n", elf_hdr.e_shoff);	        }
	if(LOG(flag))	{	fprintf(log, "Section header offset: 0x%08X\n", elf_hdr.e_shoff);	}

    // e_flags ---------------------------
    temp_word = elf_hdr.e_flags;
    elf_hdr.e_flags = (endian==big) ? ((temp_word>>24)&0xff) | ((temp_word>>8)&0xff00) | ((temp_word<<24)&0xff000000) | ((temp_word<<8)&0xff0000)
                      : temp_word;
                      
    // ehsize ---------------------------
    temp_half = elf_hdr.e_ehsize;
    elf_hdr.e_ehsize = (endian==big) ? ((temp_half&0x00ff)<<8) + ((temp_half&0xff00)>>8): temp_half;

    // ephentsize ---------------------------
    temp_half = elf_hdr.e_phentsize;
    elf_hdr.e_phentsize = (endian==big) ? ((temp_half&0x00ff)<<8) + ((temp_half&0xff00)>>8): temp_half;
   
	if(INFO(flag)) 	{	printf("Number of program entry size: %u\n", elf_hdr.e_phentsize);	        }
	if(LOG(flag))	{	fprintf(log, "Number of program entry size: %u\n", elf_hdr.e_phentsize);	}
    
    
    // e_phnum ---------------------------
    temp_half = elf_hdr.e_phnum;
    elf_hdr.e_phnum = (endian==big) ? ((temp_half&0x00ff)<<8) + ((temp_half&0xff00)>>8): temp_half;

	if(INFO(flag))  {	printf("Number of program: %u\n", elf_hdr.e_phnum);	        }
	if(LOG(flag))   {	fprintf(log, "Number of program: %u\n", elf_hdr.e_phnum);	}

    // eshentsize ---------------------------
    temp_half = elf_hdr.e_shentsize;
    elf_hdr.e_shentsize = (endian==big) ? ((temp_half&0x00ff)<<8) + ((temp_half&0xff00)>>8): temp_half;

    // e_shnum ---------------------------
    temp_half = elf_hdr.e_shnum;
    elf_hdr.e_shnum = (endian==big) ? ((temp_half&0x00ff)<<8) + ((temp_half&0xff00)>>8): temp_half;
    
    // e_shstrndx ---------------------------
    temp_half = elf_hdr.e_shstrndx;
    elf_hdr.e_shstrndx = (endian==big) ? ((temp_half&0x00ff)<<8) + ((temp_half&0xff00)>>8): temp_half;

    //-------------------------------------------------
	if(LOG(flag)) 	{	fclose(log);	}

	memcpy(p_elf_hdr, &elf_hdr, sizeof(Elf32_Ehdr));

	return 0;
}

void TForm_NT72682Updater::reOrderBlock(unsigned char fleIdx)
{
	unsigned int blkNum = blockCnt[fleIdx];
	unsigned int i, k, p, dataSecIdx=0;	//, startIdx=0;
	BurningHeader72310_short hdrBuf;
	/*FILE  *out_file, *in_file;
	out_file = fopen("content.bin", "ab");
	in_file = fopen("outBin.bin", "rb");

	if( (out_file == NULL) (in_file == NULL) )
		return; */

	for(k=0; k < vec_72310header.size(); k++)
	{
		if(vec_72310header[k].fileIndex == fleIdx)
		{
			//startIdx = k;
			break;
		}
	}	
	
	#if 1
 	for(i=0; i<blkNum; i++)
	{
		memset(&hdrBuf, 0, sizeof(BurningHeader72310) );
		if(vec_72310header[k+i].type == 0)		//text section
		{
			hdrBuf.CRC = vec_72310header[k+i].CRC;
			hdrBuf.startAddr = vec_72310header[k+i].startAddr;
			hdrBuf.endAddr = vec_72310header[k+i].endAddr;
			vec_72310header_short.push_back(hdrBuf);
			
			for(p=dataSecIdx; p<blkNum; p++)
			{
				if(vec_72310header[k+p].type == 1)		//data section
				{
					dataSecIdx = p+1;
					hdrBuf.CRC = vec_72310header[k+p].CRC;
					hdrBuf.startAddr = vec_72310header[k+p].startAddr;
					hdrBuf.endAddr = vec_72310header[k+p].endAddr;
					vec_72310header_short.push_back(hdrBuf);

					break;
				}
			}
		}
		
	}
	#else
	
	for(i=0; i<blkNum; i++)
	{
		if(vec_72310header[i+k].type == 0)	//text
		{
			/*hdrBuf.CRC = vec_72310header[i].CRC;
			hdrBuf.startAddr = vec_72310header[i].startAddr;
			hdrBuf.endAddr = vec_72310header[i].endAddr;
			hdrBuf.type = vec_72310header[i].type;
			vec_new.push_back(hdrBuf); */
			copy_vecHeader(vec_72310header_short, vec_72310header, i+k);
			
			for(p=0; p<blkNum; p++)
			{
				if(vec_72310header[p+k].type == 1)	//data
				{
					/*hdrBuf.CRC = vec_72310header[k].CRC;
					hdrBuf.startAddr = vec_72310header[k].startAddr;
					hdrBuf.endAddr = vec_72310header[k].endAddr;
					hdrBuf.type = vec_72310header[k].type;
					vec_new.push_back(hdrBuf); */
					copy_vecHeader(vec_72310header_short, vec_72310header, p+k);
					
					break;
				}
			}
			break;
			
		}
		
	}
	
	for(i=0; i<blkNum; i++)
	{
		if( (vec_72310header[i+k].type != 0) && (vec_72310header[i+k].type != 1) )	//textN or dataN
		{
			/*hdrBuf.CRC = vec_72310header[k].CRC;
			hdrBuf.startAddr = vec_72310header[k].startAddr;
			hdrBuf.endAddr = vec_72310header[k].endAddr;
			hdrBuf.type = vec_72310header[k].type;
			vec_new.push_back(hdrBuf); */
			//copy_vecHdr(i);
			copy_vecHeader(vec_72310header_short, vec_72310header, i+k);
		}
	}
	#endif
	
}

void TForm_NT72682Updater::reOrderBlock310(unsigned char fleIdx)
{
	unsigned int blkNum = blockCnt[fleIdx];
	unsigned int i, k, p, dataSecIdx=0;	//, startIdx=0;
	BurningHeader72310_short hdrBuf;
	/*FILE  *out_file, *in_file;
	out_file = fopen("content.bin", "ab");
	in_file = fopen("outBin.bin", "rb");

	if( (out_file == NULL) (in_file == NULL) )
		return; */

	for(k=0; k < vec_72310header.size(); k++)
	{
		if(vec_72310header[k].fileIndex == fleIdx)
		{	
			//startIdx = k;
			break;
		}
	}	
	
	for(i=0; i<blkNum; i++)
	{
		if(vec_72310header[i+k].type == 0)	//text
		{
			/*hdrBuf.CRC = vec_72310header[i].CRC;
			hdrBuf.startAddr = vec_72310header[i].startAddr;
			hdrBuf.endAddr = vec_72310header[i].endAddr;
			hdrBuf.type = vec_72310header[i].type;
			vec_new.push_back(hdrBuf); */
			copy_vecHeader(vec_72310header_short, vec_72310header, i+k);
			
			for(p=0; p<blkNum; p++)
			{
				if(vec_72310header[p+k].type == 1)	//data
				{
					/*hdrBuf.CRC = vec_72310header[k].CRC;
					hdrBuf.startAddr = vec_72310header[k].startAddr;
					hdrBuf.endAddr = vec_72310header[k].endAddr;
					hdrBuf.type = vec_72310header[k].type;
					vec_new.push_back(hdrBuf); */
					copy_vecHeader(vec_72310header_short, vec_72310header, p+k);
					
					break;
				}
			}
			break;
			
		}
		
	}
	
	for(i=0; i<blkNum; i++)
	{
		if( (vec_72310header[i+k].type != 0) && (vec_72310header[i+k].type != 1) )	//textN or dataN
		{
			/*hdrBuf.CRC = vec_72310header[k].CRC;
			hdrBuf.startAddr = vec_72310header[k].startAddr;
			hdrBuf.endAddr = vec_72310header[k].endAddr;
			hdrBuf.type = vec_72310header[k].type;
			vec_new.push_back(hdrBuf); */
			//copy_vecHdr(i);
			copy_vecHeader(vec_72310header_short, vec_72310header, i+k);
		}
	}
	
}

void TForm_NT72682Updater::parse_FRCfile(AnsiString inputFile, AnsiString outputFile)
{
	FILE *in_file, *out_file, *outTxt_file, *FRC_hdrFile;
	unsigned char data[256], newData[256], i;
	long fileSize, offset=0;
	char strBuf[32];
	unsigned int value, ans, FRC_hdrAddr;
	AnsiString valueStr;
	
	in_file = fopen(inputFile.c_str(), "rb");
	out_file = fopen(outputFile.c_str(), "wb");
	outTxt_file = fopen("FRC.txt", "wb");
	FRC_hdrFile = fopen("FRC_header.bin", "wb");
	
	if( (in_file == NULL) || (out_file == NULL) )
	{
		MessageBox(NULL, "Cannot open the input or output file!", "Oops", MB_OK);
		return;
	}
	fseek(in_file, 0, SEEK_END);
	fileSize = ftell(in_file);
	fseek(in_file, 0, SEEK_SET);
	
	while(offset < fileSize)
	{
		fread(data, sizeof(unsigned char), 1, in_file);
		if(data[0] == 0x3a)	// ASCII char: ':'
		{
			offset += 9;
			fseek(in_file, offset, SEEK_SET);
			fread(data, sizeof(unsigned char), 32, in_file);
			for(i=0; i<32; i++)
			{
				if(i%2 == 0)
					newData[i] = data[(i/8)*8+6 - i%8];
					//newData[i] = data[6 - i];
				else
					//newData[i] = data[8 - i];
					newData[i] = data[(i/8)*8+8 - i%8];

				//newData[i] -= 0x30;	//change to ASCII char
			}
			
			newData[32] = '\0';
			fprintf(outTxt_file, "%s\n", newData); 
			//fwrite(newData, sizeof(unsigned char), 32, out_file);
			
		}
		offset = ftell(in_file);
		
	}
	
	fclose(in_file);
	fclose(outTxt_file);

	//outTxt_file = fopen("FRC-short.txt", "rb");
	outTxt_file = fopen("FRC.txt", "rb");
	fseek(outTxt_file, 0, SEEK_END);
	fileSize = ftell(in_file);
	fseek(outTxt_file, 0, SEEK_SET);
	offset = 0;

	FRC_hdrAddr = StrToInt("0x" + LabeledEdit_310_startAddr->Text);								
	FRCtable.CRC = 0;
	FRCtable.startAddr = FRC_hdrAddr + 64;
	FRCtable.endAddr = FRCtable.startAddr;
	
	do
	{
		fgets(strBuf, 9, outTxt_file);

		if( (strBuf[0] != '\0') && (strBuf[0] != '\n') )
		{
			valueStr = AnsiString(strBuf);
			value = StrToInt("0x" + valueStr);
			//Memo_72310_dbg->Lines->Add(IntToHex( (int)value, 8) );

			FRCtable.CRC += Cal_ChkSum(value, 0);
			FRCtable.endAddr += sizeof(value);
			ChangeEndian(&value, sizeof(value), data);
			fwrite(data, sizeof(value), 1, out_file);
		}
		offset = ftell(outTxt_file);
	
	}while(offset < fileSize);

	valueStr.sprintf("chksum: %08x, endAddr: %08x\n", FRCtable.CRC, FRCtable.endAddr);
	Memo_72310_dbg->Lines->Add(valueStr);
	
	fclose(outTxt_file);
	fclose(out_file);

	//2 create FRC header file
	ChangeEndian(& FRCtable.startAddr, sizeof(FRCtable.startAddr), data);
	fwrite(data, sizeof(FRCtable.startAddr), 1, FRC_hdrFile);
	
	ChangeEndian(& FRCtable.endAddr, sizeof(FRCtable.endAddr), data);
	fwrite(data, sizeof(FRCtable.endAddr), 1, FRC_hdrFile);
	
	ChangeEndian(& FRCtable.CRC, sizeof(FRCtable.CRC), data);
	fwrite(data, sizeof(FRCtable.CRC), 1, FRC_hdrFile);
	fclose(FRC_hdrFile);
	
	//2 burn FRC header & contents to DRAM
	//I2C72310_burnCode(FRC_hdrAddr, "FRC_header.bin");
	//I2C72310_burnCode(FRCtable.startAddr, outputFile);
	
}
void __fastcall TForm_NT72682Updater::Button_310_subProgramClick(TObject *Sender)
{
	TButton *btn = (TButton *)Sender;
	AnsiString fileName, fileSize;
	int flag;

	OpenDialog->Filter = "";
	int count = sizeof(btn310)/sizeof(TButton *);
	
	for(int i=0; i<count; i++)
	{
		if(btn->Name == btn310[i]->Name)
		{
			if(OpenDialog->Execute() )
			{
				fileName = OpenDialog->FileName;
				lblEdit_310_file[i]->Text = fileName;
				
				//if(i == count-1)
					//parse_FRCfile(fileName, "FRC.bin");
			}
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm_NT72682Updater::Button_310_dmpClick(TObject *Sender)
{
	AnsiString inFileName, outFileName, outStr;
	FILE* in_file, *out_file, *hdrFileOut, *content_file, *result_file, *resultHdr_file;
	char outBuf[65536];
	int i, k, flag = 1, tmp;
	unsigned int startAddr, OPCode, DSRAM_size, PSRAM_size/*, totalOffset=0*/;
	g_u32totalOffset = 0;

	out_file = fopen("outBin.bin", "wb");		//disordered file which contains text & data.
	//hdrFileOut = fopen("header.bin", "wb");
	content_file = fopen("content.bin", "wb");	//ordered file which contains text & data.
	result_file = fopen("result.bin", "wb");	//single result file, the combinition of all other output files.
	fclose(out_file);		//clear contents of output file
	//fclose(hdrFileOut);
	fclose(content_file);
	fclose(result_file);
	
	Memo_310_dbg->Clear();
	vec_72310header.clear();
	vec_72310header_short.clear();
	vec_72310TotalHeader.clear();

	totalHdr_CRC = 0;
	totalHdr_Size = 0;

	splitOffset = StrToInt("0x" + LabeledEdit_310_splitOffset->Text);
	unsigned char subAddress = 0xfe;
	unsigned char data[16];
	
	OPCode = StrToInt("0x" + LabeledEdit_310_unlock->Text);
	data[1] = OPCode>>8 & 0xff;
	data[0] = OPCode & 0xff;
	
	/*if(I2C_Channel.I2CWrite(m_cNT72310Slave, &subAddress, data, 2) == false)
	{
		MessageBox(NULL, "unlock cfg page failed pp", "Oops", MB_OK);
	} */
	
	for(k=0; k<4; k++)
	//for(k=0; k<2; k++)			//torres100906: test
	{
		inFileName = lblEdit_310_file[k]->Text;
		//outFileName = LabeledEdit_72310_boot->Text;		//just test
		in_file = fopen(inFileName.c_str(), "rb");

		if(in_file == NULL) 
		{	
			//printf("Input file doesn't exist!\n");	
			MessageBox(NULL, "Cannot open the input file!", "Oops", MB_OK);
			outStr.sprintf("error num: %d\n", errno);
			Memo_310_dbg->Lines->Add(outStr);
			//fclose(hdrFileOut);
			return;
		}

		fread(&elf_hdr, sizeof(Elf32_Ehdr), 1, in_file);
		if(elf_header_check(&elf_hdr, flag) != 0)	
		{		
			//printf("Elf header check Error !!!\n");
			MessageBox(NULL, "ELF header check error!", "Oops", MB_OK);
			fclose(in_file);
			//fclose(hdrFileOut);
			return;
		}

		if( (k == 0) || (k == 1) )
		//if( (k == 0) )	
		{
			//tmp = StrToInt("0x" + lblEdit_72310_fileOffset[k]->Text);
			//currentOffset = (unsigned int) (ceil( (double)tmp/4 )*4);	//address align 4.
			currentOffset = 0;
		}
		if(k >= 2)
			g_bAlign4 = true;
		
		lblEdit_310_fileOffset[k]->Text = IntToHex( (int)currentOffset, 4);
		
		for(i=0; i< elf_hdr.e_phnum; i++)		//Fetch information of program header [phnum] 
		{
			fseek(in_file, elf_hdr.e_phoff+(i*elf_hdr.e_phentsize), SEEK_SET);
			fread(&ph_array[i], sizeof(Elf32_Phdr), 1, in_file);
	        	program_header_check(ph_array[i], flag);
		}
		for(i=0; i< elf_hdr.e_shnum; i++)		// Fetch information of section header [phnum] 
		{
			fseek(in_file, elf_hdr.e_shoff+(i*elf_hdr.e_shentsize), SEEK_SET);
			fread(&sh_array[i], sizeof(Elf32_Shdr), 1, in_file);
			section_header_check(sh_array[i], flag);

			if(i == elf_hdr.e_shstrndx)
				sh_strTable = & sh_array[i];		//point to string table
		}
		fileIdx = k;
		blockCnt[fileIdx] = 0;		//used to count data & text sections.
		readStrTable(&elf_hdr, sh_array, sh_strTable, in_file, outBuf);
		fclose(in_file);
		
		//2 write sub-program to SRAM, wait here until it's finish.
		if(k == 0)
		{
			//#if(writeSubProgram)
			//if(Write_SubProgram(0x9f040040) )
			//#endif	
			{
				GLOBAL_CopyFile("./subProgram.bin", "./outBin.bin");

				//2 caluate total header: subProgram
				/*totalHdr.startAddr = totalOffset;
				totalOffset += GLOBAL_GetFileSize("./subProgram.bin");
				totalHdr.endAddr = totalOffset-1;
				//totalHdr.CRC = vec_72310header[0].CRC;
				totalHdr.CRC = Cal_ChkSum_File("./subProgram.bin");
				vec_72310TotalHeader.push_back(totalHdr); */
				Cal_totalHeader("./subProgram.bin");
					
				vec_72310header.clear();
				out_file = fopen("outBin.bin", "wb");
				fclose(out_file);		//clear sub-program's data

				//MessageBox(NULL, "Now we're going to write code to DDR", "Hello", MB_OK);		//just test
				//Sleep(2000);
			}
			/*#if(writeSubProgram)
			else
			{
				MessageBox(NULL, "Write sub-program to SRAM failed!", "Oops", MB_OK);
				//fclose(hdrFileOut);
				return;
			} 
			#endif	*/
		}  
		currentOffset += splitOffset;	
		Application->ProcessMessages();
		//ProgressBar_Complete->Position += 25;
		
	}

	/*FILE *hdrFileOut;
	hdrFileOut = fopen("header.bin", "wb"); */
	for(i=0; i < vec_72310header.size(); i++)
	{
		outStr.sprintf("%d vector %d- %08x\n", i, vec_72310header[i].fileIndex, vec_72310header[i].startAddr);
		Memo_310_dbg->Lines->Add(outStr);
	}

	BurningHeader72310_short hdrTmp;
	
	//2 combine .text & .data section for flash-boot file and flash-writer file.
	hdrTmp.startAddr = vec_72310header[0].startAddr;
	hdrTmp.endAddr = vec_72310header[1].endAddr;
	hdrTmp.CRC = vec_72310header[0].CRC + vec_72310header[1].CRC;
	vec_72310header_short.push_back(hdrTmp);

	hdrTmp.startAddr = vec_72310header[2].startAddr;
	hdrTmp.endAddr = vec_72310header[3].endAddr;
	hdrTmp.CRC = vec_72310header[2].CRC + vec_72310header[3].CRC;
	vec_72310header_short.push_back(hdrTmp);
	
	//reOrderBlock310(2);		//only Program/data file needs to be reordered.
	copy_vecHeader(vec_72310header_short, vec_72310header, 4);	//tmp solution
	copy_vecHeader(vec_72310header_short, vec_72310header, 5);	//tmp solution	//torres110408 tmpM

	/*check length of .TEXT & .DATA section*/
	DSRAM_size = LabeledEdit_310_dSize->Text.ToInt();
	PSRAM_size = LabeledEdit_310_pSize->Text.ToInt();
	#if 0	//(writeSubProgram)		//torres110406
	if(vec_72310header_short.size() >= 3)		//torresM 101109 tmp for test
	{
		if(vec_72310header_short[2].endAddr - vec_72310header_short[2].startAddr + 1 > PSRAM_size)
		{
			MessageBox(NULL, "The .TEXT section is bigger than Program SRAM size!", "Oops", MB_OK);
			return;
		}
	}
	if(vec_72310header_short.size() >= 4)
	{
		if(vec_72310header_short[3].endAddr - vec_72310header_short[2].startAddr + 1 > DSRAM_size)
		{
			MessageBox(NULL, "The .DATA section is bigger than Data SRAM size!", "Oops", MB_OK);
			return;
		}
	}
	#endif
	
	in_file = fopen("outBin.bin", "rb");
	out_file = fopen("content.bin", "wb");
	if( (in_file == NULL) || (out_file == NULL) )
	{	
		//printf("Input file doesn't exist!\n");	
		MessageBox(NULL, "Cannot open the related files!", "Oops", MB_OK);
		return;
	}
	
	headerTable.CRC = 0;
	OPCode = 0x0000;		//tmp for test
	headerTable.CRC += Cal_ChkSum(OPCode, 0);
	g_u32hdrAddr = StrToInt("0x" + LabeledEdit_310_startAddr->Text);
	headerTable.startAddr = g_u32hdrAddr;
	headerTable.endAddr = headerTable.startAddr + 16 
						+ vec_72310header_short.size()*sizeof(BurningHeader72310_short) - 1;
	//g_u32startAddr = (unsigned int) (ceil( (double)(headerTable.endAddr+1)/4 )*4);	//address align 4.
	g_u32startAddr = headerTable.endAddr+1;
	headerTable.CRC += Cal_ChkSum(headerTable.startAddr, headerTable.endAddr);

	outStr.sprintf("header addr: %08x, content addr: %08x\n", g_u32hdrAddr, g_u32startAddr);
	Memo_310_dbg->Lines->Add(outStr);
	
	//2 output content file
	//Note: when the section size is 0, then endAddr < startAddr
	
	Memo_310_dbg->Lines->Add(" ");
	unsigned int size, offset=0, newOffset, lengthLeft;

	//g_bAlign4 = false;		//torres110408 test
	int statusS, statusR, error;	//test
	long pos;
    AnsiString tmpStr;
	
	Memo_310_tmp->Clear();
	for(i=0; i < vec_72310header_short.size(); i++)
	{
		size = vec_72310header_short[i].endAddr - vec_72310header_short[i].startAddr + 1;
		statusS = fseek(in_file, vec_72310header_short[i].startAddr, SEEK_SET);	//torresM
		//Memo_310_tmp->Lines->Add( "now pos = " + IntToHex((int)ftell(in_file), 0) );

		lengthLeft = size;
		while(lengthLeft)
		{
			statusR = (65536 < lengthLeft) ? 65536:lengthLeft;
			statusR = fread(outBuf, 1, statusR, in_file);

			if( (error = ferror(in_file) ) )
			{
				tmpStr.sprintf(" %d file with error: %d", i, error);
				Memo_310_tmp->Lines->Add(tmpStr);
			}
			if(statusR)
			{
				if(size == lengthLeft)
					fseek(out_file, offset, SEEK_SET);
				
				fwrite(outBuf, 1, statusR, out_file);
			
				lengthLeft -= statusR;
			}
		}
		
		vec_72310header_short[i].startAddr = offset;
		vec_72310header_short[i].endAddr = offset + size - 1;

		outStr.sprintf("%d S_vec - %08x, CRC %08x\n", i, vec_72310header_short[i].startAddr, 
						vec_72310header_short[i].CRC);
		Memo_310_dbg->Lines->Add(outStr);
		
		if(g_bAlign4)
		{	offset = (unsigned int) (ceil( (double)(vec_72310header_short[i].endAddr+1)/4 )*4);
			offset += splitOffset;
		}
		else
			//offset = vec_72310header_short[i].endAddr+1;
			offset = vec_72310header_short[i].endAddr+1 + splitOffset;		//torres101006 test

		headerTable.CRC += Cal_ChkSum(vec_72310header_short[i].CRC, 0);
		headerTable.CRC += Cal_ChkSum(vec_72310header_short[i].startAddr + g_u32startAddr, 
										vec_72310header_short[i].endAddr + g_u32startAddr);
	}
	fclose(in_file);
	fclose(out_file);
	
	//write contents file to assigned area
	Memo_310_dbg->Lines->Add("Now writing contents...");
	//I2C72310_burnCode(g_u32startAddr, "content.bin");

	//2 output header table file.
	
	unsigned char hdrBuf[256];
	hdrFileOut = fopen("header.bin", "wb");
	
	ChangeEndian(&OPCode, sizeof(OPCode), hdrBuf);
	//fwrite(&OPCode, sizeof(OPCode), 1, hdrFileOut);
	fwrite(hdrBuf, sizeof(OPCode), 1, hdrFileOut);

	ChangeEndian(&headerTable, sizeof(headerTable), hdrBuf);
	//fwrite(&headerTable, sizeof(headerTable), 1, hdrFileOut);
	fwrite(hdrBuf, sizeof(headerTable), 1, hdrFileOut);
	
	for(i=0; i < vec_72310header_short.size(); i++)
	{
		unsigned int buf;
		
		buf = vec_72310header_short[i].startAddr + g_u32startAddr;
		ChangeEndian(&buf, sizeof(buf), hdrBuf);
		fwrite(hdrBuf, sizeof(unsigned int), 1, hdrFileOut);
		//fwrite(&buf, sizeof(unsigned int), 1, hdrFileOut);

		buf = vec_72310header_short[i].endAddr + g_u32startAddr;
		//fwrite(&buf, sizeof(unsigned int), 1, hdrFileOut);
		ChangeEndian(&buf, sizeof(buf), hdrBuf);
		fwrite(hdrBuf, sizeof(unsigned int), 1, hdrFileOut);

		buf = vec_72310header_short[i].CRC;
		//fwrite(&buf, sizeof(unsigned int), 1, hdrFileOut);
		ChangeEndian(&buf, sizeof(buf), hdrBuf);
		fwrite(hdrBuf, sizeof(unsigned int), 1, hdrFileOut);
	} 
	fclose(hdrFileOut);

	Memo_310_dbg->Lines->Add("Now writing header...");
	//I2C72310_burnCode(headerTable.startAddr, "header.bin");

	//2 caluate total header: content header
	/*totalHdr.startAddr = totalOffset;
	totalOffset += GLOBAL_GetFileSize("./header.bin");
	totalHdr.endAddr = totalOffset-1;
	//totalHdr.CRC = headerTable.CRC + Cal_ChkSumF(&headerTable.CRC, sizeof(headerTable.CRC) );
	totalHdr.CRC = Cal_ChkSum_File("./header.bin");
	vec_72310TotalHeader.push_back(totalHdr); */
	Cal_totalHeader("./header.bin");

	//2 caluate total header: content 
	/*totalHdr.startAddr = totalOffset;
	totalOffset += GLOBAL_GetFileSize("./content.bin");
	totalHdr.endAddr = totalOffset-1;
	//totalHdr.CRC = headerTable.CRC + Cal_ChkSumF(&headerTable.CRC, sizeof(headerTable.CRC) );
	totalHdr.CRC = Cal_ChkSum_File("./content.bin");
	vec_72310TotalHeader.push_back(totalHdr); */
	Cal_totalHeader("./content.bin");
	//Cal_totalHeader("./outBin.bin");

	//2 parsing the FRC file
	Memo_72310_dbg->Lines->Add("Now parsing FRC header & contents...");
	parse_FRCfile(LabeledEdit_310_FRC->Text, "FRC.bin");

	//2 caluate total header: FRC header
	Cal_totalHeader("./FRC_header.bin");
	
	//2 caluate total header: FRC 
	Cal_totalHeader("./FRC.bin");

	//2 output the final result header
	unsigned char ttlHdrBuf[256];
	resultHdr_file = fopen("result_header.bin", "wb");
	
	totalHdr_Size += 2*sizeof(unsigned int);	//include 2 fields: header size & header CRC
	ChangeEndian(&totalHdr_Size, sizeof(totalHdr_Size), ttlHdrBuf);
	fwrite(ttlHdrBuf, sizeof(totalHdr_Size), 1, resultHdr_file);

	totalHdr_CRC += Cal_ChkSum(totalHdr_Size, 0);
	ChangeEndian(&totalHdr_CRC, sizeof(totalHdr_CRC), ttlHdrBuf);
	fwrite(ttlHdrBuf, sizeof(totalHdr_CRC), 1, resultHdr_file);
	
	for(i=0; i < vec_72310TotalHeader.size(); i++)
	{
		unsigned int buf;
		
		buf = vec_72310header_short[i].startAddr + g_u32startAddr;
		
		Memo_310_dbg->Lines->Add("\nTotal header " + IntToStr(i) );
		Memo_310_dbg->Lines->Add("start: 0x" + IntToHex( (int)vec_72310TotalHeader[i].startAddr, 8) );
		Memo_310_dbg->Lines->Add("end: 0x" + IntToHex( (int)vec_72310TotalHeader[i].endAddr, 8) );
		Memo_310_dbg->Lines->Add("CRC: 0x" + IntToHex( (int)vec_72310TotalHeader[i].CRC, 8) );

		buf = vec_72310TotalHeader[i].startAddr;
		ChangeEndian(&buf, sizeof(buf), ttlHdrBuf);
		fwrite(ttlHdrBuf, sizeof(unsigned int), 1, resultHdr_file);

		buf = vec_72310TotalHeader[i].endAddr;
		ChangeEndian(&buf, sizeof(buf), ttlHdrBuf);
		fwrite(ttlHdrBuf, sizeof(unsigned int), 1, resultHdr_file);

		buf = vec_72310TotalHeader[i].CRC;
		ChangeEndian(&buf, sizeof(buf), ttlHdrBuf);
		fwrite(ttlHdrBuf, sizeof(unsigned int), 1, resultHdr_file);
		
	}
	fclose(resultHdr_file);

	//2 output the final bin file (result header + result bin file)
	if(GLOBAL_CopyFile("result_header.bin", "result.bin", true) )
	{
		unlink("result_final.bin");		//delete the exisitent file
		rename("./result_header.bin", "result_final.bin");
	}
	
}
//---------------------------------------------------------------------------

void TForm_NT72682Updater::copy_vecHeader(vector<BurningHeader72310_short> &dest, 
												vector<BurningHeader72310> &src, int index)
{
	BurningHeader72310_short hdrBuf1;
	
	hdrBuf1.CRC = src[index].CRC;
	hdrBuf1.startAddr = src[index].startAddr;
	hdrBuf1.endAddr = src[index].endAddr;
	dest.push_back(hdrBuf1);
}

void __fastcall TForm_NT72682Updater::Button_310_cpyClick(TObject *Sender)
{
	GLOBAL_CopyFile("./cpy.bin", lblEdit_310_file[0]->Text);
	GLOBAL_CopyFile("./cpy.bin", lblEdit_310_file[1]->Text);

	int ans = Cal_ChkSum_File(lblEdit_310_file[3]->Text);
	Memo_310_dbg->Lines->Add("checksum of the file = 0x" + IntToHex(ans, 0) );

	#if 1
	/*GetVersionEx   takes   a   pointer   to   an   OSVERSIONINFO   struct   as
		its   only   argument.   It   will   fill   in   the   struct   with   version
		info.   The   struct   has   a   size   member   that   must   be   initialized
		to   the   size   of   the   structure. */
	OSVERSIONINFO   info;
	info.dwOSVersionInfoSize   =   sizeof(OSVERSIONINFO);
	GetVersionEx(&info);

	//add version info to a TMemo control
	Memo_310_dbg->Lines->Clear();
	Memo_310_dbg->Lines->Add( "Major Version: " + IntToStr(info.dwMajorVersion) );
	Memo_310_dbg->Lines->Add( "Minor Version: " + IntToStr(info.dwMinorVersion) );
	Memo_310_dbg->Lines->Add( "Build Number: " + IntToStr(info.dwBuildNumber) );
	Memo_310_dbg->Lines->Add( "Platform ID: " + IntToStr(info.dwPlatformId) );
	Memo_310_dbg->Lines->Add( "CSDVersion: " + AnsiString(info.szCSDVersion) );
	Memo_310_dbg->Lines->Add( " ");

	/*   if   the   major   version   is   less   than   4,   then   you   know   that   the   OS
		is   windows   NT   3.X,   since   BCB   can 't   create   16   bit   programs */
	if(info.dwMajorVersion   <   4)
		Memo_310_dbg->Lines->Add( "Windows NT 3.X detected");

	switch(info.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s:
			Memo_310_dbg->Lines->Add( "Win32s detected");
			break;
		case VER_PLATFORM_WIN32_WINDOWS:
			Memo_310_dbg->Lines->Add( "Win95 or Win 98 detected ");
			break;
		case VER_PLATFORM_WIN32_NT:
			Memo_310_dbg->Lines->Add( "Windows NT detected ");
			break;
	}
	#endif

	/*unsigned char Slave = 0x34;
	if(USBPort.IIC_SendStart(0) != STA_JIG_OK)
	{
		USBPort.IIC_SendStop(0);
		Memo_310_dbg->Lines->Add("send start failed!");
		//return false;
	}
		
	if(USBPort.IIC_Tx(0, &Slave, 1) != STA_JIG_OK)
	{
		USBPort.IIC_SendStop(0);
		Memo_310_dbg->Lines->Add("tx failed!");
		//return false;
	} */
		
}
//---------------------------------------------------------------------------

void __fastcall TForm_NT72682Updater::Cal_totalHeader(const AnsiString &inputFile)
{
	//static unsigned int totalOffset = 0;
	
	//2 caluate total header: content 
	totalHdr.startAddr = g_u32totalOffset;
	g_u32totalOffset += GLOBAL_GetFileSize(inputFile);
	totalHdr.endAddr = g_u32totalOffset-1;
	//totalHdr.CRC = headerTable.CRC + Cal_ChkSumF(&headerTable.CRC, sizeof(headerTable.CRC) );
	totalHdr.CRC = Cal_ChkSum_File(inputFile);
	vec_72310TotalHeader.push_back(totalHdr);

	totalHdr_CRC += Cal_ChkSum(totalHdr.startAddr, totalHdr.endAddr);
	totalHdr_CRC += Cal_ChkSum(totalHdr.CRC, 0);

	totalHdr_Size += sizeof(totalHdr);

	GLOBAL_CopyFile("./result.bin", inputFile, true);
}

long __fastcall TForm_NT72682Updater::GLOBAL_GetFileSize(const AnsiString &file_path)
{
    FILE* fp = fopen(file_path.c_str() , "rb");

    if(fp == NULL)
    {
        fclose(fp);
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    const long file_size = ftell(fp);
    fclose(fp);

    return file_size;
}

bool __fastcall TForm_NT72682Updater::GLOBAL_CopyFile(AnsiString &dest_filePath, AnsiString &src_filePath, bool appendMode)
{
	FILE* fp_src = fopen(src_filePath.c_str(), "rb");
	FILE* fp_dest; 

	if(!appendMode)
		fp_dest = fopen(dest_filePath.c_str(), "wb");
	else
		fp_dest = fopen(dest_filePath.c_str(), "ab");
	
	long fileSize, numRd, numWt;
	char *buff;

	if( (fp_src == NULL) || (fp_dest == NULL) )
	{
		//fclose(fp);
		return false;
	}

	fseek(fp_src, 0, SEEK_END);
	fileSize = ftell(fp_src);
	fseek(fp_src, 0, SEEK_SET);
	buff = (char *)malloc(65536);
	if(buff == NULL)
		return false;

	while(fileSize)
	{
		numRd = (65536 < fileSize) ? 65536:fileSize;
		numRd = fread(buff, 1, numRd, fp_src);

		if(numRd)
		{
			numWt = fwrite(buff, 1, numRd, fp_dest);
		}

		fileSize -= numRd;
	};

	fclose(fp_src);
	fclose(fp_dest);
	free(buff);
	
	return true;
}

int TForm_NT72682Updater::program_header_check(Elf32_Phdr& p_elf_hdr, int flag)
{
//	Elf32_Phdr elf_hdr = *p_elf_hdr;
	unsigned long temp_word;

    temp_word = p_elf_hdr.p_type;
    p_elf_hdr.p_type = (endian == big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
						| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;
                      
	temp_word = p_elf_hdr.p_offset;
    p_elf_hdr.p_offset = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00)
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;
                      
	temp_word = p_elf_hdr.p_vaddr;
    p_elf_hdr.p_vaddr = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;
                      
	temp_word = p_elf_hdr.p_paddr;
    p_elf_hdr.p_paddr = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;
                      
	temp_word = p_elf_hdr.p_filesz;
    p_elf_hdr.p_filesz = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;
                      
	temp_word = p_elf_hdr.p_memsz;
    p_elf_hdr.p_memsz = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
						| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;
                      
	temp_word = p_elf_hdr.p_flags;
    p_elf_hdr.p_flags = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	temp_word = p_elf_hdr.p_align;
    p_elf_hdr.p_align = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00)
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;    

	return 0;
}

int TForm_NT72682Updater::section_header_check(Elf32_Shdr& sec_hdr, int flag)
{
	unsigned long temp_word;

	temp_word = sec_hdr.sh_name;
    sec_hdr.sh_name = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;
                      
	temp_word = sec_hdr.sh_type;
    sec_hdr.sh_type = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;
                    
	temp_word = sec_hdr.sh_flags;
    sec_hdr.sh_flags = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	temp_word = sec_hdr.sh_addr;
    sec_hdr.sh_addr = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	temp_word = sec_hdr.sh_offset;
    sec_hdr.sh_offset = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	temp_word = sec_hdr.sh_size;
    sec_hdr.sh_size = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	temp_word = sec_hdr.sh_link;
    sec_hdr.sh_link = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	temp_word = sec_hdr.sh_info;
    sec_hdr.sh_info = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	temp_word = sec_hdr.sh_addralign;
    sec_hdr.sh_addralign = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	temp_word = sec_hdr.sh_entsize;
    sec_hdr.sh_entsize = (endian==big) ? ( (temp_word>>24)&0xff) | ( (temp_word>>8)&0xff00) 
					| ( (temp_word<<24)&0xff000000) | ( (temp_word<<8)&0xff0000) : temp_word;

	return 0;
}
int TForm_NT72682Updater::readStrTable(Elf32_Ehdr* elf_hdr, Elf32_Shdr *sh_hdr, 
											Elf32_Shdr *sh_strTable, FILE* in_file, char* outBuf)
{
	char *buf, buf2[65536*2], Zbuf[32768] = {0};
	BurningHeader72310 headerBuf;
	FILE *out_file, *hdrFileOut;
	long curPos;
	int num_rd;
	
	out_file = fopen("outBin.bin", "ab");		//tmp solution
	//hdrFileOut = fopen("header.bin", "ab");
	
	fseek(in_file, sh_strTable->sh_offset, SEEK_SET);
	fread(outBuf, sh_strTable->sh_size, 1, in_file);

	for (int i=1; i <elf_hdr->e_shnum; i++)		//index0: undefined
	{
		buf = &outBuf[ sh_hdr[i].sh_name];
		memset(&headerBuf, 0, sizeof(BurningHeader72310) );
		if( (strncmp(buf, ".text", 5) == 0) || (strncmp(buf, ".data", 5) == 0) )
		{
			//Memo_72310_dbg->Text = IntToStr(strlen(buf) );		//torres101108 test
			fseek(out_file, 0, SEEK_END);	
			curPos = ftell(out_file);
			
			headerBuf.startAddr = currentOffset;
			headerBuf.endAddr = headerBuf.startAddr + sh_hdr[i].sh_size - 1;		//Note: when size=0, endAddr will less than startAddr
			headerBuf.index = i;
			//headerBuf.CRC = Cal_ChkSum(headerBuf.startAddr, g_u32startAddr+headerBuf.endAddr);
			headerBuf.fileIndex = fileIdx;
			if(strncmp(buf, ".text", 5) == 0)
			{
				//headerBuf.type = 0;
				if(strlen(buf) == 5)	
					headerBuf.type = 0;		//.text
				else
					headerBuf.type = 2;		//.textN
				
			}
			else
			{
				//headerBuf.type = 1;
				if(strlen(buf) == 5)
					headerBuf.type = 1;		//data
				else
					headerBuf.type = 3;		//dataN
			}

			blockCnt[fileIdx]++;
			
			//currentOffset = (unsigned int) (ceil( (double)headerBuf.endAddr/4 )*4);	//address align 4.
			if(g_bAlign4)
				currentOffset = (unsigned int) (ceil( (double)(headerBuf.endAddr+1)/4 )*4);	//torres100906
			else
				currentOffset = headerBuf.endAddr + 1;
			
			//vec_72310header.push_back(headerBuf);
			//printf("%d - %s\n", i, buf);
			#if 0
			memset(buf2, 0, 65536*2);		
			fseek(in_file, sh_hdr[i].sh_offset, SEEK_SET);
			fread(buf2, sh_hdr[i].sh_size, 1, in_file);
			headerBuf.CRC = Cal_ChkSumF(buf2, sh_hdr[i].sh_size);
			vec_72310header.push_back(headerBuf);

			fwrite(Zbuf, headerBuf.startAddr-curPos, 1, out_file);	//fill 0 to empty area
			//fseek(out_file, headerBuf.startAddr, SEEK_END);
			fwrite(buf2, sh_hdr[i].sh_size, 1, out_file);
			#else
			memset(buf2, 0, 65536);
			fseek(in_file, sh_hdr[i].sh_offset, SEEK_SET);
			headerBuf.CRC = 0;
			unsigned int fileLength = sh_hdr[i].sh_size;
			while(fileLength)
			{
				num_rd = (65536 < fileLength) ? 65536 : fileLength;
				memset(buf2, 0, num_rd);
				//fread(buf2, sh_hdr[i].sh_size, 1, in_file);
				num_rd = fread(buf2, 1, num_rd, in_file);
				if(num_rd)
				{
					headerBuf.CRC += Cal_ChkSumF(buf2, num_rd);					
					//fseek(out_file, headerBuf.startAddr, SEEK_END);
					fwrite(buf2, 1, num_rd, out_file);
					//parser(sh_hdr[i], in_file, i, "tmpTest", 0);

					fileLength -= num_rd;
				}
			}
			vec_72310header.push_back(headerBuf);
			fwrite(Zbuf, headerBuf.startAddr-curPos, 1, out_file);	//fill 0 to empty area
			#endif
			
		}
		
	}
	//fwrite(&vec_72310header, sizeof(BurningHeader72310), vec_72310header.size(), hdrFileOut);
	
	fclose(out_file);
	//fclose(hdrFileOut);
	return 0;
}

unsigned int Cal_ChkSum(unsigned int u32Value1, unsigned int u32Value2)
{
	unsigned int ans=0;

	while(u32Value1)
	{
		ans += (u32Value1&0xFF);
		u32Value1 >>= 8;
	}
	while(u32Value2)
	{
		ans += (u32Value2&0xFF);
		u32Value2 >>= 8;
	}
	
	return ans;
}

void ChangeEndian(void *input, unsigned int length, unsigned char *ans)
{
	/*unsigned int ans=0;
	unsigned char buf;
	
	for(int i=0; i<4; i++)
	{
		buf = u32input>>(8*i) & 0xff;
		ans |= buf<<(8*(3-i) );
	} 
	return ans; */
	unsigned char *buf = (unsigned char*)input;
	for(unsigned int i=0; i<length; i++)		//change Endian
	{
		ans[i] = buf[3+(i/4)*4 - i%4];
	} 
}

unsigned int Cal_ChkSumF(void *input, unsigned int ByteLength)
{
	unsigned char *buf = (unsigned char *)input;
	unsigned int ans=0;

	for(int i=0; i<ByteLength; i++)
		ans += buf[i];

	return ans;
}

int Cal_ChkSum_File(AnsiString &fileName)
{
	char buf[65536]={0};
	FILE *in_file;
	long num_rd, fileSize;
	int ans=0;

	in_file = fopen(fileName.c_str(), "rb");
	if(in_file == NULL)
		return -1;

	fseek(in_file, 0, SEEK_END);
	fileSize = ftell(in_file);
	fseek(in_file, 0, SEEK_SET);
	
	while(fileSize)
	{
		num_rd = (65536 < fileSize) ? 65536:fileSize;
		num_rd = fread(buf, 1, num_rd, in_file);

		if(num_rd)
			ans += Cal_ChkSumF(buf, num_rd);

		fileSize -= num_rd;
	}

	fclose(in_file);
	return ans;

}

void __fastcall TForm_NT72682Updater::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    //PreClose(this->Name);
    Action = caFree;
}
//---------------------------------------------------------------------------


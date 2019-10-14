/*
	This tool is used to generate audio control parameters' config file,  that is stored on spi.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/audio_param.h"

int main(int argc, char **argv){

	FILE *out = NULL;
	int i = 0;
	char *amp = &amplifier[0][0];
	char *finevolume = &fine_volume[0][0];
	char *drc1_tko = NULL;
	char *drc1_table = NULL;
	char *table_mode = NULL;
	char *wall_mode = NULL;

	if(user_param.DRC_mode == SPEAKER_12V6ohm8w){
		drc1_tko = &drc1_tko_table_12V6ohm8w[0][0];
		drc1_table = &drc1_table_12V6ohm8w[0][0];
	}else{
		drc1_tko = &drc1_tko_table_12v6ohm6w[0][0];
		drc1_table = &drc1_table_12v6ohm6w[0][0];
	}
	
	if(user_param.Screen_size == SCREEN_40_42_inch){
		table_mode = &table_mode_40_42[0][0][0];
		wall_mode = &wall_mode_40_42[0][0][0];
	}else if(user_param.Screen_size == SCREEN_32_inch){
		table_mode = &table_mode_32[0][0][0];
		wall_mode = &wall_mode_32[0][0][0];
	}else if(user_param.Screen_size == SCREEN_48_inch){
		table_mode = &table_mode_48[0][0][0];
		wall_mode = &wall_mode_48[0][0][0];
	}else{
		table_mode = &table_mode_55[0][0][0];
		wall_mode = &wall_mode_55[0][0][0];
	}

	out = fopen("rom_audioparam", "wb" );
	if (out == NULL) {
		printf("failed to open output file\n");
		fclose(out);
		return 0;
	}

	fprintf(out,"%s","AMP=");
	for(i = 0; i < 4*101; i++){
		fprintf(out,"%c",*(amp+i));
	}

	fprintf(out,"%s","Fvl=");
	for(i = 0; i < 4*101; i++){
		fprintf(out,"%c",*(finevolume+i));
	}

	fprintf(out,"%s%c","Een=",user_param.EQ_enable);
	fprintf(out,"%s%c","Den=",user_param.DRC_enable);
	
	fprintf(out,"%s","TKO=");
	for(i = 0; i < 3*4; i++){
		fprintf(out,"%c",drc1_tko[i]);
	}
	
	fprintf(out,"%s","TAB=");
	for(i = 0; i < 3*8; i++){
		fprintf(out,"%c",drc1_table[i]);
	}

	fprintf(out,"%s","EQp=");
	for(i = 0; i < 2*7*20; i++){
		fprintf(out,"%c",table_mode[i]);
	}
	for(i = 0; i < 2*7*20; i++){
		fprintf(out,"%c",wall_mode[i]);
	}

exit_read:
	fclose(out);
	//printf("Generate audio parameters!\n");
	return 0;
}	


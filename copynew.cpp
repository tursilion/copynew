// copynew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int idx;
	FILE *fpIn, *fpOut;
	char szBuf[1024], szFile[1024], szExt[512];

	// copies a file, but appends xxxxx to the file, where xxxxx is the first number,
	// starting with 0, which is available

	if (argc<3) {
		printf("copynew <source file> <dest file>\nAdds the number xxxxx to dest file,\n");
		printf("where xxxxx is the first unused\nnumber in that folder, starting at 00000\n");
		return 0;
	}

	strcpy(szFile, argv[2]);
	strcpy(szExt, "");
	idx=strlen(szFile);
	while ((idx>0)&&(szFile[idx]!='.')) idx--;
	if ('.'==szFile[idx]) {
		strcpy(szExt, &szFile[idx+1]);
		szFile[idx]='\0';
	}

	idx=0;
	fpIn=(FILE*)1;
	
	while (NULL != fpIn) {
		sprintf(szBuf, "%s%05d.%s", szFile, idx, szExt);
		fpIn=fopen(szBuf, "r");
		if (NULL != fpIn) fclose(fpIn);
		idx++;
		if (idx>99999) {
			printf("* Too many files in this dir!\n");
			return 0;
		}
	}

	fpIn=fopen(argv[1], "rb");
	if (NULL == fpIn) {
		printf("* Can't open input file %s\n", argv[1]);
		return 0;
	}

	fpOut=fopen(szBuf, "wb");
	if (NULL == fpOut) {
		fclose(fpIn);
		printf("* Can't open output file %s\n", szBuf);
		return 0;
	}

	printf("- %s -> %s\n", argv[1], szBuf);

	while (!feof(fpIn)) {
		fputc(fgetc(fpIn), fpOut);
	}

	fclose(fpOut);
	fclose(fpIn);

	return 0;
}

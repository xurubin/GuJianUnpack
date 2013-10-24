#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "blowfish.h"
#include "interface.h"
#include "algorithms.h"
#include <assert.h>


#include "c/Lzma86.h"  


#pragma pack(1) 
struct FAT_Entry
{
	char bit1;
	char bit2;
	int  offset;
	int  originalsize;
	int  packedsize;
};

FILE* CreateOutputFile(char* zpkfile, char* filename)
{
	char basedir[1024];
	int  i;
	/*
	int i = strlen(zpkfile)-1;
	while(i >= 0)
		if(zpkfile[i--] == '.') break;
	if (i < 0) i = strlen(zpkfile) - 1;

	strncpy_s(basedir, sizeof(basedir), zpkfile, i+1);
	*/
	strcpy(basedir, zpkfile);
	strcat(basedir, "_e/");
	CreateDirectory(basedir, NULL);
	//Split filename
	int len = strlen(filename);
	for(i=0;i<len;i++)
	{
		if ((filename[i] == '/')||(filename[i] == '\\'))
			CreateDirectory(basedir, NULL);
		basedir[strlen(basedir)+1] = '\0';
		basedir[strlen(basedir)] = filename[i];
	}
	return fopen(basedir, "wb");
}
int main(int argc, char* argv[])
{
	CBlowFish blowfish;
	bool testmode = false;
	CFileDecrypter filedecrypter;
	//Init();
	//int T[2], R[2];
	//T[0] = 1; T[1] = 2;
	//blowfish.Initialize((BYTE*)"TESTKEY", 7);
	//blowfish.Encode((BYTE*)T, (BYTE*)R, 8);

	printf("Gujian zpk extractor - pr8ad8\n");
	if((argc == 3) &&(strcmp(argv[2], "-test") == 0)) testmode = true;
	if ((!testmode)&&(argc != 2))
	{
			printf("Usage: zpkExtract source.zpk\n");
			return 1;
	}
	unsigned char  buf[16*1024], filekey[0x110], FAT[0x10000];
	char * filebuf = (char*)malloc(16*1024*1024);
	char * inflatedbuf = (char*)malloc(32*1024*1024);
	int intbuf;

	int i;
	FILE* fin = fopen(argv[1], "rb");
	//Get FileKey
	fseek(fin, -4, SEEK_END);
	fread(&intbuf, 4, 1, fin);
	intbuf ^= 0x6FD7;
	fseek(fin, intbuf, SEEK_SET);

	//Load FileKey and initialize blow fish
	fread(buf, 1, 0x110, fin);
	int keylen = (buf[0]&0xFF) + 256 * (buf[1]&0xFF);
	memcpy(filekey, buf+2, keylen);
	blowfish.Initialize(filekey, keylen);
	filedecrypter.SetKey((char*)filekey, keylen);

	//Get offset of FAT and jump to it
	fseek(fin, keylen+2, SEEK_SET);
	fread(&intbuf, 4, 1, fin);
	int fat_offset = intbuf;

	int skey = 0x6FD7;
	while(true)
	{
		fseek(fin, fat_offset, SEEK_SET);
		//First read 2 words of xored size data;
		fread(&intbuf, 4, 1, fin); fat_offset += 4;
		int t1 = (intbuf & 0xFF) * 256 + ((intbuf>>8)&0xFF);
		int t2 = (intbuf >> 16) & 0xFFFF;
		int datasize = t1 ^ skey;
		int blocksize = t1 ^ t2;
		skey = t1;
		printf("Reading FAT: %.4x %.4x\n", datasize, blocksize);
		if ((datasize == 0)||(blocksize == 0)) break;
		if ((datasize>blocksize) ||(datasize>0xFFFF)||(blocksize>0xFFFF)) break;

		//Now read in FAT
		fread(FAT, 1, blocksize, fin); fat_offset += blocksize;

		for(i=0;i<(blocksize+7)/8;i++)
		{
			unsigned int L = ((unsigned int*)FAT)[2*i];
			unsigned int R = ((unsigned int*)FAT)[2*i+1];
			//blowfish_modify()
			((unsigned int*)FAT)[2*i] = ChangeEndianess(R);
			((unsigned int*)FAT)[2*i+1] = ChangeEndianess(L);
		}
		
		blowfish.Decode(FAT, FAT, blocksize);
		
		for(i=0;i<(blocksize+3)/4;i++)
			((unsigned int*)FAT)[i] = ChangeEndianess(((unsigned int*)FAT)[i]);

		i = 0;
		char filename[255];
		while(i < datasize)
		{
			int namelen = FAT[i+1]*256+FAT[i];
			memcpy(filename, FAT+i+2, namelen);
			filename[namelen] = '\0';
			i += 2;
			i += namelen;
			FAT_Entry* entry = (FAT_Entry*)(FAT+i);
			i += 14;
			printf("%s %.2d %.2d %.8x %.8x %.8x %.3f\n", filename, entry->bit1, entry->bit2, entry->offset, entry->originalsize, entry->packedsize,
				entry->packedsize*100.0 / (double) entry->originalsize);
			//if (stricmp(filename+strlen(filename)-4, ".jpg") != 0) continue;
			//if(entry->bit2 != 2) continue;
			fseek(fin, entry->offset, SEEK_SET);

			int outputbufsize = 0;
			while(outputbufsize < entry->originalsize)
			{
				fread(buf, 1, 8, fin);
				int partdatasize = ChangeEndianess(((int*)buf)[0]);
				int partblocksize = ((int*)buf)[1];
				assert(partblocksize <= 0x80000);
				if (partdatasize > partblocksize) break;

				fread(filebuf, 1, partblocksize, fin);
				if(entry->bit1 == 1)
				{
					filedecrypter.Decrypt(filebuf, filebuf, partblocksize, 1);
				}
				else if (entry->bit1 == 2)
				{
					filedecrypter.Decrypt(filebuf, filebuf, partblocksize, 2);
				}
				else ;//No encryption bit1 == 0

				if (entry->bit2 == 0) //No Compression
				{
					memcpy(inflatedbuf+outputbufsize, filebuf, partdatasize);
					outputbufsize += partdatasize;
				}
				else if (entry->bit2 == 1) //Simple Compression
				{
					int compresstype = filebuf[4]>>5;
					int size = 0;
					if(compresstype == 1)
					{
						size = deflate2(filebuf+4, (char*)inflatedbuf+outputbufsize, ChangeEndianess(((int*)filebuf)[0]));
					}
					else if(compresstype == 0)
					{
						size = deflate1(filebuf+4, (char*)inflatedbuf+outputbufsize, ChangeEndianess(((int*)filebuf)[0]));
					}
					else 
						printf("ERROR: Incorrect simple inflation type\n");
					if (size == 0) break;
					outputbufsize += size;
				}
				else if (entry->bit2 == 2) //Complex compression
				{
					UInt64 lzma_unpacksize;
					Lzma86_GetUnpackSize((BYTE*)filebuf+4, partdatasize, &lzma_unpacksize);
					SizeT outSizeProcessed;
					SizeT insize = (SizeT)partdatasize;
					outSizeProcessed = lzma_unpacksize;

					if (Lzma86_Decode((BYTE*)inflatedbuf+outputbufsize, &outSizeProcessed, (BYTE*)filebuf+4, &insize))
					{
						printf("ERROR: LZMA decode failed.\n");
						break;
					}

					if ((insize != partdatasize - 4)||(lzma_unpacksize!=outSizeProcessed))
					{
						printf("ERROR: LZMA decode data inconsistent.\n");
						break;
					}
					outputbufsize += outSizeProcessed;
				}
				else
				{
					printf("ERROR: Incorrect inflation type\n");
					break;
				}
			} //Read/Inflation loop 
			if (outputbufsize == entry->originalsize)
			{
				if(!testmode)
				{
					FILE* fout = CreateOutputFile(argv[1], filename);
					fwrite(inflatedbuf, 1, outputbufsize, fout);
					fclose(fout);
				}
			}
			else
				printf("ERROR: Inflation size inconsistent.\n");

		}
	}
	free(filebuf);
	free(inflatedbuf);
	fclose(fin);
}

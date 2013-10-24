#include "algorithms.h"
#include <windows.h>
unsigned int ChangeEndianess(unsigned int x)
{
	unsigned int y = 0;
	y = (y << 8) | (x & 0xFF); x >>= 8;
	y = (y << 8) | (x & 0xFF); x >>= 8;
	y = (y << 8) | (x & 0xFF); x >>= 8;
	y = (y << 8) | (x & 0xFF); x >>= 8;
	return y;
}
__declspec(naked) void __stdcall file_decrypt_1(char* src, char* dst, char* filekey, int key2)
{
	__asm
	{
                 mov     edx, [esp+4]
                 movzx   ecx, byte ptr [edx]
                 movzx   eax, byte ptr [edx+1]
                 shl     ecx, 8
                 add     ecx, eax
                 movzx   eax, byte ptr [edx+2]
                 shl     ecx, 8
                 add     ecx, eax
                 movzx   eax, byte ptr [edx+3]
                 shl     ecx, 8
                 add     ecx, eax
                 movzx   eax, byte ptr [edx+4]
                 shl     eax, 8
                 push    esi
                 movzx   esi, byte ptr [edx+5]
                 add     eax, esi
                 movzx   esi, byte ptr [edx+6]
                 movzx   edx, byte ptr [edx+7]
                 shl     eax, 8
                 add     eax, esi
                 shl     eax, 8
                 add     eax, edx
                 mov     edx, [esp+4+0x10]
                 test    edx, edx
                 jz      short loc_100052F1
                 push    ebx
                 mov     ebx, [esp+8+0xC]
                 mov     esi, [ebx+0Ch]
                 push    ebp
                 push    edi
                 mov     edi, [ebx+8]
                 mov     [esp+10h+4], edi
                 mov     edi, [ebx+4]
                 mov     ebx, [ebx]
                 mov     [esp+10h+0x10], ebx

 loc_100052B4:                           ; CODE XREF: sub_10005250+9Cj
                 mov     ebx, ecx
                 shl     ebx, 4
                 add     ebx, [esp+10h+4]
                 mov     ebp, ecx
                 shr     ebp, 5
                 add     ebp, esi
                 xor     ebx, ebp
                 lea     ebp, [edx+ecx]
                 xor     ebx, ebp
                 sub     eax, ebx
                 mov     ebx, eax
                 shl     ebx, 4
                 add     ebx, [esp+10h+0x10]
                 mov     ebp, eax
                 shr     ebp, 5
                 add     ebp, edi
                 xor     ebx, ebp
                 lea     ebp, [edx+eax]
                 xor     ebx, ebp
                 sub     ecx, ebx
                 add     edx, 61C88647h
                 jnz     short loc_100052B4
                 pop     edi
                 pop     ebp
                 pop     ebx

 loc_100052F1:                           ; CODE XREF: sub_10005250+48j
                 mov     esi, [esp+4+8]
                 mov     edx, ecx
                 shr     edx, 18h
                 mov     [esi], dl
                 mov     edx, ecx
                 mov     [esi+3], cl
                 shr     edx, 10h
                 mov     [esi+1], dl
                 mov     edx, ecx
                 shr     edx, 8
                 mov     [esi+2], dl
                 mov     ecx, eax
                 shr     ecx, 18h
                 mov     [esi+4], cl
                 mov     edx, eax
                 mov     ecx, eax
                 shr     edx, 10h
                 shr     ecx, 8
                 mov     [esi+5], dl
                 mov     [esi+6], cl
                 mov     [esi+7], al
                 pop     esi
                 retn    0x10
 	}
}

__declspec(naked) void __stdcall file_decrypt_2(char* src, char* dst, char* filekey, int key2)
{
__asm
{
                 mov     edx, [esp+4]
                 movzx   ecx, byte ptr [edx]
                 movzx   eax, byte ptr [edx+1]
                 shl     ecx, 8
                 add     ecx, eax
                 movzx   eax, byte ptr [edx+2]
                 shl     ecx, 8
                 add     ecx, eax
                 movzx   eax, byte ptr [edx+3]
                 shl     ecx, 8
                 add     ecx, eax
                 movzx   eax, byte ptr [edx+4]
                 shl     eax, 8
                 push    esi
                 movzx   esi, byte ptr [edx+5]
                 add     eax, esi
                 movzx   esi, byte ptr [edx+6]
                 movzx   edx, byte ptr [edx+7]
                 shl     eax, 8
                 add     eax, esi
                 shl     eax, 8
                 add     eax, edx
                 mov     edx, [esp+4+0x10]
                 test    edx, edx
                 jz      loc_100053C7
                 mov     esi, [esp+4+0xC]
                 push    ebx
                 push    edi

 loc_10005380:                          // CODE XREF: sub_10005330+93j
                 mov     edi, ecx
                 shr     edi, 5
                 mov     ebx, ecx
                 shl     ebx, 4
                 xor     edi, ebx
                 mov     ebx, edx
                 shr     ebx, 0Bh
                 and     ebx, 3
                 mov     ebx, [esi+ebx*4]
                 add     ebx, edx
                 add     edi, ecx
                 xor     edi, ebx
                 sub     eax, edi
                 mov     edi, eax
                 shr     edi, 5
                 mov     ebx, eax
                 shl     ebx, 4
                 xor     edi, ebx
                 add     edx, 61C88647h
                 mov     ebx, edx
                 and     ebx, 3
                 mov     ebx, [esi+ebx*4]
                 add     edi, eax
                 add     ebx, edx
                 xor     edi, ebx
                 sub     ecx, edi
                 test    edx, edx
                 jnz     loc_10005380
                 pop     edi
                 pop     ebx

 loc_100053C7:                           // CODE XREF: sub_10005330+48j
                 mov     esi, [esp+4+8]
                 mov     edx, ecx
                 shr     edx, 18h
                 mov     [esi], dl
                 mov     edx, ecx
                 mov     [esi+3], cl
                 shr     edx, 10h
                 mov     [esi+1], dl
                 mov     edx, ecx
                 shr     edx, 8
                 mov     [esi+2], dl
                 mov     ecx, eax
                 shr     ecx, 18h
                 mov     [esi+4], cl
                 mov     edx, eax
                 mov     ecx, eax
                 shr     edx, 10h
                 shr     ecx, 8
                 mov     [esi+5], dl
                 mov     [esi+6], cl
                 mov     [esi+7], al
                 pop     esi
                 retn    0x10
}
}


unsigned int CalculateKey(char * FileKey, int KeyLen, int  * derivedkey)
{
__asm
{
				 mov     ecx, derivedkey
			     mov     esi, KeyLen
				 mov     edi, FileKey
                 xor     eax, eax
                 test    esi, esi
                 mov     dword ptr [ecx], 0C33707D6h
                 mov     dword ptr [ecx+4], 4BDECFA9h
                 mov     dword ptr [ecx+8], 0FC93A039h
                 mov     dword ptr [ecx+0Ch], 0E7D3FBC8h
                 jbe     loc_10005229
                 push    ebx

 loc_10005212:                           // CODE XREF: sub_100051F0+36j
                 movzx   ebx, byte ptr [eax+edi]
                 mov     edx, eax
                 and     edx, 3
                 xor     [ecx+edx*4], ebx
                 lea     edx, [ecx+edx*4]
                 add     eax, 1
                 cmp     eax, esi
                 jb      short loc_10005212
                 pop     ebx

loc_10005229:                            // CODE XREF: sub_100051F0+1Fj
				 mov     eax, [ecx+8]
                 xor     eax, [ecx]
                 xor     eax, [ecx+4]
                 xor     eax, [ecx+0Ch]
                 mov     ecx, derivedkey //[esp+4]
				 add     ecx, 16
                 and     eax, 0Fh
                 add     eax, 10h
                 imul    eax, 9E3779B9h
                 mov     [ecx], eax
}
return derivedkey[4];
}




void CFileDecrypter::SetKey( char* FileKey, int KeyLen )
{
	memcpy(filekey, FileKey, KeyLen);
	CalculateKey(filekey, KeyLen, derivedkey);
}

int CFileDecrypter::Decrypt( char* dst, char * src, int len, int type)
{
	//int datasize = ChangeEndianess(((int*)src)[0]);
	//int blocksize = ((int*)src)[1];
	//if (datasize>blocksize) return -1;
	//if (blocksize % 8 != 0) return -1;
	//if (blocksize != len - 8) return -1;
	if (type == 1)
		for(int i=0;i<len/8;i++)
			file_decrypt_1(src+i*8, dst+i*8, (char *)derivedkey, derivedkey[4]);
	else if (type == 2)
	for(int i=0;i<len/8;i++)
		file_decrypt_2(src+i*8, dst+i*8, (char *)derivedkey, derivedkey[4]);
	return len;
}


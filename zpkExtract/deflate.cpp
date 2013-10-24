#include <string.h>
#include "algorithms.h"

__declspec(naked) void __stdcall raw_deflate1(char* arg)
{
__asm
{
                 sub     esp, 14h
                 mov     edx, [esp+14h+4]
                 push    ebx
                 push    ebp
                 push    esi
                 push    edi
                 mov     edi, ecx
                 lea     ecx, [edi+eax]
                 movzx   eax, byte ptr [edi]
                 and     eax, 1Fh
                 mov     ebp, eax
                 mov     [esp+24h-0xC], ecx
                 mov     esi, edx
                 mov     [esp+24h-0x14], ebp
                 add     edi, 1
                 mov     [esp+24h-0x10], 1
                 lea     ecx, [ecx+0]

 loc_10005690:                           //; CODE XREF: deflate1+1E5j
                 cmp     ebp, 20h
                 jb      loc_100057E6
                 mov     eax, ebp
                 mov     ebx, ebp
                 and     eax, 1Fh
                 shr     ebx, 5
                 shl     eax, 8
                 mov     ecx, esi
                 sub     ebx, 1
                 sub     ecx, eax
                 cmp     ebx, 6
                 jnz     short loc_100056BB
                 movzx   ebx, byte ptr [edi]
                 add     ebx, 6
                 add     edi, 1

 loc_100056BB:                          // ; CODE XREF: deflate1+50j
                 movzx   eax, byte ptr [edi]
                 sub     ecx, eax
                 lea     eax, [ebx+esi+3]
                 mov     [esp+24h-0x8], eax
                 lea     eax, [edx+80000h]
                 mov     edx, [esp+24h-0x8]
                 add     edi, 1
                 cmp     edx, eax
                 ja      loc_1000584A
                 lea     edx, [ecx-1]
                 cmp     edx, [esp+24h+4]
                 jb      loc_1000584A
                 cmp     edi, [esp+24h-0xC]
                 jnb     short loc_100056FC
                 movzx   ebp, byte ptr [edi]
                 mov     [esp+24h-0x14], ebp
                 add     edi, 1
                 jmp     short loc_10005704
 ; ---------------------------------------------------------------------------

 loc_100056FC:                          ; CODE XREF: deflate1+8Ej
                 mov     [esp+24h-0x10], 0

 loc_10005704:                           ; CODE XREF: deflate1+9Aj
                 cmp     ecx, esi
                 jnz     short loc_1000573C
                 mov     cl, [ecx-1]
                 mov     [esi], cl
                 add     esi, 1
                 mov     [esi], cl
                 add     esi, 1
                 mov     [esi], cl
                 add     esi, 1
                 test    ebx, ebx
                 mov     byte ptr [esp+24h-0x4], cl
                 jz      loc_10005836
                 mov     eax, [esp+24h-0x4]
                 push    ebx             ; size_t
                 push    eax             ; int
                 push    esi             ; void *
                 call    memset
                 add     esp, 0Ch
                 add     esi, ebx
                 jmp     loc_10005836
 ; ---------------------------------------------------------------------------

 loc_1000573C:                           ; CODE XREF: deflate1+A6j
                 movzx   edx, byte ptr [ecx-1]
                 sub     ecx, 1
                 mov     [esi], dl
                 mov     al, [ecx+1]
                 add     ecx, 1
                 add     esi, 1
                 mov     [esi], al
                 movzx   edx, byte ptr [ecx+1]
                 add     ecx, 1
                 add     esi, 1
                 mov     [esi], dl
                 add     esi, 1
                 add     ecx, 1
                 test    bl, 1
                 jz      short loc_10005774
                 mov     al, [ecx]
                 mov     [esi], al
                 add     esi, 1
                 add     ecx, 1
                 sub     ebx, 1

 loc_10005774:                           ; CODE XREF: deflate1+105j
                 mov     eax, esi
                 add     esi, ebx
                 shr     ebx, 1
                 cmp     ebx, 4
                 jbe     short loc_100057CF
                 lea     edx, [ebx-5]
                 shr     edx, 2
                 add     edx, 1
                 jmp     short loc_10005790
 ; ---------------------------------------------------------------------------
                 align 10h

 loc_10005790:                           ; CODE XREF: deflate1+128j
                                         ; deflate1+169j
                 mov     bp, [ecx]
                 mov     [eax], bp
                 mov     bp, [ecx+2]
                 add     ecx, 2
                 add     eax, 2
                 mov     [eax], bp
                 mov     bp, [ecx+2]
                 add     ecx, 2
                 add     eax, 2
                 mov     [eax], bp
                 mov     bp, [ecx+2]
                 add     ecx, 2
                 add     eax, 2
                 mov     [eax], bp
                 add     eax, 2
                 add     ecx, 2
                 sub     ebx, 4
                 sub     edx, 1
                 jnz     short loc_10005790
                 mov     ebp, [esp+24h-0x14]

 loc_100057CF:                           ; CODE XREF: deflate1+11Dj
                 test    ebx, ebx
                 jz      short loc_10005836

 loc_100057D3:                           ; CODE XREF: deflate1+182j
                 mov     dx, [ecx]
                 mov     [eax], dx
                 add     eax, 2
                 add     ecx, 2
                 sub     ebx, 1
                 jnz     short loc_100057D3
                 jmp     short loc_10005836
 ; ---------------------------------------------------------------------------

 loc_100057E6:                           ; CODE XREF: deflate1+33j
                 add     ebp, 1
                 lea     ebx, [esi+ebp]
                 lea     eax, [edx+80000h]
                 cmp     ebx, eax
                 ja      short loc_1000584A
                 lea     eax, [edi+ebp]
                 cmp     eax, ecx
                 ja      short loc_1000584A
                 mov     al, [edi]
                 mov     [esi], al
                 add     esi, 1
                 add     edi, 1
                 sub     ebp, 1
                 jz      short loc_10005820
                 lea     esp, [esp+0]

 loc_10005810:                           ; CODE XREF: deflate1+1BEj
                 movzx   eax, byte ptr [edi]
                 mov     [esi], al
                 add     esi, 1
                 add     edi, 1
                 sub     ebp, 1
                 jnz     short loc_10005810

 loc_10005820:                           ; CODE XREF: deflate1+1AAj
                 cmp     edi, ecx
                 sbb     eax, eax
                 neg     eax
                 mov     [esp+24h-0x10], eax
                 jz      short loc_10005854
                 movzx   ebp, byte ptr [edi]
                 mov     [esp+24h-0x14], ebp
                 add     edi, 1

 loc_10005836:                           ; CODE XREF: deflate1+C0j
                                         ; deflate1+D7j ...
                 cmp     [esp+24h-0x10], 0
                 mov     edx, [esp+24h+4]
                 jz      short loc_10005854
                 mov     ecx, [esp+24h-0xC]
                 jmp     loc_10005690
 ; ---------------------------------------------------------------------------

 loc_1000584A:                           ; CODE XREF: deflate1+77j
                                         ; deflate1+84j ...
                 pop     edi
                 pop     esi
                 pop     ebp
                 xor     eax, eax
                 pop     ebx
                 add     esp, 14h
                 retn 4
 ; ---------------------------------------------------------------------------

 loc_10005854:                           ; CODE XREF: deflate1+1CAj
                                         ; deflate1+1DFj
                 pop     edi
                 mov     eax, esi
                 pop     esi
                 pop     ebp
                 sub     eax, edx
                 pop     ebx
                 add     esp, 14h
                 retn 4
}
}
__declspec(naked) void __stdcall raw_deflate2(char* arg)
{
__asm
{
                 sub     esp, 10h
                 push    ebx
                 push    ebp
                 push    esi
                 mov     esi, [esp+1Ch+4]
                 push    edi
                 mov     edi, ecx
                 movzx   edx, byte ptr [edi]
                 lea     ecx, [edi+eax]
                 and     edx, 1Fh
                 mov     [esp+20h+-0x8], ecx
                 mov     [esp+20h+-0x10], edx
                 add     edi, 1
                 mov     [esp+20h+-0xc], 1
                 lea     esp, [esp+0]

 loc_10005890:                           //; CODE XREF: deflate2+208j
                 mov     ebp, edx
                 and     ebp, 1Fh
                 shl     ebp, 8
                 cmp     edx, 20h
                 jb      loc_10005A0A
                 mov     ebx, edx
                 shr     ebx, 5
                 mov     ecx, esi
                 sub     ebx, 1
                 sub     ecx, ebp
                 cmp     ebx, 6
                 jnz     short loc_100058C0

 loc_100058B2:                          // ; CODE XREF: deflate2+5Ej
                 mov     al, [edi]
                 movzx   edx, al
                 add     edi, 1
                 add     ebx, edx
                 cmp     al, 0FFh
                 jz      short loc_100058B2

 loc_100058C0:                           //; CODE XREF: deflate2+50j
                 mov     al, [edi]
                 movzx   edx, al
                 add     edi, 1
                 sub     ecx, edx
                 cmp     al, 0FFh
                 jnz     short loc_100058F0
                 cmp     ebp, 1F00h
                 jnz     short loc_100058F0
                 movzx   ecx, byte ptr [edi+1]
                 xor     eax, eax
                 mov     ah, [edi]
                 add     edi, 1
                 add     edi, 1
                 add     eax, ecx
                 mov     ecx, esi
                 sub     ecx, eax
                 sub     ecx, 1FFFh

 loc_100058F0:                           //; CODE XREF: deflate2+6Cj
                                         //; deflate2+74j
                 mov     edx, [esp+20h+4]
                 lea     ebp, [ebx+esi+3]
                 lea     eax, [edx+80000h]
                 cmp     ebp, eax
                 ja      loc_10005A6D
                 lea     eax, [ecx-1]
                 cmp     eax, edx
                 jb      loc_10005A6D
                 cmp     edi, [esp+20h+-0x8]
                 jnb     short loc_10005923
                 movzx   edx, byte ptr [edi]
                 mov     [esp+20h+-0x10], edx
                 add     edi, 1
                 jmp     short loc_1000592B
 ; ---------------------------------------------------------------------------

 loc_10005923:                           //; CODE XREF: deflate2+B5j
                 mov     [esp+20h+-0xc], 0

 loc_1000592B:                           //; CODE XREF: deflate2+C1j
                 cmp     ecx, esi
                 mov     edx, [esp+20h+-0x10]
                 jnz     short loc_10005967
                 mov     cl, [ecx-1]
                 mov     [esi], cl
                 add     esi, 1
                 mov     [esi], cl
                 add     esi, 1
                 mov     [esi], cl
                 add     esi, 1
                 test    ebx, ebx
                 mov     byte ptr [esp+20h+-0x4], cl
                 jz      loc_10005A5D
                 mov     eax, [esp+20h+-0x4]
                 push    ebx            // ; size_t
                 push    eax            // ; int
                 push    esi            // ; void *
                 call    memset
                 add     esp, 0Ch
                 add     esi, ebx
                 jmp     loc_10005A59
 ; ---------------------------------------------------------------------------

 loc_10005967:                           //; CODE XREF: deflate2+D1j
                 movzx   eax, byte ptr [ecx-1]
                 sub     ecx, 1
                 mov     [esi], al
                 movzx   eax, byte ptr [ecx+1]
                 add     ecx, 1
                 add     esi, 1
                 mov     [esi], al
                 movzx   eax, byte ptr [ecx+1]
                 add     ecx, 1
                 add     esi, 1
                 mov     [esi], al
                 add     esi, 1
                 add     ecx, 1
                 test    bl, 1
                 jz      short loc_100059A0
                 mov     al, [ecx]
                 mov     [esi], al
                 add     esi, 1
                 add     ecx, 1
                 sub     ebx, 1

 loc_100059A0:                          // ; CODE XREF: deflate2+131j
                 mov     eax, esi
                 add     esi, ebx
                 shr     ebx, 1
                 cmp     ebx, 4
                 jbe     short loc_100059F3
                 lea     edx, [ebx-5]
                 shr     edx, 2
                 add     edx, 1

 loc_100059B4:                          // ; CODE XREF: deflate2+18Dj
                 mov     bp, [ecx]
                 mov     [eax], bp
                 mov     bp, [ecx+2]
                 add     ecx, 2
                 add     eax, 2
                 mov     [eax], bp
                 mov     bp, [ecx+2]
                 add     ecx, 2
                 add     eax, 2
                 mov     [eax], bp
                 mov     bp, [ecx+2]
                 add     ecx, 2
                 add     eax, 2
                 mov     [eax], bp
                 add     eax, 2
                 add     ecx, 2
                 sub     ebx, 4
                 sub     edx, 1
                 jnz     short loc_100059B4
                 mov     edx, [esp+20h+-0x10]

 loc_100059F3:                          // ; CODE XREF: deflate2+149j
                 test    ebx, ebx
                 jz      short loc_10005A5D

 loc_100059F7:                           ; CODE XREF: deflate2+1A6j
                 mov     bp, [ecx]
                 mov     [eax], bp
                 add     eax, 2
                 add     ecx, 2
                 sub     ebx, 1
                 jnz     short loc_100059F7
                 jmp     short loc_10005A5D
 ; ---------------------------------------------------------------------------

 loc_10005A0A:                           //; CODE XREF: deflate2+3Bj
                 mov     eax, [esp+20h+4]
                 add     edx, 1
                 lea     ebx, [edx+esi]
                 add     eax, 80000h
                 cmp     ebx, eax
                 ja      short loc_10005A6D
                 lea     eax, [edx+edi]
                 cmp     eax, ecx
                 ja      short loc_10005A6D
                 mov     al, [edi]
                 mov     [esi], al
                 add     esi, 1
                 add     edi, 1
                 sub     edx, 1
                 jz      short loc_10005A43

 loc_10005A33:                          // ; CODE XREF: deflate2+1E1j
                 movzx   eax, byte ptr [edi]
                 mov     [esi], al
                 add     esi, 1
                 add     edi, 1
                 sub     edx, 1
                 jnz     short loc_10005A33

 loc_10005A43:                           ; CODE XREF: deflate2+1D1j
                 cmp     edi, ecx
                 sbb     eax, eax
                 neg     eax
                 mov     [esp+20h+-0xc], eax
                 jz      short loc_10005A77
                 movzx   ecx, byte ptr [edi]
                 mov     [esp+20h+-0x10], ecx
                 add     edi, 1

 loc_10005A59:                          // ; CODE XREF: deflate2+102j
                 mov     edx, [esp+20h+-0x10]

 loc_10005A5D:                          // ; CODE XREF: deflate2+EBj
                                        // ; deflate2+195j ...
                 cmp     [esp+20h+-0xc], 0
                 jz      short loc_10005A77
                 mov     ecx, [esp+20h+-0x8]
                 jmp     loc_10005890
 ; ---------------------------------------------------------------------------

 loc_10005A6D:                          // ; CODE XREF: deflate2+A0j
                                        // ; deflate2+ABj ...
                 pop     edi
                 pop     esi
                 pop     ebp
                 xor     eax, eax
                 pop     ebx
                 add     esp, 10h
                 retn    4
 ; ---------------------------------------------------------------------------

 loc_10005A77:                           //; CODE XREF: deflate2+1EDj
                                        // ; deflate2+202j
                 pop     edi
                 mov     eax, esi
                 sub     eax, [esp+1Ch+4]
                 pop     esi
                 pop     ebp
                 pop     ebx
                 add     esp, 10h
                 retn    4
}
}

int deflate1(char* src, char* dst, int len)
{
__asm
{
mov    eax, len
mov    ecx, src
push   dst
call   raw_deflate1
}
}
int deflate2(char* src, char* dst, int len)
{
__asm
{
mov    eax, len
mov    ecx, src
push   dst
call   raw_deflate2
}
}



__declspec(naked) void compute_uncompressedsize()
{
	__asm
	{/*
		mov     dword ptr [esi], 0
			mov     dword ptr [esi+4], 0
			movzx   eax, byte ptr [edi+6]
		cdq
			mov     [esi], eax
			mov     [esi+4], edx
			movzx   eax, byte ptr [edi+7]
		push    0
			cdq
			push    100h
			push    edx
			push    eax
			call    __allmul
			add     [esi], eax
			push    0
			push    10000h
			adc     [esi+4], edx
			movzx   eax, byte ptr [edi+8]
		cdq
			push    edx
			push    eax
			call    __allmul
			add     [esi], eax
			push    0
			push    1000000h
			adc     [esi+4], edx
			movzx   eax, byte ptr [edi+9]
		cdq
			push    edx
			push    eax
			call    __allmul
			add     [esi], eax
			push    1
			push    0
			adc     [esi+4], edx
			movzx   eax, byte ptr [edi+0Ah]
		cdq
			push    edx
			push    eax
			call    __allmul
			add     [esi], eax
			push    100h
			push    0
			adc     [esi+4], edx
			movzx   eax, byte ptr [edi+0Bh]
		cdq
			push    edx
			push    eax
			call    __allmul
			add     [esi], eax
			push    10000h
			push    0
			adc     [esi+4], edx
			movzx   eax, byte ptr [edi+0Ch]
		cdq
			push    edx
			push    eax
			call    __allmul
			add     [esi], eax
			push    1000000h
			push    0
			adc     [esi+4], edx
			movzx   eax, byte ptr [edi+0Dh]
		cdq
			push    edx
			push    eax
			call    __allmul
			add     [esi], eax
			adc     [esi+4], edx
			xor     eax, eax
			retn*/
	}
}

int CDecompresser::decompress( char* src, char* dst, int len )
{
	int uncompressedsize[2];
	__asm
	{
		pushad
			mov edi, src
			add edi, 4
			mov edi, uncompressedsize
			call compute_uncompressedsize
		popad
	}


}
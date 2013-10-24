#include "interface.h"
#include <Windows.h>

/*
; public: static void __cdecl AurRendererSDM::Init(void)
public ?Init@AurRendererSDM@@SAXXZ
?Init@AurRendererSDM@@SAXXZ proc near

; public: static class ZpkPackageManager * __cdecl ZpkPackageManager::Create(void)
public ?Create@ZpkPackageManager@@SAPAV1@XZ
?Create@ZpkPackageManager@@SAPAV1@XZ proc near
*/

void (*AurRendererSDM_Init)(void);
void* (*ZpkPackageManager_Create)(void);

/*
; public: static class NiFile * __cdecl NiFile::GetFile(char const *, enum  NiFile::OpenMode, unsigned int)
public ?GetFile@NiFile@@SAPAV1@PBDW4OpenMode@1@I@Z
?GetFile@NiFile@@SAPAV1@PBDW4OpenMode@1@I@Z proc near

; int __stdcall NiFile::FileRead(void *Dst, size_t MaxCount)
public ?FileRead@NiFile@@IAEIPAXI@Z
?FileRead@NiFile@@IAEIPAXI@Z proc near

; public: static void __cdecl NiMemManager::_SDMInit(void)
public ?_SDMInit@NiMemManager@@SAXXZ
?_SDMInit@NiMemManager@@SAXXZ proc near

*/
void* (*NiFile_GetFile)(const char *, int OpenMode, int unknown);
int  (*NiFile__FileRead)(void *Dst, int MaxCount);
void (*NiMemManager_SDMInit)(void);

bool Init()
{
	HMODULE hSystem = LoadLibrary("AurNiSystemS.dll");
	NiFile_GetFile = (void *(__cdecl *)(const char *,int,int))GetProcAddress(hSystem, "?GetFile@NiFile@@SAPAV1@PBDW4OpenMode@1@I@Z");
	NiFile__FileRead = (int (__cdecl *)(void *,int))GetProcAddress(hSystem, "?FileRead@NiFile@@IAEIPAXI@Z");
	NiMemManager_SDMInit = (void (__cdecl *)(void))GetProcAddress(hSystem, "?_SDMInit@NiMemManager@@SAXXZ");
	if (!NiFile_GetFile) return false;
	if (!NiFile__FileRead) return false;
	if (!NiMemManager_SDMInit) return false;

	HMODULE hRenderer = LoadLibrary("AurRendererS.dll");
	AurRendererSDM_Init = (void (__cdecl *)(void))GetProcAddress(hRenderer, "?Init@AurRendererSDM@@SAXXZ");
	ZpkPackageManager_Create = (void *(__cdecl *)(void))GetProcAddress(hRenderer, "?Create@ZpkPackageManager@@SAPAV1@XZ");


	if (!AurRendererSDM_Init) return false;
	if (!ZpkPackageManager_Create) return false;

	NiMemManager_SDMInit();
	try
	{
		AurRendererSDM_Init();
	}
	catch(...)
	{

	}
	ZpkPackageManager_Create();
	return true;
}



void SaveFile(char* fullname)
{

}
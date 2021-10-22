#ifndef RIL_PRIVATE_H
#define RIL_PRIVATE_H

#include "pmparser.h"

struct ril_request {
	RIL_Token t; // 0-3
	int req_unk; // 4-7
	size_t datalen; // 8-11
	int request; // 12-15
	void *req_handler_ptr; // 16-19
	void *req_handler_func; // 20-23
	int unk1; // 24-27
	int unk2; // 28-31
	int unk3; // 32-35
	int unk4; // 36-39
	int unk5; // 40-43
	char unk6; // 44
	char unk7; // 45
	char unk8; // 46
	char unk9; // 47
	int unk11; // 48-51
	int unk12; // 52-55
	long long unk13; // 56-63
	int unk14; // 64-67
	int unk15; // 68-71
};

struct handler_struct {
	int (*unk1)(void *, int);
	int (*unk2)(void *, int);
	int (*unk3)(void *, int);
	int (*unk4)(void *, int);
	int unk5;
};

struct hSecOem_struct {
	void *unk1;
	void *unk2;
	void *unk3;
	void *unk4;
	void *unk5;
	void *unk6;
	void *hash_table;
};

void libEvtLoading(void) __attribute__((constructor));
void libEvtUnloading(void) __attribute__((destructor));

void *origRil;
RIL_RadioFunctions const* (*origRilInit)(const struct RIL_Env *env, int argc, char **argv);

/* A copy of the original RIL function table, got from pmparser */
static const RIL_RadioFunctions *fReal_origRilFunctions;

/* A base pointer to the start of the wrapped lib */
void *gElfPtr;

/* A pointer to the .text section of wrapped lib */
void *gBasePtr;

/* A pointer to the BSS section of wrapped lib */
void *gBssPtr;

/* Vendor blob stuff */

/* verbose debugging flag pointer */
int *bdbg_enable_ptr;

struct hSecOem_struct *hSecOem_ptr;
//struct hSecOem_struct *hSecOem = NULL;
void *hash_table;

void (*fReal_DumpStateLog)(char*, int);

int *unk_E730C;

int (*CreateRequest)(void *hSecOem, int request, void *data, int datalen, RIL_Token t);

int (*SearchDataHash)(void *hash_table, int request, int *(*handler)(void *, int));

void libEvtLoading(void)
{
	/* Open and Init the original RIL. */

	origRil = dlopen(RIL_LIB_PATH, RTLD_GLOBAL);
	if (CC_UNLIKELY(!origRil)) {
		RLOGE("%s: failed to load '" RIL_LIB_PATH  "': %s\n", __func__, dlerror());
		return;
	}
	
	origRilInit = (const RIL_RadioFunctions *(*)(const struct RIL_Env *, int, char **))(dlsym(origRil, "RIL_Init"));
	if (CC_UNLIKELY(!origRilInit)) {
		RLOGE("%s: couldn't find original RIL_Init!\n", __func__);
		return;
	}

	gElfPtr = pmparser_get_addr_start(-1, "/system/vendor/lib/libsec-ril.so", 0xaa000);
	gBssPtr = pmparser_get_addr_start(-1, "/system/vendor/lib/libsec-ril.so", 0x7000);
	
	gBasePtr = origRilInit - 0x247C0;
	
	fReal_DumpStateLog = gBasePtr + 0x3EE0C;

	RLOGE("%s: RIL_Init = %x, origRil = %x, gElfPtr=%x, gBssPtr=%x, gBasePtr=%x, fReal_DumpStateLog = %x, DumpStateLog=%x", __func__, origRilInit, origRil, gElfPtr, gBssPtr, gBasePtr, fReal_DumpStateLog, dlsym(origRil, "DumpStateLog"));
	
	fReal_origRilFunctions = gElfPtr + 0xAA368;
	
	hSecOem_ptr = gElfPtr + 0xE71A8;
	//hSecOem = *hSecOem_ptr;
	unk_E730C = gElfPtr + 0xE730C;

	CreateRequest = gBasePtr + 0x2361C;
	SearchDataHash = gBasePtr + 0x20668;

	bdbg_enable_ptr = gElfPtr + 0xAB93C;

	// enable verbose debugging
	*bdbg_enable_ptr = 1;
	//fReal_DumpStateLog("_cp_RSP", 0);

	
	ALOGE("%s: hSecOem_ptr=%x", __func__, hSecOem_ptr);
	ALOGE("%s: hSecOem_ptr from dlsym=%x", __func__, dlsym(origRil, "hSecOem"));
	ALOGE("%s: SearchDataHash=%x", __func__, SearchDataHash);
	ALOGE("%s: SearchDataHash from dlsym=%x", __func__, dlsym(origRil, "SearchDataHash"));
	hash_table = hSecOem_ptr->hash_table;
	ALOGE("%s: hSecOem->hash_table=%x", __func__, hash_table);
}

void libEvtUnloading(void)
{
	if (origRil)
		 dlclose(origRil);
}
#endif
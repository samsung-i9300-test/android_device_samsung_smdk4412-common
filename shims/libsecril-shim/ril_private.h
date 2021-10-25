#ifndef RIL_PRIVATE_H
#define RIL_PRIVATE_H

#include <sys/mman.h>

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
	int unk1;
	void *unk2;
	int unk3;
	int unk4;
	void *unk5;
	void *unk6;
	void *hash_table;
};

struct readerParam_struct {
	struct hSecOem_struct *hSecOem;
	char *reader_dev_ptr;
	void *msgQueue1_ptr;
	void *msgQueue2_ptr;
};

struct procParam_struct {
	struct hSecOem_struct *hSecOem;
	char *reader_dev_ptr;
	void *msgQueue1_ptr;
	void *msgQueue2_ptr;
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


/* RIL_Init */
void (*OemInitNetwork)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitCall)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitData)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitSMS)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitSIM)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitSs)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitSound)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitMisc)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitStk)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitPower)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitGps)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitFactory)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitImei)(struct hSecOem_struct *hSecOem_ptr);
void (*OemInitCfg)(struct hSecOem_struct *hSecOem_ptr);

struct RIL_Env **s_rilenv_ptr;
pthread_mutex_t *unk_E71AC;
int *unk_E71B0;
char **isRildInit_7DA7B_ptr;

void (*Modem_Boot)();

void *(*get_rildreset_log)(void *);

int *dword_AB8F4;
char **dword_B1CA0_ptr;

void (*ipc_debug_init)(struct hSecOem_struct *hSecOem_ptr, int debug_level);
void (*StartMulticlient)(struct hSecOem_struct *hSecOem_ptr);
int (*BuildupReqHandlerHash)(struct hSecOem_struct *hSecOem_ptr);
int (*InitEventHandling)();

int *request_list_E71C4;
void (*FreeRequest)(void *ptr);
int (*InitRequestList)(void *request_list, void (*FreeRequest)(void *ptr));
int (*InitMsgQueue)(void (*freeRxData)(void *ptr));

//void (*FreeRequest)(void *ptr);
void (*freeRxData)(void *ptr);

int *unk_E71F8;
int *unk_E71FC;
int *unk_E97E0;

struct readerParam_struct *reader_init_param;

char **unk_E97D8;
int *unk_E97DC;

int (*StartRXReader)(struct readerParam_struct *reader_init_param);

int *dword_E71B4;
int *unk_E97E4;

int *dword_E71B8;
int *unk_E97E8;
int *unk_E71BC;
int *unk_E97EC;
int **unk_E9808;
int *unk_E980C;
int *unk_E9810;
int (**unk_E9814)();
int (*sub_23E5C)();
struct procParam_struct *proc_init_param;

int (*StartRilProcessor)(struct procParam_struct  *param);

long long int *ril_features_E8F20;
struct RIL_RadioFunctions *origRilFunctions_AA368;
void (*RIL_requestTimedCallback)();

int *dword_AB8F4;
int *dword_B1CA4;
//int *dword_B1CA0;

void *unk2 = 0;
int unk3 = 0;
int unk4 = 0;

struct hSecOem_struct *hSecOem_tmp;
char *reader_dev_ptr = 0;
void *msgQueue1_ptr = 0;
void *msgQueue2_ptr = 0;
void* print_gdb_thread_func(void *data);
void* print_gdb_thread_func(void *data) {
	ALOGE("print_gdb_thread_func init");
	while (1) {
		if (unk2 != hSecOem_ptr->unk2) {
			unk2 = hSecOem_ptr->unk2;
			ALOGE("%s: hSecOem_ptr->unk2 was set to %x", __func__, unk2);
		}
		if (unk3 != hSecOem_ptr->unk3) {
			unk3 = hSecOem_ptr->unk3;
			ALOGE("%s: hSecOem_ptr->unk3 was set to %x", __func__, unk3);
		}
		if (unk4 != hSecOem_ptr->unk4) {
			unk4 = hSecOem_ptr->unk4;
			ALOGE("%s: hSecOem_ptr->unk4 was set to %x", __func__, unk4);
		}
		
		if (hSecOem_tmp != reader_init_param->hSecOem) {
			hSecOem_tmp = reader_init_param->hSecOem;
			ALOGE("%s: reader_init_param->hSecOem was set to %x", __func__, hSecOem_tmp);
		}		
		if (reader_dev_ptr != reader_init_param->reader_dev_ptr) {
			reader_dev_ptr = reader_init_param->reader_dev_ptr;
			ALOGE("%s: reader_init_param->reader_dev_ptr was set to %s", __func__, reader_dev_ptr);
		}
		if (msgQueue1_ptr != reader_init_param->msgQueue1_ptr) {
			msgQueue1_ptr = reader_init_param->msgQueue1_ptr;
			ALOGE("%s: reader_init_param->msgQueue1_ptr was set to %x", __func__, msgQueue1_ptr);
		}
		if (msgQueue2_ptr != reader_init_param->msgQueue2_ptr) {
			msgQueue2_ptr = reader_init_param->msgQueue2_ptr;
			ALOGE("%s: reader_init_param->msgQueue2_ptr was set to %x", __func__, msgQueue2_ptr);
		}
		
		//usleep(1000);
	}

    return NULL;
}

struct RIL_RadioFunctions *RIL_Init1(const struct RIL_Env *env, int argc, char **argv)
{
	const struct RIL_Env *rilEnv; // r7@1
	int c; // r6@1
	//void (__fastcall *tmp_func_ptr)(_DWORD); // r1@2
	int this_tid; // r0@4
	const char *msg; // r0@25
	char ril_tag2[4]; // r1@23
	int optarg_int; // r3@23
	const char *msg2; // r2@23
	int res0; // r0@31
	int dump_req_tag; // r1@35
	int res1; // r7@35
	int res2; // r6@36
	char ril_tag[4]; // r1@37
	const char *errmsg; // r2@37
	char ril_tag1[4]; // r1@39
	const char *errmsg1; // r2@39
	int res3; // r0@42
	unsigned long long ril_reatures; // [sp+0h] [bp-40h]@0
	char tmpVal[PROPERTY_VALUE_MAX]; // [sp+Fh] [bp-31h]@12
	char tmpVal1[PROPERTY_VALUE_MAX]; // [sp+10h] [bp-30h]@1
	pthread_t newthread; // [sp+14h] [bp-2Ch]@16
	memset(hSecOem_ptr, 0, 0x1EB8u);
#if 1
	ALOGE("%s: init (1)", __func__);

	rilEnv = env;
	tmpVal1[0] = 0;
	c = 0;
	
	ALOGE("%s: init (2)", __func__);
	/*do
	{
		tmp_func_ptr = *(void (__fastcall **)(_DWORD))((char *)&off_AA7C0 + c);
		c += 4;
		tmp_func_ptr(&hSecOem);
	}
	while ( c != 56 );*/
#endif
	OemInitNetwork(hSecOem_ptr);
	OemInitCall(hSecOem_ptr);
	OemInitData(hSecOem_ptr);
	OemInitSMS(hSecOem_ptr);
	OemInitSIM(hSecOem_ptr);
	OemInitSs(hSecOem_ptr);
	OemInitSound(hSecOem_ptr);
	OemInitMisc(hSecOem_ptr);
	OemInitStk(hSecOem_ptr);
	OemInitPower(hSecOem_ptr);
	OemInitGps(hSecOem_ptr);
	OemInitFactory(hSecOem_ptr);
	OemInitImei(hSecOem_ptr);
	OemInitCfg(hSecOem_ptr);	
	
#if 1
	ALOGE("%s: init (3)", __func__);

	hSecOem_ptr->unk1 = 1;
	ALOGE("%s: init (4)", __func__);
	pthread_mutex_init(unk_E71AC, 0);
	ALOGE("%s: init (5)", __func__);
	*unk_E71B0 = 0;
	ALOGE("%s: init (6)", __func__);
	if ( *bdbg_enable_ptr )
	{
		ALOGE("[*] RIL initialized: TID(%d)", gettid());
	}
	/*if ( *bdbg_enable_ptr )
	{
		ALOGE("RIL features: 0x%llx", *ril_features_E8F20);
	}
	ALOGE("%s: init (7)", __func__);*/
#endif
	*s_rilenv_ptr = &rilEnv;
#if 0
	ALOGE("%s: init (8)", __func__);
	property_get("ril.RildInit", &tmpVal1, *isRildInit_7DA7B_ptr);
	ALOGE("%s: init (9)", __func__);
	if ( *bdbg_enable_ptr )
		ALOGE("[RIL] IsRildInit? : %c", tmpVal1);
	if ( tmpVal1[0] == 49 )
	{
		if ( *bdbg_enable_ptr )
			ALOGE("*** Restart RIL Daemon ***");
		tmpVal[0] = 0;
		property_get("ril.rildreset", &tmpVal, *isRildInit_7DA7B_ptr);
		if ( *bdbg_enable_ptr )
			ALOGE("%s : Rild resetReason : %c", tmpVal);
		if (tmpVal[0] - 50 > 4u )
		{
			property_set("ril.rildreset", "1");
			property_get("ril.rildreset", &tmpVal, *isRildInit_7DA7B_ptr);
		}
		if ( pthread_create(&newthread, 0, get_rildreset_log, &tmpVal) < 0 && *bdbg_enable_ptr )
			ALOGE("[*] GetLog thread creation failed. Couldn't get rild reset log");
	}
#endif
#if 0
	ALOGE("%s: init (10)", __func__);
	Modem_Boot();
	ALOGE("%s: init (11)", __func__);
	while ( 1 )
	{
		res0 = getopt(argc, argv, "p:d:s:");
		ALOGE("%s: init (12)", __func__);
		if ( res0 == -1 )
		{
			ALOGE("%s: init (13)", __func__);
			if ( *dword_AB8F4 < 0 && !*dword_B1CA0_ptr ) {
				ALOGE("reference-ril requires: -p <tcp port> or -d /dev/tty_device");
				return NULL;
			}
			ALOGE("%s: init (14)", __func__);
			ipc_debug_init(hSecOem_ptr, 0x1C23);
			ALOGE("%s: init (15)", __func__);
			StartMulticlient(hSecOem_ptr);
			ALOGE("%s: init (16)", __func__);
			res1 = BuildupReqHandlerHash(hSecOem_ptr);
			ALOGE("%s: init (17)", __func__);
			if ( res1 )
				return NULL;
			//DumpRequestTable(0, dump_req_tag);				// dump_req_tag is in argv?
			ALOGE("%s: init (18)", __func__);
			res2 = InitEventHandling();
			if ( res2 )
			{
//LABEL_46:
				res2 = res1;
				ALOGE("Failed to initialize event system");
				return NULL;
			}
			ALOGE("%s: init (19)", __func__);
			res1 = InitRequestList(request_list_E71C4, FreeRequest);
			if ( res1 )
			{
				ALOGE("%s: init (fail 20)", __func__);
				//*(_DWORD *)ril_tag1 = "RIL";
				//errmsg1 = "Failed to create request list";
			}
			else
			{
				ALOGE("%s: init (20)", __func__);
				res2 = InitMsgQueue(freeRxData);
				ALOGE("%s: InitMsgQueue(1) returns %x", __func__, res2);
				reader_init_param->msgQueue1_ptr = (void*)res2;
				*unk_E71F8 = res2;
				ALOGE("%s: init (22)", __func__);
				if ( res2 )
				{
					ALOGE("%s: init (23)", __func__);
					res3 = InitMsgQueue(freeRxData);
					ALOGE("%s: InitMsgQueue(2) returns %x", __func__, res3);
					reader_init_param->msgQueue2_ptr = (void*)res3;
					res2 = res3;
					*unk_E71FC = res3;
					ALOGE("%s: init (25)", __func__);
					if ( res3 )
					{
						ALOGE("%s: init (26)", __func__);
						*unk_E97E0 = res3;
						ALOGE("%s: init (27)", __func__);
						reader_init_param->hSecOem = hSecOem_ptr;
						ALOGE("%s: init (28)", __func__);
						*unk_E97D8 = gElfPtr + 0x7e44a;
						//strcpy(unk_E97D8, "/dev/dpram0");
						reader_init_param->reader_dev_ptr = gElfPtr + 0x7e44a;
						ALOGE("%s: init (29), reader_dev_ptr = %s", __func__, reader_init_param->reader_dev_ptr);
						*unk_E97DC = *unk_E71F8;
						ALOGE("%s: init (30), bdbg_enable=%d", __func__, *bdbg_enable_ptr);
						*bdbg_enable_ptr = 1;
						//hSecOem_ptr->unk2 = gElfPtr + 0x7E44A;
						
	ALOGE("%s: () hSecOem->unk1=%x", __func__, hSecOem_ptr->unk1);
	ALOGE("%s: () hSecOem->unk2=%x", __func__, hSecOem_ptr->unk2);
	ALOGE("%s: () hSecOem->unk3=%x", __func__, hSecOem_ptr->unk3);
	ALOGE("%s: () hSecOem->unk4=%x", __func__, hSecOem_ptr->unk4);
	
						res2 = StartRXReader(reader_init_param);
						if ( res2 )
						{
							//*(_DWORD *)ril_tag = "RIL";
							//errmsg = "Failed to start RX reader thread";
							//goto LABEL_46;
							ALOGE("%s: Failed to start RX reader thread, res2=%d", __func__, res2);
							return NULL;
						}
						//ALOGE("%s: exit now", __func__);
						//return NULL;
						ALOGE("%s: init (31)", __func__);
						*dword_E71B4 = *unk_E97E4;
						*dword_E71B8 = *unk_E97E8;
						*unk_E71BC = *unk_E97EC;
						*unk_E9808 = request_list_E71C4;
						*unk_E980C = *unk_E71F8;
						*unk_E9810 = *unk_E71FC;
						*unk_E9814 = sub_23E5C;
						proc_init_param->hSecOem = hSecOem_ptr;
						ALOGE("%s: init (32)", __func__);
						ALOGE("%s: exit now", __func__);
						return origRilFunctions_AA368;
						//return origRilFunctions_AA368;
						if ( !StartRilProcessor(proc_init_param) )
						{
							ALOGE("%s: init (33)", __func__);
							*unk_E71B0 = 0;
							ALOGE("%s: init (34)", __func__);
							RIL_requestTimedCallback();
							ALOGE("%s: init (35)", __func__);
							return origRilFunctions_AA368;
						}
						ALOGE("Failed to start RIL processor thread");
					}
					else
					{
						ALOGE("Failed to create RFS data queue");
					}
				}
				else
				{
					ALOGE("Failed to create RX data queue");
				}
			}
			ALOGE("Failed to create request list");
			return NULL;
		}
		if ( res0 == 112 ) {
			optarg_int = atoi(optarg);
			*dword_AB8F4 = optarg_int;
			if ( !optarg_int )
			{
				ALOGE("reference-ril requires: -p <tcp port> or -d /dev/tty_device");
				return NULL;
			}

			ALOGE("Opening loopback port %d", optarg_int);
		} 
		if ( res0 == 115 )
		{
			*dword_B1CA4 = 1;
			//msg2 = "Opening socket %s\n";
			//optarg_int = atoi(optarg);
			//memcpy((void*)dword_B1CA0, (void*)optarg);
			*dword_B1CA0_ptr = optarg;
			ALOGE("Opening socket %s", optarg);
			//goto LABEL_28;
		}
		if ( res0 == 100 )
		{
			//optarg_int = atoi(optarg);
			//*dword_B1CA0 = optarg_int;
			//memcpy((void*)dword_B1CA0, (void*)optarg);
			*dword_B1CA0_ptr = optarg;
			ALOGE("Opening tty device %s", optarg);
			//msg2 = ;
			//goto LABEL_28;
		}
		
		//break;
	}

	//msg = "reference-ril requires: -p <tcp port> or -d /dev/tty_device\n";
//LABEL_30:
	//fputs(msg, (FILE *)((char *)&_sF + 168));
//LABEL_34:
	//fputs("reference-ril requires: -p <tcp port> or -d /dev/tty_device\n", (FILE *)((char *)&_sF + 168));
#endif
	return NULL;
}

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
	if (!mprotect(gBasePtr - 1, 0xab000, PROT_READ | PROT_WRITE | PROT_EXEC)) {
		ALOGE("%s: mprotect failed!", __func__);
	} else {
		ALOGE("%s: patching RIL_Init", __func__);
		
		// NOP OemInit*() calls
		//memcpy(gBasePtr - 1 + 0x247EE, "\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46", 14);
		
		// NOP s_rilenv_ptr assignment
		//memcpy(gBasePtr - 1 + 0x24856, "\x00\x46", 2);
		
		memcpy(gBasePtr - 1 + 0x247C6, "\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46", 100);
		
		memcpy(gBasePtr - 1 + 0x2482A,"\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46\x00\x46", 230);
	}
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
	ALOGE("%s: hSecOem->unk1=%x", __func__, hSecOem_ptr->unk1);
	ALOGE("%s: hSecOem->unk2=%x", __func__, hSecOem_ptr->unk2);
	ALOGE("%s: hSecOem->unk3=%x", __func__, hSecOem_ptr->unk3);
	ALOGE("%s: hSecOem->unk4=%x", __func__, hSecOem_ptr->unk4);
	
	/* RIL_Init */
	OemInitNetwork = gBasePtr + 0x2C608;
	OemInitCall = gBasePtr + 0x2576C;
	OemInitData = gBasePtr + 0x331AC;
	OemInitSMS = gBasePtr + 0x2A3AC;
	OemInitSIM = gBasePtr + 0x278FC;
	OemInitSs = gBasePtr + 0x2D674;
	OemInitSound = gBasePtr + 0x31E92;
	OemInitMisc = gBasePtr + 0x2E41C;
	OemInitStk = gBasePtr + 0x681E0;
	OemInitPower = gBasePtr + 0x24D38;
	OemInitGps = gBasePtr + 0x6725C;
	OemInitFactory = gBasePtr + 0x377C8;
	OemInitImei = gBasePtr + 0x35C3C;
	OemInitCfg = gBasePtr + 0x3550C;

	s_rilenv_ptr = gElfPtr + 0xE989C;
	unk_E71AC = gElfPtr + 0xE71AC;
	unk_E71B0 = gElfPtr + 0xE71B0;
	isRildInit_7DA7B_ptr = gElfPtr + 0x7DA7B;

	Modem_Boot  = gBasePtr + 0x22678;

	get_rildreset_log = gBasePtr + 0x23C14;
	dword_AB8F4 = gElfPtr + 0xAB8F4;
	dword_B1CA0_ptr = gElfPtr + 0xB1CA0;

	ipc_debug_init  = gBasePtr + 0x270A0;
	StartMulticlient = gBasePtr + 0x1DB30;
	BuildupReqHandlerHash = gBasePtr + 0x23510;
	InitEventHandling = gBasePtr + 0x200F8;

	request_list_E71C4 = gElfPtr + 0xE71C4;
	FreeRequest = gBasePtr + 0x238AE;
	InitRequestList = gBasePtr + 0x235D8;
	InitMsgQueue = gBasePtr + 0x202FC;

	//FreeRequest = gBasePtr + 0x;
	freeRxData = gBasePtr + 0x227EC;

	unk_E71F8 = gElfPtr + 0xE71F8;
	unk_E71FC = gElfPtr + 0xE71FC;
	unk_E97E0 = gElfPtr + 0xE97E0;

	reader_init_param = gElfPtr + 0xE97D4;

	unk_E97D8 = gElfPtr + 0xE97D8;
	unk_E97DC = gElfPtr + 0xE97DC;

	StartRXReader = gBasePtr + 0x222FC;

	dword_E71B4 = gElfPtr + 0xE71B4;
	unk_E97E4 = gElfPtr + 0xE97E4;

	dword_E71B8 = gElfPtr + 0xE71B8;
	unk_E97E8 = gElfPtr + 0xE97E8;
	unk_E71BC = gElfPtr + 0xE71BC;
	unk_E97EC = gElfPtr + 0xE97EC;
	unk_E9808 = gElfPtr + 0xE9808;
	unk_E980C = gElfPtr + 0xE980C;
	unk_E9810 = gElfPtr + 0xE9810;
	unk_E9814 = gElfPtr + 0xE9814;
	sub_23E5C = gBasePtr + 0x23E5C;
	proc_init_param = gElfPtr + 0xE9804;

	StartRilProcessor = gBasePtr + 0x218B8;

	ril_features_E8F20 = gElfPtr + 0xE8F20;
	origRilFunctions_AA368 = gElfPtr + 0xAA368;
	RIL_requestTimedCallback = gBasePtr + 0x24094;

	dword_AB8F4 = gElfPtr + 0xAB8F4;
	dword_B1CA4 = gElfPtr + 0xB1CA4;
	//dword_B1CA0_ptr = gElfPtr + 0xB1CA0;
}

void libEvtUnloading(void)
{
	if (origRil)
		 dlclose(origRil);
}
#endif
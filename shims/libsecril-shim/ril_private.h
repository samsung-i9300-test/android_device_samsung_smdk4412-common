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
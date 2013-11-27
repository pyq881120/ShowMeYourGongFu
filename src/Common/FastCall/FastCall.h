/**
 * @file FastCall.h
 * @author created by: Peter Hlavaty
 */

#ifndef __FASTCALL_H__
#define __FASTCALL_H__

#include "../base/Shared.h"

enum 
{
	FAST_CALL = 0x666,
	SYSCALL_TRACE_FLAG = 0x200,
	SYSCALL_HOOK,

	SYSCALL_PATCH_MEMORY,
	SYSCALL_DUMP_MEMORY,

	SYSCALL_ENUM_THREAD,
	SYSCALL_ENUM_MODULES,
	SYSCALL_ENUM_MEMORY,

	SYSCALL_GETPROCADDR,

	SYSCALL_SET_ADDRESS_BP,
	SYSCALL_UNSET_ADDRESS_BP,

	SYSCALL_SET_ACCESS_BP,
	SYSCALL_UNSET_ACCESS_BP,
	SYSCALL_SET_WRITE_BP,
	SYSCALL_UNSET_WRITE_BP,
	SYSCALL_SET_EXEC_BP,
	SYSCALL_UNSET_EXEC_BP,

	SYSCALL_INIT,
	

	SYSCALL_FREEZE_THREAD,
};

enum
{
//per reg INFO
	SYSCALL_ID = RAX,
	DBI_SYSCALL = RBX,

	//DBI_SEMAPHORE = RCX, -> semapthore is on IRET->StackPtr, in other word first ptr on stack is semaphore
	DBI_FUZZAPP_PROC_ID = RDX,

	DBI_FUZZAPP_THREAD_ID = R8, 
	DBI_PARAMS = R9,
};

#define DBI_FLAGS REG_COUNT

#define SYSCAL_CS_SEGEMENT 0x33 //by default intel -> rdmsr 0xC0000082 check few instructions {swapgs, swap r3 with r0 stack pointer, push [ss, r3:rsp, rflags, cs, r3:rip] }
#define SYSCAL_SS_SEGEMENT 0x2B //-||-

enum EnumSYSENTER
{
	SReturn = RCX,
	SFlags = R11
};

enum EnumTraceReason
{
	BranchTraceFlag = 0,
	SingleTraceFlag,
	Hook,
	MemoryAcces,
	ThreadSuspended,
	MemoryTouchByKernel
};

#pragma pack(push, 1)

template<class TYPE>
struct TYPE_X86COMPATIBLE
{
	union
	{
		ULONG64 uValue;
		TYPE Value;
	};
};

struct TRACE_INFO 
{
	PFIRET StateInfo;
	TYPE_X86COMPATIBLE<BYTE> Btf;
	TYPE_X86COMPATIBLE<const void*> PrevEip;
	TYPE_X86COMPATIBLE<ULONG_PTR> Reason;
};

struct MEMORY_ACCESS
{
	TYPE_X86COMPATIBLE<const void*> Memory;
	TYPE_X86COMPATIBLE<const void*> Begin;
	TYPE_X86COMPATIBLE<size_t> Size;
	TYPE_X86COMPATIBLE<ULONG> Flags;
	TYPE_X86COMPATIBLE<ULONG_PTR> OriginalValue;
};

struct DBI_OUT_CONTEXT
{
	ULONG_PTR GeneralPurposeContext[REG_COUNT + 1];
	TRACE_INFO TraceInfo;
	MEMORY_ACCESS MemoryInfo;
};

struct CID_ENUM
{
	TYPE_X86COMPATIBLE<HANDLE> ProcId;
	TYPE_X86COMPATIBLE<HANDLE> ThreadId;
};

struct MEMORY_ENUM
{
	TYPE_X86COMPATIBLE<const void*> Begin;
	TYPE_X86COMPATIBLE<size_t> Size;
	TYPE_X86COMPATIBLE<ULONG> Flags;
};

struct MODULE_ENUM
{
	TYPE_X86COMPATIBLE<const void*> ImageBase;
	TYPE_X86COMPATIBLE<size_t> ImageSize;
	TYPE_X86COMPATIBLE<bool> Is64;
	TYPE_X86COMPATIBLE<WCHAR[0x100]> ImageName;
};

struct PARAM_API
{
	TYPE_X86COMPATIBLE<const void*> ApiAddr;
	TYPE_X86COMPATIBLE<const void*> ModuleBase;
	TYPE_X86COMPATIBLE<CHAR[0x100]> ApiName;
};

struct PARAM_MEMCOPY
{
	TYPE_X86COMPATIBLE<const void*> Src;
	TYPE_X86COMPATIBLE<void*> Dst;
	TYPE_X86COMPATIBLE<size_t> Size;
};

struct PARAM_HOOK
{
	TYPE_X86COMPATIBLE<void*> HookAddr;
};

struct PARAM_MEM2WATCH
{
	TYPE_X86COMPATIBLE<const void*> Memory;
	TYPE_X86COMPATIBLE<size_t> Size;
};

#pragma pack(pop)

#endif //__FASTCALL_H__

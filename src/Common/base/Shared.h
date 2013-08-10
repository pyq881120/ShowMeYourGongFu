/**
 * @file Shared.h
 * @author created by: Peter Hlavaty
 */

#ifndef __SHARED_H__
#define __SHARED_H__

//------------------------------------------------------------------
// ****************** DEFINE PUSHAQ order of regs ******************
//------------------------------------------------------------------

enum RegSetx86
{
	RDI = 0, 
	RSI,
	RBP,
	RSP,
	RBX,
	RDX,
	RCX,
	RAX,
	REG_X86_COUNT
};

enum RegSetx64
{
	R15 = REG_X86_COUNT,
	R14,
	R13,
	R12,
	R11,
	R10,
	R9,
	R8,
	REG_X64_COUNT
};

#define REG_COUNT REG_X64_COUNT

enum RegFastCallX64Volatile
{
	VOLATILE_REG_RCX = 0,
	VOLATILE_REG_RDX,
	VOLATILE_REG_R8,
	VOLATILE_REG_R9,
	VOLATILE_REG_COUNT
};

#define HOOK_ORIG_RSP(reg) ((ULONG_PTR*)(reg[RSP]) + 2)//ENTER_HOOK_PROLOGUE + pushf
//compiler will handle this by optimalization
#define PPARAM(reg, num) (ULONG_PTR*)((num && num <= VOLATILE_REG_COUNT) ? (num < VOLATILE_REG_R8 ? &reg[RCX + num - 1 - VOLATILE_REG_RCX] : &reg[R8 + num - 1 - VOLATILE_REG_R8]) : (HOOK_ORIG_RSP(reg) + num))
#define PRETURN(reg) HOOK_ORIG_RSP(reg)

struct IRET
{
	const void* Return;
	ULONG_PTR CodeSegment;
	ULONG_PTR Flags;
};

#define PPAGE_FAULT_IRET(reg) reinterpret_cast<IRET*>(HOOK_ORIG_RSP(reg) + 1)//skip unknown param

#define ALIGN(addr, granularity)	(ULONG_PTR)((ULONG_PTR)addr & (~(granularity - 1)))

//--------------------------------------------------------------
// ****************** DEFINE TYPES -> based.h ******************
//--------------------------------------------------------------

// windows types
typedef unsigned long long  QWORD, *PQWORD, *LPQWORD;
typedef unsigned long	DWORD,	*PDWORD,	*LPDWORD;
typedef unsigned short	WORD,	*PWORD,		*LPWORD;
typedef unsigned char	BYTE,	*PBYTE,		*LPBYTE;
typedef unsigned int	UINT,	*PUINT,		*LPUINT;
typedef int				BOOL,	*PBOOL,		*LPBOOL;
typedef void					*PVOID,		*LPVOID;

typedef signed char SBYTE;
typedef signed short SWORD;
typedef signed long int SDWORD;

typedef char CHAR;
typedef wchar_t WCHAR;
typedef short SHORT;
typedef long LONG;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;

typedef BYTE BOOLEAN;

typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

typedef const void *LPCVOID;

#endif //__SHARED_H__

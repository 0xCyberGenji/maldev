#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

#pragma once
#define STATUS_SUCCESS (NTSTATUS)0x00000000L
#define okay(MSG, ...) printf("[+] " MSG "\n", ##__VA_ARGS__)
#define info(MSG, ...) printf("[i] " MSG "\n", ##__VA_ARGS__)
#define warn(MSG, ...) printf("[-] " MSG "\n", ##__VA_ARGS__)

#pragma region STRUCTURES


/* *** => PARAMETERS <= *** */

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG Length;                                                           //0x0
    VOID* RootDirectory;                                                    //0x8
    struct _UNICODE_STRING* ObjectName;                                     //0x10
    ULONG Attributes;                                                       //0x18
    VOID* SecurityDescriptor;                                               //0x20
    VOID* SecurityQualityOfService;                                         //0x28
} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;

typedef struct _PS_ATTRIBUTE {
	ULONGLONG Attribute;				
	SIZE_T Size;						
	union {
		ULONG_PTR Value;				
		PVOID ValuePtr;					
	};
	PSIZE_T ReturnLength;				
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST
{
    SIZE_T       TotalLength;
    PS_ATTRIBUTE Attributes[1];
} PS_ATTRIBUTE_LIST, * PPS_ATTRIBUTE_LIST;

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

/* *** => FUNCTIONS <= *** */

typedef NTSTATUS(NTAPI* fn_NtOpenProcess) (
    OUT PHANDLE ProcessHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes,
    IN PCLIENT_ID ClientId OPTIONAL
);

typedef NTSTATUS(NTAPI* fn_NtAllocateVirtualMemory) (
    IN HANDLE ProcessHandle,
    IN OUT PVOID* BaseAddress,
    IN ULONG ZeroBits,
    IN OUT PSIZE_T RegionSize,
    IN ULONG AllocationType,
    IN ULONG Protect
);

typedef NTSTATUS(NTAPI* fn_NtWriteVirtualMemory) (
    IN HANDLE ProcessHandle,
    IN PVOID BaseAddress,
    IN PVOID Buffer,
    IN SIZE_T NumberOfBytesToWrite,
    OUT PSIZE_T NumberOfBytesWritten OPTIONAL
);

typedef NTSTATUS(NTAPI* fn_NtCreateThreadEx) (
    OUT PHANDLE ThreadHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
    IN HANDLE ProcessHandle,
    IN PVOID StartRoutine,
    IN PVOID Argument OPTIONAL,
    IN ULONG CreateFlags,
    IN SIZE_T ZeroBits,
    IN SIZE_T StackSize,
    IN SIZE_T MaximumStackSize,
    IN PPS_ATTRIBUTE_LIST AttributeList OPTIONAL
);

typedef NTSTATUS(NTAPI* fn_NtWaitForSingleObject) (
    _In_ HANDLE Handle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);

typedef NTSTATUS(NTAPI* fn_NtClose) (
    IN HANDLE Handle
);

#pragma endregion
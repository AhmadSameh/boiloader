#ifndef UEFI_DATA_H
#define UEFI_DATA_H

typedef enum { FALSE, TRUE } BOOLEAN;

#define IN
#define OUT
#define EFIAPI __attribute__((ms_abi))

typedef signed char          INT8;
typedef unsigned char        UINT8;
typedef signed short         INT16;
typedef unsigned short       UINT16;
typedef signed int           INT32;
typedef unsigned int         UINT32;
typedef signed long          INT64;
typedef unsigned long        UINT64;
typedef signed long          INTN;
typedef unsigned long        UINTN;

typedef signed char          CHAR8;
typedef signed short         CHAR16;
typedef unsigned short       UCHAR16;

typedef signed int           CHAR32;

typedef void                 VOID;

#endif

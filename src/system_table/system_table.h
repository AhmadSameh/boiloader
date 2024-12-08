#ifndef SYSTEM_TABLE_H
#define SYSTEM_TABLE_H

#include "uefi_data.h"
#include "status.h"

#include "protocols/console/output.h"
#include "protocols/console/input.h"

// Defined in 4.2.1:89 in UEFI spec
// Data structure that precedes all of the standard EFI table types.
typedef struct {
    UINT64 signature;
    UINT32 revision;
    UINT32 header_size;
    UINT32 CRC32;
    UINT32 reserved;
} EFI_TABLE_HEADER;

// Defined in 4.3.1:91 in UEFI spec
// Contains pointers to the runtime and boot services tables.
typedef struct {
    EFI_TABLE_HEADER                  header;
    CHAR16 *                          firmware_vendor;
    UINT32                            firmware_revision;
    EFI_HANDLE                        console_input_handle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *  console_input;
    EFI_HANDLE                        console_output_handle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL * console_output;
} EFI_SYSTEM_TABLE;

#endif

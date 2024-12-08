#ifndef OUTPUT_H
#define OUTPUT_H

#include "uefi_data.h"

// Globally Unique Identifier -> (DEADBEEF-1234-5678-9ABC-DEF123456789)
#define EFI_SIMPLE_TEXT_OUTPUT_GUID {0x387477c2,0x69c7,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b} }

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// 12.4.2 -> Resets the text output device hardware.
typedef EFI_STATUS (*EFI_TEXT_RESET) (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output, BOOLEAN extended_verification);

// 12.4.3:400 -> Writes a string to the output device.
typedef EFI_STATUS (*EFI_TEXT_STRING) ( EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output, UCHAR16 *string);

// Defined in 12.4.1:399 in UEFI spec
// Used to control text-based output devices.
typedef struct {
    INT32   max_mode;
    // Settings
    INT32   mode;
    INT32   attribute;
    INT32   cursor_column;
    INT32   cursor_row;
    BOOLEAN cursor_visible;
} SIMPLE_TEXT_OUTPUT_MODE;

// Defined in 12.4.1:398 in UEFI spec
// This protocol is used to control text-based output devices.
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET               reset;
    EFI_TEXT_STRING              output_string;
#if 0
    EFI_TEXT_TEST_STRING         test_string;
    EFI_TEXT_QUERY_MODE          query_mode;
    EFI_TEXT_SET_MODE            set_mode;
    EFI_TEXT_SET_ATTRIBUTE       set_attribute;
    EFI_TEXT_CLEAR_SCREEN        clear_screen;
    EFI_TEXT_SET_CURSOR_POSITION set_cursor_position;
    EFI_TEXT_ENABLE_CURSOR       enable_cursor;
    SIMPLE_TEXT_OUTPUT_MODE *    mode;
#endif 
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#endif

#ifndef INPUT_H
#define INPUT_H

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID  {0x387477c1,0x69c7,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b} }

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL_ EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (*EFI_INPUT_RESET) (EFI_SIMPLE_TEXT_INPUT_PROTOCOL *efi_input_protocol, BOOLEAN extended_verification);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL_ {
    EFI_INPUT_RESET    reset;
#if 0
    EFI_INPUT_READ_KEY read_key_stroke;
    EFI_EVENT          wait_for_key
#endif
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

#endif
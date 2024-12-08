#include "status.h"
#include "system_table/system_table.h"

EFI_STATUS boiloader_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE* system_table) {
    // Clear screen buffer
    system_table->console_output->reset(system_table->console_output, 1);

    // Print to the screen
    system_table->console_output->output_string(system_table->console_output, u"Hey Fam, boiloader is running!\r\n");

    while(1);

    return EFI_SUCCESS;
}

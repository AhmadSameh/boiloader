#ifndef OUTPUT_H
#define OUTPUT_H

#include "uefi_data.h"

// Globally Unique Identifier -> (DEADBEEF-1234-5678-9ABC-DEF123456789)
#define EFI_SIMPLE_TEXT_OUTPUT_GUID {0x387477c2,0x69c7,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b} }

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

/**
 * @brief Resets the text output device hardware.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type
 * EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL is defined in the “Related Definitions” of
 * EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.
 * @param extended_verification
 * Indicates that the driver may perform a more exhaustive verification operation of the device
 * during reset.
 *
 * @returns
 * - #EFI_SUCCESS        The text output device was reset.
 * - #EFI_DEVICE_ERROR   The text output device is not functioning correctly and could not be reset.
 *
 * @details
 * The reset() function resets the text output device hardware. The cursor position is set to (0, 0), and the screen is
 * cleared to the default background color for the output device.
 *
 * As part of initialization process, the firmware/device will make a quick but reasonable attempt to verify that the device
 * is functioning. If the ExtendedVerification flag is TRUE the firmware may take an extended amount of time to verify
 * the device is operating on reset. Otherwise the reset operation is to occur as quickly as possible.
 *
 * The hardware verification process is not defined by this specification and is left up to the platform firmware or driver
 * to implement.
 *
 * @see UEFI specs 12.4.2:400
 **/
typedef EFI_STATUS (EFIAPI *EFI_TEXT_RESET) (   IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol,
                                                IN BOOLEAN extended_verification);

/**
 * @brief Writes a string to the output device.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
 * is defined in the “Related Definitions” of Simple Text Output Protocol.
 * @param string
 * The Null-terminated string to be displayed on the output device(s). All output devices must also support the
 * Unicode drawing character codes defined in "Related Definitions."
 *
 * @returns
 * - #EFI_SUCCESS               The string was output to the device.
 * - #EFI_DEVICE_ERROR          The device reported an error while attempting to output the text.
 * - #EFI_UNSUPPORTED           The output device’s mode is not currently in a defined text mode.
 * - #EFI_WARN_UNKNOWN_GLYPH    This warning code indicates that some of the characters in the string could
 *                              not be rendered and were skipped.
 *
 * @details
 * The EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.output_string() function writes a string to the output
 * device. This is the most basic output mechanism on an output device. The String is displayed at the current cursor
 * location on the output device(s) and the cursor is advanced according to the rules listed in EFI Cursor
 * Location/Advance Rules.
 *
 * @note
 * If desired, the system’s NVRAM environment variables may be used at install time to determine the configured
 * locale of the system or the installation procedure can query the user for the proper language support. This is then
 * used to either install the proper EFI image/loader or to configure the installed image’s strings to use the proper text
 * for the selected locale.
 *
 * @see UEFI specs 12.4.3:400
 * @see Table 12.10 for EFI Cursor Location/Advance Rules.
 * TODO: add a "see" comment after defining the UNICODE drawing characters.
 **/
typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING) (  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol,
                                                IN UCHAR16 *string);

/**
 * @brief Verifies that all characters in a string can be output to the target device.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
 * is defined in the “Related Definitions” of Simple Text Output Protocol.
 * @param string
 * The Null-terminated string to be examined for the output device(s).
 *
 * @returns
 * - #EFI_SUCCESS       The device(s) are capable of rendering the output string.
 * - #EFI_UNSUPPORTED   Some of the characters in the string cannot be rendered by one or more of
 *                      the output devices mapped by the EFI handle.
 *
 * @details
 * The test_string() function verifies that all characters in a string can be output to the target device.
 *
 * This function provides a way to know if the desired character codes are supported for rendering on the
 * output device(s). This allows the installation procedure (or EFI image) to at least select character codes
 * that the output devices are capable of displaying. Since the output device(s) may be changed between
 * boots, if the loader cannot adapt to such changes it is recommended that the loader call
 * EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.output_string() with the text it has and ignore any “unsupported” error
 * codes. Devices that are capable of displaying the Unicode character codes will do so
 *
 * @see UEFI specs 12.4.4:403
 **/
typedef EFI_STATUS (EFIAPI *EFI_TEXT_TEST_STRING) ( IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol,
                                                    IN CHAR16 *string);

/**
 * @brief Returns information for an available text mode that the output device(s) supports.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
 * is defined in the “Related Definitions” of Simple Text Output Protocol.
 * @param mode_number
 * The mode number to return information on.
 *
 * @param columns @param rows
 * Returns the geometry of the text output device for the request ModeNumber.
 *
 * @returns
 * - #EFI_SUCCESS       The requested mode information was returned.
 * - #EFI_DEVICE_ERROR  The device had an error and could not complete the request.
 * - #EFI_UNSUPPORTED   The mode number was not valid.
 *
 * @details
 * The query_mode() function returns information for an available text mode that the output device(s) supports.
 * It is required that all output devices support at least 80x25 text mode. This mode is defined to be mode 0. If the output
 * devices support 80x50, that is defined to be mode 1. All other text dimensions supported by the device will follow as
 * modes 2 and above. If an output device supports modes 2 and above, but does not support 80x50, then querying for
 * mode 1 will return EFI_UNSUPPORTED .
 *
 * @see UEFI specs 12.4.5:403
 **/
typedef EFI_STATUS (EFIAPI *EFI_TEXT_QUERY_MODE) (  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol,
                                                    IN UINTN mode_number,
                                                    OUT UINTN *columns,
                                                    OUT UINTN *rows);

/**
 * @brief Sets the output device(s) to a specified mode.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
 * is defined in the “Related Definitions” of Simple Text Output Protocol.
 * @param mode_number
 * The text mode to set.
 *
 * @returns
 * - #EFI_SUCCESS       The requested text mode was set.
 * - #EFI_DEVICE_ERROR  The device had an error and could not complete the request.
 * - #EFI_UNSUPPORTED   The mode number was not valid.
 *
 * @details
 * The set_mode() function sets the output device(s) to the requested mode. On success the device is in the geometry for
 * the requested mode, and the device has been cleared to the current background color with the cursor at (0,0).
 *
 * @see UEFI specs 12.4.6:404
 **/
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_MODE) (IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol,
                                                IN UINTN mode_number);

/**
 * @brief Sets the background and foreground colors for the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.output_string()
 *        and EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.clear_screen() functions.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
 * is defined in the “Related Definitions” of Simple Text Output Protocol.
 * @param attribute
 * The attribute to set. Bits 0..3 are the foreground color, and bits 4..6 are the background color.
 * All other bits are reserved.
 *
 * @returns
 * - #EFI_SUCCESS       The requested attributes were set.
 * - #EFI_DEVICE_ERROR  The device had an error and could not complete the request.
 *
 * @details
 * The set_attribute() function sets the background and foreground colors for the
 * EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.output_string() and EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.clear_screen() functions.
 *
 * @see UEFI specs 12.4.7:405
 * TODO: add a see comment after defining the attributes
 **/
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (   IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol,
                                                        IN UINTN attribute);


/**
 * @brief Clears the output device(s) display to the currently selected background color.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
 * is defined in the “Related Definitions” of Simple Text Output Protocol.
 *
 * @details
 * The clear_screen() function clears the output device(s) display to the currently selected background color.
 * The cursor position is set to (0, 0).
 *
 * @returns
 * - #EFI_SUCCESS       The operation completed successfully.
 * - #EFI_DEVICE_ERROR  The device had an error and could not complete the request.
 * - #EFI_UNSUPPORTED   The output device is not in a valid text mode.
 *
 * @see 12.4.8:406
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_CLEAR_SCREEN) ( IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol);

/**
 * @brief Sets the current coordinates of the cursor position.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
 * is defined in the “Related Definitions” of Simple Text Output Protocol.
 *
 * @param column @param row
 * The position to set the cursor to. Must be greater than or equal to zero and less than the number of
 * columns and rows returned by EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.query_mode().
 *
 * @details
 * The set_cursor_position() function sets the current coordinates of the cursor position.
 * The upper left corner of the screen is defined as coordinate (0, 0).
 *
 * @returns
 * - #EFI_SUCCESS       The operation completed successfully.
 * - #EFI_DEVICE_ERROR  The device had an error and could not complete the request.
 * - #EFI_UNSUPPORTED   The output device is not in a valid text mode, or the cursor position is invalid
 *                      for the current mode.
 *
 * @see 12.4.9:407
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) ( IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol,
                                                            IN UINTN column,
                                                            IN UINTN row);

/**
 * @brief Makes the cursor visible or invisible.
 *
 * @param efi_output_protocol
 * A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL instance. Type EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
 * is defined in the “Related Definitions” of Simple Text Output Protocol.
 *
 * @param column @param row
 * If @e TRUE, the cursor is set to be visible. If @e FALSE, the cursor is set to be invisible.
 *
 * @details
 * The enable_cursor() function makes the cursor visible or invisible.
 *
 * @returns
 * - #EFI_SUCCESS       The operation completed successfully.
 * - #EFI_DEVICE_ERROR  The device had an error and could not complete the request or the device
 *                      does not support changing the cursor mode.
 * - #EFI_UNSUPPORTED   The output device does not support visibility control of the cursor.
 *
 * @see 12.4.10:407
 */
typedef EFI_STATUS (EFIAPI *EFI_TEXT_ENABLE_CURSOR) (   IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *efi_output_protocol,
                                                        IN BOOLEAN visiblel);

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
    EFI_TEXT_TEST_STRING         test_string;
    EFI_TEXT_QUERY_MODE          query_mode;
    EFI_TEXT_SET_MODE            set_mode;
    EFI_TEXT_SET_ATTRIBUTE       set_attribute;
    EFI_TEXT_CLEAR_SCREEN        clear_screen;
    EFI_TEXT_SET_CURSOR_POSITION set_cursor_position;
    EFI_TEXT_ENABLE_CURSOR       enable_cursor;
    SIMPLE_TEXT_OUTPUT_MODE *    mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#endif

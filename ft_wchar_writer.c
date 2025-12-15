#include "ft_printf.h"

/**
 * @brief Writes a 2-byte UTF-8 encoded wide character to standard output.
 *
 * This helper function encodes a wide character `wc` into its corresponding
 * 2-byte UTF-8 representation and writes it to the standard output (file descriptor 1).
 * The number of bytes written is added to the `counter` field of the provided `t_data` structure.
 *
 * @param wchar The wide character to encode and write.
 * @param data  Pointer to a t_data structure that holds parsing state and flags.
 */
static void write_wchar_2(wchar_t wchar, t_data *data)
{
    char wc_arr[2];

    wc_arr[0] = ((wchar >> 6) + 192);
    wc_arr[1] = ((wchar & 63) + 128);
    data->counter += write(1, wc_arr, 2);
}

/**
 * @brief Writes a 3-byte UTF-8 encoded wide character to standard output.
 *
 * This helper function encodes a wide character `wc` into its corresponding
 * 3-byte UTF-8 representation and writes it to the standard output (file descriptor 1).
 * The number of bytes written is added to the `counter` field of the provided `t_data` structure.
 *
 * @param wchar The wide character to encode and write.
 * @param data  Pointer to a t_data structure that holds parsing state and flags.
 */
static void write_wchar_3(wchar_t wchar, t_data *data)
{
    char wc_arr[3];

    wc_arr[0] = ((wchar >> 12) + 224);
    wc_arr[1] = (((wchar >> 6) & 63) + 128);
    wc_arr[2] = ((wchar & 63) + 128);
    data->counter += write(1, wc_arr, 3);
}

/**
 * @brief Writes a 4-byte UTF-8 encoded wide character to standard output.
 *
 * This helper function encodes a wide character `wc` into its corresponding
 * 4-byte UTF-8 representation and writes it to the standard output (file descriptor 1).
 * The number of bytes written is added to the `counter` field of the provided `t_data` structure.
 *
 * @param wchar The wide character to encode and write.
 * @param data  Pointer to a t_data structure that holds parsing state and flags.
 */
static void write_wchar_4(wchar_t wchar, t_data *data)
{
    char wc_arr[4];

    wc_arr[0] = ((wchar >> 18) + 240);
    wc_arr[1] = (((wchar >> 12) & 63) + 128);
    wc_arr[2] = (((wchar >> 6) & 63) + 128);
    wc_arr[3] = ((wchar & 63) + 128);
    data->counter += write(1, wc_arr, 4);
}

/**
 * @brief Processes and writes a wide character (wchar_t) to standard output in UTF-8 encoding.
 *
 * This function takes a wide character `wc` and encodes it into its corresponding UTF-8 byte sequence,
 * then writes the encoded bytes to the standard output (file descriptor 1). The number of bytes written
 * is added to the `counter` field of the provided `t_data` structure.
 *
 * The function handles the following Unicode code point ranges:
 * - 0 to 255: Writes the character as a single byte (ASCII/extended ASCII).
 * - 128 to 2047: Encodes and writes as a 2-byte UTF-8 sequence.
 * - 2048 to 65535: Encodes and writes as a 3-byte UTF-8 sequence.
 * - 65536 to 1114111: Encodes and writes as a 4-byte UTF-8 sequence.
 *
 * @param wchar The wide character to process and write.
 * @param data  Pointer to a t_data structure that holds parsing state and flags.
 */
void ft_wchar_writer(wchar_t wchar, t_data *data)
{
    if (wchar >= 0 && wchar <= 255)
        data->counter += write(1, &wchar, 1);
    else if (wchar >= 128 && wchar <= 2047)
        write_wchar_2(wchar, data);
    else if (wchar >= 2048 && wchar <= 65535)
        write_wchar_3(wchar, data);
    else if (wchar >= 65536 && wchar <= 1114111)
        write_wchar_4(wchar, data);
}
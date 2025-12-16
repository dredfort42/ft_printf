#include "ft_printf.h"

/*
 * The 'c' conversion specifier in printf is used to print a single character.
 * Usage examples with different flags:
 *
 * 1. Basic usage:
 *    printf("%c", 'A'); // Output: A
 *
 * 2. Field width:
 *    printf("%5c", 'A'); // Output: "    A" (A is right-aligned in a field of width 5)
 *
 * 3. Left alignment with '-' flag:
 *    printf("%-5c", 'A'); // Output: "A    " (A is left-aligned in a field of width 5)
 *
 * 4. Using length modifier 'l' for wide characters:
 *    printf("%lc", L'Æ'); // Output: Æ (prints a wide character)
 *
 * Note: Precision and zero-padding flags are ignored for the 'c' specifier.
 */

/**
 * @brief Writes a single character to the output and updates the counter.
 *
 * @param c    The character to write.
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 */
static void ft_processing_c(char c, t_data *data)
{
	data->counter += write(1, &c, 1);
}

/**
 * @brief Handles the 'c' and wide character conversion specifiers in the format string.
 *
 * This function processes the 'c' conversion specifier, applying any
 * specified flags, width, and precision from the t_data structure.
 * It updates the counter in the t_data structure to reflect the number
 * of characters printed.
 *
 * @param arg    The variadic argument list to extract values from.
 * @param data   Pointer to a t_data structure that holds parsing state and flags.
 */
static void ft_handle_char_conversion(va_list arg, t_data *data)
{
	if (data->len < 0)
	{
		data->minus = 1;
		data->len *= -1;
	}
	if (!data->minus)
	{
		while (data->len-- > 1)
			data->counter += write(1, " ", 1);
	}
	if (!data->l)
		ft_processing_c(va_arg(arg, int), data);
	else
		ft_wchar_writer(va_arg(arg, wint_t), data);
	if (data->minus)
	{
		while (data->len-- > 1)
			data->counter += write(1, " ", 1);
	}
}

/**
 * @brief Handles the 'c' conversion specifier in the format string.
 *
 * This function processes the 'c' conversion specifier, applying any
 * specified flags, width, and precision from the t_data structure.
 * It updates the counter in the t_data structure to reflect the number
 * of characters printed.
 *
 * @param arg    The variadic argument list to extract values from.
 * @param format The format string being parsed.
 * @param data   Pointer to a t_data structure that holds parsing state and flags.
 */
void ft_conversion_c(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'c')
		ft_handle_char_conversion(arg, data);
}

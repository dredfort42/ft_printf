#include "ft_printf.h"

static char *ft_processing_u(unsigned long long num, t_data *data)
{
	char *rtn;
	short digits_count;

	if (data->h)
		num = (unsigned short)num;
	if (data->hh)
		num = (unsigned char)num;
	digits_count = ft_digits_in_number(num, 10);
	if (!digits_count)
		digits_count = 1;
	rtn = ft_memory_p((digits_count + 1), data);
	rtn[digits_count--] = '\0';
	if (!num)
		rtn[digits_count--] = '0';
	while (num)
	{
		if (num > 9)
			rtn[digits_count] = '0' + (num % 10);
		else
			rtn[digits_count] = '0' + num;
		num /= 10;
		digits_count--;
	}
	return (rtn);
}

static char *ft_processing_di(long long num, t_data *data)
{
	char *rtn;
	short num_is_negative;

	if (data->h)
		num = (short)num;
	if (data->hh)
		num = (char)num;
	num_is_negative = 0;
	if (num < 0)
	{
		num_is_negative = 1;
		num *= -1;
	}
	rtn = ft_processing_u(num, data);
	if (num_is_negative)
		rtn = ft_negative_di(rtn, data);
	if (!num_is_negative && data->plus)
		rtn = ft_positive_di(rtn, data);
	if (!num_is_negative && !data->plus && data->space)
		rtn = ft_space_di(rtn, data);
	return (rtn);
}

static void ft_prepare_di_processing(va_list arg, t_data *data)
{
	if (!data->l && !data->ll)
		ft_magic_diuxX(ft_processing_di(va_arg(arg, int), data), data);
	if (data->l)
		ft_magic_diuxX(ft_processing_di(va_arg(arg, long), data), data);
	if (data->ll)
		ft_magic_diuxX(ft_processing_di(va_arg(arg, long long), data),
					   data);
}

static void ft_prepare_u_processing(va_list arg, t_data *data)
{
	if (!data->l && !data->ll)
		ft_magic_diuxX(ft_processing_u(va_arg(arg, unsigned), data),
					   data);
	if (data->l)
		ft_magic_diuxX(ft_processing_u(va_arg(arg, unsigned long), data),
					   data);
	if (data->ll)
		ft_magic_diuxX(ft_processing_u(va_arg(arg, unsigned long long),
									   data),
					   data);
}

/**
 * Handles the 'd', 'i', and 'u' conversion specifiers for the printf function.
 *
 * Description:
 * - 'd' and 'i': Print signed decimal integers. Both specifiers are functionally identical.
 * - 'u': Prints unsigned decimal integers.
 *
 * Supported Flags and Their Effects:
 * - '+': Forces a sign (+ or -) to be used on a number.
 * - ' ': (space) If no sign is going to be written, a blank space is inserted before the value.
 * - '-': Left-justify within the given field width; Right justification is the default.
 * - '0': Left-pads the number with zeros instead of spaces when padding is specified.
 * - Field Width: Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded.
 * - Precision: For integer conversions, precision specifies the minimum number of digits to appear. If the value has fewer digits, it is padded with leading zeros.
 *
 * Usage Examples:
 *   printf("%d", -42);        // Output: -42
 *   printf("%+d", 42);        // Output: +42
 *   printf("% i", 42);        // Output: ` 42` (with a leading space)
 *   printf("%05d", 42);       // Output: 00042
 *   printf("%-5u", 42);       // Output: `42   ` (left-justified, padded with spaces)
 *   printf("%.3i", 7);        // Output: 007
 *
 * Notes:
 * - For 'u', negative values are converted to their unsigned representation.
 *   printf("%u", -1);    // Output: 4294967295 (on systems where unsigned int is 32 bits)
 *
 * - Length modifiers (e.g., 'l', 'll', 'h', 'hh') can be used to specify the size of the argument.
 */

void ft_conversion_diu(va_list arg, const char *format, t_data *data)
{
	if (data->len < 0)
	{
		data->minus = 1;
		data->len *= -1;
	}
	if (data->minus)
		data->zero = 0;
	if (format[data->index] == 'd' || format[data->index] == 'i')
		ft_prepare_di_processing(arg, data);
	if (format[data->index] == 'u')
		ft_prepare_u_processing(arg, data);
}

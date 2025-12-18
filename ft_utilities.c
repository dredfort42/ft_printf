#include "ft_printf.h"

/**
 * @brief Reads a number from the format string and updates the index accordingly.
 *
 * This function parses a sequence of digit characters from the format string
 * starting at the current index (data->index) and converts them into an integer.
 * The resulting integer is stored in the variable pointed to by 'num'.
 * The index is updated to point to the character immediately following the
 * last digit processed.
 *
 * @param format The format string being parsed.
 * @param data   Pointer to a t_data structure that holds the current parsing state.
 * @param num    Pointer to an integer where the parsed number will be stored.
 */
void ft_read_number(const char *format, t_data *data, int *num)
{
	while (format[data->index] >= '0' && format[data->index] <= '9')
	{
		*num *= 10;
		*num += format[data->index] - '0';
		data->index++;
	}
	data->index--;
}

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * @param str The input string whose length is to be calculated.
 * @return The length of the string as a long integer.
 */
long ft_strlen(char *str)
{
	long i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief Calculates the number of digits in the integer part of a floating-point number for a given base.
 *
 * @param f    The floating-point number whose integer part is to be evaluated.
 * @param base The numerical base for digit calculation (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The number of digits in the integer part of the number.
 */
short ft_digits_in_number(long double f, short base)
{
	short i;
	unsigned long long num;

	if (f < 0)
		f = -f;
	num = (unsigned long long)f;
	i = 0;
	while (num)
	{
		num /= base;
		i++;
	}
	return (i);
}

char *ft_capitalizer(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

/**
 * @brief Converts an unsigned long long integer to its hexadecimal string representation.
 *
 * @param rtn           Pointer to the buffer where the resulting hexadecimal string will be stored.
 * @param num           The unsigned long long integer to convert to hexadecimal.
 * @param digits_count  Pointer to a short where the function will store the number of digits in the hexadecimal representation.
 */
void ft_hex(char *rtn, unsigned long long num, short *digits_count)
{
	char *hex;

	hex = "0123456789abcdef";
	while (num)
	{
		rtn[*digits_count] = hex[(num % 16)];
		num /= 16;
		*digits_count -= 1;
	}
}

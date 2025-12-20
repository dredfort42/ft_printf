#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

#include "libft/libft.h"

#define SUCCESS 0
#define ERROR -1

#define TRUE 1
#define FALSE 0

typedef struct s_printf_state
{
	int printed_chars; // Total number of characters printed
	long format_pos;   // Current position in the format string
	short has_error;   // Error flag
	int precision;	   // Precision after '.' in format specifier
	int field_width;   // Field width before conversion
	short flag_minus;  // '-' flag - left justify
	short flag_zero;   // '0' flag - zero padding
	short flag_hash;   // '#' flag - alternate form
	short flag_space;  // ' ' flag - space before positive numbers
	short flag_plus;   // '+' flag - always show sign
} t_printf_state;

int ft_printf(const char *format, ...);
void ft_parsing(va_list arg, const char *format, t_printf_state *state);
void ft_handle_percent_conversion(const char *format, t_printf_state *state);
void ft_handle_char_conversion(va_list arg, const char *format, t_printf_state *state);
void ft_handle_string_conversion(va_list arg, const char *format, t_printf_state *state);
void ft_handle_pointer_conversion(va_list arg, const char *format, t_printf_state *state);
void ft_handle_signed_integer_conversion(va_list arg, const char *format, t_printf_state *state);

char *ft_apply_precision_to_number(char *num_str, int precision, int is_negative);
void ft_print_formatted_number(char *str, int str_len, int padding, t_printf_state *state);

#endif // FT_PRINTF_H

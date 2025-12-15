#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

#define SUCCESS 0
#define ERROR -1

#define TRUE 1
#define FALSE 0

typedef struct s_data
{
	int counter;
	long index;
	short error;
	short space;
	short minus;
	short plus;
	short sharp;
	short zero;
	int len;
	int precision;
	short l;
	short ll;
	short h;
	short hh;
} t_data;

union u_ld
{
	long double ld;
	struct
	{
		unsigned long long mantissa : 64;
		unsigned exponent : 15;
		unsigned short sign : 1;
	} s_bits;
} u_bits;

char *ft_memory_p(int size, t_data *data);
short ft_is_flag(char chr);
short ft_is_conversion(char chr);
void ft_read_number(const char *format, t_data *data, int *num);
long ft_strlen(char *str);
short ft_digits_in_number(long double f, short base);
char *ft_capitalizer(char *str);
char *ft_c_space_str(t_data *data);
char *ft_f_space_str(t_data *data);
char *ft_inf_str(short minus, t_data *data);
char *ft_nan_str(t_data *data);
short ft_is_nan(va_list arg);
wchar_t *ft_null_str(t_data *data, short *is_empty);
void ft_hex(char *rtn, unsigned long long num, short *digits_count);
char *ft_trim_trailing_e_zeros(char *str);
char *ft_trim_trailing_f_zeros(char *str);
short ft_precision_adjustment(long double f);
short ft_dot_in_str(char *str);
void ft_power_e_g(long double f, short *precision, short *e);
void ft_conversion_c(va_list arg, const char *format, t_data *data);
void ft_conversion_s(va_list arg, const char *format, t_data *data);
void ft_conversion_p(va_list arg, const char *format, t_data *data);
void ft_conversion_diu(va_list arg, const char *format, t_data *data);
char *ft_negative_di(char *str, t_data *data);
char *ft_positive_di(char *str, t_data *data);
char *ft_space_di(char *str, t_data *data);
void ft_conversion_x(va_list arg, const char *format, t_data *data);
void ft_conversion_X(va_list arg, const char *format, t_data *data);
void ft_conversion_n(va_list arg, const char *format, t_data *data);
void ft_conversion_f(va_list arg, const char *format, t_data *data);
char *ft_whole_part_f(unsigned long long num, t_data *data);
char *ft_fractional_part_f(long double f, t_data *data);
char *ft_f_join(short minus, char *str1, char *str2, t_data *data);
void ft_conversion_e(va_list arg, const char *format, t_data *data);
char *ft_e_join(char *s1, char *s2, t_data *data);
char *ft_e_str(short *e, t_data *data);
void ft_conversion_g(va_list arg, const char *format, t_data *data);
void ft_wchar_writer(wchar_t wchar, t_data *data);
void ft_magic_diuxX(char *str, t_data *data);
void ft_magic_fe(char *str, t_data *data);
char *ft_processing_f(long double f, t_data *data);
char *ft_processing_e(long double f, t_data *data);
long double ft_rounding_f(long double f, int precision);
void ft_handle_conversion(va_list arg, char *format, t_data *data);
void ft_parsing(va_list ap, char *format, t_data *data);
int ft_printf(const char *format, ...);
#endif

#include "ft_printf.h"

/**
 * @brief Returns a wide character string representing "(null)".
 *
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 * @param is_empty Pointer to a short that will be set to 1 if the returned
 *                 string is dynamically allocated.
 * @return A pointer to the wide character string representing "(null)",
 *         or NULL if memory allocation fails.
 */
wchar_t *ft_null_str(t_data *data, short *is_empty)
{
	wchar_t *null_wcsrt;

	null_wcsrt = (wchar_t *)malloc(sizeof(wchar_t) * 7);
	if (!null_wcsrt)
	{
		data->error = 1;
		return (NULL);
	}
	*is_empty = 1;
	null_wcsrt[0] = L'(';
	null_wcsrt[1] = L'n';
	null_wcsrt[2] = L'u';
	null_wcsrt[3] = L'l';
	null_wcsrt[4] = L'l';
	null_wcsrt[5] = L')';
	null_wcsrt[6] = L'\0';
	return (null_wcsrt);
}

char *ft_inf_str(short minus, t_data *data)
{
	char *rtn;
	short len;

	len = 0;
	data->zero = 0;
	rtn = malloc(sizeof(char) * (3 + minus));
	if (!rtn)
	{
		data->error = 1;
		return (0);
	}
	if (minus)
		rtn[len++] = '-';
	rtn[len++] = 'i';
	rtn[len++] = 'n';
	rtn[len++] = 'f';
	rtn[len] = '\0';
	return (rtn);
}

char *ft_nan_str(t_data *data)
{
	char *rtn;

	data->zero = 0;
	rtn = malloc(sizeof(char) * 4);
	if (!rtn)
	{
		data->error = 1;
		return (0);
	}
	rtn[0] = 'n';
	rtn[1] = 'a';
	rtn[2] = 'n';
	rtn[3] = '\0';
	return (rtn);
}

/**
 * @brief Returns the appropriate space character based on the data flags.
 *
 * This function checks the 'zero' flag and 'precision' in the provided
 * t_data structure to determine whether to return '0' or a space character.
 *
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 * @return A string containing either "0" or " " based on the flags.
 */
char *ft_c_space_str(t_data *data)
{
	if (data->zero && data->precision < 0)
		return ("0");
	else
		return (" ");
}

char *ft_f_space_str(t_data *data)
{
	if (data->zero)
		return ("0");
	else
		return (" ");
}

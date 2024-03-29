/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panderss <panderss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:16:00 by panderss          #+#    #+#             */
/*   Updated: 2020/08/19 16:59:54 by panderss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_sign(const char *format, int j)
{
	int		sign;

	sign = 1;
	if (format[j] == '-')
	{
		sign = -1;
		++j;
	}
	return (sign);
}

long int	set_star_width(t_table *table)
{
	long int	ret;

	ret = va_arg(table->args, long int);
	return (ret);
}

long int	check_digit(t_table *table, const char *format, int j, long int ret)
{
	if (format[j] == '0')
	{
		if (table->cursor->precision == -1)
		{
			table->cursor->zero_pad = 1;
			ret = ft_atol(format, j + 1);
		}
		if (table->cursor->precision != -1)
			ret = ft_atol(format, j);
	}
	if (format[j] != '0')
		ret = ft_atol(format, j);
	return (ret);
}

long int	parse_width(t_table *table, const char *format, int j)
{
	long int	ret;

	ret = 0;
	while (is_conversion(format, j) == 0)
	{
		if (format[j] == '*')
			return (set_star_width(table));
		if (ft_isdigit(format[j]) == 1)
		{
			ret = check_digit(table, format, j, ret);
			break ;
		}
		++j;
	}
	return (ret);
}

long int	get_width(t_table *table, const char *format, int i)
{
	long int	ret;
	int			j;
	int			sign;

	ret = 0;
	j = i + 1;
	sign = get_sign(format, j);
	if (format[j] == '.')
		return (0);
	if (sign == -1)
		++j;
	ret = parse_width(table, format, j);
	return ((sign * ret));
}

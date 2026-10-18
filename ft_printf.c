/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabishev <zabishev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 20:27:13 by zabishev          #+#    #+#             */
/*   Updated: 2026/10/18 21:28:29 by zabishev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i] != '\0')
	{
		count += ft_print_char(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

int	ft_print_char(char c)
{
	return (write(1, &c, 1));//сначала печатает символ, а потом возвращает число 1 при успехе и -1 наоборот
}
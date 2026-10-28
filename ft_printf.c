/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabishev <zabishev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 20:27:13 by zabishev          #+#    #+#             */
/*   Updated: 2026/10/28 13:18:24 by zabishev         ###   ########.fr       */
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
		if (format[i] != '%')
			count += ft_print_char(format[i]);
		else if (format[i + 1] == '\0')
			break ;
		else if (format[i] == '%')
		{
			count += ft_dispatcher(format[i + 1], &ap);
			i++;
		}
		i++;
	}
	va_end(ap);
	return (count);
}

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_dispatcher(char c, va_list *ap)
{
	int		count;

	count = 0;
	if (c == 'c')
		count += ft_print_char(va_arg(*ap, int));
	else if (c == 'd')
		count += ft_putnbr(va_arg(*ap, int));
	else if (c == 's')
		count += ft_putstr(va_arg(*ap, char *));
	else if (c == 'i')
		count += ft_putnbr(va_arg(*ap, int));
	else if (c == 'p')
		count += ft_putptr(va_arg(*ap, void *), "0123456789abcdef");
	else if (c == 'x')
		count += ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		count += ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789ABCDEF");
	else if (c == 'u')
		count += ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789");
	else if (c == '%')
		count += ft_print_char('%');
	return (count);
}

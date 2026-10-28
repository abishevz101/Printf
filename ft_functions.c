/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabishev <zabishev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:48:07 by zabishev          #+#    #+#             */
/*   Updated: 2026/10/28 13:48:59 by zabishev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int number)
{
	int			i;
	char		str[11];
	long int	nb;
	int			count;

	nb = number;
	count = 0;
	i = 0;
	if (nb == 0)
		count += write (1, "0", 1);
	if (nb < 0)
	{
		count += ft_print_char('-');
		nb = -nb;
	}
	while (nb != 0)
	{
		str[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	count += i;
	while (i-- != 0)
		write (1, &str[i], 1);
	return (count);
}

int	ft_putnbr_base(size_t number, char *base)
{
	int		i;
	char	str[20];
	int		count;
	int		base_len;

	base_len = ft_strlen(base);
	count = 0;
	i = 0;
	if (number == 0)
		count += write (1, "0", 1);
	while (number != 0)
	{
		str[i] = base[number % base_len];
		number = number / base_len;
		i++;
	}
	count += i;
	while (i-- != 0)
		write (1, &str[i], 1);
	return (count);
}

int	ft_strlen(char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
		i++;
	return (i);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[count] != '\0')
	{
		write (1, &str[count], 1);
		count++;
	}
	return (count);
}

int	ft_putptr(void *ptr, char *base)
{
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	return ((ft_putstr("0x") + ft_putnbr_base((unsigned long) ptr, base)));
}

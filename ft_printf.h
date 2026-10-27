/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabishev <zabishev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 20:27:09 by zabishev          #+#    #+#             */
/*   Updated: 2026/10/18 20:32:36 by zabishev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int ft_printf(const char *format, ...);
int ft_print_char(char c);
int ft_putnbr(int number);
int ft_putstr(char *str);
int ft_putnbr_base(size_t number, char *base);
int ft_strlen(char *base);
int ft_putptr(void *ptr, char *base);
int	ft_dispatcher(char c, va_list *ap);

#endif
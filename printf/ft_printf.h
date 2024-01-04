/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:46:53 by zyamli            #+#    #+#             */
/*   Updated: 2023/12/06 15:13:12 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(int c, int *len);
void	ft_puthex(unsigned int a, char c, int *len);
void	ft_putnbr(int n, int *len);
void	ft_putptr(void *i, int *len);
int		ft_putstr(char *str, int *len);
void	ft_putunsigned(unsigned int n, int *len);
#endif
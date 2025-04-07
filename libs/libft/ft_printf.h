/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:54:27 by palexand          #+#    #+#             */
/*   Updated: 2024/11/09 12:54:27 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "libft.h"

int		ft_printf(const char *argument, ...);
int		ft_pointer_printf(void *hex);
int		ft_hexa_printf(unsigned int n, int upper_or_lower);
int		ft_nbr_printf(int n);
int		ft_str_printf(char *str);
int		ft_unbr_printf(unsigned int nr);
//int		ft_decimal_printf(int n);

#endif

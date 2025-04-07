/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:20:26 by palexand          #+#    #+#             */
/*   Updated: 2024/10/23 17:20:46 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c);
/*int	main (void)*/
/*{	*/
/*	const char	s[]="Somewhere over the\n rainbow";*/
/*	int	c = '\n';*/
/*	printf("%s", ft_strchr(s, c));*/
/*}*/

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *)&s[i]);
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:08 by palexand          #+#    #+#             */
/*   Updated: 2024/11/20 15:46:11 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
	{
		free(s1);
		return (NULL);
	}
	result = ft_calloc((ft_strlen(s1)+ft_strlen(s2) + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	free(s1);
	return (result);
}

char	*left_trim(char *left_c)
{
	int		i;
	int		k;
	char	*temp;

	i = 0;
	while (left_c[i] && left_c[i] != '\n')
		i++;
	if (!left_c[i])
	{
		free(left_c);
		return (NULL);
	}
	temp = ft_calloc((ft_strlen(left_c) - i + 1), sizeof(char));
	if (!temp)
		return (NULL);
	k = 0;
	while (left_c[i++])
		temp[k++] = left_c[i];
	temp[k] = '\0';
	free(left_c);
	return (temp);
}

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t nbytes, size_t size)
{
	size_t			i;
	unsigned char	*str;

	str = malloc(nbytes * size);
	if (!str)
		return (0);
	i = 0;
	while (i < (nbytes * size))
		str[i++] = '\0';
	return (str);
}

char	*ft_strchr_2(char *s, int c)
{
	if (!s)
		return (0);
	while (*s != c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *) s);
}

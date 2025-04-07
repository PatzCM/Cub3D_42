/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:27:15 by palexand          #+#    #+#             */
/*   Updated: 2024/10/24 18:27:15 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(s1)+ft_strlen(s2) + 1));
	if (result == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0' )
	{
		result[j] = s2[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
/*
int	main(void)
{
	char s1[] = "test";
	char s2[] = "this time";
	printf("Mine: %s\n", ft_strjoin(s1, s2));
	//printf("Original: %d\n", strjoin(s1, s2));
}
*/

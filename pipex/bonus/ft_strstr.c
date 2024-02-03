/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:20:41 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/28 18:05:41 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	index;
	char	*to_look;

	if (!haystack && needle)
		return (NULL);
	i = 0;
	to_look = (char *)haystack;
	index = 0;
	if (!needle[0] || haystack == needle)
		return (to_look);
	while (to_look[i])
	{
		j = 0;
		while (to_look[i + j] == needle[j] && needle[j])
				j++;
		if (needle[j] == '\0')
			return (&to_look[index]);

		index++;
		i = index;
	}
	return (NULL);
}


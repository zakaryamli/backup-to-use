/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:37:15 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/23 17:55:00 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int ft_isspace(char c)
{
	if(c == ' ' || c == '\t' || c == '\n')
		return 1;
	return 0;
}
char* ft_substr(char *str, int start, int len)
{
	int i;
	char *result;
	i = 0;
	result = malloc(sizeof(char) * len + 1);
	while(str[i] && i < len)
	{
		result[i] = str[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
int count_words(char *str)
{
	int i = 0;
	int word = 0;
	while(str[i])
	{
		while(ft_isspace(str[i]))
			i++;
		if(!ft_isspace(str[i]) && str[i])
			word++;
		while(!ft_isspace(str[i]) && str[i])
			i++;
		
	}
	return word;
}
int count_char(char *str)
{
	int i = 0;
	while(!ft_isspace(str[i]) && str[i])
		i++;
	return i;
}
char **ft_split(char *str)
{
	int i = 0;
	int k = 0;
	int words = count_words(str);
	char **result = malloc(sizeof(char *) * (words + 1));

	while(str[i])
	{
		while(ft_isspace(str[i]))
			i++;
		if(str[i] != '\0' && !ft_isspace(str[i]))
		{
			result[k] = ft_substr(str, i, count_char(&str[i]));
			k++;
		}
		while(str[i] != '\0' && !ft_isspace(str[i]))
			i++;
	}
	result[k] = NULL;
	return(result);
}

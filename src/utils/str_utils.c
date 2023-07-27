/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:04:46 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/23 11:44:21 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strchr_get_i(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

void	ft_str_to_str(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!src || !dst)
	{
		return ;
	}
	i = ft_strlen(dst);
	while (src[j])
	{
		dst[i] = src[j];
		j++;
		i++;
	}
}

int	ft_str_in_str(char *str, char *find)
{
	int	i;
	int	i_save;
	int	j;

	i = 0;
	j = 0;
	i_save = 0;
	if (!find)
		return (-1);
	while (str[i])
	{
		j = 0;
		i_save = i;
		while (find[j] && str[i] == find[j])
		{
			if (!find[j + 1] && find[j] != str[i + 1])
				return (i_save);
			j++;
			i++;
		}
		i = i_save;
		i++;
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:05:03 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/16 12:17:10 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_no_space_end_size(char *str)
{
	int	j;

	j = ft_strlen(str) - 1;
	while (j > 0 && str[j] && str[j] == ' ')
		j--;
	return (j);
}

int	ft_no_space_start_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	ft_clean_space_str_create_new(int clean, char *new, char *str)
{
	int	i;
	int	size;

	if (clean == 1)
	{
		i = 0;
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	else
	{
		size = 0;
		i = ft_no_space_start_size(str);
		while (i <= ft_no_space_end_size(str))
		{
			new[size] = str[i];
			size++;
			i++;
		}
	}
}

char	*ft_clean_space_str(char *str)
{
	int		size;
	int		clean;
	char	*new;

	size = 0;
	clean = 0;
	if (!str)
		return (NULL);
	if (str[0] != ' ')
	{
		size = ft_strlen(str);
		clean = 1;
	}
	else
		size = ft_no_space_end_size(str) - ft_no_space_start_size(str);
	if (size < 0)
		size = 0;
	new = ft_calloc(sizeof(char), size + 2);
	if (size == 0)
		return (new);
	ft_clean_space_str_create_new(clean, new, str);
	return (new);
}

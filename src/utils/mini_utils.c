/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:53:42 by anshimiy          #+#    #+#             */
/*   Updated: 2023/08/31 15:09:51 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(char *line)
{
	int	i;
	int	size;
	int	j;

	i = 0;
	j = 0;
	size = ft_strlen(line);
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t')
			j++;
		i++;
	}
	if (j == size)
		return (1);
	else
		return (0);
}

int	ft_str_size(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count])
	{
		count++;
	}
	return (count);
}

void	done(t_state *state)
{
	ft_free_str_table(state->g_env);
	rl_clear_history();
	exit(state->error);
}

void	ft_var_to_val_mor(char *new, char **table, int i)
{
	ft_str_to_str(new, table[i]);
	ft_free(table[i]);
}

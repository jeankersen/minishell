/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:22:15 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/16 14:24:49 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_status;

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_command_exit(t_state *state, char **run_command)
{
	state->stop = STOP;
	if (ft_arr_size(run_command) == 2)
	{
		if ((run_command[1][0] == '-' && ft_isdigit_str(run_command[1]
				+ 1) == 1) || ft_isdigit_str(run_command[1]) == 1)
		{
			state->error = ft_atoi(run_command[1]);
			g_status = state->error;
		}
		else
		{
			ft_putstr_fd(M_NUMBER_ARG_ERR, 2);
			g_status = 255;
		}
	}
}

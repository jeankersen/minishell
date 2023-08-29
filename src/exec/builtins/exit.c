/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:22:15 by anshimiy          #+#    #+#             */
/*   Updated: 2023/08/29 09:08:44 by jvillefr         ###   ########.fr       */
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
	if(state->nb_cmds == 1)
		ft_putstr_fd("exit\n", 2); // exit a// mettre exit quand il ny as pas pipes
	if (ft_arr_size(run_command) == 2)
	{
		//printf("\n run_command) == 2\n");
		if ((run_command[1][0] == '-' && ft_isdigit_str(run_command[1]
				+ 1) == 1) || ft_isdigit_str(run_command[1]) == 1)
		{
			//printf("\nA-voici run_command[1]+1: %s\n", run_command[1]+1);
			//ft_putstr_fd("exit 1\n", 2); // exit 2
			state->error = ft_atoi(run_command[1]);
			g_status = state->error; // exit 00:
			//printf("\nB- run_command[1]: %s\n", run_command[1]);
			//printf("\ng_status: %d\n", g_status);
		}
		else
		{
			//printf("\nexit 2 \n");
			//ft_putstr_fd("exit\n", 2); // exit a
			err_mini_exit(state, run_command[1], "numeric argument required\n", 255); //exit a//ok, verifier status
			g_status = 255;
		}
		state->stop = STOP;
	}
	else
	{
		if (ft_isdigit_str(run_command[1]) == 0)
		{
			//printf("\nexit 3 \n");
			//ft_putstr_fd("exit\n", 2);
			err_mini_exit(state, run_command[1], "numeric argument required\n", 255); // exit a a / ok
			state->stop = STOP;
		}
		else if(ft_arr_size(run_command) > 2)
		{
			//printf("\nexit 4 \n");
			//ft_putstr_fd("exit\n", 2);
			err_mini_exit(state, NULL, "too many arguments\n", 1); // exit 1 1 ok
			//state->stop = NO_ERROR;
			g_status = 256;
		}
		else
		{
			//printf("\nexit 5 \n");
			//ft_putstr_fd("exit\n", 2);
			//err_mini(state, run_command[1], "exit\n", 0); // exit ok
			//g_status = 0;
			state->stop = STOP;
		}
	}

}

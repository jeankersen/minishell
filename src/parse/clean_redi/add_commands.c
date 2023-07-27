/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:51:56 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/31 16:33:01 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_clean_quotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			str = ft_trim_char(str, i);
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				str = ft_trim_char(str, i);
		}
		else
			i++;
	}
	return (str);
}

/// @brief 
/// @param state 
/// @param i 
/// @param table 
/// @todo: On line: if (ft_strcmp(table[0], "echo") != 0),
///		we should check instead if the table[j] before is quotted,
///		if so, we sould not clean the space using ft_clean_space_str.
void	ft_add_commands_clean(t_state *state, int i, char **table)
{
	int		modife;
	int		j;
	char	*path;

	modife = 1;
	j = 0;
	while (table && table[j])
	{
		if (table[j][0] == '\'')
			modife = 0;
		table[j] = ft_clean_quotes(table[j]);
		if (ft_strcmp(table[0], "echo") != 0)
		{
			path = ft_clean_space_str(table[j]);
			ft_free(table[j]);
			table[j] = NULL;
			table[j] = path;
		}
		if (modife == 1)
			ft_handle_env_varibles(state, i, j);
		j++;
	}
}

void	ft_add_commands_redirection_while(t_state *state, t_cmd *cmd, int i)
{
	if ((cmd->cmd_args[0] && ft_strncmp(cmd->cmd_args[0], "||\0",
				3) == 0)
		|| (ft_arr_size(cmd->cmd_args) == 0 && state->nb_cmds == 1))
	{
		ft_minishell_err(state, M_UNXPTD_TOKEN_ERR, N_UNXPTD_TOKEN_ERR);
		return ;
	}
	if (cmd->redirect[cmd->i_redi] == 1)
	{
		state->index = i;
		ft_greater_than(state, 0);
	}
	if (cmd->redirect[cmd->i_redi] == 3)
	{
		state->index = i;
		ft_two_greater_than(state, 0);
	}
	if (ft_arr_size(cmd->t_redirection) > 0 && cmd->redirect[cmd->i_redi] == 2)
		ft_create_herodoc(state, i);
}

void	ft_add_commands_redirection(t_state *state, t_cmd *cmd, int i)
{
	cmd->i_redi = 0;
	while (cmd->i_redi < cmd->n_of_redi - 1 && state->error == NO_ERROR)
	{
		ft_add_commands_redirection_while(state, cmd, i);
		cmd->i_redi++;
	}
	cmd->i_redi = 0;
}

void	ft_add_info_commands(t_state *state)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	while (i < state->nb_cmds && state->error == NO_ERROR)
	{
		cmd = &state->cmds[i];
		ft_add_commands_clean(state, i, cmd->cmd_args);
		j = 0;
		while (cmd->t_redirection && cmd->t_redirection[j])
		{
			cmd->t_redirection[j] = ft_clean_quotes(cmd->t_redirection[j]);
			j++;
		}
		ft_add_commands_redirection(state, cmd, i);
		i++;
	}
}

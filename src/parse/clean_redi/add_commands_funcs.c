/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_commands_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:53:40 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/24 13:48:02 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_status;

int	ft_handle_env_varibles_if(t_state *state, int i, int j)
{
	t_cmd	*cmd;

	cmd = &state->cmds[i];
	if (ft_strchr_get_i(cmd->cmd_args[j],
			'$') >= 0 && ft_strlen(cmd->cmd_args[j])
		> (size_t)ft_strchr_get_i(cmd->cmd_args[j],
			'$') && ft_strlen(cmd->cmd_args[j]) > 1)
	{
		return (1);
	}
	return (0);
}

int	ft_is_delete(t_state *state, int *num, char *tmp)
{
	t_cmd	*cmd;
	char	*str;

	cmd = &state->cmds[num[0]];
	str = cmd->cmd_args[num[1]];
	if (ft_str_in_str(str + num[2], tmp) >= 0)
	{
		if (ft_str_in_str(str + num[2], tmp) + num[2]
			- 1 >= 0 && str[ft_str_in_str(str + num[2], tmp) + num[2]
				- 1] == '$')
		{
			num[2] = ft_str_in_str(str + num[2], tmp) + 1;
			return (1);
		}
	}
	return (0);
}

char	*ft_modif(char *cmd_args, char **env, int j)
{
	char	*path_clean;
	char	*path;
	char	*new;
	int		plus;
	int		i;

	i = 0;
	path_clean = ft_only_str_isalnum(cmd_args);
	path = ft_strjoin(path_clean, "=");
	plus = ft_strlen(cmd_args) - ft_strlen(path_clean);
	if (ft_find_env_value(env, path) != NULL && j == 1)
		new = ft_cat_env_value(env, path, plus);
	else if (j == 1)
		new = ft_calloc(sizeof(char), plus + 1);
	else
		return (ft_free_3_ret(path, path_clean, NULL, cmd_args));
	i = ft_strlen(path_clean);
	plus = ft_strlen(new);
	while (cmd_args[i])
		new[plus++] = cmd_args[i++];
	return (ft_free_3_ret(path, path_clean, cmd_args, new));
}

char	*ft_var_to_val(t_state *state, int *num, int j, int i)
{
	char	**table;
	char	*new;
	t_cmd	*cmd;

	cmd = &state->cmds[i];
	table = ft_split(cmd->cmd_args[j], '$');
	if (!ft_strncmp(table[0], "?", 1))
		return (ft_itoa(g_status));
	while (table[num[4]])
	{
		table[num[4]] = ft_modif(table[num[4]], state->g_env,
				ft_is_delete(state, num, table[num[4]]));
		num[3] += ft_strlen(table[num[4]]);
		num[4]++;
	}
	new = ft_calloc(sizeof(char), num[3] + 1);
	i = -1;
	while (++i < num[4])
	{
		ft_str_to_str(new, table[i]);
		ft_free(table[i]);
	}
	ft_free(table);
	return (new);
}

void	ft_handle_env_varibles(t_state *state, int i, int j)
{
	t_cmd	*cmd;
	char	*new;
	int		num[5];

	cmd = &state->cmds[i];
	num[3] = 0;
	num[4] = 0;
	if (ft_handle_env_varibles_if(state, i, j) == 1)
	{
		num[0] = i;
		num[1] = j;
		num[2] = 0;
		new = ft_var_to_val(state, num, j, i);
		ft_free(cmd->cmd_args[j]);
		cmd->cmd_args[j] = new;
	}
}

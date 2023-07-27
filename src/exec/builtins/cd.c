/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:21:10 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/18 08:01:07 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_state *state)
{
	char	*str_tem;

	str_tem = getcwd(NULL, 0);
	if (!str_tem)
	{
		ft_minishell_err(state, M_PATH_ERR, N_PATH_ERR);
		return ;
	}
	printf("%s\n", str_tem);
	ft_free(str_tem);
}

void	ft_cd_utils(t_state *state)
{
	char	**tmp;
	char	*tmp_cmd;

	tmp = calloc(sizeof(char *), 3);
	tmp_cmd = ft_strdup("OLDPWD");
	ft_delete_env(state, &tmp_cmd);
	tmp[0] = ft_find_env_value(state->g_env, "PWD=");
	tmp[1] = ft_strjoin("OLDPWD=", tmp[0]);
	ft_add_env(state, tmp, 1);
	tmp[1] = ft_free(tmp[1]);
	tmp_cmd = ft_free(tmp_cmd);
	tmp_cmd = ft_strdup("PWD");
	ft_delete_env(state, &tmp_cmd);
	tmp[0] = getcwd(NULL, 0);
	tmp[1] = ft_strjoin("PWD=", tmp[0]);
	ft_add_env(state, tmp, 1);
	ft_free(tmp[0]);
	ft_free(tmp[1]);
	ft_free(tmp);
	ft_free(tmp_cmd);
}

void	ft_cd(t_state *state)
{
	char	**past;
	char	*path;

	past = state->cmds[state->index].cmd_args;
	if (ft_arr_size(past) == 1)
	{
		path = ft_find_env_value(state->g_env, "HOME=");
		if (!path)
			ft_minishell_err(state, "minishell: cd: HOME not set\n",
				N_HOME_UNSET_ERR);
	}
	if (ft_arr_size(past) >= 2)
		path = state->cmds[state->index].cmd_args[1];
	if (path != NULL && chdir(path) == 0)
		ft_cd_utils(state);
	else if (path != NULL)
		ft_minishell_err(state, "minishell: cd: HOME not set\n",
			N_HOME_UNSET_ERR);
}

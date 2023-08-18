/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:21:10 by anshimiy          #+#    #+#             */
/*   Updated: 2023/08/18 08:50:11 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_state *state)
{
	char	*str_tem;

	str_tem = getcwd(NULL, 0);
	if (!str_tem)
	{
		//printf("\ncd.c: ft_pwd\n");
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


void    ft_cd(t_state *state)
{
    char    **past;
    char    *path;
    past = state->cmds[state->index].cmd_args;
    if (ft_arr_size(past) == 1)
    {
        //printf("\noooooOOOOOO\n");
        path = ft_find_env_value(state->g_env, "HOME=");
		//printf(" voici le path == 1: %s\n", path);
        if (!path)
		{
        	    ft_minishell_err(state, "minishell: cd: HOME not set\n",
                N_HOME_UNSET_ERR);
				g_status = 256;
    	}

		}
    if (ft_arr_size(past) >= 2)
	{
        path = state->cmds[state->index].cmd_args[1];
		//printf(" voici le SIZE > = 2path >= 2: %s\n", path);

	}
	//printf(" voici le SIZE APRS LE SIZE >2: %s\n", path);
    if (path != NULL)
	{
		if(chdir(path) == 0)
        	ft_cd_utils(state);
		else
		{

			//printf(" voici le path 3: %s\n", path);
			//if(ft_strcmp(path, "cd HOME") == 0)
				//printf("\n home found\n");
			//if(ft_strcmp(path, "cd $HOME") == 0)
				//printf("\n $home found\n");
			//printf("\nwwwwwwwwwww state->cmds[state->index].cmd_args[0]: %s\n", state->cmds[state->index].cmd_args[0]);
			//printf("\nwwwwwwwwwww state->cmds[state->index].cmd_args[1]: %s\n", state->cmds[state->index].cmd_args[1]);
			min_shell_err(state, "cd", strerror(errno), N_ENV_PATH_ERR);
			g_status = 256;
		}

	}
	/*
	if (path != NULL)
	{


		if(ft_strcmp(path, "HOME") == 0)
			 printf("\nwwwwwwwwwww ho me found\n");



		min_shell_err(state, strerror(errno), N_ENV_PATH_ERR);
		//fprintf(stderr, "Error: %s\n", strerror(errno));

	}

	*/
}



/*

int open_file_tmp(int in_or_out)
{
	int ret;
	char *tmp_file;

	ret = open(tmp_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if(ret == -1)
		exti(0);
	return (ret);
}
void	ft_heredoc(t_state *state)
{
	int fd_out;

	fd_out = open_file_tmp();
}
void here_doc(char **av)
*/

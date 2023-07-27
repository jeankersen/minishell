/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:00:28 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/11 13:37:21 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_create_herodoc_utils(t_cmd *cmd)
{
	char	*str;

	str = readline("> ");
	while (ft_strcmp(str, cmd->t_redirection[cmd->i_redi]) != 0)
	{
		ft_putstr_fd(str, cmd->fd_file);
		ft_putstr_fd("\n", cmd->fd_file);
		ft_free(str);
		str = readline("> ");
	}
	ft_free(str);
}

void	ft_create_herodoc(t_state *state, int index)
{
	t_cmd	*cmd;
	char	*file;
	char	*file_tem;
	char	*number;
	char	*i_redi;

	cmd = &state->cmds[index];
	number = ft_itoa(cmd->id);
	i_redi = ft_itoa(cmd->i_redi);
	file_tem = ft_strjoin(number, i_redi);
	file = ft_strjoin(".tmp_heredoc", file_tem);
	ft_free(file_tem);
	ft_free(number);
	ft_free(i_redi);
	cmd->fd_file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (cmd->fd_file < 0)
	{
		ft_minishell_err(state, M_NO_FILE_DIR_ERR, N_NO_FILE_DIR_ERR);
		ft_free(file);
		return ;
	}
	ft_create_herodoc_utils(cmd);
	close(cmd->fd_file);
	ft_free(file);
}

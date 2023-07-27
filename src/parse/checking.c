/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:15:39 by anshimiy          #+#    #+#             */
/*   Updated: 2023/07/25 14:48:04 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_other_pipes(t_state *state)
{
	t_node	*aff;

	aff = ft_get_first_node(state->tokens);
	aff = aff->next;
	while (aff)
	{
		if (ft_strncmp(aff->content, "||\0", 3) == 0 && ft_strncmp(aff->content,
				"|", 1) == 0)
		{
			ft_minishell_err(state, M_TOKENS_ERR, N_TOKENS_ERR);
			return ;
		}
		aff = aff->next;
	}
}

int	ft_is_redi(t_state *state, t_node *aff)
{
	int	j;

	j = 3;
	while (j >= 0)
	{
		if (ft_strncmp(aff->content, state->t_redirection[j],
				ft_strlen(state->t_redirection[j])) == 0)
		{
			return (1);
		}
		j--;
	}
	return (0);
}

int	ft_is_pipe(char *str)
{
	if (ft_strncmp(str, "|\0", 2) == 0 || ft_strncmp(str, "||\0", 2) == 0)
	{
		return (1);
	}
	return (0);
}

int	ft_unexptd_token_check(t_node *list)
{
	t_node	*temp;
	char	c;

	temp = ft_get_first_node(list);
	while (temp)
	{
		if (*temp->content == '<' || *temp->content == '>'
			|| *temp->content == '|')
		{
			c = *temp->content;
			if (!temp->next)
				return (0);
			temp = temp->next;
			if (*temp->content == c)
			{
				printf("minishell: syntax error near unexpected token '%c'\n",
					c);
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

void	ft_check_pipes(t_state *state)
{
	t_node	*aff;

	aff = ft_get_first_node(state->tokens);
	if (aff->content && ft_strncmp(aff->content, "|\0", 2) == 0)
	{
		ft_minishell_err(state, M_TOKEN_ERR, N_TOKEN_ERR);
		return ;
	}
	else if (aff->content && ft_strncmp(aff->content, "||\0", 3) == 0)
	{
		ft_minishell_err(state, M_TOKENS_ERR, N_TOKENS_ERR);
		return ;
	}
	ft_check_other_pipes(state);
}

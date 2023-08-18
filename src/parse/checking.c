/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:15:39 by anshimiy          #+#    #+#             */
/*   Updated: 2023/08/18 08:51:14 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_other_pipes(t_state *state)
{
	t_node	*temp;

	temp = ft_get_first_node(state->tokens);
	temp = temp->next;
	while (temp)
	{
		if (ft_strncmp(temp->content, "||\0", 3) == 0 && ft_strncmp(temp->content,
				"|", 1) == 0)
		{
			//printf("\n annothe term\n"); example echo |
			//printf("\nchecking.c: check_other_pipes\n");
			ft_minishell_err(state, M_TOKENS_ERR, N_TOKENS_ERR);
			return ;
		}
		temp = temp->next;
	}
}

int	ft_is_redi(t_state *state, t_node *temp) //check is a redirection n
{
	int	j;

	j = 3; // state->t_redirection[3] = ft_strdup(">>");
	while (j >= 0)
	{
		if (ft_strncmp(temp->content, state->t_redirection[j],
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

	temp = ft_get_first_node(list); // get first content of the node
	while (temp)
	{
		if (*temp->content == '<' || *temp->content == '>'
			|| *temp->content == '|' )
		{
			c = *temp->content;
			if (!temp->next)
				return (0);
			temp = temp->next;
			if (*temp->content == c)
			{
				//printf("\nchecking.c: unexptd_token_check\n");
				printf("minishell: syntax error near unkjkexpected token '%c'\n",
					c); // si il y a une triple character dans content,  ex: <<<
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

void	ft_check_pipes(t_state *state)
{
	t_node	*temp;

	temp = ft_get_first_node(state->tokens); // get first content of node
	// annuler erreur execution dans ce cas
	if (temp->content && ft_strncmp(temp->content, "|\0", 2) == 0)
	{
		//printf("\nje suis juste ici\n"); // si la commande commence par |
		ft_minishell_err(state, M_TOKEN_ERR, N_TOKEN_ERR);
		return ;
	}
	else if (temp->content && ft_strncmp(temp->content, "||\0", 3) == 0)
	{
		// printf("\nje suis juste la\n"); si la commande commance par ||
		//printf("bibibibi\n");
		ft_minishell_err(state, M_TOKENS_ERR, N_TOKENS_ERR);
		return ;
	}
	ft_check_other_pipes(state); // si les autres content commence par |, mais ca  bogue
}

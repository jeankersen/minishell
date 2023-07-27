/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 08:13:18 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/16 14:33:40 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_t_redirection(t_state *state)
{
	state->t_redirection = ft_calloc(sizeof(char *), 5);
	state->t_redirection[0] = ft_strdup("<");
	state->t_redirection[1] = ft_strdup(">");
	state->t_redirection[2] = ft_strdup("<<");
	state->t_redirection[3] = ft_strdup(">>");
	state->t_redirection[4] = 0;
}

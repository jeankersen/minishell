/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:27 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/16 14:27:37 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	ft_update_g_status(void)
{
	g_status /= 256;
	if (g_status == 9)
		g_status = 127;
}

void	ft_minishell_err(t_state *state, char *msg, int err)
{
	state->error = err;
	ft_putstr_fd(msg, 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:25:35 by anshimiy          #+#    #+#             */
/*   Updated: 2023/05/16 14:00:41 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief		Close possibly used file descriptors by dup() function
/// @details Closes all file descriptors from 3 to 200 since dup()
///				allocate an fd from the smallest available
void	ft_close_fd(void)
{
	int	i;

	i = 2;
	while (++i < 200)
		close(i);
}

void	ft_check_exit(t_state *state)
{
	ft_close_fd();
	ft_free_all(state);
}

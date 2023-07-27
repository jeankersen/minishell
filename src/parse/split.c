/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:29:36 by anshimiy          #+#    #+#             */
/*   Updated: 2023/07/25 14:48:18 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1) If the previous character is not a splitter, create a new token
// 2) If the next character is the same as the current character, skip it
// 3) If the current character is not a space, create a new token
int	ft_create_token(char *args, int i, int start, t_node *list)
{
	if (args[i - 1] && !ft_is_splitable(args[i - 1]))
	{
		ft_lst_add_back(&list, ft_substr(args, start, (i - start)));
		start = i;
	}
	if (args[i + 1] && args[i] == args[i + 1])
		i++;
	if (args[i] != ' ')
		ft_lst_add_back(&list, ft_substr(args, start, (i - start + 1)));
	return (i);
}

//  This function finds the end of a quoted section in args
//  starting from the ith character
//  Move forward until we find the matching end quote
//  If we found the matching end quote, return the
//  index of the next character
//  If we didn't find the matching end quote,
//  print an error message and return -1
int	ft_quotes(char *args, int i)
{
	char	quote;

	quote = args[i++];
	while (args[i] && args[i] != quote)
		i++;
	if (args[i])
		return (i + 1);
	printf("minishell: Unclosed quotes\n");
	return (-1);
}

// If we're inside quotes, skip to the end of the quoted section
// call ft_quotes to find the end of the quoted section
// if there is an error (unclosed quote), exit 1
// if the current character is a separator (space, <, >, or |),
// - create a new token from the substring between
//  the last separator and this one
// call ft_create_token to create a new token from the current substring
// set the start index of the next token to be the
//  character after the current separator
// if the last character in the string is not a separator,
//  create a new token from the substring
// - between the last separator and the end of the string
// call ft_lst_add_back to create a new token from the remaining substring
t_node	*ft_get_tokens(char *args)
{
	t_node	*tmp;
	int		i;
	int		start;

	i = -1;
	start = 0;
	ft_init_tmp_head(&tmp);
	while (args && args[++i])
	{
		while (args[i] == '\"' || args[i] == '\'')
		{
			i = ft_quotes(args, i);
			if (i == -1)
				exit(1);
		}
		if (ft_is_splitable(args[i]))
		{
			i = ft_create_token(args, i, start, tmp);
			start = i + 1;
		}
	}
	if (!ft_is_splitable(args[i - 1]))
		ft_lst_add_back(&tmp, ft_substr(args, start, (i - start)));
	ft_delete_head(&tmp);
	return (tmp);
}

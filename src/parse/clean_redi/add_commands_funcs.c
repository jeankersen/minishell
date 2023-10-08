/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_commands_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:48:53 by jvillefr          #+#    #+#             */
/*   Updated: 2023/10/07 20:27:17 by jvillefr         ###   ########.fr       */
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
/*
char	*ft_var_to_val(t_state *state, int *num, int j, int i)
{
	char	**table;
	char	*new;
	t_cmd	*cmd;
	int k;

	cmd = &state->cmds[i];

	size_t l;
	//get_double_sign_away(cmd->cmd_args[j], '$');
	//printf("\n cmd->cmd_args: %s\n", cmd->cmd_args[j]);

	if(more_then_two_dollar(cmd->cmd_args[j]) ==1)
	{
		get_double_sign_away(cmd->cmd_args[j], '$');
		table = ft_split(cmd->cmd_args[j], '\v');
		k = 0;
		while (table[k])
		{
			printf("\ntable[%d]: %s\n", k,  table[k]);
			k++;
		}
		k = 0;
		while (table[k])
		{
			l = 0;
			while(table[k][l])
			{
				if(table[k][l] == '$')
				{
					table[k] = ft_strjoin(extract_before_index(table[k], l), extract_after_index(table[k], l+1));
					break;
				}
				l++;
			}
			k++;
		}
		k = 0;
		while (table[k])
		{
			printf("\ntable[%d]: %s\n", k,  table[k]);
			k++;
		}
	}
	else
		table = ft_split(cmd->cmd_args[j], '$');

	//get_double_sign_away(cmd->cmd_args[j], '$');
	//table = ft_split(cmd->cmd_args[j], '$');
	if (!ft_strncmp(table[0], "?", 1))
		return (ft_itoa(g_status));
	while (table[num[4]])
	{

		table[num[4]] = ft_modif(table[num[4]], state->g_env,
				ft_is_delete(state, num, table[num[4]]));
		num[3] += ft_strlen(table[num[4]]);
		printf("\n*table[%d]: %s\n", num[4], table[num[4]]);
		num[4]++;
	}
	k = 0;
	while (table[k])
	{
		printf("\ntable[%d] :::: %s\n", k,  table[k]);
		k++;
	}

	new = ft_calloc(sizeof(char), num[3] + 1);
	i = -1;
	while (++i < num[4])
	{
		ft_var_to_val_mor(new, table, i);
	}
	ft_free(table);
	return (new);
}
*/

char * enleverPremierElement(char *tableau) {

    int longueur = strlen(tableau);
    for (int i = 0; i < longueur - 1; ++i) {
        tableau[i] = tableau[i + 1];
    }

    // Mettre à jour la dernière position avec le caractère nul
    tableau[longueur - 1] = '\0';
	return (tableau);
}
char *put_status(char *str)
{
    int i;
	char *s;
	char *new;


	i = 0;
	new = NULL;
	new = ft_itoa(g_status);

printf("\n 3-put_status %s\n", new);
	if(ft_strlen(str) > 1)
	{
		s = enleverPremierElement(str);
		printf("\n 1-put_status %s\n", s);
		//strlcpy(new, str, strlen(new));
		new = ft_strjoin(new, s);

	}
	printf("\n 2-put_status %s\n", new);
	return (new);
}


void get_double_sign_away(char *str)
{
    int i;


	i = 0;
	while ( str[i] != '\0')
	{
		if (str[i] ==  str[i + 1] && str[i] == '$')
		{
			str[i] = '+';
			str[i + 1] = '+';
			i++;
		}
		i++;
	}
	printf("\n ******** %s\n", str);
}


int count_dollar(char *str)
{
	int occ;
	int i;

	i = 0;
	occ = 0;
	while ( str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if(str[i+1] == '$')
			{
				i++;
				occ = 0;
			}
			else
			{
				i++;
				occ++;
			}
		}
		i++;
	}
	return  occ;
}

int count_double_dollar(char *str)
{
	int occ;
	int i;

	i = 0;
	occ = 0;
	while ( str[i] != '\0')
	{
		if (str[i] ==  str[i + 1] && str[i] == '$')
		{
			return (1);
		}
		i++;
	}
	return  (0);
}


void delete_by_index(char *s, size_t index) {
    // Vérification de la validité de l'index
    if (index < 0 || index >= ft_strlen(s)) {
        return;
    }

    // Effacer les caractères à partir de l'index
    s[index] = '\0';
}


char* extract_after_index(char *s, size_t index) {

	if (index < 0 || index >= ft_strlen(s)) {
		return NULL;
	}

	size_t longueur = ft_strlen(s + index);

	char *resultat = (char *)malloc(longueur + 1);

	strcpy(resultat, s + index);

	return resultat;
}

char* extract_before_index(char *s, size_t index) {

	if (index < 0 || index >= ft_strlen(s)) {
		return NULL;
	}

	 size_t longueur = index + 1;

	char *resultat = (char *)malloc(longueur);

	strncpy(resultat, s, longueur);
	resultat[longueur - 1] = '\0'; // Ajout du caractère nul à la fin
	return resultat;

}

//echo $jan$$fev$$$mar$$$$avril$$$$$alo




void re_arrange_table_double(t_state *state, char **s, int *num)
{
	int i;
	int j;
	int k;
	char **table;
	int l;

	i = 0;
	j = 0;
	k = 0;

	printf("\n re_arrange_table_double 1\n");
	while (s[i])
	{
		if(count_dollar(s[i]) == 0)
		{
			printf("\n ######%s\n", s[i]);
			printf("\n re_arrange_table_double 111111\n");
			i++;
		}
		else
		{
		printf("\n re_arrange_table_double 2\n");
			table = ft_split(s[i], '$');
			printf("\n re_arrange_table_double 3\n");
			j = ft_strlen(s[i]);
			if(s[i][j - 1] == '$')
				k++;
			printf("\n re_arrange_table_double 4\n");
			while (table[num[4]])
			{
			printf("\n re_arrange_table_double 5\n");
				if(table[num[4]][0] == '?')
				{
					table[num[4]] = put_status(table[num[4]]);
					num[3] += ft_strlen(table[num[4]]);
					num[4]++;
				}
				else if(s[i][0] != '$')
				{
					printf("\n re_arrange_table_double 6\n");
					num[3] += ft_strlen(table[num[4]]);
					num[4]++;
				}

				else
				{
					printf("\n re_arrange_table_double 7\n");
					table[num[4]] = ft_modif(table[num[4]], state->g_env,
					ft_is_delete(state, num, table[num[4]]));
					num[3] += ft_strlen(table[num[4]]);
					num[4]++;
				}
			}
			s[i] = ft_calloc(sizeof(char), num[3] + 1);
			l = -1;
			while (++l < num[4])
			{
				printf("\n re_arrange_table_double 8\n");
				ft_var_to_val_mor(s[i], table, l);
			}
			printf("\n re_arrange_table_double 9\n");
			if(k > 0)
				s[i] = ft_strjoin(s[i], "$");
				printf("\n re_arrange_table_double 10\n");
			num[3] = 0;
			num[4] = 0;
			free(table);
			i++;
		}
		printf("\n re_arrange_table_double 11\n");
	}
	printf("\n re_arrange_table_double 12\n");
}


char *re_arrange_table(t_state *state, char *s, int *num, int i)
{
	char	**table;
	char	*new;
	int l;

	table = ft_split(s, '$');
	l = ft_strlen(s);
	while (table[num[4]])
	{
		printf("\n re_arrange_table 1\n");

		 if(table[num[4]][0] == '?')
		{
		printf("\n re_arrange_table 3\n");
			table[num[4]] = put_status(table[num[4]]);
			num[3] += ft_strlen(table[num[4]]);
			num[4]++;
		}
		else if(s[0] != '$')
		{
			printf("\n re_arrange_table 2\n");
			num[3] += ft_strlen(table[num[4]]);
			num[4]++;
		}
		else
		{
			table[num[4]] = ft_modif(table[num[4]], state->g_env,
				ft_is_delete(state, num, table[num[4]]));
			num[3] += ft_strlen(table[num[4]]);
			num[4]++;

		}
	}
	new = ft_calloc(sizeof(char), num[3] + 1);
	i = -1;
	while (++i < num[4])
	{
		ft_var_to_val_mor(new, table, i);
	}
	if(s[l - 1] == '$')
		{
			new = ft_strjoin(new, "$");
		}
	ft_free(table);
	return (new);
}


char	*ft_var_to_val(t_state *state, int *num, int j, int i)
{
	char	**table;
	char	*new;
	t_cmd	*cmd;
	//size_t	l;

	//l = ft_strlen(cmd->cmd_args[j]);
	cmd = &state->cmds[i];

	if(count_double_dollar(cmd->cmd_args[j])) //$$mama
	{
		printf("\n ft_var_to_val 1\n");
		get_double_sign_away(cmd->cmd_args[j]);
		printf("\n ft_var_to_val 2\n");
		table = ft_split(cmd->cmd_args[j], '+');
		printf("\n ft_var_to_val 3\n");
		re_arrange_table_double(state, table, num);
		printf("\n ft_var_to_val 4\n");
		while (table[num[4]])
		{
			num[3] += ft_strlen(table[num[4]]);
			num[4]++;
		}
		new = ft_calloc(sizeof(char), num[3] + 1);
		i = -1;
		while (++i < num[4])
		{
			ft_var_to_val_mor(new, table, i);
		}
		ft_free(table);
		return (new);
	}
	else if(count_dollar(cmd->cmd_args[j]) > 0)
	{
	printf("\n ft_var_to_val 44\n");
		return (re_arrange_table(state, cmd->cmd_args[j], num, i));
	}

	else
	{
		printf("\n ft_var_to_val 4444\n");
		return(cmd->cmd_args[j]);
	}
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
		cmd->cmd_args[j] = new;
	}
}

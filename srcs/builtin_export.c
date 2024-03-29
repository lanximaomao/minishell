/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:19:16 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 16:03:39 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int	is_valid_argument(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
		return (printf_error(" not a valid identifier\n", 1));
	while (arg[i])
	{
		if (!(ft_isalnum(arg[i]) || ft_isalpha(arg[i]) || arg[i] == '_')
			&& is_equal_sign(arg, i, '=') == 0)
			return (printf_error(" not a valid identifier\n", 1));
		i++;
	}
	return (0);
}

/* sign 0 means arg there isn't any equal sign in argument*/
static int	add_argument(t_list **env, char *arg)
{
	int		sign;
	int		status;
	t_list	*node;
	char	**env_content;

	if (ft_strchr(arg, '='))
		sign = 1;
	else
		sign = 0;
	env_content = env_split(arg, '=');
	status = env_find_and_replace(env, env_content[0], env_content[1], sign);
	if (status == 0)
	{
		node = ft_lstnew(env_content);
		if (!node)
			ft_error(" minishell: cann't create a new node", 1, 0);
		ft_lstadd_back(env, node);
		return (0);
	}
	free_char(env_content);
	return (1);
}

static int	empty_aguments(t_list **env)
{
	t_list	*tmp;
	char	**env_content;

	tmp = *env;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		ft_printf("declare -x %s", env_content[0]);
		if (ft_strncmp(env_content[1], "", 1))
			ft_printf("=\"%s\"\n", env_content[1]);
		else
			ft_printf("\n");
		tmp = tmp->next;
	}
	return (0);
}

void	my_export(char **arg, t_list **env)
{
	int	i;
	int	is_valid;

	i = 1;
	while (arg[i])
	{
		is_valid = is_valid_argument(arg[i]);
		if (is_valid == 0)
			add_argument(env, arg[i]);
		if (is_valid == 0)
			g_exitcode = 0;
		else
			g_exitcode = 1;
		i++;
	}
	if (!arg[1] && empty_aguments(env) == 0)
		g_exitcode = 0;
}

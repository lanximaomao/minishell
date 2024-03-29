/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:19:57 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 16:54:28 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/minishell.h"

char	**env_split(char const *s, char c)
{
	char	**str_arr;
	size_t	len;

	str_arr = (char **)ft_calloc(sizeof(char *), (2 + 1));
	if (!str_arr)
		ft_error(" minishell: malloc fail or null input?\n", MALLOC, 0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			str_arr[0] = ft_substr(s - len, 0, len);
			if (!str_arr[0])
				ft_error(" minishell: malloc fail", MALLOC, 0);
			str_arr[1] = ft_substr(s - len, len + 1, ft_strlen(s));
			if (!str_arr[1])
				ft_error(" minishell: malloc fail", MALLOC, 0);
			break ;
		}
		else
			s++;
	}
	return (str_arr);
}

/*
** this function create a linked list
** and each node contains a enviromental variable's name and value
*/
void	env_init(t_mini *mini, char **env)
{
	int		i;
	int		is_oldpwd;
	char	**env_content;
	t_list	*node;

	i = 0;
	mini->env = NULL;
	while (env[i])
	{
		env_content = env_split(env[i], '=');
		is_oldpwd = ft_strncmp(env_content[0], "OLDPWD",
				ft_strlen(env_content[0]));
		if (is_oldpwd == 0)
			ft_bzero(env_content[1], ft_strlen(env_content[1]));
		node = ft_lstnew(env_content);
		if (!node)
			ft_error(" minishell: fail to init a node\n", 1, 0);
		ft_lstadd_back(&mini->env, node);
		i++;
	}
}

/*
** ! to be updated due to empty argument values
** by giving the name of the enviromental varible, such as HOME
** it returns a string of its values.
*/
char	*env_handler(t_list **env, char *str)
{
	char	**env_content;
	t_list	*tmp;
	size_t	len;

	tmp = *env;
	env_content = (char **)(*env)->content;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		len = ft_strlen(env_content[0]);
		if (len == ft_strlen(str) && ft_strncmp(str, env_content[0],
				(int)len) == 0)
			return (env_content[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** convert enviromental varible from a linked list to a double pointer, char**
** this could be used in execve function call.
*/
char	**env_convert(t_list **env)
{
	int		i;
	t_list	*tmp;
	char	**ret;
	char	*ret_tmp;
	char	**env_content;

	i = -1;
	tmp = *env;
	ret = (char **)malloc(sizeof(char *) * (ft_lstsize(*env) + 1));
	if (!ret)
		ft_error(" minishell: malloc fail.\n", 1, 0);
	ret[ft_lstsize(*env)] = NULL;
	while (++i < ft_lstsize(*env))
	{
		env_content = (char **)tmp->content;
		ret_tmp = ft_strjoin(env_content[0], "=");
		if (!ret_tmp)
			ft_error("minishell: malloc fail.\n", 1, 0);
		ret[i] = ft_strjoin(ret_tmp, env_content[1]);
		if (!ret[i])
			ft_error("minishell: malloc fail.\n", 1, 0);
		free(ret_tmp);
		tmp = tmp->next;
	}
	return (ret);
}

/*
** this function is used to update the enviromental varible
*/
int	env_find_and_replace(t_list **env, char *to_find, char *to_replace,
		int sign)
{
	char	**env_content;
	t_list	*tmp;
	size_t	len;

	tmp = *env;
	env_content = (char **)(*env)->content;
	while (tmp)
	{
		env_content = (char **)tmp->content;
		len = ft_strlen(env_content[0]);
		if (len == ft_strlen(to_find) && ft_strncmp(to_find, env_content[0],
				(int)len) == 0)
		{
			if (ft_strncmp(to_replace, "", 1) == 0 && sign == 0)
				return (-1);
			if (ft_strlen(to_replace) > ft_strlen(env_content[1]))
				env_content[1] = ft_realloc(env_content[1], len + 1,
						ft_strlen(to_replace) + 1);
			ft_strlcpy(env_content[1], to_replace, ft_strlen(to_replace) + 1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

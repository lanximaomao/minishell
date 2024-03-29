/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:23:58 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 17:02:52 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 exit(error_code)
 # define MALLOC 1
 # define FILE_OP 2
 # define SYNTAX 3
 # define FUNC 4
 error_code: <= 2 for system perror(malloc, file_err...)
 others for the mini_error(syntax, parse_err)
 flag 0 means exit, flag 1 means return
*/

void	ft_error(char *msg, int error_code, int flag)
{
	if (error_code <= 2)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	g_exitcode = error_code;
	if (flag == 0)
		exit(g_exitcode);
}

/*
** if: the | or < is the last character
** else if: if current is pipe, error occurs
** when the next and next next are both empty
** else if: if current does not contain a pipe
** error occurs when this and the next are both empty lines
*/
static int	handle_parse_error(int cmd_order, t_list *line_lst, int sign)
{
	int	ret;

	ret = 0;
	if (sign == 1 && (((t_input *)line_lst->content)->pipe_sign == 1
			|| ((t_input *)line_lst->content)->redir_sign != 0))
		ret = -1;
	else if ((sign == 2 && cmd_order == 0
			&& !ft_strncmp(((t_input *)line_lst->content)->tmp_line, "", 1))
		|| ((sign == 2 && ((t_input *)line_lst->next->content)->pipe_sign == 1)
			&& !ft_strncmp(((t_input *)line_lst->next->content)
				->tmp_line, "", 1)))
		ret = -1;
	else if (sign == 3 && ((((t_input *)line_lst->next->content)->redir_sign
				&& !ft_strncmp(((t_input *)line_lst->next->content)
					->tmp_line, "", 1))
			|| (((t_input *)line_lst->next->content)->pipe_sign
				&& !ft_strncmp(((t_input *)line_lst->next->content)
					->tmp_line, "", 1))))
		ret = -1;
	if (ret == -1)
		ft_error("minishell: Syntax error: parse error", SYNTAX, 1);
	return (ret);
}

static void	trim_pipe(t_list **line_lst)
{
	t_list	*tmp;

	tmp = (*line_lst)->next;
	(*line_lst)->next = (*line_lst)->next->next;
	tmp->next = NULL;
	free_input((t_input *)tmp->content);
	free(tmp);
	tmp = NULL;
	return ;
}

int	validator(t_list **line_lst)
{
	int			count;
	t_input		*input;

	count = 0;
	while (*line_lst)
	{
		input = (t_input *)(*line_lst)->content;
		if (!((*line_lst)->next))
			if (handle_parse_error(count, (*line_lst), 1) == -1)
				return (-1);
		if (input->pipe_sign == 1)
		{
			if (handle_parse_error(count, (*line_lst), 2) == -1)
				return (-1);
		}
		else if (input->redir_sign)
			if (handle_parse_error(count, (*line_lst), 3))
				return (-1);
		if (input->redir_sign == 3
			&& ((t_input *)(*line_lst)->next->content)->pipe_sign)
			trim_pipe(line_lst);
		count++;
		(*line_lst) = (*line_lst)->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:51:13 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/24 23:56:59 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_args(t_list **cmd_args)
{
	int		counter;
	int		type;
	t_list	*link;

	if (!*cmd_args)
		return (0);
	counter = 0;
	link = *cmd_args;
	type = ft_ectracttype(link);
	while (link)
	{
		type = ft_ectracttype(link);
		if (type != LX_SEP && type != LX_AND && type != LX_OR)
			counter++;
		link = link->next;
	}
	return (counter);
}

void	ft_make_argv(t_group *group, int cmd_i, int arg_num)
{
	int		arg_i;
	int		type;
	t_list	*link;

	arg_i = 0;
	group->cmds->newargvs[cmd_i] = malloc(sizeof(char *) * (arg_num + 1));
	link = *group->cmds->cmd_args[cmd_i];
	while (link)
	{
		type = ft_ectracttype(link);
		if (type != LX_SEP && type != LX_AND && type != LX_OR)
		{
			group->cmds->newargvs[cmd_i][arg_i] = \
				ft_strdup(ft_ectracttext(link));
			arg_i++;
		}
		link = link->next;
	}
	group->cmds->newargvs[cmd_i][arg_i] = 0;
}

int	ft_make_newargvs(t_group *group)
{
	int		cmd_i;
	int		arg_num;

	cmd_i = 0;
	while (cmd_i < group->cmds->cmd_num)
	{
		arg_num = ft_count_args(group->cmds->cmd_args[cmd_i]);
		if (!arg_num)
		{
			cmd_i++;
			continue ;
		}
		ft_make_argv(group, cmd_i, arg_num);
		cmd_i++;
	}
	return (0);
}

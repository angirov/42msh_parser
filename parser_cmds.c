/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:33:00 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/15 00:51:31 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_cmds(t_list **lexems)
{
	int		counter;
	int		type;
	t_list	*link;

	counter = 1;
	link = *lexems;
	type = ft_ectracttype(link);
	if (type == LX_PIPE)
		return (ft_error("syntax error: | the first token of a group", -401));
	type = ft_ectracttype(ft_lstlast(link));
	if (type == LX_PIPE)
		return (ft_error("syntax error: | the last token of a group", -499));
	while (link)
	{
		type = ft_ectracttype(link);
		if (type == LX_PIPE)
			counter++;
		link = link->next;
	}
	return (counter);
}

int	ft_count_args(t_list **cmd_args)
{
	int		counter;
	int		type;
	t_list	*link;

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

int	ft_make_cmd_args(t_group *group)
{
	int		i;
	t_list	*link;
	int		type;
	char	*text;

	group->cmds = malloc(sizeof(t_cmds));
	group->cmds->cmd_num = ft_count_cmds(group->lexems);
	if (group->cmds->cmd_num <= 0)
		return (ft_error("could not parse group", -400 -(10 * group->index)));
	group->cmds->cmd_args = malloc(sizeof(t_list **) * group->cmds->cmd_num);
	i = 0;
	link = *group->lexems;
	while (i < group->cmds->cmd_num)
	{
		group->cmds->cmd_args[i] = malloc(sizeof(t_list *));
		*group->cmds->cmd_args[i] = NULL;
		while (link)
		{
			type = ft_ectracttype(link);
			if (type == LX_PIPE && *group->cmds->cmd_args[i])
			{
				link = link->next;
				break ;
			}
			if (!(type == LX_SEP && !*group->cmds->cmd_args[i]))
			{
				text = ft_strdup(ft_ectracttext(link));
				ft_addlexem(group->cmds->cmd_args[i], ft_newlexem(type, text));
			}
			link = link->next;
		}
		ft_dellastsep(group->cmds->cmd_args[i]);
		i++;
	}
	return (0);
}

int	ft_make_newargvs(t_group *group)
{
	int		cmd_i;
	int		arg_i;
	t_list	*link;
	int		arg_num;
	int		type;

	group->cmds->newargvs = malloc(sizeof(char **) * group->cmds->cmd_num);
	cmd_i = 0;
	link = *group->lexems;
	while (cmd_i < group->cmds->cmd_num)
	{
		arg_i = 0;
		arg_num = ft_count_args(group->cmds->cmd_args[cmd_i]);
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
		cmd_i++;
	}
	return (0);
}

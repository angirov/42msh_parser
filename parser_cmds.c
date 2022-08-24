/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:33:00 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/24 23:52:20 by vangirov         ###   ########.fr       */
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

void	ft_loop_thru_args(t_list *link, t_group *group, int i)
{
	int		type;
	char	*text;

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
}

int	ft_make_cmd_args(t_group *group)
{
	int		i;
	t_list	*link;

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
		ft_loop_thru_args(link, group, i);
		ft_dellastsep(group->cmds->cmd_args[i]);
		i++;
	}
	return (0);
}

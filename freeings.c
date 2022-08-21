/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:19:07 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/15 01:10:03 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_lexems(t_list **head)
{
	t_list	*link;
	t_list	*next;

	if (!head)
		return ;
	link = *head;
	while (link)
	{
		next = link->next;
		ft_free_lexem(link);
		link = next;
	}
	free(head);
}

// void	ft_free_gr_lexems(t_group *group, int cmd_i)
// {
// 	t_list	*link;
// 	t_list	*next;

// 	link = *group->cmds->cmd_args[cmd_i];
// 	while (link)
// 	{
// 		next = link->next;
// 		ft_free_lexem(link);
// 		link = next;
// 	}
// }
void	ft_free_gr_lexems(t_group *group, int cmd_i)
{
	ft_free_lexems(group->cmds->cmd_args[cmd_i]);
	ft_free_lexems(group->cmds->redirs[cmd_i]);
	ft_free_split(group->cmds->newargvs[cmd_i]);
}

void	ft_free_groups(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->group_num)
	{
		ft_loop_cmds(msh->groups[i], ft_free_gr_lexems);
		free(msh->groups[i]->cmds->cmd_args);
		free(msh->groups[i]->cmds->redirs);
		free(msh->groups[i]->cmds->newargvs);
		free(msh->groups[i]->cmds);
		ft_free_lexems(msh->groups[i]->lexems);
		free(msh->groups[i]);
		i++;
	}
	free(msh->groups);
}

void	ft_free_msh(t_msh *msh)
{
	if (!msh->lexems)
	{
		free(msh->delims);
		return ;
	}
	ft_free_lexems(msh->lexems);
	ft_free_groups(msh);
}

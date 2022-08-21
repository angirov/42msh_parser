/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_groups.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:32:00 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/13 19:37:54 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* if the first token is AND or OR print error */
int	ft_count_groups(t_list **lexems)
{
	int		counter;
	int		type;
	t_list	*link;

	if (!*lexems)
		return (0);
	counter = 1;
	link = *lexems;
	type = ft_ectracttype(link);
	if (type == LX_AND || type == LX_OR)
		return (ft_error("syntax error: || or && as the first token", -301));
	type = ft_ectracttype(ft_lstlast(link));
	if (type == LX_AND || type == LX_OR)
		return (ft_error("syntax error: || or && as the last token", -399));
	while (link)
	{
		type = ft_ectracttype(link);
		if (type == LX_AND || type == LX_OR)
			counter++;
		link = link->next;
	}
	return (counter);
}

int	ft_makegroups(t_msh *msh)
{
	int		i;
	t_list	*link;
	int		type;
	char	*text;

	msh->group_num = ft_count_groups(msh->lexems);
	if (msh->group_num <= 0)
		return (ft_error("could not parse", -300));
	msh->groups = malloc(sizeof(t_group *) * msh->group_num);
	i = 0;
	link = *msh->lexems;
	while (i < msh->group_num)
	{
		msh->groups[i] = malloc(sizeof(t_group));
		msh->groups[i]->index = i;
		msh->groups[i]->lexems = malloc(sizeof(t_list *));
		*msh->groups[i]->lexems = NULL;
		if (i == 0)
			msh->groups[i]->type = -1;
		else
			msh->groups[i]->type = ft_ectracttype(link);
		while (link)
		{
			type = ft_ectracttype(link);
			if ((type == LX_AND || type == LX_OR) && *msh->groups[i]->lexems)
				break ;
			text = ft_strdup(ft_ectracttext(link));
			ft_addlexem(msh->groups[i]->lexems, ft_newlexem(type, text));
			link = link->next;
		}
		ft_dellastsep(msh->groups[i]->lexems);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_groups.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:32:00 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/24 21:38:58 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_trim_lexems_front(t_list **lexems)
{
	t_list	*link;
	t_list	*next;
	int		type;

	link = *lexems;
	while(link)
	{
		next = link->next;
		type = ft_ectracttype(link);
		if (type == LX_AND || type == LX_OR || type == LX_SEP || type == LX_PIPE)
		{
			ft_lst_detach_from(lexems, link);
			ft_free_lexem(link);
		}
		else
			break;
		link = next;
	}
}

void ft_trim_lexems_back(t_list **lexems)
{
	t_list	*link;
	t_list	*prev;
	int		type;

	link = ft_lstlast(*lexems);
	while(link)
	{
		prev = ft_lst_find_preceding(lexems, link);
		type = ft_ectracttype(link);
		if (type == LX_AND || type == LX_OR || type == LX_SEP || type == LX_PIPE)
		{
			ft_lst_detach_from(lexems, link);
			ft_free_lexem(link);
		}
		else
			break;
		link = prev;
	}
}

/* if the first token is AND or OR print error */
int	ft_count_groups(t_list **lexems)
{
	int		counter;
	int		type;
	t_list	*link;

	ft_trim_lexems_front(lexems);
	ft_trim_lexems_back(lexems);
	if (!*lexems)
		return (0);
	counter = 1;
	link = *lexems;
	type = ft_ectracttype(link);

	while (link)
	{
		type = ft_ectracttype(link);
		if (type == LX_AND || type == LX_OR)
			counter++;
		link = link->next;
	}
	return (counter);
}

void	ft_init_group(t_msh *msh, int i, int type)
{
	msh->groups[i] = malloc(sizeof(t_group));
	msh->groups[i]->index = i;
	msh->groups[i]->lexems = malloc(sizeof(t_list *));
	*msh->groups[i]->lexems = NULL;
	if (i == 0)
		msh->groups[i]->type = -1;
	else
		msh->groups[i]->type = type;
}

void	ft_make_agroup(t_msh *msh, int i)
{
	t_list	*link;
	int		type;
	char	*text;

	link = *msh->lexems;
	ft_init_group(msh, i, ft_ectracttype(link));
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
}

int	ft_makegroups(t_msh *msh)
{
	int		i;

	msh->group_num = ft_count_groups(msh->lexems);
	printf("gr num: %d\n", msh->group_num);
	if (msh->group_num <= 0)
	{
		ft_free_lexems(msh->lexems);
		return (ft_error("could not parse", -300));
	}
	msh->groups = malloc(sizeof(t_group *) * msh->group_num);
	i = 0;
	while (i < msh->group_num)
	{
		ft_make_agroup(msh, i);
		i++;
	}
	return (msh->group_num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:55:47 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/24 23:55:53 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_trim_lexems_front(t_list **lexems)
{
	t_list	*link;
	t_list	*next;
	int		type;

	link = *lexems;
	while (link)
	{
		next = link->next;
		type = ft_ectracttype(link);
		if (type == LX_AND || type == LX_OR
			|| type == LX_SEP || type == LX_PIPE)
		{
			ft_lst_detach_from(lexems, link);
			ft_free_lexem(link);
		}
		else
			break ;
		link = next;
	}
}

void	ft_trim_lexems_back(t_list **lexems)
{
	t_list	*link;
	t_list	*prev;
	int		type;

	link = ft_lstlast(*lexems);
	while (link)
	{
		prev = ft_lst_find_preceding(lexems, link);
		type = ft_ectracttype(link);
		if (type == LX_AND || type == LX_OR
			|| type == LX_SEP || type == LX_PIPE)
		{
			ft_lst_detach_from(lexems, link);
			ft_free_lexem(link);
		}
		else
			break ;
		link = prev;
	}
}

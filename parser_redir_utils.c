/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:39:08 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/13 19:47:54 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lst_shift_head_n(t_list **head, int n)
{
	t_list	*link;

	if (!head)
		return (NULL);
	link = *head;
	while (n-- && link)
	{
		*head = link->next;
		link = link->next;
	}
	return (*head);
}

/*	Returns NULL if head does not exist or points to NULL (i.e.
	there are no links in the list) or there is no link
	between the head and he target link */
t_list	*ft_lst_find_preceding(t_list **head, t_list *target)
{
	t_list	*link;

	if (!head)
		return (NULL);
	if (*head == target)
		return (NULL);
	link = *head;
	while (link)
	{
		if (link->next == target)
			return (link);
		link = link-> next;
	}
	return (NULL);
}

t_list	*ft_lst_detach_from(t_list **headfrom, t_list *target)
{
	t_list	*preceding;

	if (!headfrom)
		exit(1);
	if (*headfrom == target)
		*headfrom = ft_lst_shift_head_n(headfrom, 1);
	else
	{
		preceding = ft_lst_find_preceding(headfrom, target);
		if (preceding)
			preceding->next = target->next;
	}
	target->next = NULL;
	return (target);
}

void	ft_free_lexem(t_list *link)
{
	free(ft_ectracttext(link));
	free(link->content);
	free(link);
}

char	*ft_strjoinfree(char *tofree1, char *tofree2)
{
	char	*newline;

	newline = ft_strjoin(tofree1, tofree2);
	free(tofree1);
	free(tofree2);
	return (newline);
}

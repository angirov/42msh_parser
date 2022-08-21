/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:50:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/15 00:50:27 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lst_penult(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}

t_lexem	*ft_newlexem(int lx_type, char *text)
{
	t_lexem	*lexem;

	lexem = malloc(sizeof(t_lexem));
	lexem->text = text;
	lexem->type = lx_type;
	return (lexem);
}

void	ft_addlexem(t_list **lexems, t_lexem *lexem)
{
	t_list	*new;

	new = ft_lstnew(lexem);
	if (*lexems)
		ft_lstadd_back(lexems, new);
	else
		*lexems = new;
}

void	ft_dellastsep(t_list **lexems)
{
	t_list	*last;

	last = ft_lstlast(*lexems);
	if (last && (*(t_lexem *)last->content).type == LX_SEP)
	{
		ft_lst_penult(*lexems)->next = NULL;
		ft_free_lexem(last);
	}
}

// (*(t_lexem *)link->content).text
char	*ft_ectracttext(t_list *link)
{
	return ((*(t_lexem *)link->content).text);
}

int	ft_ectracttype(t_list *link)
{
	return ((*(t_lexem *)link->content).type);
}
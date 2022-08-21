/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:10:15 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/13 19:49:26 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expand_all_groups_vars(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->group_num)
	{
		ft_expand_gr_vars(msh, i);
	}
}

/*	Returns malloced string string==value of the variable*/
char	*ft_get_var_value(char *text, t_msh *msh)
{
	t_env	*var;

	if (ft_strncmp(text, "?", 2) == 0)
		return (ft_itoa(msh->last_exit_stat));
	var = find_env_node(msh->env_list, text);
	if (var)
		return (ft_strdup(var->bash_v_content));
	else
		return (NULL);
}

void	ft_expand_gr_vars(t_msh *msh, int group_i)
{
	t_list	*link;
	t_list	*next;
	char	*value;
	char	*text;

	link = *msh->groups[group_i]->lexems;
	while (link)
	{
		next = link->next;
		if (ft_ectracttype(link) == LX_VAR)
		{
			text = (*(t_lexem *)link->content).text;
			value = ft_get_var_value(text, msh);
			if (value)
			{
				(*(t_lexem *)link->content).text = value;
				(*(t_lexem *)link->content).type = LX_WORD;
			}
			else
			{
				ft_lst_detach_from(msh->groups[group_i]->lexems, link);
			}
		}
		link = next;
	}
}

int	ft_get_var_len(char *ptr, t_msh *msh)
{
	int		len;
	char	*closings;

	closings = msh->delims[LX_VAR] + 1;
	len = 0;
	while (*ptr && !ft_strchr(closings, *ptr))
	{
		len++;
		ptr++;
	}
	return (len);
}

char	*ft_expand_text(t_msh *msh, char *text)
{
	char	*ptr;
	char	*ret;
	char	*name;
	char	*value;
	int		len;

	ptr = text;
	ret = malloc(sizeof(char));
	ret[0] = '\0';
	while (*ptr)
	{
		if (*ptr != '$')
		{
			ret = ft_strjoinfree(ret, ft_chr2str(*ptr));
			ptr++;
		}
		else
		{
			len = ft_get_var_len(++ptr, msh);
			name = ft_gettext(ptr, len);
			value = ft_get_var_value(name, msh);
			free(name);
			if (value)
			{
				ret = ft_strjoinfree(ret, value);
			}
			ptr += len;
		}
	}
	return (ret);
}

void	ft_expand_gr_fields(t_msh *msh, int group_i)
{
	t_list	*link;
	t_list	*next;
	char	*text;
	char	*expanded;

	link = *msh->groups[group_i]->lexems;
	while (link)
	{
		next = link->next;
		if (ft_ectracttype(link) == LX_EXT_FIELD)
		{
			text = (*(t_lexem *)link->content).text;
			expanded = ft_expand_text(msh, text);
			free(text);
			(*(t_lexem *)link->content).text = expanded;
		}
		link = next;
	}
}

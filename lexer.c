/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:13:13 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/24 23:33:20 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_delims(t_msh *msh)
{
	char	**delims;

	msh->lexems = NULL;
	delims = malloc(sizeof(char *) * (LX_NUM + 1));
	delims[LX_FIELD] = "''";
	delims[LX_EXT_FIELD] = "\"\"";
	delims[LX_VAR] = "$$ '\"@!#%^&*()+_-=}{[]\\/?.,<>`~";
	delims[LX_PAR] = "()";
	delims[LX_PIPE] = "|";
	delims[LX_REDIR_OUT] = ">";
	delims[LX_REDIR_IN] = "<";
	delims[LX_AND] = "&&";
	delims[LX_OR] = "||";
	delims[LX_REDIR_APPEND] = ">>";
	delims[LX_REDIR_INSRC] = "<<";
	delims[LX_NUM] = "  $|'\"><&";
	msh->delims = delims;
}

char	*ft_getfield(int lx_type, char *ptr, t_msh *msh)
{
	int		len;
	char	*start;
	char	*closings;

	closings = msh->delims[lx_type] + 1;
	len = 0;
	start = ptr;
	while (*ptr && !ft_strchr(closings, *ptr))
	{
		len++;
		ptr++;
	}
	ft_addlexem(msh->lexems, ft_newlexem(lx_type, ft_gettext(start, len)));
	if (*ptr && lx_type <= LX_EXT_FIELD)
		ptr++;
	return (ptr);
}

char	*ft_finding(char *ptr, t_msh *msh, int i)
{
	if (i <= LX_VAR)
		return (ft_getfield(i, ++ptr, msh));
	else if (i >= LX_PIPE && i <= LX_REDIR_IN \
		&& ((*(ptr + 1) && *(ptr + 1) != *ptr) || !*(ptr + 1)))
	{
		ft_addlexem(msh->lexems, ft_newlexem(i, ft_strdup("")));
		return (ptr + 1);
	}
	else if (i == LX_AND && ((*(ptr + 1) \
		&& *(ptr + 1) != *ptr) || !*(ptr + 1)))
	{
		ft_addlexem(msh->lexems, \
			ft_newlexem(LX_WORD, ft_chr2str(*ptr)));
		return (ptr + 1);
	}
	else if (i >= LX_AND && i <= LX_REDIR_INSRC && *(ptr + 1) == *ptr)
	{
		ft_addlexem(msh->lexems, ft_newlexem(i, ft_strdup("")));
		return (ptr + 2);
	}
	return (NULL);
}

char	*ft_findsym(char *ptr, t_msh *msh)
{
	int		i;
	char	*result;

	i = 0;
	while (*ptr && i < LX_NUM)
	{
		if (*ptr == msh->delims[i][0])
		{
			result = ft_finding(ptr, msh, i);
			if (result)
				return (result);
		}
		i++;
	}
	return (ptr);
}

void	ft_lexer(char *line, t_msh *msh)
{
	char	*ptr;
	char	*tmp;

	msh->lexems = malloc(sizeof(t_list *));
	*msh->lexems = NULL;
	ptr = line;
	while (*ptr)
	{
		ptr = ft_skip_spaces(ptr, msh);
		tmp = ft_findsym(ptr, msh);
		if (*ptr && ptr == tmp)
		{
			ptr = ft_getfield(LX_WORD, ptr, msh);
		}
		else
			ptr = tmp;
	}
	ft_dellastsep(msh->lexems);
}

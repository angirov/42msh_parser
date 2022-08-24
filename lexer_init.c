/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:28:26 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/24 23:57:55 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_gettext(char *ptr, int len)
{
	char	*text;
	int		i;

	text = malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		text[i] = ptr[i];
		i++;
	}
	text[i] = '\0';
	return (text);
}

char	*ft_skip_spaces(char *ptr, t_msh *msh)
{
	int	sep;

	sep = 0;
	while (*ptr && *ptr == ' ')
	{
		ptr++;
		sep++;
	}
	if (sep && ft_lstsize(*msh->lexems))
		ft_addlexem(msh->lexems, ft_newlexem(LX_SEP, ft_strdup("")));
	return (ptr);
}

char	*ft_chr2str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = 0;
	return (str);
}

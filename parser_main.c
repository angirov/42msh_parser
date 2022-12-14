/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:37:48 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/24 23:38:52 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse_group(t_msh *msh, int group_i)
{
	ft_expand_gr_vars(msh, group_i);
	ft_expand_gr_fields(msh, group_i);
	ft_make_cmd_args(msh->groups[group_i]);
	ft_loop_cmds(msh->groups[group_i], ft_expand_gr_wcs);
	msh->groups[group_i]->cmds->redirs = malloc(sizeof(t_list **) \
		* msh->groups[group_i]->cmds->cmd_num);
	ft_loop_cmds(msh->groups[group_i], ft_init_redirs);
	ft_loop_cmds(msh->groups[group_i], ft_format_redirs);
	ft_unite_texts(msh->groups[group_i]);
	ft_loop_cmds(msh->groups[group_i], ft_extract_redirs);
	msh->groups[group_i]->cmds->newargvs = \
		ft_calloc(msh->groups[group_i]->cmds->cmd_num, sizeof(char **));
	ft_make_newargvs(msh->groups[group_i]);
}

void	ft_parser(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->group_num)
	{
		ft_parse_group(msh, i);
		i++;
	}
}

int	ft_error(char *error_text, int error_num)
{
	ft_fdprintf(2, "minishell: %s (%d)\n", error_text, -error_num);
	return (error_num);
}

void	ft_loop_for_sep(t_list	*link, t_list	*next)
{
	char	*text;

	while (next && ft_ectracttype(next) \
		!= LX_SEP && ft_is_redir(ft_ectracttype(next)) == -1)
	{
		text = ft_ectracttext(link);
		((t_lexem *)(link->content))->text = \
			ft_strjoin(text, ft_ectracttext(next));
		link->next = next->next;
		free(text);
		ft_free_lexem(next);
		next = link->next;
	}
}

int	ft_unite_texts(t_group *group)
{
	int		cmd_i;
	t_list	*link;
	t_list	*next;

	cmd_i = 0;
	while (cmd_i < group->cmds->cmd_num)
	{
		link = *group->cmds->cmd_args[cmd_i];
		while (link)
		{
			if (ft_ectracttype(link) != LX_SEP)
			{
				next = link->next;
				ft_loop_for_sep(link, next);
			}
			link = link->next;
		}
		cmd_i++;
	}
	return (0);
}

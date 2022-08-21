/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:34:14 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/15 00:03:09 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// parser_main.c
void	ft_parse_group(t_msh *msh, int group_i);
void	ft_parser(t_msh *msh);
int		ft_error(char *error_text, int error_num);

// parser_wc.c
void	ft_expand_gr_wcs(t_group *group, int cmd_i);

// parser_groups.c
int		ft_makegroups(t_msh *msh);
int		ft_count_groups(t_list **lexems);
int		ft_unite_texts(t_group *group);

// parser_cmds.c
int		ft_count_cmds(t_list **lexems);
int		ft_count_args(t_list **cmd_args);
int		ft_make_cmd_args(t_group *group);
int		ft_make_newargvs(t_group *group);

// redirs
int		ft_is_redir(int type);
void	ft_loop_cmds(t_group *group, void (*opearation)(t_group *, int i));
void	ft_init_redirs(t_group *group, int cmd_i);
void	ft_format_redirs(t_group *group, int cmd_i);
void	ft_extract_redirs(t_group *group, int cmd_i);

// redir_utils
t_list	*ft_lst_shift_head_n(t_list **head, int n);
t_list	*ft_lst_find_preceding(t_list **head, t_list *target);
t_list	*ft_lst_detach_from(t_list **headfrom, t_list *target);
void	ft_free_lexem(t_list *link);
char	*ft_strjoinfree(char *tofree1, char *tofree2);

// printing
void	ft_printlexems(t_list **lexems);
void	ft_print_arg_redir(t_group *group);
void	ft_print_newargvs(t_group *group);
void	ft_print_groups(t_msh *msh);

// expantion
void	ft_expand_gr_vars(t_msh *msh, int group_i);
void	ft_expand_gr_fields(t_msh *msh, int group_i);

// freeings.c
void	ft_free_lexems(t_list **head);
void	ft_free_groups(t_msh *msh);
void	ft_free_msh(t_msh *msh);

#endif

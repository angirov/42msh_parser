/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:34:14 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/25 00:27:04 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* freeings.c */
void	ft_free_lexems(t_list **head);
void	ft_free_gr_lexems(t_group *group, int cmd_i);
void	ft_free_groups(t_msh *msh);
void	ft_free_msh(t_msh *msh);

/* lexems.c */
t_lexem	*ft_newlexem(int lx_type, char *text);
void	ft_addlexem(t_list **lexems, t_lexem *lexem);
void	ft_dellastsep(t_list **lexems);
char	*ft_ectracttext(t_list *link);

/* lexer.c */
void	ft_init_delims(t_msh *msh);
char	*ft_getfield(int lx_type, char *ptr, t_msh *msh);
char	*ft_finding(char *ptr, t_msh *msh, int i);
char	*ft_findsym(char *ptr, t_msh *msh);
void	ft_lexer(char *line, t_msh *msh);

/* lexer_init.c */
char	*ft_gettext(char *ptr, int len);
char	*ft_skip_spaces(char *ptr, t_msh *msh);
char	*ft_chr2str(char c);

/* lists.c */
t_list	*ft_lst_penult(t_list *lst);

/* parser_argvs.c */
int		ft_count_args(t_list **cmd_args);
void	ft_make_argv(t_group *group, int cmd_i, int arg_num);
int		ft_make_newargvs(t_group *group);

/* parser_cmds.c */
int		ft_count_cmds(t_list **lexems);
void	ft_loop_thru_args(t_list *link, t_group *group, int i);
int		ft_make_cmd_args(t_group *group);

/* parser_expansion.c */
char	*ft_get_var_value(char *text, t_msh *msh);
void	ft_expand_gr_vars(t_msh *msh, int group_i);
int		ft_get_var_len(char *ptr, t_msh *msh);
char	*ft_expand_text(t_msh *msh, char *text);
void	ft_expand_gr_fields(t_msh *msh, int group_i);

/* parser_groups.c */
int	ft_count_groups(t_list **lexems);
void	ft_init_group(t_msh *msh, int i, int type);
void	ft_make_agroup(t_msh *msh, int i);
int		ft_makegroups(t_msh *msh);

/* parser_main.c */
void	ft_parse_group(t_msh *msh, int group_i);
void	ft_parser(t_msh *msh);
int		ft_error(char *error_text, int error_num);
void	ft_loop_for_sep(t_list	*link, t_list	*next);
int		ft_unite_texts(t_group *group);

/* parser_redirs.c */
int	ft_is_redir(int type);
void	ft_loop_cmds(t_group *group, void (*opearation)(t_group *, int i));
void	ft_init_redirs(t_group *group, int cmd_i);
void	ft_format_redirs(t_group *group, int cmd_i);
void	ft_extract_redirs(t_group *group, int cmd_i);

/* parser_redir_utils.c */
t_list	*ft_lst_shift_head_n(t_list **head, int n);
t_list	*ft_lst_find_preceding(t_list **head, t_list *target);
t_list	*ft_lst_detach_from(t_list **headfrom, t_list *target);
void	ft_free_lexem(t_list *link);
char	*ft_strjoinfree(char *tofree1, char *tofree2);

/* printer.c */
void	ft_printlexems(t_list **lexems);
void	ft_print_arg_redir(t_group *group);
void	ft_print_newargvs(t_group *group);
void	ft_print_groups(t_msh *msh);

/* parser_wc.c */
void	ft_exchange_link_for_list(t_list **head, t_list *target, t_list *new);
void	ft_print_split(char **arr);
t_list	*ft_expanded2list(char *expanded);
void	ft_expand_gr_wcs(t_group *group, int cmd_i);

/* trimmers.c */
void	ft_trim_lexems_front(t_list **lexems);
void	ft_trim_lexems_back(t_list **lexems);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/03/16 13:40:44 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

//prototyping global struct
typedef struct s_global t_global;

typedef struct s_redir //become redirection
{
	int					redirection;
	char				*content;
	struct  s_parser	*prev;
	struct  s_parser	*next;
} t_redir;

typedef struct s_args //become args
{
	char			*content;
	int				 index;	
	struct  s_args	 *prev;
	struct  s_args	 *next;
} t_args;

typedef struct s_parser
{
	char				*cmd;
	char				*options;
	int					index;
	struct  s_args   	*args;
	struct  s_redir  	*redir; 
	struct  s_args	 	*prev;
	struct  s_args	 	*next;
} t_parser;

// utils/args_utils.c
t_args	*argsnew_ms(char *content, int x);
void	argsaddback_ms(t_args **lst, t_args *new);
t_args	*argsfreelist_ms(t_args **lst);

// utils/redir_utils.c
t_redir	*redirnew_ms(char *content, int redir);
void	rediraddback_ms(t_redir **lst, t_redir *new);
t_redir *redirfreelist_ms(t_redir **lst);

// utils/parser_utils.c
t_parser	*parsernew_ms(char *cmd, char *content, int redir, int x);
void	parseraddback_ms(t_parser **lst, t_parser *new);
t_parser *parserfreelist_ms(t_parser **lst);

//define_join.c
int	define_groups(t_global **global);
void join_cmd(t_global **global);

#endif

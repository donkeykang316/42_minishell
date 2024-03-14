/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/03/14 18:00:53 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

//prototyping global struct
typedef struct s_global t_global;

typedef struct s_parser //become redirection
{
	int		redirection;
	char	*content;
	struct  s_parser	*prev;
	struct  s_parser	*next;
} t_parser;

typedef struct s_temp //become args
{
	char	*content;
	int		index;	
	struct  s_args	 *prev;
	struct  s_args	 *next;
} t_temp;

typedef struct s_args
{
	char	*cmd;
	char	*options;
	struct  s_temp   *temp;
	struct  s_parser *parser; 
	struct  s_args	 *prev;
	struct  s_args	 *next;
} t_args;

// utils/parser_utils.c
t_parser	*parsernew_ms(char *cmd, char *content, int redir, int x);
void	parseraddback_ms(t_parser **lst, t_parser *new);
t_parser *parserfreelist_ms(t_parser **lst);

//define_join.c
int	define_groups(t_global **global);
void join_cmd(t_global **global);

#endif

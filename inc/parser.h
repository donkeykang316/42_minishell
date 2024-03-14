/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/03/14 13:44:05 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

//prototyping global struct
typedef struct s_global t_global;

typedef struct s_parser
{
	char	*cmd;
	int		redirection;
	int		index;
	char	*content;
	struct  s_parser	*prev;
	struct  s_parser	*next;
} t_parser;

// utils/parser_utils.c
t_parser	*parsernew_ms(char *cmd, char *content, int redir, int x);
void	parseraddback_ms(t_parser **lst, t_parser *new);
t_parser *parserfreelist_ms(t_parser **lst);

//define_join.c
int	define_groups(t_global **global);

#endif

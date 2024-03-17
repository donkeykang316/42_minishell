/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:12:05 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/17 12:35:23 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"

//prototyping prompt struct
typedef struct s_prompt t_prompt;

//main_utils.c
t_prompt *init_prompt(t_prompt *prompt);
char	**double_dup(char **str);
void	free_double(char **double_str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:22:54 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/01 13:08:26 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "../collection/list.h" 
# include "../parser/compiler.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define ECHO	0
# define CD		1
# define PWD	2
# define EXPORT	3
# define UNSET	4
# define ENV	5
# define EXIT	6


typedef struct s_pro_join
{
	char		*envp_join;
}t_pro_join;

void	pipe_start(t_list *tokens);

#endif
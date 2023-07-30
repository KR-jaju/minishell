/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:22:54 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/30 19:01:56 by jaeyojun         ###   ########seoul.kr  */
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


typedef struct s_pipe
{
	int		pipe_fds_from_prev[2];
	int		pipe_fds_to_next[2];
}t_pipe;
void	pipe_start(t_list *tokens);

#endif
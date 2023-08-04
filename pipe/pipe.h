/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:22:54 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/04 16:51:27 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <str/str.h>
# include <parser/tokenizer.h>
# include <collection/list.h>
# include <parser/compiler.h>
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

void		process_run(t_list *tokens);
int			execute_fork(t_list *p_test);
void		wait_process(int pid);
void		child_process(t_process	*tmp, int *prev_read_fd, int *next);
void		parent_process(int *prev_read_fd, int *next);
int			check_builtin(char *name, int *idx);
int			execute(t_process *process);
int			execute_builtins(int builtin_idx, t_process *tmp);
void		execute_no_fork(t_process *tmp, int builtin_idx);
char const	*envp_split(char const *envp_path, char *cmd);

#endif

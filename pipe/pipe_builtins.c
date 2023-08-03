/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:46:26 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/03 21:55:40 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <shell/minishell.h>

int		echo_main(t_process *this);
int		pwd_main(t_process *this);
int		cd_main(t_process *this);
int		export_main(t_process *this);
int		execute(t_process *process);
int		env_main(t_process *this);
int		exit_main(t_process *this);
int		unset_main(t_process *this);

//builtin 첫 번째 
void	start_builtin(t_process *tmp, int builtin_idx)
{
	int	stdout_copy;

	stdout_copy = dup(1);
	dup2(tmp->out_fd, 1);
	g_minishell.exit_code = execute_builtins(builtin_idx, tmp);
	dup2(stdout_copy, 1);
	close(stdout_copy);
}

//builtin인 검사
int	check_builtin(char *name, int *idx)
{
	char**const	builtins = (char *[]){
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};
	int			i;

	if (name == (void *)0)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (str_equals(name, builtins[i]) == 1)
			return (*idx = i, 1);
		i++;
	}
	return (0);
}

//builtins 실행
int	execute_builtins(int builtin_idx, t_process *tmp)
{
	if (builtin_idx == ECHO)
		return (echo_main(tmp));
	else if (builtin_idx == CD)
		return (cd_main(tmp));
	else if (builtin_idx == PWD)
		return (pwd_main(tmp));
	else if (builtin_idx == EXPORT)
		return (export_main(tmp));
	else if (builtin_idx == UNSET)
		return (unset_main(tmp));
	else if (builtin_idx == ENV)
		return (env_main(tmp));
	else if (builtin_idx == EXIT)
		return (exit_main(tmp));
	return (0);
}

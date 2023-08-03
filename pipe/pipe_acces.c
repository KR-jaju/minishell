/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_acces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:10:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/03 22:07:34 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <shell/minishell.h>
#include <parser/compiler.h>
#include <launcher/error.h>
#include <libft/libft.h>
#include <signal/signal.h>
#include <readline/readline.h>
#include <string.h>

//builtin or 명령어 실행
int	execute(t_process *process)
{
	char const	*path_envp = get_env("PATH");
	int			builtin_idx;
	char const	*path_split;

	if (process->name == (void *)0)
		exit(0);
	path_split = envp_split(path_envp, process->name);
	if (check_builtin(process->name, &builtin_idx))
		return (exit(execute_builtins(builtin_idx, process)), 0);
	else
	{
		if (execve(path_split, process->argv, get_envp()) == -1)
		{
			printf("bash: %s: command not found\n", process->argv[0]);
			exit(127);
		}
		return (1);
	}
}

//signal에 대한 exitcode_넣어주기
void	child_signal(int status, int *i, int pid, int child)
{
	int	signo;

	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if ((*i) == 0)
		{
			if (signo == SIGINT)
				printf("^C\n");
			else if (signo == SIGQUIT)
				printf("^\\Quit: 3\n");
			(*i) = 1;
		}
		if (child == pid)
			g_minishell.exit_code = 128 + signo;
	}
	else if (child == pid)
		g_minishell.exit_code = WEXITSTATUS(status);
}

//끝난 자식의 프로세스 exit_code 반영과, 표준 입력을 받을 때 signal 
void	exitcode_signal(int pid)
{
	int	i;
	int	status;
	int	child;

	i = 0;
	child = waitpid(0, &status, 0);
	while (child > 0)
	{
		child_signal(status, &i, pid, child);
		child = waitpid(0, &status, 0);
	}
}

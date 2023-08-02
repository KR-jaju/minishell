/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_acces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:10:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/02 15:14:07 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "../parser/tokenizer.h"
#include "../shell/minishell.h"
#include "../str/str.h"
#include "../parser/compiler.h"
#include <errno.h>
#include <string.h>

int		echo_main(t_process *this);
int 	pwd_main(t_process *this);
int		cd_main(t_process *this);
int		export_main(t_process *this);
int		execute(t_process *process);
int		env_main(t_process *this);
int		exit_main(t_process *this);
int		unset_main(t_process *this);
void	execute_error(char *tmp, char *name);

char	const *check_acces(char *envp, char *cmd)
{
	char	*tmp;
	char	const *envp_plus;

	tmp = str_join("/", cmd);
	//printf("tmp : %s\n", tmp);
	envp_plus = str_join(envp, tmp);
	//printf("envp_plus : %s\n", envp_plus);
	free(tmp);
	return (envp_plus);

}

char const	*envp_split(char const *envp_path, char *cmd)
{
	char	*envp = str_clone(envp_path);
	char	*envp_split;
	char	const	*combine;
	int		fd;

	int i = 0;
	if (!envp_path || !cmd)
		return (NULL);
	while (1)
	{
		if (i == 0)
		{
			envp_split = str_tokenize(envp, ":");
			i++;
		}
		else
			envp_split = str_tokenize((void *)0, ":");
		if (!envp_split)
			break ;
		combine = check_acces(envp_split, cmd);
		//printf("combine : %s\n" , combine );
		fd = access(combine, X_OK);
		if (fd != -1)
		{
			//free(envp_split);
			return (combine);
		}
		close(fd);
		//free(combine);
	}
	
	return (NULL);
}




int	is_builtin(char *name, int *idx)
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




int	execute(t_process *process)
{
	char const	*path_envp = get_env("PATH");
	int			builtin_idx;
	char const	*path_split;

	if (process->name == (void *)0)
		exit(0);
	path_split = envp_split(path_envp, process->name);
	if (is_builtin(process->name, &builtin_idx))
	{
		return (exit(execute_builtins(builtin_idx, process)), 0);
	}
	else
	{
		//printf("DEBUG\n");
		printf("pro->name  : %s\n", process->name);
		if (execve(path_split, process->argv, get_envp()) == -1)
		{
			printf("bash: %s: command not found\n", process->argv[0]);
			exit(127);
		}
		return (1);
	}
}
//1. 프로세스가 1개냐 아니냐로 분기
//2. 프로세스가 1개이면 빌트인인지 확인

// 프로세스가 1개이면 빌트인인지 확인
//프로세스가 1개냐 아니냐로 분기
#include <libft/libft.h>
void	pipe_acces(t_list *p_test)
{
	t_process	*tmp;
	int			i;
	int			builtin_idx;
	int			pid;
	int			prev_read_fd;
	int			next[2] = {0, 1};
	int			last_pid;

	tmp = list_get(p_test, 0);
	if (p_test->length == 1 && is_builtin(tmp->name, &builtin_idx)) // fork 없이 빌트인 실행 조건
	{
		int stdout_copy = dup(1);
		dup2(tmp->out_fd, 1);
		g_minishell.exit_code = execute_builtins(builtin_idx, tmp);
		dup2(stdout_copy, 1);
		close(stdout_copy);
	}
	else // 그 외 일반적인 경우
	{	
		i = 0;
		prev_read_fd = dup(0);
		while (i < p_test->length)
		{
			tmp = list_get(p_test, i);
			if (i != p_test->length - 1) // 현재 프로세스가 마지막 프로세스가 아니라면
				pipe(next); //파이프 생성
			else
			{
				next[0] = dup(0);// (닫을 수 있는) 표준 출력을 next fd에 넣는다.
				next[1] = dup(1);
			}
			pid = fork(); // 자식 프로세스 생성
			//
			if (i == p_test->length - 1)
				last_pid = pid;
			//
			if (pid == 0) // 자식 프로세스
			{
				if (tmp->in_fd == 0) // Input redirection이 없을 때는
					tmp->in_fd = prev_read_fd; // 그 자리를 이전 파이프에서 받는 fd로 채운다
				else
					close(prev_read_fd);
				if (tmp->out_fd == 1) // Output redirection이 없을 때는
					tmp->out_fd = next[1]; // 그 자리를 다음 파이프에 쓰는 fd로 채운다
				else
					close(next[1]);
				dup2(tmp->in_fd, 0); // 표준 입출력이 in_fd와 out_fd를 대체하도록 한다
				dup2(tmp->out_fd, 1);
				close(tmp->out_fd);
				close(tmp->in_fd); // in_fd와 out_fd는 닫아도 된다.
				close(next[0]);// 남은 fd는 다음 파이프에서 받는 fd뿐
				execute(tmp);
			}
			else if (pid > 0)
			{
				close(prev_read_fd);// 이전 파이프에서 받는 fd는 더 이상 쓸 일이 없다.
				close(next[1]);// 다음 파이프에 출력하는 것도 더이상 필요 없다.
				prev_read_fd = next[0];

				if (i == p_test->length - 1)
				{
					while (waitpid(last_pid, &g_minishell.exit_code, 0) > 0)
						;
					if (WIFEXITED(g_minishell.exit_code))
						g_minishell.exit_code = WEXITSTATUS(g_minishell.exit_code);
				}
			}
			i++;
		}
		close(prev_read_fd); // 모든게 끝나고 남은 건 이전 파이프의 읽는 fd
		while (wait((void *)0) > 0)
			;
	}
}


void	pipe_start(t_list *tokens)
{
	t_list p_test = compile(tokens);
	pipe_acces(&p_test);
}
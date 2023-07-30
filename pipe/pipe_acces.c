/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_acces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:10:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/30 18:40:43 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "../parser/tokenizer.h"
#include "../shell/minishell.h"
#include "../str/str.h"
#include "../parser/compiler.h"

void	echo_main(t_process *this);
int 	pwd_main(t_process *this);
void	cd_main(t_process *this);
int		export_main(t_process *this);
int		execute(t_process *process);
int		exit_main(t_process *this);
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

	i = 0;
	while (i < 7)
	{
		if (str_equals(name, builtins[i]) == 1)
			return (*idx = i, 1);
		i++;
	}
	return (0);
}

void	execute_builtins(int builtin_idx, t_process *tmp)
{
	if (builtin_idx == ECHO)
		echo_main(tmp);
	else if (builtin_idx == CD)
		cd_main(tmp);
	else if (builtin_idx == PWD)
		pwd_main(tmp);
	 else if (builtin_idx == EXPORT)
	 	export_main(tmp);
	// else if (check_builtins == UNSET)
	// 	execute_UNSET();
	// else if (check_builtins == ENV)
	// 	execute_ENV();
	else if (builtin_idx == EXIT)
		exit_main(tmp);
}


// void	pipe_execute(t_process *tmp, char const *path_split)
// {
// 	//printf("tmp->argc : %d\n", tmp->argc);
// 	//printf("%s\n", path_split);
// }

int	execute(t_process *process)
{
	char const	*path_envp = get_env("PATH");
	int			builtin_idx;
	char const	*path_split;

	path_split = envp_split(path_envp, process->name);
	//printf("path_split : %s\n", path_split);
	// printf("tmp -> outfd : %d\n", tmp->out_fd);
	// printf("tmp -> outfd : %d\n", tmp->in_fd);
	// printf("tmp -> outfd : %d\n", tmp->bad_process);
	//pipe_execute(tmp, path_split);
	// execve(path_split, tmp->argv, get_envp());
	if (is_builtin(process->name, &builtin_idx))
	{
		return (execute_builtins(builtin_idx, process), 0);
	}
	else
	{
		//printf("debug");
		if ((execve(path_split, process->argv, get_envp()) == -1))
			//execute_error("command not found\n", process->name);
			return (0);
		return (1);
	}
}
//1. 프로세스가 1개냐 아니냐로 분기
//2. 프로세스가 1개이면 빌트인인지 확인

// 프로세스가 1개이면 빌트인인지 확인
//프로세스가 1개냐 아니냐로 분기

void	pipe_acces(t_list *p_test)
{
	t_process	*tmp;
	int			i;
	int			j;
	int			builtin_idx;
	int			pid;
	int			pipe_fds[2] = {0, 1};
	//int			prev_fds[2] = {0, 1};

	i = 0;
	j = 0;
	while (i < p_test->length)
	{
		tmp = list_get(p_test, i);
		printf("i[%d] tmp->out_fd : %d\n", i, tmp->out_fd);
		printf("i[%d] tmp->in_fd : %d\n", i, tmp->in_fd);
		if (p_test->length == 1 && is_builtin(tmp->name, &builtin_idx))
			execute_builtins(builtin_idx, tmp);
		else
		{
			pid = fork();
			if (tmp->in_fd == 0)
				tmp->in_fd = pipe_fds[0];
			//printf("prev_fds[0] : %d, prev_fds[1] : %d\n", prev_fds[0], prev_fds[1]);
			printf("pipe_fds[0] : %d, pipe_fds[1] : %d\n", pipe_fds[0], pipe_fds[1]);
			//prev_fds[0] = pipe_fds[0];
			//prev_fds[1] = pipe_fds[1];
			//printf("2 prev_fds[0] : %d, prev_fds[1] : %d\n", prev_fds[0], prev_fds[1]);
			//printf("2 pipe_fds[0] : %d, pipe_fds[1] : %d\n", pipe_fds[0], pipe_fds[1]);
			pipe(pipe_fds);
			//printf("3 prev_fds[0] : %d, prev_fds[1] : %d\n", prev_fds[0], prev_fds[1]);
			printf("3 pipe_fds[0] : %d, pipe_fds[1] : %d\n", pipe_fds[0], pipe_fds[1]);
			if (tmp->out_fd == 1)
				tmp->out_fd = pipe_fds[1];
			if (pid == -1)
				perror("fork error");
			else if (pid == 0)
			{
				execute(tmp);
				j++;
				// else
				// 	execute_error("command not found", tmp->name);
			}
		}
		i++;
	}
	while (j-- > 0)
		wait((void *)0);
}



void	pipe_start(t_list *tokens)
{
	t_list p_test = compile(tokens);
	pipe_acces(&p_test);
}
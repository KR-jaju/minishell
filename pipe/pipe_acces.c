/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_acces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:10:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/31 20:15:48 by jaeyojun         ###   ########seoul.kr  */
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

	printf("cmd - > : %s\n", cmd);
	tmp = str_join("/", cmd);
	printf("tmp : %s\n", tmp);
	envp_plus = str_join(envp, tmp);
	printf("envp_plus : %s\n", envp_plus);
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
		printf("envp : %s\n", envp_split);
		printf("ls : %s\n", cmd);
		combine = check_acces(envp_split, cmd);
		//printf("envp : %s\n", envp_split);
		printf("combine : %s\n" , combine );
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

	write(2, "DEBUG\n", 6);
	path_split = envp_split(path_envp, process->name);
	printf("process->name : %s\n", process->name);
	printf("path_split : %s\n", path_split);
	exit(1);
	//printf("path_split : %s\n", path_split);
	// printf("tmp -> outfd : %d\n", tmp->out_fd);
	// printf("tmp -> outfd : %d\n", tmp->in_fd);
	// printf("tmp -> outfd : %d\n", tmp->bad_process);
	//pipe_execute(tmp, path_split);
	// execve(path_split, tmp->argv, get_envp());
	if (is_builtin(process->name, &builtin_idx))
	{
		execute_builtins(builtin_idx, process);
		exit(0);
		return (0);
	}
	else
	{
		//printf("debug");
		write(2, path_split, str_length(path_split));
		write(2, "\n", 1);
		write(2, "argv : ", 8);
		write(2, process->argv[0], str_length(process->argv[0]));
		write(2, "argv awdawd : ", 14);
		if ((execve(path_split, process->argv, get_envp()) == -1))
			execute_error("command not found\n", process->name);
			//return (0);
		return (1);
	}
}
//1. 프로세스가 1개냐 아니냐로 분기
//2. 프로세스가 1개이면 빌트인인지 확인

// 프로세스가 1개이면 빌트인인지 확인
//프로세스가 1개냐 아니냐로 분기

void	pipe_acces(t_list *p_test, t_pipe *pipe_str)
{
	t_process	*tmp;
	int			i;
	int			j;
	int			builtin_idx;
	int			pid;
	//int			pipe_fds[2] = {0, 1};
	// int			prev_fds[2] = {0, 1};

	i = 0;
	j = 0;
	
	printf("p_test : %d\n", p_test->length);
	while (i < p_test->length)
	{
		tmp = list_get(p_test, i);
		printf("tmp -> name %s\n",tmp->name);
		//printf("i[%d] tmp->out_fd : %d\n", i, tmp->out_fd);
		//printf("i[%d] tmp->in_fd : %d\n", i, tmp->in_fd);
		if (p_test->length == 1 && is_builtin(tmp->name, &builtin_idx))
			execute_builtins(builtin_idx, tmp);
		else
		{
			//printf("number : %d\n" , i);
			//printf("first : pipe_fds[0] : %d, pipe_fds[1] : %d\n", pipe_fds[0], pipe_fds[1]);
			if (i > 1)
			{
				close(pipe_str->pipe_fds_from_prev[0]);
				close(pipe_str->pipe_fds_from_prev[1]);
			}
			//printf("first : prev_fds[0] : %d, prev_fds[1] : %d\n", pipe_str->pipe_fds_from_prev[0], pipe_str->pipe_fds_from_prev[1]);
			//printf("first : pipe_fds[0] : %d, pipe_fds[1] : %d\n", pipe_str->pipe_fds_to_next[0], pipe_str->pipe_fds_to_next[1]);
			pipe_str->pipe_fds_from_prev[0] = pipe_str->pipe_fds_to_next[0];
			pipe_str->pipe_fds_from_prev[1] =  pipe_str->pipe_fds_to_next[1];
			if (i < p_test->length - 1)
				pipe(pipe_str->pipe_fds_to_next);
			pid = fork();
			//printf("second : prev_fds[0] : %d, prev_fds[1] : %d\n", pipe_str->pipe_fds_from_prev[0], pipe_str->pipe_fds_from_prev[1]);
			//printf("second : pipe_fds[0] : %d, pipe_fds[1] : %d\n", pipe_str->pipe_fds_to_next[0], pipe_str->pipe_fds_to_next[1]);
			if (pid == -1)
				perror("fork error");
			else if (pid == 0)
			{
				//printf(" p_test->length : %d\n",  p_test->length);
				//printf("tmp in -> %d\n" ,tmp->in_fd );
				//printf("tmp out -> %d\n" ,tmp->out_fd );
				// if (tmp->in_fd == 0)
				// 	exit(1);
				if (i == 0)//처음일때
				{
					// printf("dfebnda");
					// printf("부모 프로세스 실행\n");
					// printf("부모 프로세스 ID: %d\n", getpid());
					// printf("자식 프로세스 ID: %d\n", pid);
					//if ( p_test->length == 1)//
					if (tmp->in_fd == 0 && p_test->length == 1)
					{
						write(2, "fuck\n", 5);
						execute(tmp);
					}
					else
					{
						close(pipe_str->pipe_fds_to_next[0]);
						dup2(pipe_str->pipe_fds_to_next[1], STDOUT_FILENO);
						close(pipe_str->pipe_fds_to_next[1]);
						execute(tmp);
					}
					
				}
				if (i != p_test->length - 1)//중간일때
				{
					//dup2(pipe_str->pipe_fds_from_prev[0], STD);
				}
				else 
				{
					close(pipe_str->pipe_fds_from_prev[1]);
					dup2(pipe_str->pipe_fds_from_prev[0], STDIN_FILENO);
					//dup2(pipe_str->outfile, STDOUT_FILENO);
					if (tmp->out_fd != 1)
					{
						dup2(tmp->out_fd, STDOUT_FILENO);
						close(tmp->out_fd);
					}
					else
						dup2(STDOUT_FILENO, 1);
					close(pipe_str->pipe_fds_from_prev[0]);
					
					execute(tmp);
				}
				//execute(tmp);
				// else
				// 	execute_error("command not found", tmp->name);
			}
			else 
				;
				//waitpid(pid, NULL, WNOHANG);
		}
		i++;
	}
	close(pipe_str->pipe_fds_from_prev[0]);
	close(pipe_str->pipe_fds_from_prev[1]);
	while (wait(NULL) > 0)
		;
	// while (j-- > 0)
	// 	wait((void *)0);
}



void	pipe_start(t_list *tokens)
{
	t_list p_test = compile(tokens);
	t_pipe pipe_number;
	pipe_acces(&p_test, &pipe_number);
}
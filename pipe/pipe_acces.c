/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_acces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:10:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/30 04:35:54 by jaeyojun         ###   ########seoul.kr  */
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
void	execute(t_process	*tmp);

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




int	check_name_builtins(char *name)
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
			return (i);
		i++;
	}
	return (-1);

}

void	execute_builtins(int check_builtins, t_process *tmp)
{
	if (check_builtins == ECHO)
		echo_main(tmp);
	else if (check_builtins == CD)
		cd_main(tmp);
	else if (check_builtins == PWD)
		pwd_main(tmp);
	// else if (check_builtins == EXPORT)
	// 	execute_EXPORT();
	// else if (check_builtins == UNSET)
	// 	execute_UNSET();
	// else if (check_builtins == ENV)
	// 	execute_ENV();
	// else if (check_builtins == EXIT)
	// 	execute_EXIT();
}

void	execute(t_process	*tmp)
{
	char const	*path_envp = get_env("PATH");
	char const	*path_split;

	path_split = envp_split(path_envp, tmp->name);
	//printf("path_split : %s\n", path_split);
	printf("tmp -> outfd : %d\n", tmp->out_fd);
	printf("tmp -> outfd : %d\n", tmp->in_fd);
	printf("tmp -> outfd : %d", tmp->bad_process);
	//execve(path_split, tmp->argv, get_envp());

}


void	pipe_acces(t_list *p_test)
{
	t_process	*tmp;
	int			i;
	int			check_builtins;

	i = 0;
	while (i < p_test->length)
	{
		tmp = list_get(p_test, i);
		check_builtins = check_name_builtins(tmp->name);
		if (check_builtins != -1)
			execute_builtins(check_builtins, tmp);
		else
		{
			execute(tmp);

		}
		i++;
	}

}



void	pipe_start(t_list *tokens)
{
	t_list p_test = compile(tokens);
	
	// int i;

	// i = 0;
	// while (i < p_test.length)
	// {
	// 	t_process *p = list_get(&p_test, i);
	// 	printf("p->name : %s\n", p->name);
	// 	i++;
	// }
	pipe_acces(&p_test);
}
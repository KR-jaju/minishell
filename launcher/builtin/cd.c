/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:42:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/05 18:11:15 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/compiler.h"
#include <parser/parser.h>
#include "../../str/str.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>

//에러가 나는 인수 출력
static int	out_argv(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (write(2, &argv[i], 1) == -1)
		{
			perror("write");
			return (1);
		}
		i++;
	}
	return (0);
}

//입력값 출력하고 ": " 출력하고 perror출력
static int	print_argv(char	**argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		out_argv(argv[i]);
		if (write(2, ": ", 2) == -1)
		{
			perror("write");
			return (1);
		}
		i++;
	}
	perror("");
	return (0);
}

int	check_behind(t_process *this)
{
	char		*path;
	int			fd;

	if (this->argc == 1)
		fd = chdir(get_env("HOME"));
	else
	{
		path = str_clone(this->argv[1]);
		fd = chdir(path);
		free(path);
	}
	if (fd == 0)
		return (SUCCES_EXIT);
	else
	{
		if (write(2, "basha: ", 6) == -1)
			return (perror("write"), ERROR_EXIT);
		if (print_argv(this->argv) == 1)
			return (ERROR_EXIT);
		return (ERROR_EXIT);
	}
}

//SUCCES_EXIT 0
//ERROR_EXIT 1
int	cd_main(t_process *this)
{
	char const	*path_envp;

	if (this->argc == 1)
	{
		path_envp = get_env("HOME");
		if (!path_envp)
			return (ERROR_EXIT);
		if (chdir(path_envp) == -1)
		{
			//perror결과값과 strerror결과값이 같음
			if ((write(2, "basha: ", 6) == -1))
				return (perror("write"), ERROR_EXIT);
			if (print_argv(this->argv) == 1)
				return (ERROR_EXIT);
		}
	}
	else if (this->argc >= 2)
		return (check_behind(this));
	return (SUCCES_EXIT);
}

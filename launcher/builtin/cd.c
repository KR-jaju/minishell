/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:42:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/06 17:48:13 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/compiler.h"
#include <parser/parser.h>
#include "../../str/str.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>
#include <limits.h>

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

//cd를 실행시킨후 환경변수 PWD 초기화
void	cd_execut_change_pwd(void)
{
	char			pwd[PATH_MAX];
	t_list*const	env_list = &g_minishell.env_list;
	t_envp			*env;
	int				i;
	int				j;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i++);
		if (str_equals(env->name, "PWD"))
		{
			if (getcwd(pwd, PATH_MAX) != (void *)0)
			{
				char*const tmp = allocate(str_length(pwd));
				j = 0;
				while (pwd[j])
				{
					tmp[j] = pwd[j];
					j++;
				}
				tmp[j] = '\0';
				free(env->value);
				env->value = tmp;
			}
		}
	}
}

//cd를 하기 전에 PWD값을 OLDPWD에 저장
void	oldpwd_save(void)
{
	char			pwd[PATH_MAX];
	t_list*const	env_list = &g_minishell.env_list;
	t_envp			*env;
	int				i;
	int				j;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i++);
		if (str_equals(env->name, "OLDPWD"))
		{
			if (getcwd(pwd, PATH_MAX) != (void *)0)
			{
				char*const tmp = allocate(str_length(pwd));
				j = 0;
				while (pwd[j])
				{
					tmp[j] = pwd[j];
					j++;
				}
				tmp[j] = '\0';
				free(env->value);
				env->value = tmp;
			}
		}
	}
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
	{
		cd_execut_change_pwd();
		return (SUCCES_EXIT);
	}
	else
	{
		if (write(2, "bash: ", 6) == -1)
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

	//cd를 하기 전에 OLDPWD에 저장 
	//실패해도 성공해도 저장이 됨.
	oldpwd_save();
	if (this->argc == 1)
	{
		path_envp = get_env("HOME");
		if (!path_envp)
			return (ERROR_EXIT);
		if (chdir(path_envp) == -1)
		{
			//perror결과값과 strerror결과값이 같음
			if ((write(2, "bash: ", 6) == -1))
				return (perror("write"), ERROR_EXIT);
			if (print_argv(this->argv) == 1)
				return (ERROR_EXIT);
		}
		cd_execut_change_pwd();
	}
	else if (this->argc >= 2)
		return (check_behind(this));
	return (SUCCES_EXIT);
}

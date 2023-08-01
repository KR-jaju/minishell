/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:42:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/31 21:03:29 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/compiler.h"
#include <parser/parser.h>
#include "../../str/str.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>


void	check_behind(t_process *this)
{
	char		*path;
	char		*tmp;
	int 		fd; 

	path = str_clone(this->argv[1]);
	if (path[0] == '~' && (path[1] == '/' || path[1] == '\0')) //cd,
	{
		tmp = str_join("$HOME", path + 1);
		free(path);
		path = tmp;
	}
	tmp = unquote_env(path);
	if (str_length(tmp) == 0)
		fd = chdir(get_env("HOME"));
	else
		fd = chdir(tmp);
	if (fd == 0)
		printf("성공");
	else
	{
		perror("bash ");
	}
}


void	cd_main(t_process *this)
{
	char const	*path_envp;

	if (this->argc == 1)
	{
		path_envp = get_env("HOME");
		chdir(path_envp);
	}
	else if (this->argc >= 2)
	{
		check_behind(this);
	}
}

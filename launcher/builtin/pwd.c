/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:25:57 by jaju              #+#    #+#             */
/*   Updated: 2023/08/01 21:08:18 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <libft/libft.h>
#include <str/str.h>
#include <shell/minishell.h>

void	panic_error(char *msg);

int	pwd_main(t_process *this)
{
	char	pwd[PATH_MAX];

	if (this->argc != 1)
		return (panic_error("pwd: too many arguments"), ERROR_EXIT);
	if (getcwd(pwd, PATH_MAX) != (void *)0)
		printf("%s\n", pwd);
	return (SUCCES_EXIT);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:25:57 by jaju              #+#    #+#             */
/*   Updated: 2023/07/31 21:04:08 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <libft/libft.h>
#include <str/str.h>

int	pwd_main(t_process *this)
{
	char	pwd[PATH_MAX];

	if (this->argc != 1)
		panic("pwd: too many arguments");
	if (getcwd(pwd, PATH_MAX) != (void *)0)
		printf("%s\n", pwd);
	return (0);
}

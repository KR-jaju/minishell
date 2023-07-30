/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:25:57 by jaju              #+#    #+#             */
/*   Updated: 2023/07/30 10:21:34 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <unistd.h>
#include <limits.h>
#include <libft/libft.h>
#include <str/str.h>

int	pwd_main(t_process *this)
{
	char	pwd[PATH_MAX];

	if (this->argc != 1)
		panic("pwd: too many arguments");
	if (getcwd(pwd, PATH_MAX) != (void *)0)
		write(this->out_fd, pwd, str_length(pwd));
	return (0);
}

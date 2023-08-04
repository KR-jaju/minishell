/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:18:16 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/03 19:58:10 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	error_open(void)
{
	int const	backup = dup(0);

	dup2(2, 0);
	return (backup);
}

void	error_close(int backup)
{
	dup2(backup, 0);
	close(backup);
}

void	ft_putstr_fd(char *tmp, int fd)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		write(fd, &tmp[i], 1);
		i++;
	}
}

void	execute_error(char *tmp, char *name)
{
	int	i;

	i = 0;
	write(2, "bash : ", 7);
	write(2, name, str_length(name));
	write(2, ": ", 2);
	while (tmp[i])
	{
		write(2, &tmp[i], 1);
		i++;
	}
	exit(127);
}

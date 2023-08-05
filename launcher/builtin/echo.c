/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:08:14 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/05 17:46:21 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/compiler.h"
#include <parser/parser.h>
#include "../../str/str.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>

int	is_n_flag(char const *str)
{
	int	i;

	if (str == (void *)0)
		return (0);
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	echo_main(t_process *this)
{
	int		n_flag;
	int		i;
	char	*tmp;
	int		fd;

	i = 1;
	if (this->argc >= 2)
		while (is_n_flag(this->argv[i]))
			i++;
	n_flag = (i != 1);
	while (this->argv[i] != (void *)0)
	{
		tmp = str_clone(this->argv[i]);
		fd = write(1, tmp, str_length(tmp));
		if (fd == -1)
			return (perror("write"), ERROR_EXIT);
		free(tmp);
		if (i != this->argc - 1)
		{
			fd = write(1, " ", 1);
			if (fd == -1)
				return (perror("write"), ERROR_EXIT);
		}
		i++;
	}
	if (!n_flag)
	{
		fd = write(1, "\n", 1);
		if (fd == -1)
			return (perror("write"), ERROR_EXIT);
	}
	return (SUCCES_EXIT);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:08:14 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/29 23:04:17 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/compiler.h"
#include <parser/parser.h>
#include "../../str/str.h"
#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>

static int	check_alp_n(char *tmp)
{
	int	i;

	i = 1;
	while (tmp[i])
	{
		if (tmp[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// void	put_str(char **argv)
// {
// 	int i = 0;
	

// }

void	echo_main(t_process *this)
{

	int argc = 2;
	if (argc == 1)
		write(1, "\n", 1);
	else
	{
		if (check_alp_n(this->argv[1]) == 1 && this->argv[1][0] == '-')
		{
			//put_str(this->argv);
			//printf("%s", this->argv[2]);
			//printf("%s\n", this->argv)
		}
		else
		{
			int i = 1;
			while (this->argv[i])
			{
				printf("%s", unquote_env(this->argv[i]));
				i++;
			}
		}
	}
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:54:31 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/30 17:08:57 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../str/str.h"

void	execute_error(char *tmp, char *name)
{
	int i; 

	write(2, "bash : ", 7);
	write(2, name, str_length(name));
	write(2, ": ", 2);
	//printf("%s: ", name);
	i = 0;
	while (tmp[i])
	{
		write(2, &tmp[i], 1);
		i++;
	}
	exit(127);
}

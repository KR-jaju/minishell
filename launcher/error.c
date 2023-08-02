/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:18:16 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/02 21:03:58 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

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


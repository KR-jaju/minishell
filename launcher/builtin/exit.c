/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:31 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 22:24:35 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <libft/libft.h>
#include <stdlib.h>

#define STDIN 0
#define STDOUT 1

int	exit_main(t_process *this)
{
	if (this->argc != 1)
		panic("exit: too many arguments");
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:08:14 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/30 01:37:49 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/compiler.h"
#include <parser/parser.h>
#include "../../str/str.h"
#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>

int is_n_flag(char *str)
{
    int i;
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
void    echo_main(t_process *this)
{
    int     n_flag;
    int     i;
    char    *tmp;
    i = 1;
	if (this->argc >= 2)
        while (is_n_flag(this->argv[i]))
            i++;
    n_flag = (i != 1);
    while (this->argv[i] != (void *)0)
    {
        tmp = unquote_env(this->argv[i]);
        write(this->out_fd, tmp, str_length(tmp));
        free(tmp);
        if (i != this->argc - 1)
            write(1, " ", 1);
        i++;
    }
    if (!n_flag)
        write(this->out_fd, "\n", 1);
}


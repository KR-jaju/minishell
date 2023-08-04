/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:47:06 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/03 19:58:02 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdlib.h>
# include "../str/str.h"

int		error_open(void);
void	error_close(int backup);
void	ft_putstr_fd(char *tmp, int fd);

#endif
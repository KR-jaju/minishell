/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:28:28 by jaju              #+#    #+#             */
/*   Updated: 2023/07/30 13:30:42 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>

static int	syntax_var_name(char const *str)
{
	int	i;

	if (str[0] == '_' || is_alphabet(str[0]))
	{
		i = 1;
		while (str[i] != '\0')
		{
			if (!(str[0] == '_' || is_alphabet(str[0]) || is_number(str[0])))
				return (0);
			i++;
		}
	}
	return (1);
}

int	unset_main(t_process *this)
{
	int	i;

	i = 1;
	while (i < this->argc)
	{

	}
}

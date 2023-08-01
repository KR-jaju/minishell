/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:28:28 by jaju              #+#    #+#             */
/*   Updated: 2023/08/01 12:19:19 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <shell/minishell.h>
#include <libft/libft.h>

static int	syntax_var_name(char const *str)
{
	int	i;

	if (str[0] == '_' || is_alphabet(str[0]))
	{
		i = 1;
		while (str[i] != '\0')
		{
			if (!(str[i] == '_' || is_alphabet(str[i]) || is_number(str[i])))
				return (0);
			i++;
		}
	}
	return (1);
}

int	unset_main(t_process *this)
{
	char	*name;
	int		i;

	i = 1;
	while (i < this->argc)
	{
		name = this->argv[i];
		if (syntax_var_name(name))
			remove_env(name);
		i++;
	}
	return (0);
}

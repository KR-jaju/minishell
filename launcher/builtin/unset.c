/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:28:28 by jaju              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/01 12:19:19 by jaju             ###   ########.fr       */
=======
/*   Updated: 2023/08/01 21:15:28 by jaeyojun         ###   ########seoul.kr  */
>>>>>>> upstream/jaeyojun
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
<<<<<<< HEAD
				return (0);
=======
				return (SUCCES_EXIT);
>>>>>>> upstream/jaeyojun
			i++;
		}
	}
	return (ERROR_EXIT);
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
<<<<<<< HEAD
	return (0);
=======
	return (SUCCES_EXIT);
>>>>>>> upstream/jaeyojun
}

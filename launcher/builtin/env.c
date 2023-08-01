/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:09:29 by jaju              #+#    #+#             */
/*   Updated: 2023/08/01 13:12:29 by jaju             ###   ########.fr       */
=======
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:09:29 by jaju              #+#    #+#             */
/*   Updated: 2023/08/01 20:54:50 by jaeyojun         ###   ########seoul.kr  */
>>>>>>> upstream/jaeyojun
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <shell/minishell.h>
#include <stdio.h>

int	env_main(t_process *this)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_envp			*env;
	int				i;

	(void)this;
	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
<<<<<<< HEAD
=======
		//env->value이 null일 때
		if (!env->value)
			return (ERROR_EXIT);
>>>>>>> upstream/jaeyojun
		if (env->value != (void *)0)
			printf("%s=%s\n", env->name, env->value);
		i++;
	}
<<<<<<< HEAD
	return (0);
=======
	return (SUCCES_EXIT);
>>>>>>> upstream/jaeyojun
}

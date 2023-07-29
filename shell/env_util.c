/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 04:00:45 by jaju              #+#    #+#             */
/*   Updated: 2023/07/30 04:04:25 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <str/str.h>
#include <libft/libft.h>

t_envp	*find_env(char const *name)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_envp			*env;
	int				i;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (str_equals(name, env->name))
			return (env);
		i++;
	}
	return ((void *)0);
}

char	*env_to_str(t_envp *env)
{
	int const	name_len = str_length(env->name);
	int const	value_len = str_length(env->value);
	char*const	new = allocate(name_len + value_len + 2);
	char		*ptr;

	ptr = new;
	copy(env->name, ptr, name_len);
	ptr += name_len;
	copy("=", ptr, 1);
	ptr += 1;
	copy(env->value, ptr, value_len);
	return (new);
}

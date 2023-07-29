/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:57:55 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 20:37:14 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "str/str.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

//미니쉘(전역변수) 초기화
void	minishell_init(char **envp)
{
	t_envp	*pair;
	t_list	env;
	int		i;
	int		index;

	list_init(&env);
	i = 0;
	while (envp[i] != (void *)0)
	{
		pair = allocate(sizeof(t_envp));
		index = str_indexof(envp[i], '=');
		pair->name = str_substr(envp[i], 0, index);
		pair->value = str_substr(envp[i], index + 1, str_length(envp[i]));
		list_add(&env, pair);
		i++;
	}
	g_minishell.env_list = env;
}

//문자열에 대응하는 환경변수의 값을 리턴
char const	*get_env(char const *str)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_envp			*env;
	int				i;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (str_equals(str, env->name))
			return (env->value);
		i++;
	}
	return ("");
}
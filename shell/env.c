/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 03:49:42 by jaju              #+#    #+#             */
/*   Updated: 2023/08/01 13:03:44 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <str/str.h>
#include <libft/libft.h>
#include <stdlib.h>

//envp구조체를 char *로 만들어 줌
char	*env_to_str(t_envp *env);

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

void	set_env(char const *name, char const *value)
{
	t_list*const	env_list = &g_minishell.env_list;
	int				i;
	t_envp			*env;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i++);
		if (str_equals(env->name, name))
		{
			if (value == (void *)0)
				return ;
			else
				return (free(env->value), env->value = str_clone(value), (void)0);
		}
	}
	env = allocate(sizeof(t_envp));
	list_add(env_list, env);
	env->name = str_clone(name);
	env->value = str_clone(value);
}

void	remove_env(char const *name)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_envp			*env;
	int				i;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (str_equals(env->name, name))
			break ;
		i++;
	}
	free(env->name);
	free(env->value);
	free(env);
	while (i + 1 < env_list->length)
	{
		env_list->data[i] = env_list->data[i + 1];
		i++;
	}
	env_list->length--;
}

char	**get_envp(void)
{
	t_list*const	env_list = &g_minishell.env_list;
	char**const		envp = allocate((env_list->length + 1) * sizeof(char *));
	t_envp			*env;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (env->value != (void *)0)
			envp[j++] = env_to_str(env);
		i++;
	}
	return (envp);
}

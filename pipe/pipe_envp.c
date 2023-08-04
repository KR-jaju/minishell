/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:06:52 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/04 17:07:05 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <libft/libft.h>

//환경변수 + / + 명령어를 한 것 리턴
static char	*path_join(char const *env, char const *cmd)
{
	char*const	new = allocate(str_length(env) + str_length(cmd) + 2);
	char		*ptr;

	ptr = new;
	while (*env != '\0')
		*(ptr++) = *(env++);
	*(ptr++) = '/';
	while (*cmd != '\0')
		*(ptr++) = *(cmd++);
	return (new);
}

//환경변수 실행 권한 확인
char const	*envp_split(char const *envp_path, char *cmd)
{
	char		*envp;
	char		*envp_split;
	char		*combine;
	int			cmd_exists;

	envp = str_clone(envp_path);
	if (envp == (void *)0)
		return ((void *)0);
	cmd_exists = access(cmd, X_OK);
	if (cmd_exists != -1)
		return (cmd);
	envp_split = str_tokenize(envp, ":");
	while (envp_split != (void *)0)
	{
		combine = path_join(envp_split, cmd);
		cmd_exists = access(combine, X_OK);
		if (cmd_exists != -1)
		{
			return (free(envp), combine);
		}
		free(combine);
		close(cmd_exists);
		envp_split = str_tokenize((void *)0, ":");
	}
	return (free(envp), (void *)0);
}

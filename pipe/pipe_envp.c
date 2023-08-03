/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:06:52 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/03 20:15:40 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

//환경변수 + / + 명령어를 한 것 리턴
char const	*check_acces(char *envp, char *cmd)
{
	char		*tmp;
	char const	*envp_plus;

	tmp = str_join("/", cmd);
	envp_plus = str_join(envp, tmp);
	free(tmp);
	return (envp_plus);
}

//환경변수 : 기준으로 나누기
char	*envp_str_tokenize(int *i, char *envp)
{
	char	*envp_split;

	if ((*i) == 0)
	{
		envp_split = str_tokenize(envp, ":");
		(*i)++;
	}
	else
		envp_split = str_tokenize((void *)0, ":");
	return (envp_split);
}

//환경변수 실행 권한 확인
char const	*envp_split(char const *envp_path, char *cmd)
{
	char		*envp;
	char		*envp_split;
	char const	*combine;
	int			fd;
	int			i;

	i = 0;
	envp = str_clone(envp_path);
	if (!envp_path || !cmd)
		return (NULL);
	fd = access(cmd, X_OK);
	if (fd != -1)
		return (cmd);
	while (1)
	{
		envp_split = envp_str_tokenize(&i, envp);
		if (!envp_split)
			break ;
		combine = check_acces(envp_split, cmd);
		fd = access(combine, X_OK);
		if (fd != -1)
			return (combine);
		close(fd);
	}
	return (NULL);
}

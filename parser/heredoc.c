/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:44:23 by jaju              #+#    #+#             */
/*   Updated: 2023/07/31 21:08:48 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <libft/libft.h>
#include <parser/parser.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

//heredoc에 사용할 tmp파일의 이름
static char	*heredoc_filename(int idx)
{
	char*const	name = allocate(8);

	copy("_NN.tmp", name, 8);
	name[1] = (idx / 10) + '0';
	name[2] = (idx % 10) + '0';
	return (name);
}

//heredoc 입력을 받기 위한 프롬프트 열기
static void	heredoc_prompt(t_token *heredoc, t_token *delim, int idx)
{
	char*const	name = heredoc_filename(idx);
	int const	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("heredoc_fd : %d\n", fd);
	char*const	parsed_delim = unquote(delim->content);
	char		*str;

	if (fd == -1)
		panic("Failed to create tmp file for heredoc");
	while (1)
	{
		str = readline("> ");
		if (str == (void *)0)
			break ;
		if (str_equals(str, parsed_delim))
			break ;
		write(fd, str, str_length(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(delim->content);
	delim->content = name;
	heredoc->type = TK_IRD;
	close(fd);
}

//heredoc 임시파일 삭제
void	heredoc_unlink_tmp(void)
{
	int		i;
	char	*name;

	i = 0;
	while (i < 16)
	{
		name = heredoc_filename(i);
		unlink(name);
		free(name);
		i++;
	}
}

//<<를 <로 치환, delimiter를 tmp파일로 치환
void	heredoc_substitute(t_list *tokens)
{
	t_token	*token;
	int		i;
	int		heredoc_idx;

	i = 0;
	heredoc_idx = 0;
	while (i < tokens->length)
	{
		token = list_get(tokens, i++);
		if (token->type == TK_HRD)
		{
			if (heredoc_idx == 16)
				panic("Too many heredoc");
			heredoc_prompt(token, list_get(tokens, i++), heredoc_idx++);
		}
	}
}

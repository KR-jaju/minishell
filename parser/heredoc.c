/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:44:23 by jaju              #+#    #+#             */
/*   Updated: 2023/08/02 15:50:00 by jaju             ###   ########.fr       */
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

void sighere_doc(int sign);
void sigtermHandler(int sign);

//heredoc에 사용할 tmp파일의 이름
static void	heredoc_filename(char *dst, int idx)
{
	copy("_NN.tmp", dst, 8);
	dst[1] = (idx / 10) + '0';
	dst[2] = (idx % 10) + '0';
}

void	sigint_handler_nonl(int sig)
{
	rl_on_new_line();
	//rl_replace_line("", 0);
	//printf("DED\n");
	rl_redisplay();
	exit(1);
	(void) sig;
}

//heredoc 입력을 받기 위한 프롬프트 열기
static void	heredoc_prompt(char const *filename, char const *end)
{
	int const	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char*const	parsed_delim = unquote(end);
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
	free(parsed_delim);
	close(fd);
}



//heredoc 임시파일 삭제
void	heredoc_unlink_tmp(void)
{
	int		i;
	char	name[20];

	i = 0;
	while (i < 16)
	{
		heredoc_filename(name, i);
		unlink(name);
		i++;
	}
}

void	heredoc_replace(t_list *tokens, char **end_list)
{
	t_token	*token;
	int		i;
	int		heredoc_idx;
	char	filename[20];

	i = 0;
	heredoc_idx = 0;
	while (i < tokens->length)
	{
		token = list_get(tokens, i);
		if (token->type == TK_HRD)
		{
			token->type = TK_IRD;
			token = list_get(tokens, ++i);
			end_list[heredoc_idx] = token->content;
			heredoc_filename(filename, heredoc_idx);
			token->content = str_clone(filename);
			heredoc_idx++;
		}
		i++;
	}
}

//<<를 <로 치환, delimiter를 tmp파일로 치환
int	heredoc_substitute(t_list *tokens)
{
	int		heredoc_idx;
	pid_t	pid;
	int		exit_code;
	char	*end_list[17];
	char	filename[20];

	for (int i = 0; i < 17; i++)
	{
		end_list[i] = (void *)0;
	}
	heredoc_replace(tokens, end_list);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler_nonl);
		heredoc_idx = 0;
		while (end_list[heredoc_idx] != (void *)0)
		{
			heredoc_filename(filename, heredoc_idx);
			heredoc_prompt(filename, end_list[heredoc_idx]);
			heredoc_idx++;
		}
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &exit_code, 0);
		if (WIFEXITED(exit_code))
			exit_code = WEXITSTATUS(exit_code);
		signal(SIGINT, SIG_DFL);
	}
	return (exit_code == 0);
}


// 	if (pid == 0)
// 		heredoc_child(mini);
// 	waitpid(pid, &status, 0);
// 	input(mini, ".heredoc.tmp");
// }
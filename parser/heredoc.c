/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:44:23 by jaju              #+#    #+#             */
/*   Updated: 2023/08/02 14:03:33 by jaeyojun         ###   ########seoul.kr  */
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
static char	*heredoc_filename(int idx)
{
	char*const	name = allocate(8);

	copy("_NN.tmp", name, 8);
	name[1] = (idx / 10) + '0';
	name[2] = (idx % 10) + '0';
	return (name);
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
static void	heredoc_prompt(t_token *heredoc, t_token *delim, int idx)
{
	char*const	name = heredoc_filename(idx);
	int const	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char*const	parsed_delim = unquote(delim->content);
	char		*str;


	if (fd == -1)
		panic("Failed to create tmp file for heredoc");
	while (1)
	{
		str = readline("> ");
		//signal(SIGINT, sigtermHandler);
		if (str == (void *)0)
		{
			//exit(1);
			break ;
		}
		if (str_equals(str, parsed_delim))
		{
			//exit(1);
			break ;
		}
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

//void	heredoc_count(t_list)

//<<를 <로 치환, delimiter를 tmp파일로 치환
void	heredoc_substitute(t_list *tokens)
{
	t_token	*token;
	int		i;
	int		heredoc_idx;
	pid_t	pid;
	//int		status;

	i = 0;
	heredoc_idx = 0;
	pid = fork();

	if (pid == 0)
	{
		signal(SIGINT, sigint_handler_nonl);
		while (i < tokens->length)
		{
			token = list_get(tokens, i++);
			if (token->type == TK_HRD)
			{
				if (heredoc_idx == 16)
					panic("Too many heredoc");
				//printf("token->type : %d\n", token->type);
				//pid = fork();
				
				//if (pid == 0)
				//{
					heredoc_prompt(token, list_get(tokens, i++), heredoc_idx++);
				//}
				//else
					//signal(SIGINT, SIG_IGN);
				//waitpid(pid, &status, 0);
			}
		}
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		//wait(NULL);
		waitpid(pid, NULL, 0);
	}
	// while (wait(NULL) > 0)
	// 	;
}


// 	if (pid == 0)
// 		heredoc_child(mini);
// 	waitpid(pid, &status, 0);
// 	input(mini, ".heredoc.tmp");
// }
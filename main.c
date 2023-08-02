/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:41:01 by jaju              #+#    #+#             */
/*   Updated: 2023/08/02 16:33:16 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <str/str.h>
#include <collection/list.h>
#include <parser/tokenizer.h>
#include <parser/syntax.h>
#include <parser/heredoc.h>
#include <shell/minishell.h>
#include <pipe/pipe.h>
#include <parser/compiler.h>
#include <signal/signal.h>
#include <termios.h>

void sigtermHandler(int sign);

void	visualize(t_list tokens)
{
	int		i;
	t_token	*token;

	printf("syntax_wrong: %d\n\n", syntax_check(&tokens));
	i = 0;
	while (i < tokens.length)
	{
		token = list_get(&tokens, i);
		if (token->type == TK_STR)
		{
			printf("%s\n", token->content);
			free(token->content);
		}
		else if (token->type == TK_IRD)
			printf("<\n");
		else if (token->type == TK_HRD)
			printf("<<\n");
		else if (token->type == TK_ORD)
			printf(">\n");
		else if (token->type == TK_ARD)
			printf(">>\n");
		else if (token->type == TK_PIPE)
			printf("|\n");
		else if (token->type == TK_INVALID)
			printf("(invalid)\n");
		//free(token);
		i++;
	}
}

void	ft_putstr_fd(char *tmp, int fd)
{
	int i = 0;
	
	while (tmp[i])
	{
		write(fd, &tmp[i], 1);
		i++;
	}
}


void	set_terminal_print_off(void)
// 터미널에 ^C, ^\등의 시그널표식을 출력하지않도록 설정
{
	struct termios	term; // 터미널 설정이 담겨있는 termios 구조체

	tcgetattr(1, &term); // 현재 터미널의 설정을 term에 가져옴
	term.c_lflag &= ~(ECHOCTL); // 시그널표식 출력이 true 라면 false로 변경
	tcsetattr(1, 0, &term); // 변경한 term 설정을 현재 터미널에 적용
}

void	set_terminal_print_on(void)
// 터미널에 ^C, ^\등의 시그널표식을 출력하도록 설정
{
	struct termios	term; // 터미널 설정이 담겨있는 termios 구조체

	tcgetattr(1, &term); // 현재 터미널의 설정을 term에 가져옴
	term.c_lflag |= (ECHOCTL); // 시그널표식 출력이 false 라면 true로 변경
	tcsetattr(1, 0, &term);  // 변경한 term 설정을 현재 터미널에 적용
}

void	do_sigterm(int sin)
// ctrl+d를 눌렀을때 작동
{
	(void) sin;
	ft_putstr_fd("\033[1A", 2); // 현재 커서의 위치를 한칸 위로 올려줌 
	ft_putstr_fd("\033[11C", 2); // 현재 커서의 위치를 12번째칸으로 이동
	ft_putstr_fd("exit\n", 2); // exit를 출력
	exit(g_minishell.exit_code = 0);
}


int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	char	*str;
	//int		status;
	t_list	tokens;
	//int		heredoc_check;

	minishell_init(envp);
	set_terminal_print_off();
	all_signal();
	while (1)
	{
		
		str = readline("minishell$ ");
		//signal(SIGINT, sigintHandler);
		if (str == (void *)0)
		{
			do_sigterm(1);
			//signal(SIGTERM, sigtermHandler);
			//printf("\b\b  \b\b");
			    //printf("\033[1A\033[K");
			// printf("exit\n");
			// exit(g_minishell.exit_code = 0);
		}
			
		if (str_length(str) == 0)
			continue ;
		add_history(str);
		if (!tokenize_command(str, &tokens))
			continue ; //ERROR!
		if (!heredoc_substitute(&tokens))
			continue ;
		//t_token	*t0 = list_get(&tokens, 0);
		//t_token	*t1 = list_get(&tokens, 1);
		//printf("%s %s\n", t0->content, t1->content);
		//if (tokens.name)
		//waitpid(-1, &status, 0);
		//status = WEXITSTATUS(status);
		//t_list p_test = compile(&tokens);
		//(void) p_test;
		//exit(0);
		//visualize(tokens);
		//exit(1);
		//printf("wad\n");
		pipe_start(&tokens);
		heredoc_unlink_tmp();
		free(str);
	}
	set_terminal_print_on();
	return (0);
}

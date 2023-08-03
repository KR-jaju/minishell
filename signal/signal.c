/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:06:31 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/03 17:12:05 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <signal/signal.h>
#include <./shell/minishell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <launcher/error.h>

//heredoc에서 ctrl+c을 눌렀을 때 
void	main_sigint_handler_heredoc(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_redisplay();
	exit(1);
}

//heredoc에서 ctrl+d을 눌렀을 때 
void	sigterm_handler_heredoc(int sin)
{
	(void) sin;
	ft_putstr_fd("\033[1A", 2); // 현재 커서의 위치를 한칸 위로 올려줌 
	ft_putstr_fd("\033[2C", 2); // 현재 커서의 위치를 2번째칸으로 이동 // exit를 출력
	exit(g_minishell.exit_code = 0);
}

//main에서 ctrl+c을 눌렀을 때 
void	main_sigint_handler(int sign)
{
	(void )	sign;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_minishell.exit_code = 1;
}

//main ctrl+d를 눌렀을때 작동 signal은 발생하지 않음
void	main_sigterm_handler(void)
{
	ft_putstr_fd("\033[1A", 2); // 현재 커서의 위치를 한칸 위로 올려줌 
	ft_putstr_fd("\033[11C", 2); // 현재 커서의 위치를 12번째칸으로 이동
	ft_putstr_fd("exit\n", 2); // exit를 출력
	exit(g_minishell.exit_code = 0);
}

//main에서 signal 정의
//SIGINT == ctrl+c, SIGQUIT == ctrl+\, SIGTERM == ctrl+d 
void	all_signal(void)
{
	signal(SIGINT, main_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

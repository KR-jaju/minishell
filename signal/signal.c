/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:06:31 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/02 04:02:45 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <signal/signal.h>
#include <./shell/minishell.h>
#include <stdio.h>
#include <readline/readline.h>

void	sigintHandler(int sign)
{
	if (sign == SIGINT)
	{	
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_minishell.exit_code = 1;
	}
}

// void	sigquitHandler(int sign)
// {
// 	// if (sign == SIGQUIT)
// 	// {
// 	// 	//rl_on_new_line();
// 	// 	//rl_replace_line("", 0);
// 	// 	rl_redisplay();
// 	// 	//printf("\nCtrl+\\ (SIGQUIT) 시그널을 받았습니다.\n");
// 	// 	//printf("DEBUG");
// 	// }

// }

void sigtermHandler(int sign)
{
	(void) sign;
		//printf("\nCtrl+\\ (SIGQUIT) 시그널을 받았습니다.\n");
	printf("exit\n");
	g_minishell.exit_code = 0;
	
}

void sighere_doc(int sign)
{
	printf("DEBUIG\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	(void) sign;
	exit(1);
	//g_minishell.exit_code = 0;
}

void	all_signal(void)
{
	signal(SIGINT, sigintHandler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, sigtermHandler);
}

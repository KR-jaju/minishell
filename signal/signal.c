/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:06:31 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/01 23:38:10 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <signal/signal.h>
#include <./shell/minishell.h>
#include <stdio.h>
#include <readline/readline.h>

void	sigintHandler(int sign)
{
	if (sign == SIGINT)
	{	printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//printf("%d\n", signal);
		ag_minishell.exit_code = 1;
		//exit(1);
	}
	else if (sign == SIGQUIT)
	{
		;
	}
	else if (sign == SIGTERM)
	{
		;
	}

}

void	all_signal(void)
{
	signal(SIGINT, sigintHandler);
	signal(SIGQUIT, sigintHandler);
	signal(SIGTERM, sigintHandler);
}

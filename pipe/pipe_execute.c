/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:59:04 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/04 17:00:39 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <shell/minishell.h>

void	process_run(t_list *tokens)
{
	t_list		p_test;
	t_process	*tmp;
	int			pid;
	int			builtin_idx;

	p_test = compile(tokens);
	tmp = list_get(&p_test, 0);
	if (p_test.length == 1 && check_builtin(tmp->name, &builtin_idx)) // fork 없이 빌트인 실행 조건
		execute_no_fork(tmp, builtin_idx);
	else // 그 외 일반적인 경우
	{
		pid = execute_fork(&p_test);
		wait_process(pid);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:59:04 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/03 21:59:28 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	parent_process(int *prev_read_fd, int *next)
{
	signal(SIGINT, SIG_IGN);
	close((*prev_read_fd));// 이전 파이프에서 받는 fd는 더 이상 쓸 일이 없다.
	close(next[1]);// 다음 파이프에 출력하는 것도 더이상 필요 없다.
	(*prev_read_fd) = next[0];
}

void	child_process(t_process	*tmp, int *prev_read_fd, int *next)
{
	//signal 기본값으로 되돌린다.
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (tmp->in_fd == 0) // Input redirection이 없을 때는
		tmp->in_fd = (*prev_read_fd); // 그 자리를 이전 파이프에서 받는 fd로 채운다
	else
		close((*prev_read_fd));
	if (tmp->out_fd == 1) // Output redirection이 없을 때는
		tmp->out_fd = next[1]; // 그 자리를 다음 파이프에 쓰는 fd로 채운다
	else
		close(next[1]);
	dup2(tmp->in_fd, 0); // 표준 입출력이 in_fd와 out_fd를 대체하도록 한다
	dup2(tmp->out_fd, 1);
	close(tmp->out_fd);
	close(tmp->in_fd); // in_fd와 out_fd는 닫아도 된다.
	close(next[0]);// 남은 fd는 다음 파이프에서 받는 fd뿐
	execute(tmp);
}

void	all_process(t_process *tmp, t_pipe *pipe_st, int *pid, t_list *p_test)
{
	int	i;

	i = 0;
	pipe_st->prev_read_fd = dup(0);
	while (i < p_test->length)
	{
		tmp = list_get(p_test, i);
		if (i != p_test->length - 1) // 현재 프로세스가 마지막 프로세스가 아니라면
			pipe(pipe_st->next); //파이프 생성
		else
		{
			pipe_st->next[0] = dup(0);// (닫을 수 있는) 표준 출력을 next fd에 넣는다.
			pipe_st->next[1] = dup(1);
		}
		(*pid) = fork(); // 자식 프로세스 생성
		if (i == p_test->length - 1)
			pipe_st->last_pid = (*pid);
		if ((*pid) == 0) // 자식 프로세스
			child_process(tmp, &(pipe_st->prev_read_fd), pipe_st->next);
		else if ((*pid) > 0)
			parent_process(&(pipe_st->prev_read_fd), pipe_st->next);
		i++;
	}
}

void	pipe_acces(t_list *p_test)
{
	t_process	*tmp;
	t_pipe		pipe_st;
	int			pid;

	pipe_st.next[0] = 0;
	pipe_st.next[1] = 1;
	tmp = list_get(p_test, 0);
	if (p_test->length == 1 && \
		check_builtin(tmp->name, &(pipe_st.builtin_idx))) // fork 없이 빌트인 실행 조건
		start_builtin(tmp, pipe_st.builtin_idx);
	else // 그 외 일반적인 경우
	{
		all_process(tmp, &pipe_st, &pid, p_test);
		close(pipe_st.prev_read_fd); // 모든게 끝나고 남은 건 이전 파이프의 읽는 fd
		exitcode_signal(pid);
	}
}

void	pipe_start(t_list *tokens)
{
	t_list	p_test;

	p_test = compile(tokens);
	pipe_acces(&p_test);
}

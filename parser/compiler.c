/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:51:48 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 23:00:51 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"
#include <libft/libft.h>
#include <parser/tokenizer.h>

#define FALSE 0
#define TRUE 1

//프로세스 구조체 초기화
void	process_init(t_process *process);
//프로세스의 이름 설정
void	set_name(t_process *process, char const *name);
//프로세스의 옵션 추가
void	add_arg(t_process *process, char const *arg);
//프로세스의 출력 파일을 설정, 실패 시 0, 성공 시 1 리턴
int		set_output(t_process *process, char *filename, int append);
//프로세스의 입력을 설정, 실패 시 0 리턴, 성공 시 1 리턴
int		set_input(t_process *process, char *filename);

//토큰 리스트로부터 프로세스의 정보를 채워넣음
static t_process	*parse_process( t_process *process, t_list const *tokens,
	int *i)
{
	t_token			*token;

	token = list_get(tokens, *i);
	while (token != (void *)0 && (token->type != TK_PIPE || *i == tokens->length))
	{
		if (token->type == TK_STR && process->name == (void *)0)
			set_name(process, token->content);
		else if (token->type == TK_STR)
			add_arg(process, token->content);
		else if (token->type == TK_ORD
			&& !set_output(process, list_get(tokens, ++(*i)), FALSE))
			break ;
		else if (token->type == TK_ARD
			&& !set_output(process, list_get(tokens, ++(*i)), TRUE))
			break ;
		else if (token->type == TK_IRD)
			if (!set_input(process, list_get(tokens, ++(*i))))
				break ;
		token = list_get(tokens, ++(*i));
	}
	return (process);
}

//파이프라인 (|) 단위로 프로세스를 만들어 리스트에 넣고 리턴
t_list	compile(t_list const *tokens)
{
	int			i;
	t_process	*process;
	t_list		process_list;

	list_init(&process_list);
	i = 0;
	while (i < tokens->length)
	{
		process = allocate(sizeof(t_process));
		process_init(process);
		parse_process(process, tokens, &i);
		list_add(&process_list, process);
		i++;
	}
	return (process_list);
}

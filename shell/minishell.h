/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:40:16 by jaju              #+#    #+#             */
/*   Updated: 2023/07/30 03:40:13 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <collection/list.h>

//환경변수의 이름과 내용을 저장하는 구조체
typedef struct s_envp
{
	char	*name;
	char	*value;
}t_envp;

//미니쉘이 실행되는 동안 지니고 있어야 할 정보를 담는 구조체
typedef struct s_minishell
{
	t_list	env_list;
	int		exit_code;
}t_minishell;

//프로그램 종료까지 전역적으로 사용할 미니쉘 전역변수
t_minishell	g_minishell;

//미니쉘(전역변수) 초기화
void		minishell_init(char **envp);
//문자열에 대응하는 환경변수의 값을 리턴
char const	*get_env(char const *str);
char		**get_envp(void);

#endif
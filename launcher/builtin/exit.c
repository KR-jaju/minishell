/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:54:31 by jaju              #+#    #+#             */
/*   Updated: 2023/08/02 21:14:07 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <libft/libft.h>
#include <stdlib.h>
#include <parser/parser.h>
#include <stdio.h>

#define STDIN 0
#define STDOUT 1

#define LL_MAX 9223372036854775807ULL

typedef unsigned long long	t_ull;

//positive -> abs % 256;
//negative -> 256 - (abs % 256)
static int	parse_exit_code(char const *str, int *code)
{
	int		is_negative;
	t_ull	abs;
	int		i;

	is_negative = 0;
	abs = 0;
	i = 0;
	if (str[0] == '-')
	{
		str++;
		is_negative = 1;
	}
	while (str[i] != '\0')
	{
		if (i >= 19 || !is_number(str[i]))
			return (0);
		abs *= 10;
		abs += (str[i] - '0');
		i++;
	}
	if ((!is_negative && abs > LL_MAX) || (is_negative && abs > (LL_MAX + 1)))
		return (0);
	if (is_negative)
		return (*code = 256 - (abs % 256), 1);
	return (*code = (abs % 256), 1);
}

int	exit_main(t_process *this)
{
	int	code;

	if (this->argc == 1)
		exit(0);
	else if (this->argc == 2)
	{
		//$가 오는데 뒤에 환경변수를 실행할 수 없는 거면 exit화면에 출력하고 정상 종료
		//$가 오는데 뒤에 환경변수를 실행시킬 수 있으면 결과값을 보여주고 numeric argument required 후 255출력

		if (!parse_exit_code(this->argv[1], &code))
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", unquote_env(this->argv[1]));
			exit(255); //numeric argument required
		}
		// else
		// {

		// }
		printf("exit\n");
		// if (this->argv[1][0] == '$')
		// {
		// 	exit(0);
		// }
		//printf("code : %d\n", code);
		exit(code);
	}
	//printf("exit\n");
	printf("exit: too many arguments\n");
	exit(1); // too many argument
}

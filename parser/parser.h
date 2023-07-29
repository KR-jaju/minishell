/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:34:21 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 18:51:37 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <libft/libft.h>
# include <str/str.h>

//환경변수 치환 없이 따옴표 제거
char	*unquote(char const *str);
//작은 따옴표 ('')를 제외한 부분에서 환경변수 치환
char	*unquote_env(char const *str);

#endif
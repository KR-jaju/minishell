/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:37:44 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 19:23:55 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include <collection/list.h>
# include "tokenizer.h"

//토큰 리스트에서 확인할 수 있는 문법 체크
int	syntax_check(t_list	*tokens);

#endif

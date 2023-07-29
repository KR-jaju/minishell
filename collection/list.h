/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:21:42 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 19:09:09 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

//void *를 저장하는 리스트
typedef struct s_list{
	void	**data;
	int		length;
	int		capacity;
}t_list;

//리스트 초기화
void	list_init(t_list *this);
//리스트에 포인터를 추가
void	list_add(t_list *this, void *element);
//리쇼트에서 포인터를 가져오기
void	*list_get(t_list const *this, int i);


#endif
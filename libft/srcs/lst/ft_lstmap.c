/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:52:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:29:45 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*head;

	if (!lst)
		return (NULL);
	new = f(lst);
	head = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = (f(lst));
		new = new->next;
	}
	return (head);
}

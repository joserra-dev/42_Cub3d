/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscastr <joscastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:30:08 by joscastr          #+#    #+#             */
/*   Updated: 2025/03/14 19:30:09 by joscastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lsapply(t_list *l, t_list *s, void *(*f)(void *), void (*d)(void *))
{
	if (l)
	{
		s = ft_lstnew(f(l->content));
		if (!s)
		{
			ft_lstclear(&s, d);
			return (NULL);
		}
		s->next = ft_lsapply(l->next, s->next, f, d);
	}
	return (s);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;

	start = NULL;
	start = ft_lsapply(lst, start, f, del);
	return (start);
}

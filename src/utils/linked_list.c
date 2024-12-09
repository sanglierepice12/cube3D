/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:28:59 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 13:28:59 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

size_t	get_list_len(t_list *list)
{
	t_list	*tmp;
	size_t	len;

	tmp = list;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

t_list	*ft_lst_last(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lst_add_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lst_add_back(t_list **head, t_list *new)
{
	t_list	*last;

	if (*head)
	{
		last = ft_lst_last(*head);
		last->next = new;
		new->prev = last;
	}
	else
		*head = new;
}

t_list	*ft_new_node(char *value)
{
	t_list	*env;

	env = ft_calloc(1, sizeof(t_list));
	if (!env)
		return (NULL);
	if (value)
		env->value = ft_dup(value);
	env->next = NULL;
	env->prev = NULL;
	return (env);
}

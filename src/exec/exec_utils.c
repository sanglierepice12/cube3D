/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:10:56 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/26 11:43:39 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"


// void	ft_bzero(void *s, size_t n)
// {
// 	while (n)
// 	{
// 		*(char *)s = '\0';
// 		s++;
// 		n--;
// 	}
// }

// void	*ft_calloc(size_t nbdelement, size_t tailleelement)
// {
// 	void	*ptr;

// 	ptr = malloc (tailleelement * nbdelement);
// 	if (ptr == NULL)
// 		return (NULL);
// 	if (nbdelement == 0)
// 		((char *)ptr)[0] = '\0';
// 	else
// 		ft_bzero(ptr, tailleelement * nbdelement);
// 	return (ptr);
// }

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*ptr;

	ptr = pointer;
	while (count)
	{
		*ptr = (unsigned char) value;
		ptr++;
		count--;
	}
	return (pointer);
}
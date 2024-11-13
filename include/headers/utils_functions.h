/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:34:41 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 13:34:41 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H

/*==================utils=====================*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_cal_loc(size_t nmemb, size_t size);
char		*ft_dup(const char *s);
size_t		ft_strlen(const char *s);

/*==================linked_list=====================*/
t_env		*ft_lst_last(t_env *lst);
void		ft_lst_add_front(t_env **lst, t_env *new);
void		ft_lst_add_back(t_env **head, t_env *new);
t_env		*ft_new_node(char *value);

/*==================exit & free=====================*/
void		free_tab(char **tab);
void		ft_exit(char *msg, int code);

#endif
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
int			ft_comp_str(const char *src, const char *str); //return 1 if equal
void		ft_bzero(void *s, size_t n);
void		*ft_cal_loc(size_t nmemb, size_t size);
char		*ft_dup(const char *s);
size_t		ft_strlen(const char *s);

/*==================linked_list=====================*/
t_list		*ft_lst_last(t_list *lst);
void		ft_lst_add_front(t_list **lst, t_list *new);
void		ft_lst_add_back(t_list **head, t_list *new);
t_list		*ft_new_node(char *value);
void		free_list(t_list *list);

/*==================exit & free=====================*/
void		free_tab(char **tab);
void		ft_exit(char *msg, int code);

#endif
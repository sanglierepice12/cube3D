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
# define UTILS_FUNCTIONS_H

/*==================utils=====================*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_comp_str(const char *src, const char *str); //return 1 if equal
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *pointer, int value, size_t count);
char		*ft_dup(const char *s);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strjoin(const char *s1, const char *s2);
char		*rm_bs_wp(char *str);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *nptr);
int			parse_ws(char *line);

/*==================linked_list=====================*/
t_list		*ft_lst_last(t_list *lst);
void		ft_lst_add_front(t_list **lst, t_list *new);
void		ft_lst_add_back(t_list **head, t_list *new);
t_list		*ft_new_node(char *value);
void		free_list(t_list *list);
size_t		get_list_len(t_list *list);

/*==================exit & free=====================*/
void		free_rgb(t_rgb *rgb);
void		free_tab(char **tab);
void		free_s_map(t_map *map);
void		free_texture(t_texture *texture);
void		exit_parse(t_game *game);
void		simple_exit(char *msg, int code);
void		free_parse(t_game *game);
void		exit_prog(t_game *game);

#endif

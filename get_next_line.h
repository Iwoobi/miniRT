/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:52:30 by youhan            #+#    #+#             */
/*   Updated: 2022/09/07 18:52:32 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

void	ft_join(char **str, char *back, int flag);
int		ft_move_str(char **str, int a);
char	*ft_str_return_fin(char **str, int *i, int *j);
char	*ft_str_return(char **str, int *k);
int		ft_read(int fd, char **str, char *buff, int size);
char	*get_next_line(int fd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:10:29 by mabriand          #+#    #+#             */
/*   Updated: 2022/05/20 11:08:57 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>

# include <stdio.h>

typedef struct s_trans
{
	pid_t	pid;
	char	*msg;
}	t_trans;

/*	Libft			*/
size_t	ft_strlen(const char *s);
size_t	ft_intlen(int n);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_realloc(char *buffer, int size);
/*	Utils			*/
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_print_error(char *strerror);

#endif
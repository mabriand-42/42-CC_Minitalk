/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:44:45 by mabriand          #+#    #+#             */
/*   Updated: 2022/01/27 14:28:27 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == ' '
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_intlen(int n)
{
	int	i;

	i = 1;
	while (n > 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str != NULL)
		write(fd, str, ft_strlen(str));
}

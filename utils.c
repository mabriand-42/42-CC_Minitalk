/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:46:54 by mabriand          #+#    #+#             */
/*   Updated: 2022/01/04 21:35:54 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' ||c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	nbr;

	i = 0;
	minus = 1;
	nbr = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		nbr = (nbr * 10) + str[i] - 48;
		i++;
	}
	return (nbr * minus);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putendl_fd(char *str, int fd)
{
	size_t	len;

	if (str)
	{
		len = ft_strlen(str);
		write(fd, str, len);
		write(fd, "\n", 1);
	}
	return ;
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str != NULL)
		write(fd, str, ft_strlen(str));
}

void		ft_error(char *strerror)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(strerror, 2);
	exit(1);
}
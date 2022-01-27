/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:46:54 by mabriand          #+#    #+#             */
/*   Updated: 2022/01/27 14:29:30 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

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

char	*ft_itoa(int n)
{
	long	tmp;
	char	*str;
	size_t	len;

	tmp = (long)n;
	str = NULL;
	len = ft_intlen(tmp);
	if (n < 0)
	{
		len += 1;
		tmp *= -1;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str != NULL)
	{
		str[len] = '\0';
		while (len > 0)
		{
			str[len - 1] = (tmp % 10) + '0';
			len--;
			tmp /= 10;
		}
		if (n < 0)
			str[0] = '-';
	}
	return (str);
}

void	ft_putendl_fd(char *str, int fd)
{
	size_t	len;

	if (str)
	{
		len = ft_strlen(str);
		write(fd, str, len);
		write(fd, " \n", 2);
	}
	return ;
}

void	ft_error(char *strerror)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(strerror, 2);
	exit(1);
	return ;
}

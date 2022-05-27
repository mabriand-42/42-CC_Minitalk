/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:10:24 by mabriand          #+#    #+#             */
/*   Updated: 2022/05/27 14:59:35 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

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

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	nbr;

	i = 0;
	minus = 1;
	nbr = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == ' '
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		nbr = (nbr * 10) + str[i] - 48;
		i++;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	long	tmp;
	char	*str;
	size_t	len;

	tmp = (long)n;
	len = ft_intlen(tmp);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str != NULL)
	{
		if (n < 0)
		{
			len += 1;
			tmp *= -1;
			str[0] = '-';
		}
		str[len] = '\0';
		while (len > 0)
		{
			str[len - 1] = (tmp % 10) + '0';
			len--;
			tmp /= 10;
		}
	}
	return (str);
}

char	*ft_realloc(char *buffer, int size)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0')
	{
		new_str[i] = buffer[i];
		++i;
	}
	new_str[i] = '\0';
	free(buffer);
	return (new_str);
}

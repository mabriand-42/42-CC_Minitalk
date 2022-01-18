/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:04:51 by mabriand          #+#    #+#             */
/*   Updated: 2022/01/18 18:37:18 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_trans		g_client;

static int	get_bit(char *str)
{
	bool		bit;
	static int	i_bit = 0;
	static int	i = 0;

	if (i_bit > 7)
	{
		if (!str[i])
			return (-1);
		i_bit = 0;
		++i;
	}
	bit = (str[i] >> i_bit) & 1;
	++i_bit;
	return (bit);
}

static void	send_bit(pid_t pid, bool bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			ft_error("No such process");
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_error("No such process");
	}
	return ;
}

static void	send_next_bit(int signum)
{
	int	bit;

	if (signum == SIGUSR2)
		ft_error("Wrong signal. Please relaunch...");
	bit = get_bit(g_client.msg);
	usleep(100);
	if (bit == -1)
	{
		ft_putstr_fd("\nEnd of transmission! \n", 1);
		exit(EXIT_SUCCESS);
	}
	send_bit(g_client.pid, bit);
}

void	client_speaking(char *av1, char *av2)
{
	ft_putstr_fd("Client speaking. Receptionned the following:\n", 1);
	ft_putstr_fd("PID = ", 1);
	ft_putendl_fd(av1, 1);
	ft_putstr_fd("MSG = ", 1);
	ft_putendl_fd(av2, 1);
	return ;
}

int	main(int ac, char **av)
{
	pid_t	pid_server;

	if (ac != 3)
	{
		ft_error("Usage is as follows:\n'./client [PID] [string]'\n");
		return (1);
	}
	pid_server = ft_atoi(av[1]);
	if (pid_server < 1)
		ft_error("Wrong PID");
	client_speaking(av[1], av[2]);
	g_client.msg = av[2];
	g_client.pid = pid_server;
	signal(SIGUSR1, send_next_bit);
	signal(SIGUSR2, send_next_bit);
	send_bit(g_client.pid, get_bit(g_client.msg));
	while (1)
	{
		if (sleep(1) == 0)
			ft_error("Transmission failed.\nPlease relaunch the server");
	}
	return (0);
}
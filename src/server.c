/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:34:21 by mabriand          #+#    #+#             */
/*   Updated: 2022/05/19 11:47:38 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

/*
**
*/
void	prepare_new_delivery(char **buffer, int *size, int *i)
{
	ft_putstr_fd(*buffer, 1);
	free(*buffer);
	*buffer = NULL;
	*size = 0;
	*i = 0;
	return ;
}

/*
**	Parameters:
**		@ int	byte	:	the receptionned byte to store.
**
**	Description:
**	->	Allocates a buffer if there isn't one yet (size == 0).
**
**	->	Put the byte in it at position 'i', then increments 'i' for next byte.
**
**	-->	Reallocates buffer if needed.
**
**	-->	If the byte receptionned was NULL, it means it was the last one, so it
**		calls prepare_new_delivery(3)
**	
**	Return values:
**		If the byte is full, it returns the corresponding int, -1 else.		
*/
void	store_byte(int byte)
{
	static char	*buffer;
	static int	i = 0;
	static int	size = 0;

	if (size == 0)
	{
		buffer = (char *)malloc(sizeof(char) * (size + 1));
		if (!buffer)
			ft_error("malloc error");
		size++;
	}
	buffer[i++] = byte;
	if (i >= size)
	{
		size *= 2;
		buffer = ft_realloc(buffer, size);
		if (!buffer)
			ft_error("malloc error");
	}
	if (!byte)
		prepare_new_delivery(&buffer, &size, &i);
	return ;
}

/*
**	Parameters:
**		@ int	signum	:	integer corresponding to the signal received by the
**							client process (so sent by the server process)
**
**	Description:
**	->	If the signal SIGUSR2 is received, makes a left bit-shifting operation
**		to building the current byte. (Mutiplies by 2^'bits' in order to place
**		the bit 1 at the right place in our byte).
**	
**	->	Increments 'bits' to move forward in the byte.
**
**	->	1.	If 8 bits are stored, the byte is full.
**			Reboots all static variables at 0 and returns the corresponndng int.
**		2.	If not, returns -1, meaning more bits are neeeded to finish.
**	
**	Return values:
**		If the byte is full, it returns the corresponding int, -1 else.		
*/
static int	get_byte(int signum)
{
	static int	bits = 0;
	static char	byte = 0;
	char		c;

	if (signum == SIGUSR2)
		byte += 1 << bits;
	++bits;
	if (bits == 8)
	{
		c = byte;
		byte = 0;
		bits = 0;
		return (c);
	}
	return (-1);
}

/*
**	Parameters:
**		@ int	signum	:	integer corresponding to the signal received by the
**							server process.
**
**	Description:
**	->	If the return of get_byte(1) is > -1, the byte receptionned is stored
**		thanks to store_byte(1).
**
**	->	Sends SIGUSR1 to the client process so it keeps sending the bits, either
**		for a new byte, or for the current one (if get_byte(1) returned -1).
**	
**	Return values:
**		None.
*/
void	print_msg(int signum, siginfo_t *info, void *unused)
{
	int	byte;

	byte = get_byte(signum);
	if (byte != -1)
		store_byte(byte);
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error("No such process.");
	(void)unused;
	return ;
}

/*
**	Parameters:
**		None.
**
**	Description:
**	->	Gets the process ID (PID) with getpid(). It will enable communication 
**		between processes later.
**		
**	->	Thanks to sigaction(3), defines which action occurs when SIGUSR1 or
**		SIGUSR2 is received.
**	
**	->	Wait for a signal from the client. (For both signals, print_msg(3) will
**		be called. However, the succession of actions will defer inside the
**		function according to the signal recevied).
**	
**	Return values:
**		If an error occurs, the process returns 1, else 0.
*/
int	main(void)
{
	pid_t				pid_server;
	char				*str;
	struct sigaction	s;

	pid_server = getpid();
	str = ft_itoa(pid_server);
	ft_putendl_fd(str, 1);
	s.sa_sigaction = print_msg;
	s.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &s, NULL) < 0)
		return (1);
	if (sigaction(SIGUSR2, &s, NULL) < 0)
		return (1);
	while (1)
		pause();
	return (0);
}

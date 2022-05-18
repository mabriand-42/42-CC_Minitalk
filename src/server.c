/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:34:21 by mabriand          #+#    #+#             */
/*   Updated: 2022/05/16 11:39:26 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

/*
**	Parameters:
**		@ int 		signum	:
**
**	Description:
**	->	If the signal SIGUSR2 is received, we make a left bit-shifting
**		operation to contributes to building the current byte.
**		(We multiply by 2 at the power of 'bits' in order to place the
**		bit 1 at the right place in our byte)
**	->	We increment 'bits' by one, to indicated we have moved forward
**		in the byte.
**	->	1)	If we already stored 8 bits, it means our byte is full.
**			We then reboot all static variables at 0 and return the 
**			corresponding integer.
**		2)	If not, we return -1, meaning we need more bits to finish.
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

void	prepare_new_byte(char **buffer, int *size, int *i)
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
**		@ int 		signum	:
**		@ sigingo_t	*info	:
**		@ void		*unused	:
**
**	Description:
**		This function constructs the message transmitted bit by bit thanks
**		to the signals received from the client process.
**	
**	->	When a signal is received, it is transmitted to get_byte().
**
**	->	1)	If get_byte() returns -1.
**			It means that we are lacking bits to create the current
**			character (i.e. byte = 8 bits (= 1 or 0).
**			We must then keep going and collect the rest.
**	
**		2)	If get_byte() returns the corresponding integer (>= 0)
**			It means we received the 8 bits needed and built the byte.
**		
**			Then, we put the current char in our buffer.
**			If it happens to be '\0', we print our buffer in stdout.
**		
**	->	We send the signal SIGUSR1 to the client process for it to
**		continue the transmission and get the next bit. 
**	
**	Return values:
**		None.
*/
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

void	do_print(int byte)
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
		prepare_new_byte(&buffer, &size, &i);
	return ;
}

void	print_msg(int signum, siginfo_t *info, void *unused)
{
	int	byte;
	/*int	j;*/

	byte = get_byte(signum);
	/*j = 0;*/
	if (byte != -1)
		do_print(byte);
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
**	->	We get the Process Identifier (PID) with getpid().
**		It will enable communication between processes later.
**	
**	->	Thanks to sigaction(3), we define which action will occur when
**		specific signals (here SIGUSR1 or SIGUSR2 as they are the only
**		ones allowed by the subject) is received.
**	
**	->	We wait for a signal from the client.
**		(For both signals, print_msg() will be called. However, the
**		succession of actions will defer inside the function according
**		to the signal recevied).
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

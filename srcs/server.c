/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:00:11 by lanton-m          #+#    #+#             */
/*   Updated: 2025/10/01 20:19:50 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	struct sigaction	sa;

	ft_print_pid();
	ft_sigaction_server(&sa);
	while (1)
		pause();
	return (0);
}

void	ft_print_pid(void)
{
	pid_t	pid;

	pid = getpid();
	if (ft_printf("Server PID: %d\n", pid) == -1)
		ft_error("Error: write failed");
}

void	ft_handler_server(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit_index = 0;
	static pid_t			g_client_pid = 0;

	(void)context;
	g_client_pid = info->si_pid;
	if (signum == SIGUSR1)
		c |= (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == ASCII_BITS)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = 0;
		bit_index = 0;
	}
	if (kill(g_client_pid, SIGUSR1) == -1)
		ft_error("Error: Failed to send acknowledgment");
}

void	ft_sigaction_server(struct sigaction *sa)
{
	sa->sa_sigaction = ft_handler_server;
	sa->sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) == -1)
		ft_error("Error: sigemptyset failed");
	if (sigaction(SIGUSR1, sa, NULL) == -1
		|| sigaction(SIGUSR2, sa, NULL) == -1)
		ft_error("Error: sigaction failed");
}

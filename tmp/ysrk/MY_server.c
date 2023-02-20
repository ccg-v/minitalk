#include "minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == 0)
		return ;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

static void	ft_rebuild_strlen(char **message, int *current_bit, int *flag, int signal)
{
	static int	message_len = 0;

	if (signal == SIGUSR2)
		message_len = (message_len | 1 << *current_bit);
	(*current_bit)++;
	if (*current_bit == 32)
	{
		*flag = 1;
		*message = calloc(message_len + 1, sizeof(char));
		*current_bit = 0;
printf("Sending  %d bytes...\n", message_len);	
		message_len = 0;
		return;
	}
}


static void	ft_print_message(int *flag, char **str, int *i)
{
	*flag = 0;
	if (str)
	{
		ft_putendl_fd(*str, 1);
		free(*str);
	*str = 0;
	}
	*i = 0;
}


static void	ft_rebuild_message(int signal)
{
	static int	octet;
	static int	current_bit;
	static int	flag;
	static int	i;
	static char	*message;

	if (flag == 0)
		ft_rebuild_strlen(&message, &current_bit, &flag, signal);
	else
	{
		if (signal == SIGUSR2)
			octet = (octet | 1 << current_bit);
		current_bit++;
		if (current_bit == 8)
		{
			message[i] = octet;
			i++;
			current_bit = 0;
			if (octet == 0)
				return (ft_print_message(&flag, &message, &i));
			octet = 0;
			return ;
		}
	}
}

int	main(void)
{
	printf("Server's ready, PID is %d\n", getpid());
	signal(SIGUSR1, ft_rebuild_message);
	signal(SIGUSR2, ft_rebuild_message);
	while (1)
		pause();
}


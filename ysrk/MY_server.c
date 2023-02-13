#include "minitalk.h"

/*
int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0 && power == 0)
		return (1);
	else
		return (nb * ft_recursive_power(nb, power - 1));
}
*/

void	*ft_calloc_exit(size_t count, size_t size)
{
	size_t	total_size;
	void	*ret;

	total_size = size * count;
	ret = malloc(total_size);
	if (!ret)
		exit(EXIT_FAILURE);
	bzero(ret, total_size);
	return (ret);
}

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

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	m;

	m = (unsigned int)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		m *= -1;
	}
	if (m >= 10)
	{
		ft_putnbr_fd(m / 10, fd);
		ft_putnbr_fd(m % 10, fd);
	}
	else
	{
		ft_putchar_fd('0' + m, fd);
	}
}

static void	ft_receive_strlen(int *curr_bit, char **str, int *flag, int signal)
{
	static int	len_val = 0;

	if (signal == SIGUSR2)
//		len_val += ft_recursive_power(2, *curr_bit);
		len_val = (len_val | 1 << *curr_bit);
	if (*curr_bit == 31)
	{
		*flag = 1;
		*str = ft_calloc_exit(len_val + 1, sizeof(char));
		*curr_bit = 0;
		len_val = 0;
		return ;
	}
	(*curr_bit)++;
}

static void	ft_restart_variables(int *flag, char **str, int *i)
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

static void	ft_receive_information_from_the_client(int signal)
{
	static int	char_value = 0;
	static int	current_bit = 0;
	static int	flag = 0;
	static int	i = 0;
	static char	*final_str = 0;

	if (!flag)
		ft_receive_strlen(&current_bit, &final_str, &flag, signal);
	else
	{
		if (signal == SIGUSR2)
//			char_value += ft_recursive_power(2, current_bit);
			char_value = (char_value | 1 << current_bit);
		if (current_bit == 7)
		{
			final_str[i] = char_value;
			i++;
			current_bit = 0;
			if (char_value == 0)
				return (ft_restart_variables(&flag, &final_str, &i));
			char_value = 0;
			return ;
		}
		current_bit++;
	}
}

int	main(void)
{
	int	id;

	id = (int)(getpid());
	ft_putnbr_fd(id, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, ft_receive_information_from_the_client);
	signal(SIGUSR2, ft_receive_information_from_the_client);
	while (1)
		pause();
}


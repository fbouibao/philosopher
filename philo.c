/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:01:49 by fbouibao          #+#    #+#             */
/*   Updated: 2021/06/18 19:56:51 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define ttd  "600"
#define tte  "100"
#define tts  "100"
int i = 0;
int d = 0;
int t[2];
// pthread_mutex_t mut;

typedef struct s_philo
{
	int id;
	pthread_mutex_t *mut;
	pthread_mutex_t message;
	int iseating;
	int issleeping;
	int nbr_ph;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
}					t_philo;
t_philo     *ph;

typedef struct s_philosopher
{
	int id;
	pthread_t *p;
	pthread_mutex_t *mut;
	pthread_mutex_t message;
	int nbr_ph;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
}					t_philosopher;

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}
void	ft_putnbr_fd(int nbr, int fd)
{
	unsigned int	num;

	num = nbr;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		num = num * -1;
	}
	if (num < 10)
	{
		ft_putchar_fd(num + 48, fd);
	}
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putchar_fd(num % 10 + 48, fd);
	}
}
// void *fun(void * ikhan)
// {
//    /* for (int j = 0; j < 1000000; j++)
//     {
//         pthread_mutex_lock(&mut);
//         i++;
//         pthread_mutex_unlock(&mut);

//     }
//     return (NULL);*/
// }
void ft_print(char *m, t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->message);
	ft_putstr_fd("philo ", 1);
	ft_putnbr_fd(i, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(m, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&ph->message);
}
void    mysleep(int usecond)
{
    struct timeval tv;
    struct timezone tz;
    size_t time;
    size_t time2;
    size_t res;

    gettimeofday(&tv,&tz);
    time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);

    
    usleep((usecond - 10) * 1000);
    
    // time2 = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
    // res = time2 - time;
    while (res != usecond)
    {
        gettimeofday(&tv,&tz);
        time2 = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
           res = time2 - time;
        
    }
    // ft_putnbr_fd(time, 1);
    // ft_putstr_fd("\n", 1);
    // ft_putnbr_fd(time2, 1);
    // ft_putstr_fd("\n", 1);
    




    // printf("result ==> %lu", res);

}
void *fun2(void *ikhan)
{
	// t_philo *ph = (t_philo *)ikhan;
	t_philosopher  *p = (t_philosopher *)ikhan;
	

	// if (ph->id == 1)
	// {
	
	// if (ph->id == 1)
	//     fprintf(stderr, "\x1B[31mphilosopher number %d\n", ph->id);
	// else if (ph->id == 2)
	//     fprintf(stderr, "\x1B[32mphilosopher number %d\n", ph->id);

	// ft_putnbr_fd(p->id, 1);
	// ft_putstr_fd("\n", 1);
	pthread_mutex_lock(&p->mut[(p->id - 1)]);
	ft_print("has taking a fork", ph, p->id);
	pthread_mutex_lock(&p->mut[(p->id) % p->nbr_ph]);
	ft_print("has taking a fork", ph, p->id);
	ft_print("is eteing", ph, p->id);
	mysleep(p->time_to_eat);
	pthread_mutex_unlock(&p->mut[(p->id) % p->nbr_ph]);
	pthread_mutex_unlock(&p->mut[(p->id - 1)]);
	ft_print("is sleeping", ph, p->id);
	mysleep(p->time_to_sleep);
	ft_print("thinking", ph, p->id);
	

	   

	

	return (NULL);
}

// void *fun3(void * ikhan)
// {
//     // pthread_mutex_lock(&mut);
//     // i++;
//     // pthread_mutex_unlock(&mut);
//     // return (NULL);
// }

t_philo    *initial_ph()
{
	t_philo *ph;
	ph = malloc(sizeof(t_philo));
	return (ph);
}



int main(int ac, char *av[])
{
	int nbr_ph;
	t_philosopher **p;
	pthread_t *p1;


if (ac > 4)
{
	int i2 = 2;
	t[0] = 0;
	t[1] = 0;
 
	ph = initial_ph();
	
	ph->nbr_ph = atoi(av[1]);
	ph->time_to_die = atoi(av[2]);
	ph->time_to_eat = atoi(av[3]);
	ph->time_to_sleep = atoi(av[4]);
	int i;
	p1 = malloc(sizeof(pthread_t) * ph->nbr_ph);
	i = -1;	
	ph->mut = malloc(sizeof(pthread_mutex_t) * ph->nbr_ph);
	pthread_mutex_init(&ph->message, NULL);
	while (++i < ph->nbr_ph)
	{
		pthread_mutex_init(&ph->mut[i], NULL);
	}
	
	p = malloc(sizeof(t_philosopher *) * ph->nbr_ph);
	int k = -1;
	while (++k < ph->nbr_ph)
	{
		p[k] = malloc(sizeof(t_philosopher));
		p[k]->id = k + 1;
		p[k]->nbr_ph = ph->nbr_ph;
		p[k]->p = p1;
		p[k]->mut = ph->mut;
		p[k]->message = ph->message;
		p[k]->time_to_die = ph->time_to_die;
		p[k]->time_to_eat = ph->time_to_eat;
		p[k]->time_to_sleep = ph->time_to_sleep;
	}
	


	
	while (1)
	{
		
		i = -1;
		while (++i < ph->nbr_ph)
		{
			pthread_create(&p1[i], NULL, fun2, p[i]);
			usleep(100);
		    // pthread_join(p1[i - 1], NULL);
		}
		i = 0;
		 while (++i <= ph->nbr_ph)
        {
            // ph->id = i;
            // pthread_create(&p1[i - 1], NULL, fun2, ph);
			int k = pthread_join(p1[i - 1], NULL);
			// printf("join == [%d] i == [%d]\n", k, i);
			// ft_putnbr_fd(i, 1);
        }

	}
}
	
	

	//pthread_mutex_destroy(&mut);
	return (0);
}
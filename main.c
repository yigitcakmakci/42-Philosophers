#include "philo.h"
#include <pthread.h>
#include <stdio.h>//DİKKAT!
#include <stdlib.h>
#include <unistd.h>

int is_dead(unsigned long last_eat, int time_to_die)
{
    unsigned long current_time;

    current_time = get_time_in_ms();
    if ((current_time - last_eat) > (unsigned long)time_to_die)
        return (1);
    return (0);
}

void	*life_loop(void *arg)
{
	s_philo	*philo;

	philo = (s_philo *)arg;
	if (philo->current.id % 2 == 0)
        usleep(1500);
	philo->current.last_eat = get_time_in_ms();
	while (!is_dead(philo->current.last_eat, philo->metabolism->time_to_die) && philo-> current.eat_count < philo->metabolism->required_food_number)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("philo : %d taken left_fork\n", philo->current.id);
		pthread_mutex_lock(philo->right_fork);
		printf("philo : %d taken right_fork\n", philo->current.id);
		philo->current.last_eat = get_time_in_ms();
		printf("philo : %d is eating\n", philo->current.id);
		usleep(philo->metabolism->time_to_eat);
		philo->current.eat_count++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("philo : %d is sleeping\n", philo->current.id);
		usleep(philo->metabolism->time_to_sleep);
		printf("philo : %d is thinking\n", philo->current.id);
	}
	if (is_dead(philo->current.last_eat, philo->metabolism->time_to_die))
	{
		printf( "BEN FİZOLOF %d :::::: IM DEAD \n", philo-> current.id);
		return ((void *)0);
	}
	return ((void *)0);
}

s_metabolism	get_meta(char **argv)
{
	s_metabolism	meta;

	meta.number_of_philosophers = ft_atoi(argv[1]);
	meta.time_to_eat = ft_atoi(argv[2]);
	meta.time_to_die = ft_atoi(argv[3]);
	meta.time_to_sleep = ft_atoi(argv[4]);
	meta.required_food_number = ft_atoi(argv[5]);
	return (meta);
}

int	main(int argc, char **argv)
{
	s_metabolism	meta;
	s_philo			*philo;
	int				i;

	i = 0;
	meta = get_meta(argv);
	meta.forks = malloc(sizeof(pthread_mutex_t) * meta.number_of_philosophers);
	philo = malloc(sizeof(s_philo) * meta.number_of_philosophers);
	while (i < meta.number_of_philosophers)
	{
		pthread_mutex_init(&meta.forks[i], NULL);
		philo[i].current.id = i + 1;
		philo[i].current.eat_count = 0;
		philo[i].metabolism = &meta;
		i++;
	}
	i = 0;
	while (i < meta.number_of_philosophers)
	{
		philo[i].left_fork = &meta.forks[i];
		philo[i].right_fork = &meta.forks[(i + 1) % meta.number_of_philosophers];
		pthread_create(&philo[i].thread_id, NULL, &life_loop, &philo[i]);
		i++;
	}

	i = 0;
	while (i < meta.number_of_philosophers)
	{
		
		i++;
	}
	

	i = 0;
	while (i < meta.number_of_philosophers)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	return (0);
}

// EN SON FİZOLOFLARI DİZİ ŞEKLİNDE NASIL TUTACAĞIN KONUSUNDA KALDIN. AKLINDA 2 YÖNTEM VAR. (ÇOK FAZLA FİZOLOFA İHTİYACIMIZ VAR AMA SADECE 1 ADET METABOLİZM VERİSİ BULUNUYOR)
// 1- STRUCT'LARI AYIR. PHİLO İÇERİSİNDEKİ METABOLİSM KISMINI TAMAMEN AYRI TUT (ANCAK SANIRIM MÜMKÜN DEĞİL ÇÜNKİ PTHREAD_CREATE FONKSİYONUNDA SADECE 1 ŞEY GÖNDERİLEBİLİNİYOR.)
// 2- PHİLO_VALUES[0]'I SADECE METABOLİSM İÇERİKLEİR İÇİN KULLAN. KALANINI FİZOLOFLAR 1'DEN BAŞLAR.(DÜZENLİ AMA ORGANİZASYONEL SIKINTI RİSKİ)
// 3- PHILO_VALUES[0]'DA HEM FİZOLOF HEM DE METABOLİSM İÇERİKLERİ İÇİN KULLAN.(DÜZENSİZ AMA ORGANİZASYONEL DAHA AZ RİSK)
// 4- TÜM PHILO_VALUES INDEXLERİNE METABOLİSM DEĞERLERİNİ YERLEŞTİR(EĞER PTHREAD_CREATE PHILO STRUCT'ININ SADECE 1 ADET INDEXINI GONDERIYORSA EN OPTIMUM SEÇENEK BUDUR.)
// 5- BAŞKA BİR ŞEY BUL. (İLLAKİ KULLANABİLECEĞİMİZ DAHA MANTIKLI BİR YOL VARDIR)

//ÇÖZÜMÜ TÜM PHILO INDEXLERİNE AYNI YERİ İŞARET EDEN BİR VERİ GÖNDERMEYİ BULDUN VE UYGULADIN
//ŞİMDİKİ PROBLEM: 
//MUTEX YÖNETİMİ VE HERKESİN YAŞAYIP YAŞAMADIĞINI KONTROL EDECEK BİR SİSTEM.
//MAĞLUM PTHREAD İLE OLUŞTURULAN BİR FONKSİYON İŞLEVİNİN GERİ DEĞER DÖNDÜRÜP DÖNDÜRMEDİĞİNİ ÖĞRENMEN GEREKİYOR.
//YA DA GEMİNİ YARDIMIYLA BİR ŞEKİLDE BU PROBLEMİ ÇÖZ
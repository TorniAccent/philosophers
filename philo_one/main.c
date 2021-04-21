/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 20:12:04 by swquinc           #+#    #+#             */
/*   Updated: 2021/04/06 20:47:22 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

void	*phil(void *ptr)
{
	static int i;

	
	i++;
	pthread_lock();
	printf("%d\n", i);
	return (NULL);
}

int main()
{
	char	*str;
	pthread_t potok[3];

	str = strdup("World!");
	pthread_create(&potok[0], NULL, phil, str);
	pthread_detach(potok[0]);
	pthread_create(&potok[1], NULL, phil, str);
	pthread_detach(potok[1]);
	pthread_create(&potok[2], NULL, phil, str);
	pthread_detach(potok[2]);
}
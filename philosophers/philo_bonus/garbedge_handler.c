/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbedge_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:16:17 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/10 19:41:15 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	garb_add(t_garbage **lst, t_garbage *new)
{
	t_garbage	*lastone;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

static t_garbage	*garb_new(void *addrress)
{
	t_garbage	*newnode;

	newnode = malloc(sizeof(t_garbage));
	if (newnode == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	newnode->adr = addrress;
	newnode->next = NULL;
	return (newnode);
}

static void	free_garb_list(t_garbage **head)
{
	t_garbage	*current;
	t_garbage	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->is_free)
		{
			free(current->adr);
			current->adr = NULL;
		}
		current = next;
	}
}

void	*zyalloc(size_t size, int flag)
{
	static t_garbage	*gooper;
	t_garbage			*node;
	void				*address;

	address = NULL;
	if (flag == 'a')
	{
		address = malloc(size);
		if (!address)
			return (NULL);
		if (gooper == NULL)
			gooper = garb_new(address);
		else
		{
			node = garb_new(address);
			garb_add(&gooper, node);
		}
	}
	else if (flag == 'f')
		free_garb_list(&gooper);
	return (address);
}

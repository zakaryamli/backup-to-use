/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:20:27 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/13 23:37:02 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include<string.h>

void lst_add(t_env **lst, t_env *new)
{
	t_env *lastone;

	if (!lst || !new)
		return;
	if (!(*lst))
	{
		*lst = new;
		return;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

t_env *env_new(char *var, char *name)
{
    t_env *newnode = (t_env *)malloc(sizeof(t_env));
    if (newnode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    newnode->var = strdup(var);
    newnode->name = strdup(name);
    newnode->next = NULL;
    return newnode;
}


t_env *duplicate_list(t_env *head)
{
	if (head == NULL)
		return NULL;

	t_env *tmp = head; 
	t_env *newlist = NULL;
	t_env *tmpnew = NULL;
	t_env *newnode;

	while (tmp != NULL)
	{
		// printf("%s====%s\n",tmp->name , tmp->var);
		newnode = env_new(tmp->var, tmp->name);
		if (newlist == NULL)
			newlist = newnode;
		else
			tmpnew->next = newnode;
		tmpnew = newnode;
		tmp = tmp->next;
	}
	return (newlist); 
}

void swap(t_env *a, t_env *b) 
{
    char *temp = a->var;
    a->var = b->var;
    b->var = temp;
	char *temp1 = a->name;
	a->name = b->name;
	b->name = temp1;
}
void env_search_replace(t_env *head, char *to_replace, char *to_look)
{
	t_env	*tmp;

	if (!head) 
	{
		printf("Invalid data or data->env is NULL\n");
		return;
	}

	tmp = head;
	while(tmp)
		{
			if(strcmp(tmp->name, to_look) == 0)
			{
				tmp->var = strdup(to_replace);
				return;
			}
				
			tmp = tmp->next;
		}
		return;
}
int env_list_serch(t_env **head, char *to_look)
{
	t_env	*tmp;

	if (!*head) 
	{
		printf("Invalid data or data->env is NULL\n");
		return (0);
	}

	tmp = *head;
	while(tmp)
		{
			if(strcmp(tmp->name, to_look) == 0)
				return(1);
			tmp = tmp->next;
		}
		return(0);
}
void env_search_and_add(t_env *head, char *to_add, char *to_look)
{
	t_env	*tmp;

	if (!head) 
	{
		printf("Invalid data or data->env is NULL\n");
		return;
	}

	tmp = head;
	while(tmp)
		{
			if(strcmp(tmp->name, to_look) == 0)
			{
				// printf("{%s}", tmp->next->name);
				
				tmp->var = ft_strjoin(tmp->var ,to_add);
				return;
			}
				
			tmp = tmp->next;
		}
		return;
}
void env_print(t_toexec *data)
{
    t_env *tmp;

    if (!data || !data->env) {
        printf("Invalid data or data->env is NULL\n");
        return;
    }
	
    tmp = data->env; // Initialize tmp to point to the first node of the linked list
    while (tmp) {
        printf("%s=", tmp->name);
        printf("\"%s\"\n", tmp->var);
        tmp = tmp->next;
    }
}

// void env_export(t_env *head)
// {
// 	int swapped;
//     t_env *tmp;
//     t_env *cur = NULL;

//     /* Checking for empty list */
//     if (head == NULL)
//         return;

//     while (1)
// 	{
//         swapped = 0;
//         tmp = head;

//         while (tmp->next != cur)
// 		{
//             if (strcmp(tmp->var, tmp->next->var) > 0)
// 			{
// 						// printf("hna\n");
//                 swap(tmp, tmp->next);
//                 swapped = 1;
//             }
//             tmp = tmp->next;
//         }

//         if (!swapped)
//             break;

//         cur = tmp;
//     }
	
// }
void ft_export(char *name, char *var, t_env *head)
{
	t_toexec data;
	t_env *exported_env = duplicate_list(head);
	t_env *newnode;
		// printf("{%s .   %s}\n",head->var, head->next->var);
	if (name == NULL)
	{
		// env_export(exported_env);
		data.env = exported_env;
		env_print(&data);

	}
	else
	{
		// printf("{%s .   %s}\n",head->var, head->next->var);
		newnode = env_new(var, name);
		lst_add(&head ,newnode);
		lst_add(&exported_env ,newnode);
	}
}
char **split_env(char *arg)
{
	int i;
	char **res = malloc(sizeof(char *) * 3);
	
	i = 0;
	while(arg[i] != '=' && arg[i])
		i++;
	if(arg[i] == '=')
	{
		res[0] = ft_substr(arg, 0, i);
		res[1] = ft_substr(arg ,i + 1 , strlen(arg));
		res[2] = NULL;
		return(res);
	}
	return(NULL);
}

int main(int ac, char **av, char **env)
{
	t_env	*envi = NULL;
	t_env	*tmp = NULL;
	char	**arg =NULL;
	t_toexec data;
	// data.env = NULL;

	(void)ac;
	// (void)av;
	int i;
	i = 0;
	while (env[i] != NULL)
	{
		t_env *new_env = malloc(sizeof(t_env));
		if (!new_env)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
        }
		arg = ft_split(env[i], '=');
        new_env->var = arg[1];
		// printf("%s", arg[0]);
		new_env->name = arg[0];
        new_env->next = NULL;
        if (envi == NULL)
            envi = new_env;
		else
		{
			tmp = envi;
            while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
		}
		i++;
	}
	data.env = envi;
	// env_print(&data);
	// printf("FGhfgh\n");
	// printf("%s--------------------------------------\n", data.env->var);

	char **to_add;
	if(strstr(av[1], "+=") != NULL)
	{
		to_add = ft_split(av[1], '+');
	}
	else
	{
		to_add = split_env(av[1]);
	}
	if(env_list_serch(&data.env, to_add[0]))
	{
		if(strstr(av[1], "+=") != NULL)
		{
			env_search_and_add(data.env, &to_add[1][1], to_add[0]);
		}
		else if(strstr(av[1], "=") != NULL)
		{
			env_search_replace(data.env, to_add[1], to_add[0]);
			// printf("{%s . %s}\n", to_replace[1], to_replace[0]);
		}
		// else
		// 	ft_export(av[1], "", data.env);
	}
	else if(!env_list_serch(&data.env, to_add[0]))
	{

		if(strstr(av[1], "+=") != NULL)
		{
			ft_export(to_add[0], &to_add[1][1],data.env);
		}
		else if(strstr(av[1], "=") != NULL)
		{
			ft_export(to_add[0], to_add[1],data.env);
		}
	}
	env_print(&data);
}

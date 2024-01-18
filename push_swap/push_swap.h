/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:49:17 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 14:10:31 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>

void	rotate_a(int arr[], int size);
void	rotate_b(int arr[], int size);
void	reverse_rotate_a(int arr[], int size);
void	reverse_rotate_b(int arr[], int size);
void	push_a(int source[], int dest[], int *source_size, int *dest_size);
void	push_b(int source[], int dest[], int *source_size, int *dest_size);
void	swap_a(int arr[], int size);
void	swap_b(int arr[], int size);
void	push_swap(int arr[], int size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
long	ft_atoi(const char *str);
char	**free_leaks(char **strs);
int		check_duplicate_int(int arr[], int size);
int		check_duplicate(char **str);
int		find_index(int stack[], int size, int element);
int		find_small(int arr[], int size);
int		find_largest_number(int arr[], int size);
int		steps_needed(int size, int index);
void	make_to_top_b(int *stack, int size, int index);
void	make_to_top_a(int *stack, int size, int index);
void	extract_largest(int *stack_a, int *stack_b, int *size_a, int *size_b);
void	extract_second_largest(int *stack_a, int *stack_b,
			int *size_a, int *size_b);
void	largest_two(int *stack_a, int *stack_b, int *size_a, int *size_b);
void	sort_three(int *arr, int size);
void	sort_five(int *stack_a, int *stack_b, int *size_a, int *size_b);
int		ft_protection(char **arg);
char	**set_strings(int ac, char **av);
int		*set_array(char **strings);
int		last_check(int *arr, int j);
int		check_spaces_signs(int ac, char **av);
#endif

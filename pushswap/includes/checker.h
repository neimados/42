/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:02:01 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 17:29:39 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# define BUFFER_SIZE 42

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../includes/push_swap.h"

char	*get_next_line(int fd);
char	*ft_read(int fd, char *buffer);
char	*ft_findnl(char *buffer);
char	*ft_carry(char *buffer);
char	*ft_strjoin2(char *s1, char *s2);
void	ft_sa2(t_stack *stacka, int size);
void	ft_sb2(t_stack *stackb, int size);
void	ft_ss2(t_stack *stacka, t_stack *stackb, int size);
void	ft_pb2(t_stack *stacka, t_stack *stackb);
void	ft_pa2(t_stack *stacka, t_stack *stackb);
void	ft_ra2(t_stack *stacka);
void	ft_rb2(t_stack *stackb);
void	ft_rr2(t_stack *stacka, t_stack *stackb);
void	ft_rra2(t_stack *stacka);
void	ft_rrb2(t_stack *stackb);
void	ft_rrr2(t_stack *stacka, t_stack *stackb);
int		ft_checktask(char *str, t_stack *jobs);
void	dotask(t_stack *jobs, t_stack *stacka, t_stack *stackb);
int		ft_checkfirst(int argc, t_stack *stacka, t_stack *stackb, char **argv);

#endif
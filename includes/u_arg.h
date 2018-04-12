/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_arg.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gelambin <gelambin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 11:38:57 by gelambin          #+#    #+#             */
/*   Updated: 2018/04/11 17:50:14 by gelambin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_ARG_H
# define U_ARG_H
# include <flags.h>

typedef union	u_va_data
{
	unsigned char	c;
	int				d;
	unsigned int	u;
	unsigned int	x;
	unsigned int	X;
	double			e;
	double			E;
	double			f;
	char			*s;
	void			*p;
}				t_va_data;

typedef struct	s_printf_arg
{
	t_printf_flags	flags;
}				t_printf_arg;


#endif

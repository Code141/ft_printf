/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gelambin <gelambin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:44:31 by gelambin          #+#    #+#             */
/*   Updated: 2018/05/19 15:59:19 by gelambin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <s_ctx.h>
#include <specifiers.h>

int		argument_access(char *str, t_ctx *ctx, t_flag *flags)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;

	while (str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10) + str[i++] - '0';
	if (str[i] == '*')
		nb = va_arg(ctx->current_args, int);
	if (str[-1] == '.')
		flags->precision = nb;
	else if (str[i] == '$' && nb)
	{
		va_end(ctx->current_args);
		va_copy(ctx->current_args, ctx->args);
		while (nb-- > 1)
			va_arg(ctx->current_args, void*);
		i++;
	}
	else
		flags->width = nb;
	return (i);
}

int		length(char *str, t_flag *flags)
{

	if (str[0] == 'h' && str[1] == 'h')
		flags->length = e_length_hh;
	else if (str[0] == 'l' && str[1] == 'l')
		flags->length = e_length_ll;
	if (flags->length)
		return (1);
	if (str[0] == 'h')
		flags->length = e_length_h;
	else if (str[0] == 'l')
		flags->length = e_length_l;
	else if (str[0] == 'j')
		flags->length = e_length_j;
	else if (str[0] == 'z')
		flags->length = e_length_z;
	return (0);
}

int		flag(char *str, t_ctx *ctx, t_flag *flags)
{
	int	i;

	i = 0;
	while (str[i++])
		if (str[i] == '#')
			flags->alternate = 1;
		else if (str[i] == '.')
			flags->precision = 0;
		else if (str[i] == '0')
			flags->pad = 1;
		else if ((str[i] >= '1' && str[i] <= '9') || str[i] == '*')
			i += argument_access(str + i, ctx, flags) - 1;
		else if (str[i] == '-')
			flags->left_align = 1;
		else if (str[i] == '+')
			flags->explicite_sign = 1;
		else if (str[i] == ' ')
			flags->space_for_sign = 1;
		else if (str[i] == 'h' || str[i] == 'l'
			|| str[i] == 'j' || str[i] == 'z' )
			i += length(str + i, flags);
		else
			return (i);
	return (i);
}
/*
 static const t_conv g_conv[] = {
     { "bdiouxX", int_arg },
     { "DOU", dou_arg },
     { "Cc", c_arg },
     { "s", s_arg },
     { "S", ws_arg },
     { "p", p_arg },
     { "%", pct_arg }
 };
 */
int		specifier(char *str, t_flag *flags)
{
	if (*str == 'c')
		flags->procedure = &spec_c;
	else if (*str == 'd')
		flags->procedure = &spec_d;
	else if (*str == 'u')
		flags->procedure = &spec_u;
	else if (*str == 'x' || *str == 'X')
		flags->procedure = &spec_x;
	else if (*str == 'o')
		flags->procedure = &spec_o;
/*	else if (*str == 'e')
		flags->procedure = &spec_e;
	else if (*str == 'E')
		flags->procedure = &spec_E;
	else if (*str == 'f')
		flags->procedure = &spec_f;
	else if (*str == 'g')
		flags->procedure = &spec_g;
	else if (*str == 'G')
		flags->procedure = &spec_G;
*/	else if (*str == 's')
		flags->procedure = &spec_s;
	else if (*str == 'p')
		flags->procedure = &spec_p;
	else if (*str == '%')
		flags->procedure = &spec_percent;
	else
		return (0); // UNKNOW SPECIFIER
	flags->specifier = *str;
	return (1);
}

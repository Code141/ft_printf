#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: gelambin <gelambin@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2018/04/04 15:30:23 by gelambin          #+#    #+#             *#
#*   Updated: 2018/04/10 18:20:07 by gelambin         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME		=	libftprintf.a

SRCSPATH	=	srcs

CC			=	gcc

CFLAGS		=	#-Wall -Wextra -Werror						\
				#-std=c89 -pedantic							\
				#-Wmissing-prototypes -Wstrict-prototypes	\
				#-Wold-style-definition

CPPFLAGS	=	-I./includes/

SRCS		=	ft_printf.c									\
				eval.c

OBJS		=	$(addprefix $(SRCSPATH)/, $(SRCS:.c=.o))

all			:	 $(NAME) test

$(NAME)		:	$(OBJS)
	ar rc $(NAME) $?

clean		:
	rm -f $(OBJS)

fclean		:	clean
	rm -f $(NAME) $(OBJS)

re			:
	$(MAKE) $(MFLAGS) fclean
	$(MAKE) $(MFLAGS) all

.PHONY		:	 all clean fclean re

################################################################################

test		:	$(NAME)
	$(CC) -g -fsanitize=address -I./includes -L./ -lftprintf main.c -o test

g			:	$(OBJS)
	$(CC) -g $(OBJS) -o $(NAME)

fsanitize	:	$(OBJS)
	$(CC) -g -fsanitize=address $(OBJS) -o $(NAME)

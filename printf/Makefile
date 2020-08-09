# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 02:10:01 by acortes-          #+#    #+#              #
#    Updated: 2020/01/23 18:55:10 by acortes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS =	ft_all_values_to_start.c ft_super_function.c ft_x.c ft_big_x.c  ft_c.c ft_d.c ft_i.c \
		ft_my_args.c ft_new_me.c ft_p.c ft_printf.c ft_rest.c ft_restart_values.c ft_s.c \
		ft_u.c ft_write_and_sum.c ft_convert_to_hex.c ft_functions1.c ft_functions2.c ft_functions3.c
CFLAGS = -Wall -Wextra -Werror
COMP =	${OBJS:.c=.o}
NAME = libftprintf.a

all: $(NAME)

$(NAME): ${OBJS} ft_printf.h
	@gcc -c ${CFLAGS} ${OBJS}
	@ar rc ${NAME} ${COMP}
clean:
	@rm -f ${COMP}
fclean:	clean
	@rm -f ${NAME}
re: fclean all

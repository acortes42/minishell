SRCS				= ft_uitostr.c ft_ulitostr.c ft_ullitostr.c ft_litostr.c ft_llitostr.c ft_uctostr.c ft_ctostr.c ft_itostr.c ft_isspace.c ft_isupper.c ft_islower.c ft_isascii.c ft_strdup.c ft_calloc.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isprint.c \
	ft_memchr.c ft_memcmp.c ft_memccpy.c ft_memcpy.c ft_memmove.c ft_strchr.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strnlen.c ft_strncmp.c ft_strcmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_substr.c ft_strjoin.c ft_putnstr_fd.c

SRCS_BONUS 			= ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstnew_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c

OBJS				= ${SRCS:.c=.o}

OBJS_BONUS 			= ${SRCS_BONUS:.c=.o}

NAME				= libft.a

ARFLAGS				= rcs

CFLAGS				= -Wall -Werror -Wextra -g

all:        ${NAME}

${NAME}:
			${CC} -c ${SRCS} ${CFLAGS}
			ar rcs ${NAME} ${OBJS}
			ranlib ${NAME}

bonus:
			${CC} -c ${SRCS_BONUS} ${CFLAGS}
			ar rcs ${NAME} ${OBJS_BONUS}
			ranlib ${NAME}

norme:
	norminette *.c *.h

re:	fclean all

clean:
	${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
	${RM} ${NAME} ${OBJS} ${OBJS_BONUS}

fclean_bonus:	fclean
		${RM} ${OBJS_BONUS}

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sravonin <sravonin@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 13:55:37 by sravonin          #+#    #+#              #
#    Updated: 2025/01/27 14:01:10 by sravonin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_itoa.c ft_striteri.c ft_strmapi.c ft_split.c ft_strtrim.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strjoin.c ft_substr.c ft_calloc.c ft_strnstr.c ft_memcmp.c ft_memchr.c ft_strrchr.c ft_strchr.c ft_isalnum.c ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c ft_atoi.c ft_isalpha.c ft_isprint.c ft_memset.c ft_strlen.c ft_toupper.c ft_bzero.c ft_isascii.c ft_memcpy.c ft_strdup.c ft_strncmp.c ft_strlcat.c get_next_line.c get_next_line_utils.c

OBJS = ft_itoa.o ft_striteri.o ft_strmapi.o ft_split.o ft_strtrim.o ft_putnbr_fd.o ft_putendl_fd.o ft_putstr_fd.o ft_putchar_fd.o ft_strjoin.o ft_substr.o ft_calloc.o ft_strnstr.o ft_memcmp.o ft_memchr.o ft_strrchr.o ft_strchr.o ft_isalnum.o ft_isdigit.o ft_memmove.o ft_strlcpy.o ft_tolower.o ft_atoi.o ft_isalpha.o ft_isprint.o ft_memset.o ft_strlen.o ft_toupper.o ft_bzero.o ft_isascii.o ft_memcpy.o ft_strdup.o ft_strncmp.o ft_strlcat.o get_next_line.o get_next_line_utils.o

CC = cc

FLAGS = -Wall -Werror -Wextra

RM = rm -f

all : $(NAME)

.c.o :
	@$(CC) -c -I $(FLAGS) -o $@ $<

$(NAME) : $(OBJS)
	@ar -r $(NAME) $(OBJS)
	@ranlib $(NAME)

clean :
	@$(RM) *.o

fclean : clean
	@$(RM) $(NAME)

re : fclean all

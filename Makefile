# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 04:09:57 by mbelbiad          #+#    #+#              #
#    Updated: 2022/09/14 12:57:45 by mbelbiad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = CC
SRC = main.c philo_utils.c philo.c
OBJS = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror 

all : $(NAME)

$(NAME) : $(OBJS)
	 $(CC) $(CFLAGS) $(SRC) -o $(NAME) -fsanitize=thread -g

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2023/08/29 13:08:32 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   pipex

CC      = 	cc

CFLAGS  =   -Wall -Wextra -Werror -g

SRCDIR	=	src

INCDIR	=   includes

LIBFTDIR =  $(SRCDIR)/libft

SRC		=	main.c

LIBS 	=   -L$(LIBFTDIR) -lft

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: libft $(NAME) 

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	@ $(CC) $(CFLAGS) -c $< -I $(INCDIR) -I $(LIBFTDIR) -o $@

libft:
	@cd $(LIBFTDIR) && make -s && make -s clean

clean:
	@ $(MAKE) -s -C $(LIBFTDIR) clean
	@ $(RM) $(OBJS)

fclean: clean
	@ $(MAKE) -s -C $(LIBFTDIR) fclean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
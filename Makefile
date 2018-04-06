# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/04/06 18:03:14 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	rt
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft

SRCS		=	$(SRCD)/main.c $(SRCD)/objects.c $(SRCD)/objects_set.c \
				$(SRCD)/vec.c $(SRCD)/types.c $(SRCD)/ft_atof_s.c \
				$(SRCD)/reader.c $(SRCD)/parser.c \
				$(SRCD)/parse_funs1.c $(SRCD)/parse_funs2.c \
				$(SRCD)/parse_funs3.c $(SRCD)/parse_details.c \
				$(SRCD)/parse_type.c $(SRCD)/parse_type_2.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(INCD) -O3 -flto -march=native -std=c11 -pedantic \
				-I$(LIBFTD)/includes
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -lft -lm -framework OpenCL

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LDLIBS)
	@echo "rtv1 - compiled"

libs:
	make -C $(LIBFTD)
	
%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBFTD) clean
	@rm -f $(OBJS)
	@echo "rtv1 - cleaned"

fclean: clean
	make -C $(LIBFTD) __fclean
	@rm -f $(NAME)
	@echo "rtv1 - lib cleaned"

re: fclean all

rer:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	make $(NAME)
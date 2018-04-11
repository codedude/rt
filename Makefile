# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/04/11 16:26:55 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	rt
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
ENVD		=	$(SRCD)/env
OBJECTSD	=	$(SRCD)/objects
PARSERD		=	$(SRCD)/parser
UTILSD		=	$(SRCD)/utils

SRCS		=	$(SRCD)/main.c
SRCS		+=	$(ENVD)/env.c \
				$(ENVD)/camera_set.c $(ENVD)/canvas_set.c \
				$(ENVD)/camera_get.c $(ENVD)/canvas_get.c
SRCS		+=	$(UTILSD)/vec.c $(UTILSD)/types.c
SRCS		+=	$(OBJECTSD)/objects.c $(OBJECTSD)/objects_format.c \
				$(OBJECTSD)/objects_set1.c $(OBJECTSD)/objects_set2.c \
				$(OBJECTSD)/objects_set3.c
SRCS		+=	$(PARSERD)/reader.c $(PARSERD)/parser.c \
				$(PARSERD)/parse_funs1.c $(PARSERD)/parse_funs2.c \
				$(PARSERD)/parse_funs3.c $(PARSERD)/parse_funs4.c \
				$(PARSERD)/parse_details.c $(PARSERD)/parse_data.c\
				$(PARSERD)/parse_type.c $(PARSERD)/parse_type_2.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-O3 -flto -march=native -std=c11 -pedantic \
				-I$(LIBFTD)/includes -I$(INCD) 
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

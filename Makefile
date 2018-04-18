# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/04/18 15:08:50 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	rt
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
ENVD		=	env
OBJECTSD	=	objects
PARSERD		=	parser
UTILSD		=	utils
OPENCLD		=	opencl
SDLD		=	sdl
SDLLIBD		=	$(HOME)/.brew/lib
SDLINCD		=	$(HOME)/.brew/include/SDL2

FILES		=	main.c render_test.c
FILES		+=	$(ENVD)/rt.c $(ENVD)/env.c \
				$(ENVD)/camera_set.c $(ENVD)/canvas_set.c \
				$(ENVD)/camera_get.c $(ENVD)/canvas_get.c
FILES		+=	$(UTILSD)/vec.c $(UTILSD)/types.c
FILES		+=	$(OBJECTSD)/objects.c $(OBJECTSD)/objects_queue.c \
				$(OBJECTSD)/objects_format.c \
				$(OBJECTSD)/objects_set1.c $(OBJECTSD)/objects_set2.c \
				$(OBJECTSD)/objects_set3.c
FILES		+=	$(PARSERD)/reader.c $(PARSERD)/parser.c \
				$(PARSERD)/parse_funs1.c $(PARSERD)/parse_funs2.c \
				$(PARSERD)/parse_funs3.c $(PARSERD)/parse_funs4.c \
				$(PARSERD)/parse_details.c $(PARSERD)/parse_data.c\
				$(PARSERD)/parse_type.c $(PARSERD)/parse_type_2.c
FILES		+=	$(OPENCLD)/opencl.c $(OPENCLD)/opencl_init1.c \
				$(OPENCLD)/opencl_init2.c $(OPENCLD)/opencl_init_buffers.c \
				$(OPENCLD)/opencl_update_buffers.c $(OPENCLD)/opencl_kernels.c \
				$(OPENCLD)/opencl_errors.c $(OPENCLD)/opencl_get_image.c \
				$(OPENCLD)/opencl_run.c
FILES		+=	$(SDLD)/sdl.c

SRCS		=	$(addprefix $(SRCD)/, $(FILES))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-O3 -flto -march=native -std=c11 -pedantic \
				-I$(LIBFTD)/includes -I$(INCD) -I$(SDLINCD)
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -lft -lm -framework OpenCL \
				-L$(SDLLIBD) -lsdl2

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

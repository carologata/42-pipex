NAME	:= pipex
NAME_BONUS	:=	pipex_bonus
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBFT	:= ./libft

HEADERS	:= -I $(LIBFT)
LIBS	:= $(LIBFT)/libft.a

SRCS	:= $(addprefix ./mandatory/, pipex.c pipex_fill.c pipex_check.c pipex_process.c \
					pipex_exec.c pipex_utils.c)
OBJS	:= ${SRCS:.c=.o}

SRCS_BONUS	:= $(addprefix ./bonus/, pipex_bonus.c pipex_fill_bonus.c pipex_check_bonus.c \
					pipex_process_bonus.c pipex_exec_bonus.c pipex_utils_bonus.c)
OBJS_BONUS	:= ${SRCS_BONUS:.c=.o}

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

bonus: libft $(NAME_BONUS)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJS_BONUS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@make -C $(LIBFT) fclean

re: clean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(SRCS_BONUS) ./include

.PHONY: all, clean, fclean, re, libft
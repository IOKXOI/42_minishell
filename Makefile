include minishell.mk

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -g3 -MMD -MP -o $@ -c $< -I $(INCS_DIR)

all: $(NAME)

-include  $(SRCS_OBJS:.o=.d)

$(NAME): $(SRCS_OBJS)
	$(CC) $(LBSD) $(CFLAGS) $^ -o $(NAME) -lm

clean:
	rm -f $(SRCS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)

re: fclean
	make

.PHONY	: all clean fclean re

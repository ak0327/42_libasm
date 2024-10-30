NAME 	= a.out

SRCS_DIR	= srcs
ASM_SRCS	= hello.s \
		  	  ft_strlen.s

OBJS_DIR	= objs
OBJS		= $(ASM_SRCS:%.s=$(OBJS_DIR)/%.o)
DEPS		= $(OBJS:%.o=%.d)

LIB 	= lib/libasm.a

C_SRC	= srcs/main.c

INCL	= includes


.PHONY : all
all : $(NAME)

$(NAME) : $(C_SRC) $(LIB)
	gcc $(C_SRC) -I$(INCL) -Llib -lasm -o $@

$(LIB): $(OBJS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.s
	@mkdir -p $(dir $@)
	nasm -f elf64 $^ -o $@

.PHONY : clean
clean :
	rm -rf objs lib

.PHONY : fclean
fclean : clean
	rm -f $(NAME)

.PHONY : re
re : fclean all

.PHONY : run
run : all
	./$(NAME)


.PHONY : bonus
bonus :

-include $(DEPS)

build:
	docker build --platform=linux/amd64 -t ubuntu-x86 .
	docker run --platform=linux/amd64 -it -v $(shell pwd):/app ubuntu-x86 bash

NAME 	= a.out

ASM_SRC	= srcs/hello.asm

OBJ 	= objs/hello.o

LIB 	= lib/libasm.a

C_SRC	= srcs/main.c

INCL	= includes


.PHONY : all
all : $(NAME)

$(NAME) : $(C_SRC) $(LIB)
	gcc $(C_SRC) -I$(INCL) -Llib -lasm -o $@

$(LIB): $(OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $<

$(OBJ) : $(ASM_SRC)
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

build:
	docker build --platform=linux/amd64 -t ubuntu-x86 .
	docker run --platform=linux/amd64 -it -v $(shell pwd):/app ubuntu-x86 bash

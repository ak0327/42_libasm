NAME 	= hello
SRC 	= playground/hello.asm
OBJ 	= playground/hello.o


.PHONY : all
all : $(NAME)

$(NAME) : $(OBJ)
	ld $^ -o $@

$(OBJ) : $(SRC)
	nasm -f elf64 $^ -o $@

.PHONY : clean
clean :
	rm -f $(OBJ)

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

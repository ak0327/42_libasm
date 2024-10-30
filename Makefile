NAME 	= a.out

SRCS_DIR	= srcs
ASM_SRCS	= hello.s \
		  	  ft_strlen.s \
		  	  ft_strcpy.s

OBJS_DIR	= objs
OBJS		= $(ASM_SRCS:%.s=$(OBJS_DIR)/%.o)
DEPS		= $(OBJS:%.o=%.d)

LIB 	= lib/libasm.a

C_SRC	= srcs/main.c

INCL	= includes

CONTAINER_NAME := libasm-dev

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

.PHONY	: utest
utest	:
	cmake -S . -B build
	cmake --build build
	./build/utest

.PHONY	: t
t	:
	docker exec $(CONTAINER_NAME) make
	docker exec $(CONTAINER_NAME) make utest

-include $(DEPS)

docker-run: docker-build docker-exec

docker-build:
	docker build --platform=linux/amd64 -t ubuntu-x86 .
	docker run \
		--detach --interactive \
		--platform=linux/amd64 \
		--volume $(shell pwd):/app \
		--name $(CONTAINER_NAME) \
		ubuntu-x86 tail -f /dev/null

docker-exec:
	docker exec -it $(CONTAINER_NAME) bash

docker-stop:
	@if [ "$$(docker ps -q -f name=$(CONTAINER_NAME))" ]; then \
		docker stop $(CONTAINER_NAME); \
	else \
		echo "Container $(CONTAINER_NAME) is not running"; \
	fi

docker-clean: docker-stop
	docker rm -f $(CONTAINER_NAME)

docker-fclean:
	docker system prune -a

docker-info:
	docker exec $(CONTAINER_NAME) lscpu

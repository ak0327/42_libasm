all: re

build:
	docker build --platform=linux/amd64 -t ubuntu-x86 .

run:
	docker run --platform=linux/amd64 -it -v $(shell pwd):/app ubuntu-x86 bash

re: build run

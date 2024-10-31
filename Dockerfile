FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    binutils \
    build-essential \
    cmake \
    make \
    nasm

ENV MAKEFLAGS=--no-print-directory

WORKDIR /app

COPY . .

CMD ["bash"]

FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    binutils \
    build-essential \
    make \
    nasm

WORKDIR /app

COPY . .

CMD ["bash"]

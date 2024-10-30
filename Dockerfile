FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    binutils \
    build-essential \
    cmake \
    make \
    nasm
#    libgtest-dev

#RUN cd /usr/src/googletest && \
#    cmake CMakeLists.txt && \
#    make && \
#    cp lib/*.a /usr/lib

WORKDIR /app

COPY . .

CMD ["bash"]

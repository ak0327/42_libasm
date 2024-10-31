# libasm
## 1. Overview


<br>

## 2. How to use
### 2.1 Clone
```shell
git clone git@github.com:ak0327/42_libasm.git
cd 42_libasm
```

### 2.2 Build docker container
```shell
# build
$ docker build --platform=linux/amd64 -t ubuntu-x86 .

$ docker run --platform=linux/amd64 -it -v $(shell pwd):/app ubuntu-x86 bash

# confirmation of x86_64
$ uname -m
x86_64

$ ps aux | grep qemu
root         1  0.0  0.0 149292 12720 pts/0    Ssl  23:39   0:00 /usr/bin/qemu-x86_64 /usr/bin/bash bash
```

<br>

## 3. Confirmed Environments
* Ubuntu 22.04.1 LTS (x86_64)

<br>

## 4. References
- System V Application Binary Interface, Draft 0.99.6 – July 2, 2012 – 17:14
- 矢沢久雄, プログラムはなぜ動くのか 第2版, 日経BP社

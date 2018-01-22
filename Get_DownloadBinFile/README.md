
- [x] Author : Runner
- [x] Date   : 2017-12-19

### 工程简介

- inc      : 存放全局头文件
- md5      : 存放md5算法文件
- src_bin  : 存放原始bin文件
- out      : 存放新生成的bin文件
- main.c   : 工程主程序
- Makefile : 工程管理文件
- tags     : tags文件
- get_bin  : 编译生成的可执行文件

### 工程编译

- make

> 编译成功后，在out目录下会生成一个Download.bin，该文件头部有32字节用于存放src_bin目录下的bin文件大小和该bin文件对应的MD5摘要值，
其中前4个字节用于存放文件大小，紧接着16个字节用于存放MD5摘要值，剩余几个字节存放0.

### 清除工程

- make clean

### 使用

> 使用该工程，只需要事先将要操作的bin文件存放入src_bin目录，然后编译工程，执行得到的get_bin文件，即可在out目录得到处理好的bin文件，文件名为Download.bin.

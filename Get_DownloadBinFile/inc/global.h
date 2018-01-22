#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


#include "../md5/md5.h"

#define DEBUG 				0

#define SRC_BIN_PATH "./src_bin/uart_irq.bin"
#define OUT_BIN_PATH "./out/Download.bin"

#define BUFF_SIZE           1024
#define MD5_SIZE   			16
#define HEAD_SIZE 		    128 //由于stm32的程序起始地址必须是128的整数倍，所以这里的头必须设置为128的整数倍	

typedef unsigned char   	U8;
typedef unsigned short  	U16;
typedef unsigned int    	U32;
typedef int 				S32;
typedef long int 			S64;
typedef unsigned long int 	U64;


U32 GetFileSize(const char *path);


#endif

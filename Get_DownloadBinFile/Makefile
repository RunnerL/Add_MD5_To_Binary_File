
OBJS = main.o ./md5/md5.o
CC = gcc
CFLAGS = -Wall -O -g

get_binfile : $(OBJS)
	$(CC) $(OBJS) -o get_bin


main.o : main.c ./inc/global.h
	$(CC) $(CFLAGS) -c main.c -o main.o
md5.o  : ./md5/md5.c ./md5/md5.h
	$(CC) $(CFLAGS) -c ./md5/md5.c -o ./md5/md5.o

clean:
	rm -rf *.o get_bin md5/*.o out/Download.bin 

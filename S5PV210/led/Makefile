CC=arm-linux-gcc
OBJ=start.o led.o
NAME=led
FLAGS=-nostartfiles -nostdlib
BINARY=arm-linux-objcopy  -O  binary

all:$(OBJ)
	$(CC)  -T link.lds   $(FLAGS)   $(OBJ)  -o  $(NAME).elf
	$(BINARY)  $(NAME).elf   $(NAME).bin
	cp  $(NAME).bin  ~/shared/image

%.o:%.s
	$(CC) -c   $<  -o  $@

%.o:%.c
	$(CC) -c   $<  -o  $@

clean:
	rm  $(NAME).elf   $(NAME).bin  $(OBJ)

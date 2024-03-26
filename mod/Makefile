include $(DEVKITPPC)/gamecube_rules

all: payload.bin

FLAGS	=	-DGEKKO -mcpu=750 -meabi -mhard-float

bootstrap.o: bootstrap.asm
	$(AS) -o bootstrap.o bootstrap.asm

payload.elf: main.c bootstrap.o linker.ld
	$(CC) $(FLAGS) -Os -nostartfiles -nostdlib main.c bootstrap.o -o payload.elf -fpie -Wall -T linker.ld -Wl,-Map,output.map

payload.bin: payload.elf
	$(OBJCOPY) -O binary payload.elf payload.bin

bootstrap.bin: bootstrap.o
	$(OBJCOPY) -O binary bootstrap.o bootstrap.bin

clean:
	rm -f payload.bin payload.elf output.map bootstrap.o

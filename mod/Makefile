include $(DEVKITPPC)/gamecube_rules

all: payload.bin

bootstrap.o: bootstrap.asm
	$(AS) -o bootstrap.o bootstrap.asm

payload.elf: main.c bootstrap.o linker.ld
	$(CC) -Os -nostartfiles -nostdlib main.c bootstrap.o -o payload.elf -fpie -Wall -T linker.ld

payload.bin: payload.elf
	$(OBJCOPY) -O binary payload.elf payload.bin

bootstrap.bin: bootstrap.o
	$(OBJCOPY) -O binary bootstrap.o bootstrap.bin

clean:
	rm -f payload.bin payload.elf bootstrap.o

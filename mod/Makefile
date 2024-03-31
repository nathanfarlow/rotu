include $(DEVKITPPC)/gamecube_rules

all: payload.bin

FLAGS	=	-DGEKKO -mcall-sysv -mcpu=750 -meabi -mhard-float

# MODS = -DHEAD_MOD

bootstrap.o: bootstrap.s
	$(AS) -o bootstrap.o bootstrap.s

payload.elf: main.c head_mod.c gfx.c npc.c common.c bootstrap.o linker.ld
	$(CC) $(FLAGS) $(MODS) -Werror -O2 -g main.c head_mod.c gfx.c npc.c common.c bootstrap.o -o payload.elf -Wall -T linker.ld -Wl,-Map,output.map,-Bstatic

payload.bin: payload.elf
	$(OBJCOPY) -O binary payload.elf payload.bin

clean:
	rm -f payload.bin payload.elf output.map bootstrap.o

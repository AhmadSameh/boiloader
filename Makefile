CC = x86_64-w64-mingw32-gcc
INLCUDES = -I./includes -I./src/system_table -I./src/protocols/console -I./src
FLAGS = -g -Wall -Werror -Iinc -nostdlib -Wno-cpp -Werror -fno-builtin -m64 -mabi=sysv

all: BOOTX64.EFI
	cp ./BOOTX64.EFI ./tools/UEFI-GPT-image-creator
	./tools/UEFI-GPT-image-creator/write_gpt

BOOTX64.EFI: ./build/bootloader.o
	${CC} ${INLCUDES} ./src/bootloader.c -std=c17 -Wall -Wextra -Wpedantic -mno-red-zone -ffreestanding -nostdlib -Wl,--subsystem,10 -e boiloader_main -o BOOTX64.EFI

./build/bootloader.o: ./src/bootloader.c
	${CC} ${INLCUDES} -c ./src/bootloader.c -o ./build/bootloader.o

clean:
	rm ./BOOTX64.EFI
	rm ./build/bootloader.o

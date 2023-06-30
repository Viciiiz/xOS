


all: main rootfs.img
	mcopy -i rootfs.img@@1M main ::/
	mmd -i rootfs.img@@1M boot 
	mcopy -i rootfs.img@@1M grub.cfg ::/boot

main: src/main.c
	gcc -c -ffreestanding -mgeneral-regs-only -mno-mmx -m32 -march=i386 -fno-pie -fno-stack-protector -g3 -Wall src/main.c
	gcc -c -ffreestanding -mgeneral-regs-only -mno-mmx -m32 -march=i386 -fno-pie -fno-stack-protector -g3 -Wall src/rprintf.c
	gcc -c -ffreestanding -mgeneral-regs-only -mno-mmx -m32 -march=i386 -fno-pie -fno-stack-protector -g3 -Wall src/putc.c
	gcc -c -ffreestanding -mgeneral-regs-only -mno-mmx -m32 -march=i386 -fno-pie -fno-stack-protector -g3 -Wall src/io_ports.c
	mv *.o obj/
	ld -T kernel.ld  -e main -melf_i386  obj/main.o obj/rprintf.o obj/putc.o obj/io_ports.o -o main


rootfs.img:
	dd if=/dev/zero of=rootfs.img bs=1M count=32
#	/usr/local/grub-i386/bin/grub-mkimage -p "(hd0,msdos1)/boot" -o grub.img -O i386-pc normal biosdisk multiboot multiboot2 configfile fat exfat part_msdos
	grub-mkimage -p "(hd0,msdos1)/boot" -o grub.img -O i386-pc normal biosdisk multiboot multiboot2 configfile fat exfat part_msdos
#	dd if=/usr/local/grub-i386/lib/grub/i386-pc/boot.img  of=rootfs.img conv=notrunc
	dd if=/usr/lib/grub/i386-pc/boot.img  of=rootfs.img conv=notrunc
	dd if=grub.img of=rootfs.img conv=notrunc seek=1
	echo 'start=2048, type=83, bootable' | sfdisk rootfs.img
	mkfs.vfat --offset 2048 -F16 rootfs.img

debug:
	screen -S qemu -d -m qemu-system-i386 -S -s -hda rootfs.img
	TERM=xterm gdb -x gdb_os.txt && killall qemu-system-i386

clean:
	rm -f grub.img main rootfs.img

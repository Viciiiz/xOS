# xOS
xOS is an operating system designed to run on x86 architecture.


## Description

This is an implementation of some of the main OS features designed to run on x86 architecture. It's important to note that this project is not a complete OS, though it might be in the future. What is implemented here is a mix of the semester project from the Operating Systems class from Loyola ( https://neilklingensmith.com/teaching/loyola/cs310-s2023/ ) and the OS Development Wiki ( https://wiki.osdev.org/Main_Page ). I plan to take the project a little further than what is made available on the class website for the sake of exploring more features of an OS. 
This project will use Grub (GRand Unified Bootloader) to load the kernel, and will be mainly written in C although some assembly is required. Since the project will be written from scratch, some C libraries won't be made available (such as stdio.h for example); in which case, the functions needed from those libraries will be written from scratch or imported ( the printf function will be imported from https://neilklingensmith.com/teaching/loyola/cs310-s2023/homework/rprintf.c for example). The project creates a disk image with a FAT16 file system, and uses qemu to simulate an x86-based computer system for running the operating system contained in the disk image.

## Setup & installation

After cloning the repo on your Ubuntu 22.* VM, install the following packages:

```
sudo apt install mtools make build-essentials gcc screen qemu qemu-system-i386
```

or

```
sudo apt install mtools
sudo apt install make
sudo apt install build-essentials
sudo apt install gcc
sudo apt install screen
sudo apt install qemu
sudo apt install qemu-system-i386
```


## Build project

To build the project, run the following command:

```
make clean && make
```

It will execute the commands in the Makefile which are designed to run on x86. 
The makefile commands basically compile the C programs under src/ using gcc, and then link the object files using ld to create the main executable. It then proceed to create a disk image file with a partitioned FAT16 file system. Finally, the necessary files are copied into the appropriate locations within the disk image file (rootfs.img), allowing it to be used as the root file system for running the operating system.

If you are using a Mac with a M1 chip, you will need to use the Makefile.m1 file with the following command: 

```
make clean && make -f Makefiles/Makefile.m1
```

## debug

The "debug" target in the Makefile starts a detached screen session and launches the qemu-system-i386 emulator in debugging mode with the specified disk image (rootfs.img). It then initiates a gdb session using configurations from gdb_os.txt and terminates the emulator after the debugging session ends. 
In the home directory, run the following command:

``` 
make debug
```

Use gdb commands to step through the code (n for next line, c for continue, si to step into a function, b to branch, p to print, etc.) The qemu is used to simulate an x86-based computer system for running the operating system contained in the "rootfs.img" disk image.


## components

- rprintf.c

Contains useful functions from stdio.h such as rprintf (the equivalent of printf()). The code is from https://neilklingensmith.com/teaching/loyola/cs310-s2023/homework/rprintf.c

- putc.c

Contains a function putc(char c) that is going to be passed to rprintf. The qemu terminal has 24 rows and 88 columns; putc.c contains functions that handle the scrolling effect on the qemu (the scrolling effect involves each line overwriting the previous line and freeing the last line of the screen). Putc() basically takes a character and writes it to the video memory (address 0xb8000); more specifically, it writes 16 bits per character to the video memory--the first 8 bits being the background color, and the remaining 8 bits the actual char data.

- io_ports.c

Contains 2 functions: inb() and outb(). inb(p) reads from I/O port p, and returns a one byte value. outb(p, val) writes a byte val to a specified I/O port p. The infinite loop in main() reads from port 0x64 to check if the keyboard has been pressed (that is, if there is any scancode to read). If it's the case, it then reads the scancode from port 0x60 and converts it to ascii using the keyboard_map[] in main.h. Used in this way, inb allows the implementation of a keyboard driver that reads keyboard input and displays it to the qemu. 

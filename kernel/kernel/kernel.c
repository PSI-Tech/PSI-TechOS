#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <stdio.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Ready to go!\n");
	gdt_init();

	printf("Wassup \n");
}

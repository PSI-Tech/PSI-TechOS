#include <kernel/gdt.h>
#include <kernel/tss.h>
#include <string.h>
#include <stdio.h>

void gdt_set_gate(int num, unsigned long base, unsigned long limit,
		unsigned char access, unsigned char gran)
{
	/* Setup descriptor base address */
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	/* Setup the descriptor limits */
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_init()
{
	gdtp.limit = GDT_SIZE * 8;
	gdtp.base = GDT_BASE;

	default_tss.debug_flag = 0x00;
	default_tss.io_map = 0x00;
	default_tss.esp0 = 0x1FFF0;
	default_tss.ss0 = 0x18;

	/* set null entry */
	gdt_set_gate(0, 0x0, 0x0, 0x0, 0x0);

	gdt_set_gate(1, 0x0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0x0, 0xFFFFFFFF, 0x92, 0xCF);

	memcpy((char*) gdtp.base, (char*) gdt, gdtp.limit);
	gdt_flush();
}

#include <kernel/gdt.h>

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access,
	       	uint8_t flags) 
{
	if (gdt[num].base_low == 0) {
		//TODO: error reporting
		return;
	}
	/* base adress */
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	/* limit */
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].limit_high_flags = ((limit >> 16) & 0x0F);

	/* access and flags */
	gdt[num].limit_high_flags |= (flags & 0xF0);
	gdt[num].access = access;
}

void gdt_init()
{
	gdtp.limit = (sizeof(struct gdt_entry) * GDT_SIZE) - 1;
	gdtp.base = &gdt;

	/* set null entry - we get complaints from emulators etc without this */
	gdt_set_gate(0, 0, 0, 0, 0);

	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	gdt_flush();
}	

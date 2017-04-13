#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_SIZE 10

/* Define a GDT entry. An entry is something like an LDT or TSS */

struct gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t limit_high_flags;
	uint8_t base_high;
} __attribute((packed));

/* Define a GDT pointer. This is what is uploaded to the GDTR */

struct gdt_ptr 
{
	uint16_t limit;
	uint32_t base;
} __attribute((packed));

struct gdt_entry gdt[GDT_SIZE];
struct gdt_ptr gdtp;

extern void gdt_flush();

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access,
		uint8_t flags);
void gdt_init();

#endif

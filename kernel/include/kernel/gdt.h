#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_SIZE 10
#define GDT_BASE 0x00000800

/* Define a GDT entry. An entry is something like an LDT or TSS */

struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
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

void gdt_set_gate(int num, unsigned long base, unsigned long limit,
		unsigned char access, unsigned char gran);
void gdt_init();

#endif

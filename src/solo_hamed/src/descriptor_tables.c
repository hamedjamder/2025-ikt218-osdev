#include "common.h"
#include "descriptor_tables.h"
#include "isr.h"

extern void gdt_flush(u32int);
extern void idt_flush(u32int);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

static void init_gdt();
static void init_idt();
static void gdt_set_gate(s32int,u32int,u32int,u8int,u8int);
static void idt_set_gate(u8int,u32int,u16int,u8int);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void init_descriptor_tables()
{
   init_gdt();
   init_idt();
}

static void init_gdt()
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (u32int)&gdt_entries;

   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   gdt_flush((u32int)&gdt_ptr);
}

static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}

static void init_idt()
{
   idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
   idt_ptr.base  = (u32int)&idt_entries;

   memset((u8int*)&idt_entries, 0, sizeof(idt_entry_t)*256);

   outb(0x20, 0x11);
   outb(0xA0, 0x11);
   outb(0x21, 0x20);
   outb(0xA1, 0x28);
   outb(0x21, 0x04);
   outb(0xA1, 0x02);
   outb(0x21, 0x01);
   outb(0xA1, 0x01);
   outb(0x21, 0x0);
   outb(0xA1, 0x0);

   idt_set_gate( 0, (u32int)isr0 , 0x08, 0x8E);
   idt_set_gate( 1, (u32int)isr1 , 0x08, 0x8E);
   idt_set_gate( 2, (u32int)isr2 , 0x08, 0x8E);
   idt_set_gate( 3, (u32int)isr3 , 0x08, 0x8E);
   idt_set_gate( 4, (u32int)isr4 , 0x08, 0x8E);
   idt_set_gate( 5, (u32int)isr5 , 0x08, 0x8E);
   idt_set_gate( 6, (u32int)isr6 , 0x08, 0x8E);
   idt_set_gate( 7, (u32int)isr7 , 0x08, 0x8E);
   idt_set_gate( 8, (u32int)isr8 , 0x08, 0x8E);
   idt_set_gate( 9, (u32int)isr9 , 0x08, 0x8E);
   idt_set_gate(10, (u32int)isr10, 0x08, 0x8E);
   idt_set_gate(11, (u32int)isr11, 0x08, 0x8E);
   idt_set_gate(12, (u32int)isr12, 0x08, 0x8E);
   idt_set_gate(13, (u32int)isr13, 0x08, 0x8E);
   idt_set_gate(14, (u32int)isr14, 0x08, 0x8E);
   idt_set_gate(15, (u32int)isr15, 0x08, 0x8E);
   idt_set_gate(16, (u32int)isr16, 0x08, 0x8E);
   idt_set_gate(17, (u32int)isr17, 0x08, 0x8E);
   idt_set_gate(18, (u32int)isr18, 0x08, 0x8E);
   idt_set_gate(19, (u32int)isr19, 0x08, 0x8E);
   idt_set_gate(20, (u32int)isr20, 0x08, 0x8E);
   idt_set_gate(21, (u32int)isr21, 0x08, 0x8E);
   idt_set_gate(22, (u32int)isr22, 0x08, 0x8E);
   idt_set_gate(23, (u32int)isr23, 0x08, 0x8E);
   idt_set_gate(24, (u32int)isr24, 0x08, 0x8E);
   idt_set_gate(25, (u32int)isr25, 0x08, 0x8E);
   idt_set_gate(26, (u32int)isr26, 0x08, 0x8E);
   idt_set_gate(27, (u32int)isr27, 0x08, 0x8E);
   idt_set_gate(28, (u32int)isr28, 0x08, 0x8E);
   idt_set_gate(29, (u32int)isr29, 0x08, 0x8E);
   idt_set_gate(30, (u32int)isr30, 0x08, 0x8E);
   idt_set_gate(31, (u32int)isr31, 0x08, 0x8E);

   idt_set_gate(32, (u32int)irq0, 0x08, 0x8E);
   idt_set_gate(33, (u32int)irq1, 0x08, 0x8E);
   idt_set_gate(34, (u32int)irq2, 0x08, 0x8E);
   idt_set_gate(35, (u32int)irq3, 0x08, 0x8E);
   idt_set_gate(36, (u32int)irq4, 0x08, 0x8E);
   idt_set_gate(37, (u32int)irq5, 0x08, 0x8E);
   idt_set_gate(38, (u32int)irq6, 0x08, 0x8E);
   idt_set_gate(39, (u32int)irq7, 0x08, 0x8E);
   idt_set_gate(40, (u32int)irq8, 0x08, 0x8E);
   idt_set_gate(41, (u32int)irq9, 0x08, 0x8E);
   idt_set_gate(42, (u32int)irq10, 0x08, 0x8E);
   idt_set_gate(43, (u32int)irq11, 0x08, 0x8E);
   idt_set_gate(44, (u32int)irq12, 0x08, 0x8E);
   idt_set_gate(45, (u32int)irq13, 0x08, 0x8E);
   idt_set_gate(46, (u32int)irq14, 0x08, 0x8E);
   idt_set_gate(47, (u32int)irq15, 0x08, 0x8E);

   idt_flush((u32int)&idt_ptr);
}

static void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   idt_entries[num].flags   = flags;
}

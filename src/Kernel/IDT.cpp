#include "IDT.h"

extern struct IDT64 _idt[256];
extern uint_64 isr1;
extern uint_64 irq0;
extern "C" void LoadIDT();

//void (*MainKeyboardHandler)(uint_8 scanCode, uint_8 chr);

void InitializeIDT()
{
    //for(uint_64 t = 0; t < 256; t++)
    //{
    _idt[33].zero = 0;
    _idt[33].offset_low = (uint_16)(((uint_64)&isr1 & 0x000000000000ffff));
    _idt[33].offset_mid = (uint_16)(((uint_64)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[33].offset_high = (uint_32)(((uint_64)&isr1 & 0xffffffff00000000) >> 32);
    _idt[33].ist = 0;
    _idt[33].selector = 0x08;
    _idt[33].types_attr = 0x8e;

    _idt[32].zero = 0;
    _idt[32].offset_low = (uint_16)(((uint_64)&irq0 & 0x000000000000ffff));
    _idt[32].offset_mid = (uint_16)(((uint_64)&irq0 & 0x00000000ffff0000) >> 16);
    _idt[32].offset_high = (uint_32)(((uint_64)&irq0 & 0xffffffff00000000) >> 32);
    _idt[32].ist = 0;
    _idt[32].selector = 0x08;
    _idt[32].types_attr = 0x8e;
    //}

    PIC_remap();

    //outb(0x21, 0xfd);
    //outb(0x21, 0xfc);
    //outb(0xa1, 0xff);
    
    LoadIDT();
}

extern "C" void irq_handler()
{
    ticks++;
    if(ticks > 10000)
    {
        ticks = 0;
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}

extern "C" void isr1_handler()
{
    uint_8 scanCode = inb(0x60); 
    uint_8 chr = 0;
    if(scanCode <= 0x39)
    {
        if(LShiftOn == true)
        {
            chr = KBSet1::ScanCodeTableShift[scanCode];
        }
        else if(CapsLockOn == true)
        {
            chr = KBSet1::ScanCodeTableCaps[scanCode];
        }
        else
        {
            chr = KBSet1::ScanCodeTable[scanCode];
        }
    }

    MainKeyboardHandler(scanCode, chr);
    //PrintString(HexToString(scanCode)); 

    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}
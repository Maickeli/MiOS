OUTPUT_FORMAT(binary)

ENTRY(_start)

INPUT
(
    ExtendedProgram.o
    Kernel.o
    IO.o
    PrintText.o
    IDT.o
    KeyboardHandler.o
    MemoryMap.o
    Terminal.o
    Binaries.o
    Heap.o
    DetectStorage.o
)

OUTPUT
(
    Kernel.bin
)

SECTIONS
{
    . = 0x8000;

    .text : ALIGN(0x1000)
    {
        *(.text)
    }

    .idt BLOCK(0x1000) : ALIGN(0x1000)
    {
        _idt = .;
        . = . + 0x1000;
    }

    .data : ALIGN(0x1000)
    {
        *(.data)
    }

    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
        *(.rdata*)
    }

    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
    }

}
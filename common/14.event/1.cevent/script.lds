/*script.lds*/

SECTIONS
{
    . = ALIGN(16);
    _cevent_start = .;
    cEvent : {
    *(cEvent) 
    }
    _cevent_end = .;
}
INSERT AFTER .rodata
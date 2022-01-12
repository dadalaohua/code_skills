/*script.lds*/
SECTIONS
{
    . = ALIGN(16);
    .rodata_nr_shell_cmd_start : {
      *(.rodata_nr_shell_cmd_start) 
      }
    .rodata_nr_shell_cmd : {
      *(.rodata_nr_shell_cmd) 
      }
    .rodata_nr_shell_cmd_end : {
      *(.rodata_nr_shell_cmd_end) 
      }
}
INSERT AFTER .rodata
/*script.lds*/
SECTIONS
{
    . = ALIGN(16);
    .rodata_test_cmd_start : {
      *(.rodata_nr_shell_cmd_start) 
      }
    .rodata_test_cmd : {
      *(.rodata_test_cmd) 
      }
    .rodata_test_cmd_end : {
      *(.rodata_test_cmd_end) 
      }
}
INSERT AFTER .rodata
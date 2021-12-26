# Generic ring buffer manager

https://github.com/yinjinzhong/ringbuff



Library provides generic FIFO ring buffer implementation.

## Features

- Written in ANSI C99, compatible with `size_t` type for size data types
- Platform independent
- FIFO (First In First Out) buffer implementation
- No dynamic allocation
- Fast read/write operations using memory copy functions
- Thread safe when used as pipe with single write and single read
- Interrupt safe when used as pipe with single write and single read
- Suitable for DMA transfers
- Supports data peek and data skip

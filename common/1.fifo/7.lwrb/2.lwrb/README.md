# Lightweight ring buffer manager

https://github.com/MaJerle/lwrb



- Library provides generic FIFO ring buffer implementation.

  ### Read first: [Documentation](http://docs.majerle.eu/projects/lwrb/)

  ## Features

  - Written in ANSI C99, compatible with `size_t` for size data types
  - Platform independent, no architecture specific code
  - FIFO (First In First Out) buffer implementation
  - No dynamic memory allocation, data is static array
  - Uses optimized memory copy instead of loops to read/write data from/to memory
  - Thread safe when used as pipe with single write and single read entries
  - Interrupt safe when used as pipe with single write and single read entries
  - Suitable for DMA transfers from and to memory with zero-copy overhead between buffer and application memory
  - Supports data peek, skip for read and advance for write
  - Implements support for event notifications
  - User friendly MIT license

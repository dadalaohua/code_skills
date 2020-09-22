# `#pragma once`——用于保证头文件只被编译一次
（1）#pragma once 用于保证头文件只被编译一次 
（2）#pragma once 是编译器相关的，不一定被支持（vc\gcc 都支持,bcc 不支持）
（3）#pragma once 比#ifndef…#define…#endif 效率高，因为后者定义的头文件仍然被处理。前者只要头文件被定义一次，就不会再次被处理。

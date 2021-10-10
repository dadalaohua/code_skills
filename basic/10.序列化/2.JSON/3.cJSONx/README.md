# cJSONx

**C语言JSON序列化反序列化工具库**

> cJSONx是依赖于cJSON解析库的二次封装库，实现快速、灵活地对在C语言结构体(struct)与JSON字符串之间转换

https://blog.csdn.net/Biang1231/article/details/111875394

https://github.com/CodeBiang/cJSONx

https://github.com/DaveGamble/cJSON

# 1. 前言

  C语言是嵌入式领域为数不多的选择之一，现代嵌入式应用当中又有很多业务逻辑会涉及到JSON转换的需求，此工具库依赖于C语言JSON解析库[cJSON](https://github.com/DaveGamble/cJSON)，编写cJSONx的目的是实现相对优雅地对JSON字符串进行正反序列化。

# 2 参考

本工具库实现参考了

- [C语言实现Json与结构体相互转换——cson](https://blog.csdn.net/s448573057/article/details/103710275)
- [在C语言上优雅地使用json - CSON原理解析](https://blog.csdn.net/qq_34245464/article/details/100168884)

# 3 实现目标

  cJSONx的目标就是最大化简化相关业务逻辑代码，实现的模式基本上就是参照Java谷歌[GSON](https://github.com/google/gson)，通过类反射机制进行数据读写，使用`@Expose`、`@SerializedName`等注解实现一些基本的正反序列化规定，关于GSON的使用不再赘述。

# 4 使用简介

  cJSONx参考了一部分cson的实现，做了一些拓展和完善，在宏API设计上进行了完善。
  cJSONx支持对c语言所有基本类型的反射，包括不同长度的整型和float、double两种浮点类型。
   cJSONx支持`ptr`反射和`preallocated`反射，使用时选用不同的**宏**来声明当前field是否需要申请空间，`ptr`反射会通过依赖库cJSON中`cJSON_Hooks`指定的内存申请、释放函数进行内存分配释放操作(默认为标准库的malloc，free)，preallocated反射则用于静态内存field。

## 4.1 宏API

注意，函数名字中不带有ptr的声明均用于静态内存声明。

### 4.1.1 基础类型反射

```c
__cjsonx_int(type, field) // 对应 1,2,4,8任意字节长度整型
__cjsonx_real(type, field) // 对应 float 或者 double
__cjsonx_bool(type, field) // 对应 bool, 或者任意整型
__cjsonx_str(type, field) // 对应字符数组 char c[20]
__cjsonx_str_ptr(type, field) // 对应字符指针 char* str
__cjsonx_object(type, field, reflect) // 对应结构体
__cjsonx_object_ptr(type, field, reflect) // 对应结构体指针
```

### 4.1.2 静态Array反射

```c
__cjsonx_array_int(type, field, item_count_field) // 对应任意整型数组
__cjsonx_array_real(type, field, item_count_field) // 对应任意浮点型数组
__cjsonx_array_bool(type, field, item_count_field) // 对应bool数组或者整型数组
__cjsonx_array_str_ptr(type, field, item_count_field) // 对应字符指针数组, char* strs[10]
__cjsonx_array_str(type, field, item_count_field) // 对应 char[20][50]
__cjsonx_array_object(type, field, item_count_field, refelct) // 对应结构体数组
```

### 4.1.3 指针(动态内存)Array反射

```c
__cjsonx_array_ptr_int(type, field, item_count_field) // 8/16/32/64位int* arr_i
__cjsonx_array_ptr_real(type, field, item_count_field) // float/double* arr_d 
__cjsonx_array_ptr_bool(type, field, item_count_field) // bool* arr_b
__cjsonx_array_ptr_str_ptr(type, field, item_count_field) // char** strs
__cjsonx_array_ptr_object(type, field, item_count_field, refelct) // 结构体指针
```

### 4.1.4 扩展注解的反射

```c
__cjsonx_int_ex(type, field, annotations...)
__cjsonx_real_ex(type, field, annotations...)
__cjsonx_bool_ex(type, field, annotations...)
__cjsonx_str_ex(type, field, annotations...)
__cjsonx_str_ptr_ex(type, field, annotations...)
__cjsonx_object_ex(type, field, reflect, annotations...)
__cjsonx_object_ptr_ex(type, field, reflect, annotations...)

__nullable(__val) // 注解此field不可为空
__deserialized(__val) // 注解此field是否反序列化
__serialized(__val) // 注解此field是否序列化
__serialized_name(__name) // 注解此field序列化名
...
```

### 4.1.5 正反序列化API

```c

/**
 * Convert Json string to struct
 * 
 * @param jstr Json string
 * @param output Struct address
 * @param tbl Reflection table
 * @return Error code 
 */
int cjsonx_str2struct(const char* jstr, void* output, const cjsonx_reflect_t* tbl);

/**
 * Convert Json string with length to struct
 * 
 * @param jstr Json string preallocated
 * @param len Buffer length
 * @param output Struct address
 * @param tbl Reflection table
 * @return Error code 
 */
int cjsonx_nstr2struct(const char* jstr, size_t len, void* output, const cjsonx_reflect_t* tbl);

/**
 * Convert cJSON object to struct
 * 
 * @param jo Json object
 * @param output Struct address
 * @param tbl Reflection table
 * @return Error code 
 */
int cjsonx_obj2struct(cJSON* jo, void* output, const cjsonx_reflect_t* tbl);

/**
 * Convert struct to json (string allocated)
 * 
 * @param jstr Pointer to place string address
 * @param input Struct address
 * @param tbl Reflection table
 * @return error code
 */
int cjsonx_struct2str(char** jstr, void* input, const cjsonx_reflect_t* tbl);

/**
 * Convert struct to json (char buffer preallocated)
 * 
 * @param jstr String buffer
 * @param size Buffer size
 * @param input Struct address
 * @param tbl Reflection table
 * @return error code
 */
int cjsonx_struct2str_preallocated(char* jstr, const int size, void* input, const cjsonx_reflect_t* tbl);

/**
 * Convert struct to cJSON object
 * 
 * @param obj cJSON object
 * @param input Struct address
 * @param tbl Reflection table
 * @return error code
 */
int cjsonx_struct2obj(cJSON* obj, void* input, const cjsonx_reflect_t* tbl);
```

## 4.2 使用实例

### 4.2.1 简单使用

  使用反射的第一步要声明结构体的反射，声明的方式是构建一个不定长反射数组`cjsonx_reflect_t device_reflection[]`来获取结构体域内存的反射数据，反射数组成员则是前面介绍以双下划线开头的的反射`宏函数`，声明完成后直接调用正反序列化转换函数完成转换。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSONx.h"

struct device {
    int id;
    char name[20];
    float temprature;
    unsigned long tick;
    
    unsigned int ip;
    unsigned int netmask;
    unsigned int gateway;
};

const cjsonx_reflect_t device_reflection[] = {
    __cjsonx_int(struct device, id),
    __cjsonx_str(struct device, name),
    __cjsonx_real(struct device, temprature),
    __cjsonx_int(struct device, tick),
    __cjsonx_int(struct device, ip),
    __cjsonx_int(struct device, netmask),
    __cjsonx_int(struct device, gateway),
    
    __cjsonx_end()
};

static void simple_serialize();
static void simple_deserialize();

int main(int argc, char* argv[]) {
    simple_serialize();
    simple_deserialize();
}

void simple_serialize() {
    struct device d = {
        .id = 1,
        .ip = 0x0A01A8C0,
        .gateway = 0x0101A8C0,
        .netmask = 0x00FFFFFF,
        .name = "Hello World",
        .temprature = 36.2F,
        .tick = 123
    };
    char buf[300];
    int ret = cjsonx_struct2str_preallocated(buf, sizeof(buf), &d, device_reflection);
    if (ret == ERR_CJSONX_NONE) {
        printf("Serialized JSON string: %s\n", buf);
    }
}

void simple_deserialize() {
    const char* json = "{\"id\":1,\"name\":\"Hello World\",\"temprature\":36.2,\"tick\":123,\"ip\":167880896,\"netmask\":16777215,\"gateway\":16885952}";
    struct device d;
    int ret = cjsonx_str2struct(json, &d, device_reflection);
    if (ret == ERR_CJSONX_NONE) {
        printf("Deserialized struct: id[%d], name[%s], temprature[%f], tick[%ld], ip[%#08X], netmask[%#08X], gateway[%#08X]\n",
            d.id, d.name, d.temprature, d.tick, d.ip, d.netmask, d.gateway);
    }
}
```

### 4.2.2 复杂混合使用

注意，包含动态申请内存结构体域声明的结构，注意使用`cjsonx_reflection_ptr_free`进行动态申请内存的释放

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSONx.h"

struct date {
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
};

enum booktype {
    BOOK_TECH = 0,
    BOOK_CARTOON
};

struct book {
    char* name;
    struct date time;
    enum booktype type;
    
    char isbn[11];

    char** authors;
    int author_cnt;

    short chapter_pages[15];
    int chapter_page_cnt;
};

const cjsonx_reflect_t date_reflection[] = {
    __cjsonx_int(struct date, year),
    __cjsonx_int(struct date, month),
    __cjsonx_int(struct date, day),
    __cjsonx_int(struct date, min),
    __cjsonx_int(struct date, hour),
    __cjsonx_int(struct date, sec),
    __cjsonx_end()
};

const cjsonx_reflect_t book_reflection[] = {
    __cjsonx_str_ptr(struct book, name),
    __cjsonx_object(struct book, time, date_reflection),
    __cjsonx_int(struct book, type),
    __cjsonx_str_ex(struct book, isbn, __serialized_name("ISBN")),
    __cjsonx_array_ptr_str_ptr(struct book, authors, author_cnt),
    __cjsonx_array_int(struct book, chapter_pages, chapter_page_cnt),
    __cjsonx_end()
};

static void complex_serialize();
static void complex_deserialize();

int main(int argc, char* argv[]) {
    struct book b = {0};
    const char* json = "{\"name\":\"AAA\",\"ISBN\":\"1234567890\",\"type\":0,\"authors\""
        ":[\"a\",\"b\",\"c\"],\"time\":{\"year\":2020,\"month\":11,\"day\":10,\"hour\":12"
        ",\"min\":12,\"sec\":12}, \"chapter_pages\":[10,15,28,77]}";
    int ret = cjsonx_str2struct(json, &b, book_reflection);
    if (ret == ERR_CJSONX_NONE) {
        char* p;
        cjsonx_struct2str(&p, &b, book_reflection);
        printf("%s\n", p);
        cjsonx_reflection_ptr_free(&b, book_reflection);
        free(p);
    }
}
```

### 4.2.3 扩展参数使用

  使用`__xx_ex`类型宏函数时，例如`__cjsonx_int_ex(type, field, annotations...)`，如果可变参数列表`annotations...`为空时，则拓展配置**保持默认**关系。
  示例如下：

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSONx.h"

struct date {
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
};

enum booktype {
    BOOK_TECH = 0,
    BOOK_CARTOON
};

struct book {
    char* name;
    struct date time;
    enum booktype type;
    
    char isbn[11];

    char** authors;
    int author_cnt;
};


const cjsonx_reflect_t date_reflection[] = {
    __cjsonx_int(struct date, year),
    __cjsonx_int(struct date, month),
    __cjsonx_int(struct date, day),
    __cjsonx_int(struct date, min),
    __cjsonx_int(struct date, hour),
    __cjsonx_int(struct date, sec),
    __cjsonx_end()
};

const cjsonx_reflect_t book_reflection[] = {
    __cjsonx_str_ptr_ex(struct book, name),
    __cjsonx_object_ex(struct book, time, date_reflection, 
        __serialized(false)),
    __cjsonx_int(struct book, type),
    __cjsonx_str_ex(struct book, isbn, __serialized_name("ISBN")),
    __cjsonx_array_ptr_str_ptr(struct book, authors, author_cnt),
    __cjsonx_end()
};

int main(int argc, char* argv[]) {
    struct book b = {0};
    const char* json = "{\"name\":\"AAA\",\"ISBN\":\"1234567890\",\"type\":0"
        ",\"authors\":[\"a\",\"b\",\"c\"],\"time\":{\"year\":2020,\"month\":11"
        ",\"day\":10,\"hour\":12,\"min\":12,\"sec\":12}}";
    int ret = cjsonx_str2struct(json, &b, book_reflection);
    if (ret == ERR_CJSONX_NONE) {
        char* p;
        cjsonx_struct2str(&p, &b, book_reflection);
        printf("%s\n", p);
        cjsonx_reflection_ptr_free(&b, book_reflection);
        free(p);
    }
}
```

# 5 实现原理

## 5.1 主要数据结构

### 5.1.1 cjsonx_reflect_t

  `cjsonx_reflect_t`是实现数据内存反射信息存储的核心数据结构，用于存储结构体每个field的内存偏移、内存宽度、数组父子项关系以及拓展注解信息等等。

```c
/** Reflection **/
typedef struct cjsonx_reflect {
    const char* field;                      /* field name */
    size_t offset;                          /* field address offset */
    size_t size;                            /* field size */
    cjsonx_type_e type;                     /* json element type */

    /* item reflection of array item or buffered string */
    const struct cjsonx_reflect* reflection;

    /* array counter field name */
    /* notice! this field should not be reflected */
    const char* arr_count_field;

    /* array item size */
    size_t item_size;

    /* data will be allocated by `malloc` or `malloc in cJSON_Hooks` */
    bool constructed;

    /* expanded reflection */
    const cjsonx_exopt_t annotation;
} cjsonx_reflect_t;
```

### 5.1.2 cjsonx_exopt_t

  exopt(extension options)是用于存储扩展配置的数据结构，这一部分的宏定义实现方式让扩展配置贴近于Java注解接口。
  此结构会在转换时，在相应的切面做相应的对应逻辑处理。注意该结构体结构在cJSONx使用过程中是对外封闭的，是使用时不需要关注的部分。

```c
typedef struct {
    /* when `nullalbe` is false, (de)serializing operation will not be terminated by missing field */
    /* default true */
    bool nullable;
    
    /* when `serialized` is false, field will be ignored when serializing */
    /* default true */
    bool serialized;

    /* when `deserialized` is false, field will be ignored when deserializing */
    /* default true */
    bool deserialized;

    /* field name mapping, if it's not NULL, real field name will be ignored */
    /* default NULL */
    const char* serialized_name;
} cjsonx_exopt_t;
```

## 5.2 大致实现思路

  这里的实现主要还是参考了cson的实现，有兴趣的可以看看开头提到的两篇博客。
  首先利用编程语言命名不能以数字开头特性，定义了基础数据类型反射。

```c
const cjsonx_reflect_t _cjsonx_reflect_int[] = {
    {"0integer", 0, sizeof(int), CJSONX_INTEGER, NULL, NULL, 0, 0, {0}}, {0}};

const cjsonx_reflect_t _cjsonx_reflect_string_ptr[] = {
    {"0strptr", 0, sizeof(char*), CJSONX_STRING, NULL, NULL, 0, 1, {0}}, {0}};

const cjsonx_reflect_t _cjsonx_reflect_real[] = {
    {"0real", 0, sizeof(double), CJSONX_REAL, NULL, NULL, 0, 0, {0}}, {0}};

const cjsonx_reflect_t _cjsonx_reflect_string_preallocated[] = {
    {"0str", 0, sizeof(char*), CJSONX_STRING, NULL, NULL, 0, 0, {0}}, {0}};
    
const cjsonx_reflect_t _cjsonx_reflect_float[] = {
    {"0float", 0, sizeof(float), CJSONX_REAL, NULL, NULL, 0, 0, {0}}, {0}};

const cjsonx_reflect_t _cjsonx_reflect_double[] = {
    {"0double", 0, sizeof(double), CJSONX_REAL, NULL, NULL, 0, 0, {0}}, {0}};

const cjsonx_reflect_t _cjsonx_reflect_bool[] = {
    {"0bool", 0, sizeof(int), CJSONX_TRUE, NULL, NULL, 0, 0, {0}}, {0}};
```

在数据反射之前，我们使用从cJSON操作，正反序列化的流程应该是:

开始 -> JSON字符串 -> cJSON_Parse -> cJSON Object -> 结束

开始t -> cJSON Objectt -> cJSON_Printt -> JSON字符串t -> 结束

数据反射之后：

开始t -> JSON字符串t -> cJSON_Parset -> cJSON Objectt -> 反射赋值 -> Struct -> 结束

开始 -> Struct -> 反射读取 -> cJSON Object -> cJSON_Print -> JSON字符串 -> 结束

  所以可以看到，反射工具库所做事情只有Object与结构体之间的内存映射读写。
  内存反射的实现也十分简单，通过`offsetof`与`sizeof`获取到结构体field的偏移和内存大小后，根据不同的类型、构造方式、扩展配置等，给对应的内存进行赋值或者内存复制即可。

# 6 优化范围

  cJSONx处于初期版本，有很多待完善的地方，例如静态数count域有时是没有必要的。
  另外，对于`serialized_name`选项设计为不定长数组，用于适配多个名称这样更为合理，但由于c语言只支持将不定长数组放在结构体末尾，并且必须是`static`，可能会造成使用者的不便、困惑等，所以目前就只实现了一个序列化名识别。
————————————————
版权声明：本文为CSDN博主「Biang1231」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/Biang1231/article/details/111875394


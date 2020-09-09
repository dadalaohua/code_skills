# C 库函数 - localeconv()

## 描述

C 库函数 **struct lconv \*localeconv(void)**  设置或读取地域化信息。它会返回一个 **lconv** 结构类型的对象。

## 声明

下面是 localeconv() 函数的声明。

```c
struct lconv *localeconv(void)
```

## 参数

- **NA**

## 返回值

该函数返回一个指向当前区域 **struct lconv** 的指针，它的结构如下：

```c
typedef struct {
   char *decimal_point;
   char *thousands_sep;
   char *grouping;    
   char *int_curr_symbol;
   char *currency_symbol;
   char *mon_decimal_point;
   char *mon_thousands_sep;
   char *mon_grouping;
   char *positive_sign;
   char *negative_sign;
   char int_frac_digits;
   char frac_digits;
   char p_cs_precedes;
   char p_sep_by_space;
   char n_cs_precedes;
   char n_sep_by_space;
   char p_sign_posn;
   char n_sign_posn;
} lconv
```
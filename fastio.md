## 宏标记

### `MIRAI_INPUT_BUFFER`

打开输入缓存。

### `MIRAI_INPUT_BUFFER_SIZE`

应当能够被转化为 `std::size_t` 类型字面量。表示输入缓存的大小（具体实现会在末尾添加一位，值恒为 `'\0'`）。缺省值为 `(1UL << 22)`。

### `MIRAI_OUTPUT_BUFFER`*

打开输出缓存。

### `MIRAI_OUTPUT_BUFFER_SIZE`*

应当能够被转化为 `std::size_t` 类型字面量。表示输出缓存的大小。缺省值为 `(1UL << 22)`。

### `MIRAI_USE_READ_FUNC`

使用 `unistd.h` 内的 `read` 函数读取。

### `MIRAI_USE_ISDIGIT`

使用 `cctype` 内的 `std::isdigit` 执行数字的判断。如果关闭则会使用 `#define digit(x) ((x)>='0'&&(x)<='9')` 宏。

### `MIRAI_USE_ARG_LIST`

对 `mirai::read` 和 `mirai::sread` 使用可变参数模板（C++11 特性）。如果以下两者都被满足，则库会忽略此宏：

- C++ 版本不到 C++11；
- `MIRAI_FORCE_USE_ARG_LIST` 被打开。

### `MIRAI_FORCE_USE_ARG_LIST`

强制对 `mirai::read` 和 `mirai::sread` 使用可变参数模板，忽略 C++ 版本。

### `MIRAI_ATTR_EXPECT`

对 `if` 和 `while` 使用 `[[likely]]` /`[[unlikely]]` 属性分支预测（C++20 特性）。如果以下两者都被满足，则库会忽略此宏：

- C++ 版本不到 C++20；
- `MIRAI_FORCE_ATTR_EXPECT` 被打开。

### `MIRAI_FORCE_ATTR_EXPECT`

强制对 `if` 和 `while` 使用 `[[likely]]` /`[[unlikely]]` 属性分支预测，忽略 C++ 版本。

### `MIRAI_BUILTIN_EXPECT`

对 `if` 和 `while` 使用 `__builtin_expect` 分支预测。

## 函数

以下函数都在 `mirai` 命名空间内。

### `flush_input`

```cpp
void flush_input(void);
```

如果开启输入缓存，则刷新输入缓存。

### `sscan`

```cpp
long long sscan(void);
```

读入一个 `long long ` 类型的数。支持的整数表达由如下两部分组成：

- （可选）一个正号或负号；
- 一个仅包含数字的字符串，表示整数的十进制表示。

无论读入多大的整数，都不会引起有符号整形溢出（Signed overflow）。如果输入值过大，返回值会为输入的整数对 `ULLONG_MAX` 取模再转化为 `long long` 的结果。

在实际读取中，所有正号都被忽略（即，不尾随数字的正号会被忽略）；不尾随数字的负号会被识别为 0。

### `scan`

```cpp
unsigned long long scan(void);
```

读入一个 `unsigned long long` 类型的数。支持的整数表达由如下两部分组成：

- （可选）一个正号。
- 一个仅包含数字的字符串，表示整数的十进制表示。

无论读入多大的整数，都不会引起有符号整形溢出（Signed overflow）。如果输入值过大，返回值会为输入的整数对 `ULLONG_MAX` 取模的结果。

在实际读取中，所有正号都被忽略（即，不尾随数字的正号会被忽略）。

### `sread`

```cpp
void sread(bool&);
void sread(int&);
void sread(short&);
void sread(long&);
void sread(long long&);
void sread(unsigned int&);
void sread(unsigned short&);
void sread(unsigned long&);
void sread(unsigned long long&);
```

用 `sscan` 读入，然后强制转化成目标类型。

```cpp
void sread(char&);
```

读入一个字符。不忽略空白字符。

```cpp
void sread(char*);
```

读入一个 C 风格字符串。

```cpp
void read(float& u);
void read(double& u);
void read(long double& u);
```

读入一个浮点类型。格式参考 `readf`。

```cpp
template <typename type> void sread(type&);
```

除上述特化以外皆没有实现。

```cpp
template <typename type, typename... Args) void sread(type&, Args&... args);
```

按从前往后的顺序为传入的每个变量逐一读入。

如果 `MIRAI_USE_ARG_LIST`/`MIRAI_FORCE_USE_ARG_LIST` 未打开，则不会实现此函数。

### `read`

```cpp
void read(bool&);
void read(int&);
void read(short&);
void read(long&);
void read(long long&);
void read(unsigned int&);
void read(unsigned short&);
void read(unsigned long&);
void read(unsigned long long&);
```

用 `scan` 读入，然后强制转化成目标类型。

```cpp
void read(char&);
```

读入一个字符。不忽略空白字符。

```cpp
void read(char*);
```

读入一个 C 风格字符串。

```cpp
void read(float& u);
void read(double& u);
void read(long double& u);
```

读入一个浮点类型。格式参考 `readf`。

```cpp
template <typename type> void read(type&);
```

除上述特化以外皆没有实现。

```cpp
template <typename type, typename... Args) void read(type&, Args&... args);
```

按从前往后的顺序为传入的每个变量逐一读入。

如果 `MIRAI_USE_ARG_LIST`/`MIRAI_FORCE_USE_ARG_LIST` 未打开，则不会实现此函数。

### `readch`

```cpp
char readch(void);
```

读入一个字符。

### `readc`

```cpp
char readc(void);
```

读入一个字符，忽略空白字符。

### `readstr`

```cpp
void readstr(char*);
```

读入一个 C 风格字符串，到空白字符停止。

### `readf`/`readdf`/`readlf`

```cpp
float readf(void);
double readdf(void);
long double readlf(void);
```

读入一个浮点数，支持的浮点数表达由以下部分组成：

- （可选）一个正号或负号；
- 一个非空数字串，中间有可选的一个小数点；
- （可选）一个 `e` 或 `E`，后紧跟：
  - （可选）一个正号或负号；
  - 一个非空字符串。

效率还有很大优化空间。

### (TODO)实现 `scanf` 的大多数功能

### (TODO)添加输出缓存，并实现 `printf` 的大多数功能

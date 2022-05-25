namespace mirai {

#if !defined(MIRAI_FORCE_USE_ARG_LIST) && defined(MIRAI_USE_ARG_LIST) && \
  __cplusplus < 201103L
#error MIRAI_USE_ARG_LIST needs C++11 to enable. \
use MIRAI_FORCE_USE_ARG_LIST if really need.
#endif
#ifdef MIRAI_FORCE_USE_ARG_LIST
#define MIRAI_USE_ARG_LIST
#endif

#if !defined(MIRAI_FORCE_ATTR_EXPECT) && defined(MIRAI_ATTR_EXPECT) && \
  __cplusplus < 202002L
#error MIRAI_ATTR_EXPECT needs C++20 to enable. \
use MIRAI_FORCE_ATTR_EXPECT if really need.
#undef MIRAI_ATTR_EXPECT
#endif
#ifdef MIRAI_FORCE_ATTR_EXPECT
#define MIRAI_ATTR_EXPECT
#endif

#ifdef MIRAI_ATTR_EXPECT
#define ift(x) [[likely]] if (x)
#define iff(x) [[unlikely]] if (x)
#define whilet(x) [[unlikely]] while (x)
#define whilef(x) [[likely]] while (x)
#elif defined(MIRAI_BUILTIN_EXPECT)
#define ift(x) if (__builtin_expect(!!(x), 1))
#define iff(x) if (__builtin_expect(!!(x), 0))
#define whilet(x) while (__builtin_expect(!!(x), 1))
#define whilef(x) while (__builtin_expect(!!(x), 0))
#else 
#define ift(x) if (x)
#define iff(x) if (x)
#define whilet(x) while (x)
#define whilef(x) while (x)
#endif

#ifndef MIRAI_INPUT_BUFFER_SIZE
#define MIRAI_INPUT_BUFFER_SIZE (1UL << 16)
#endif
#ifndef MIRAI_OUTPUT_BUFFER_SIZE
#define MIRAI_OUTPUT_BUFFER_SIZE (1UL << 16)
#endif

#ifdef MIRAI_INPUT_BUFFER
// let *input_buffer_end = '\0'.
char input_buffer[MIRAI_INPUT_BUFFER_SIZE + 1];
char *input_buffer_now = input_buffer;
char *input_buffer_end = input_buffer + MIRAI_INPUT_BUFFER_SIZE;

void flush_input(void) {
  #ifdef MIRAI_USE_READ_FUNC
  std::size_t ret = ::read(0, input_buffer, MIRAI_INPUT_BUFFER_SIZE);
  #else
  std::size_t ret = std::fread(input_buffer, sizeof(input_buffer[0]), 
    MIRAI_INPUT_BUFFER_SIZE, stdin);
  #endif
  iff(ret < MIRAI_INPUT_BUFFER_SIZE) {
    input_buffer[ret] = '\0';
  }
  input_buffer_now = input_buffer;
  return;
}
#else
void flush_input(void) {}
#endif

#ifndef MIRAI_INPUT_BUFFER
#define readchar() (std::getchar())
#else
char readchar(void) {
  iff(input_buffer_now == input_buffer_end) {
    flush_input();
  }
  return *(input_buffer_now++);
}
#endif

#ifdef MIRAI_USE_ISDIGIT
#define digit(x) (std::isdigit(x))
#else
#define digit(x) ((x) >= '0' && (x) <= '9')
#endif

void readstr(char*);

long long sscan(void) {
  char ch = readchar();
  whilet(!digit(ch) && ch != '-') {
    ch = readchar();
  }
  unsigned long long ret = 0;
  bool flag = false;
  iff(ch != '-') {
    ret = ch - '0';
  } else {
    flag = true;
  }
  ch = readchar();
  whilet(digit(ch)) {
    ret = ret * 10 + ch - '0';
    ch = readchar();
  }
  iff(flag) {
    return -ret;
  } else {
    return ret;
  }
}

void sread(bool& u) { u = sscan(); }
void sread(int& u) { u = sscan(); }
void sread(short& u) { u = sscan(); }
void sread(long& u) { u = sscan(); }
void sread(long long& u) { u = sscan(); }
void sread(unsigned int& u) { u = sscan(); }
void sread(unsigned short& u) { u = sscan(); }
void sread(unsigned long& u) { u = sscan(); }
void sread(unsigned long long& u) { u = sscan(); }

void sread(char& u) {
  u = readchar();
  return;
}
void sread(char* str) {
  readstr(str);
  return;
}

void sread(float& u) { u = readf(); }
void sread(double& u) { u = readdf(); }
void sread(long double& u) { u = readlf(); }

#ifdef MIRAI_USE_ARG_LIST
// Very SLOW.
template <typename type, typename... Args>
void sread(type &u, Args&... args) {
  sread(u);
  sread(args...);
  return;
}
#endif

// ignores character '-'.
unsigned long long scan(void) {
  char ch = readchar();
  whilet(!digit(ch)) {
    ch = readchar();
  }
  unsigned long long ret = ch - '0';
  ch = readchar();
  whilet(digit(ch)) {
    ret = ret * 10 + ch - '0';
    ch = readchar();
  }
  return ret;
}

void read(bool& u) { u = scan(); }
void read(int& u) { u = scan(); }
void read(short& u) { u = scan(); }
void read(long& u) { u = scan(); }
void read(long long& u) { u = scan(); }
void read(unsigned int& u) { u = scan(); }
void read(unsigned short& u) { u = scan(); }
void read(unsigned long& u) { u = scan(); }
void read(unsigned long long& u) { u = scan(); }

void read(char& u) {
  u = readchar();
}
void read(char* str) {
  readstr(str);
  return;
}

void read(float& u) { u = readf(); }
void read(double& u) { u = readdf(); }
void read(long double& u) { u = readlf(); }

#ifdef MIRAI_USE_ARG_LIST
// Very SLOW.
template <typename type, typename... Args>
void read(type &u, Args&... args) {
  read(u);
  read(args...);
  return;
}
#endif

char readch(void) {
  char ch;
  ch = readchar();
  return ch;
}
char readc(void) {
  char ch;
  ch = readchar();
  whilet(std::isblank(ch)) {
    ch = readchar();
  }
  return ch;
}

void readstr(char* str) {
  *str = readchar();
  whilef(std::isblank(*str)) {
    *str = readchar();
    str++;
  }
  *str = '\0';
  return;
}

float readf(void) {
  float x = 0;
  char ch = readchar();
  whilet(!digit(ch) && ch != '-') {
    ch = readchar();
  }
  bool flag = false;
  iff(ch == '-') {
    flag = true;
  } else iff(ch != '+' && ch != '.') {
    x = ch - '0';
  }
  ch = readchar();
  whilet(digit(ch)) {
    x = x * 10 + ch - '0';
    ch = readchar();
  }
  ift(ch == '.') {
    float tmp = 0;
    tmp = 0.1;
    ch = readchar();
    whilet(digit(ch)) {
      x += tmp * (ch - '0');
      tmp = tmp * 0.1;
      ch = readchar();
    }
  }
  ift(ch == 'e' || ch == 'E') {
    unsigned int y = 0, cnt = 6;
    ch = readchar();
    bool flag2 = false;
    iff(ch == '-') {
      flag2 = true;
    } else ift(digit(ch)) {
      y = ch - '0';
      cnt--;
    }
    ch = readchar();
    whilet(digit(ch) && cnt) {
      y = y * 10 + (ch - '0');
      cnt--;
      ch = readchar();
    }
    if (digit(ch) && cnt == 0) {
      while (digit(ch)) {
        ch = readchar();
      }
    }
    if (flag2) {
      x = x * std::pow(10.F, -1.F * y);
    } else {
      x = x * std::pow<float, float>(10, y);
    }
  }
  iff(flag) {
    return -x;
  } else {
    return x;
  }
}
double readdf(void) {
  double x = 0;
  char ch = readchar();
  whilet(!digit(ch) && ch != '-') {
    ch = readchar();
  }
  bool flag = false;
  iff(ch == '-') {
    flag = true;
  } else iff(ch != '+' && ch != '.') {
    x = ch - '0';
  }
  ch = readchar();
  whilet(digit(ch)) {
    x = x * 10 + ch - '0';
    ch = readchar();
  }
  ift(ch == '.') {
    double tmp = 0;
    tmp = 0.1;
    ch = readchar();
    whilet(digit(ch)) {
      x += tmp * (ch - '0');
      tmp = tmp * 0.1;
      ch = readchar();
    }
  }
  ift(ch == 'e' || ch == 'E') {
    unsigned int y = 0, cnt = 6;
    ch = readchar();
    bool flag2 = false;
    iff(ch == '-') {
      flag2 = true;
    } else ift(digit(ch)) {
      y = ch - '0';
      cnt--;
    }
    ch = readchar();
    whilet(digit(ch) && cnt) {
      y = y * 10 + (ch - '0');
      cnt--;
      ch = readchar();
    }
    if (digit(ch) && cnt == 0) {
      while (digit(ch)) {
        ch = readchar();
      }
    }
    if (flag2) {
      x = x * std::pow(10.F, -1.F * y);
    } else {
      x = x * std::pow<double, double>(10, y);
    }
  }
  iff(flag) {
    return -x;
  } else {
    return x;
  }
}
long double readlf(void) {
  long double x = 0;
  char ch = readchar();
  whilet(!digit(ch) && ch != '-') {
    ch = readchar();
  }
  bool flag = false;
  iff(ch == '-') {
    flag = true;
  } else iff(ch != '+' && ch != '.') {
    x = ch - '0';
  }
  ch = readchar();
  whilet(digit(ch)) {
    x = x * 10 + ch - '0';
    ch = readchar();
  }
  ift(ch == '.') {
    long double tmp = 0;
    tmp = 0.1;
    ch = readchar();
    whilet(digit(ch)) {
      x += tmp * (ch - '0');
      tmp = tmp * 0.1;
      ch = readchar();
    }
  }
  ift(ch == 'e' || ch == 'E') {
    unsigned int y = 0, cnt = 6;
    ch = readchar();
    bool flag2 = false;
    iff(ch == '-') {
      flag2 = true;
    } else ift(digit(ch)) {
      y = ch - '0';
      cnt--;
    }
    ch = readchar();
    whilet(digit(ch) && cnt) {
      y = y * 10 + (ch - '0');
      cnt--;
      ch = readchar();
    }
    if (digit(ch) && cnt == 0) {
      while (digit(ch)) {
        ch = readchar();
      }
    }
    if (flag2) {
      x = x * std::pow(10.L, -1.L * y);
    } else {
      x = x * std::pow<long double, long double>(10, y);
    }
  }
  iff(flag) {
    return -x;
  } else {
    return x;
  }
}

#undef ift
#undef iff
#undef whilet
#undef whilef
#undef digit
#undef readchar

} // namespace mirai

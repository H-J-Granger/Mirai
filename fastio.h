#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>

#define MIRAI_INPUT_BUFFER
#define MIRAI_INPUT_BUFFER_SIZE (1L << 16)
#define MIRAI_USE_ARG_LIST

#ifdef MIRAI_USE_READ_FUNC
#include <unistd.h>
#endif

namespace mirai {

void fflush_input(void);

long long sscan(void);
void sread(bool&);
void sread(int&);
void sread(short&);
void sread(long&);
void sread(long long&);
void sread(unsigned int&);
void sread(unsigned short&);
void sread(unsigned long&);
void sread(unsigned long long&);
void sread(char&);
void sread(char*);
void sread(float&);
void sread(double&);
void sread(long double&);
template <typename type> void sread(type&);
template <typename type, typename... Args> void sread(type&, Args&...);

unsigned long long scan(void);

void read(bool&);
void read(int&);
void read(short&);
void read(long&);
void read(long long&);
void read(unsigned int&);
void read(unsigned short&);
void read(unsigned long&);
void read(unsigned long long&);
void read(char&);
void read(char*);
void read(float&);
void read(double&);
void read(long double&);
template <typename type> void read(type&);
template <typename type, typename... Args> void read(type&, Args&...);
char readch(void);
char readc(void);
void readstr(char*);

float readf(void);
double readdf(void);
long double readlf(void);

} // namespace mirai

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <unistd.h>
#define MIRAI_INPUT_BUFFER
#define MIRAI_INPUT_BUFFER_SIZE (1L << 16)
#define MIRAI_USE_ARG_LIST
#define ll long long
#define u unsigned
namespace mirai { void fflush_input(); ll sscan(); void sread(bool&); void sread(int&); void sread(u&); 
void sread(short&); void sread(long&); void sread(ll&); void sread(u short&); void sread(u long&); void sread(u ll&); 
void sread(char&); void sread(char*); void sread(float&); void sread(double&); void sread(long double&); 
template <typename type> void sread(type&); template <typename type, typename... Args> void sread(type&, Args&...); 
u ll scan(); void read(bool&); void read(int&); void read(short&); void read(long&); void read(ll&); void read(u int&); 
void read(u short&); void read(u long&); void read(u ll&); void read(char&); void read(char*); void read(float&);
void read(double&); void read(long double&); template <typename type> void read(type&);
template <typename type, typename... Args> void read(type&, Args&...); char readch(); char readc(); void readstr(char*);
float readf(); double readdf(); long double readlf(); }
#undef u
#undef ll

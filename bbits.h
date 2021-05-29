
typedef  unsigned char u_char;
typedef  unsigned int u_int;
typedef  unsigned long long u_lol;
#if defined(__GNUC__)  // GCC, Clang, ICC
/*
inline int lsb(u_lol in) {
  return int(__builtin_ctzll(in));
}

inline int msb(u_lol in) {
  return int(63 ^ __builtin_clzll(in));
}*/
inline int popcnt( u_lol a )
{
	// http://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
	return __builtin_popcountll(a) ;

}

void _BitScanForward64(int *rv,u_lol in){
    *rv= __builtin_clzll(in);
    //std::cout << __builtin_clzll(in);
}
void _BitScanReverse64(int *rv,u_lol in){
    *rv= __builtin_ctzll(in);
}  //int idx;
//_BitScanForward64(&idx, in);
//return (int) idx;
inline int lsb(u_lol in) {

    return __builtin_ctzll(in);
}

inline int msb(u_lol in) {

 return 63^__builtin_clzll(in);
}

#elif defined(_MSC_VER)  // MSVC

#ifdef _WIN64  // MSVC, WIN64
#include <intrin.h>
int popcnt( u_lol a )
{
	// http://msdn.microsoft.com/en-us/library/bb385231(v=vs.100).aspx
	return __popcnt64(a) ;
}

inline int lsb(u_lol in) {
  unsigned long idx;
  _BitScanForward64(&idx, in);
  return (int) idx;
}

inline int msb(u_lol in) {

  unsigned long idx;
  _BitScanReverse64(&idx, in);
  return (int) idx;
}

#else  // MSVC, WIN32

inline int lsb(u_lol in) {
  unsigned long idx;
  if (in & 0xffffffff) {
	  _BitScanForward(&idx, int32_t(in));
	  return int(idx);
  } else {
	  _BitScanForward(&idx, int32_t(in >> 32));
	  return int(idx + 32);
  }
}

inline int msb(u_lol in) {
  unsigned long idx;
  if (in >> 32) {
	  _BitScanReverse(&idx, int32_t(in >> 32));
	  return int(idx + 32);
  } else {
	  _BitScanReverse(&idx, int32_t(b));
	  return int(idx);
  }
}

#endif

#endif

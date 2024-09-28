#include <assert.h>
#include <stdint.h>

#if !defined(USE_LITTLE_ENDIAN) && !defined(USE_BIG_ENDIAN)

#  if defined(__avr32__) || defined(__hppa__) || defined(__m68k__) ||          \
    defined(__mips__) || defined(__powerpc__) || defined(__s390__) ||          \
    defined(__s390x__) || defined(__sparc__)

#    define USE_BIG_ENDIAN

#  endif

#endif

int main()
{
  uint16_t x[2];
  x[0] = 1;
  x[1] = 2;
  uint8_t *y = (uint8_t *)x;
  uint16_t z = *((uint16_t *)(y + 1));

#ifdef USE_BIG_ENDIAN
  assert(z == 256u);
#else
  assert(z == 512u);
#endif
}

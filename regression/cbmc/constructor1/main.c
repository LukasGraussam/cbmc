#include <assert.h>

#ifdef __GNUC__
int x, y, z;

// forward declaration with and without attribute is ok
static __attribute__((constructor)) void format_init(void);
static void other_init(void);
static __attribute__((constructor)) void more_init(void);

static __attribute__((constructor))
void format_init(void)
{
  x=42;
  return;
}

static __attribute__((constructor)) void other_init(void)
{
  y = 42;
}

static void more_init(void)
{
  z = 42;
}
#endif

int main()
{
#ifdef __GNUC__
  assert(x==42);
  assert(y == 42);
  assert(z == 42);
#endif
  return 0;
}

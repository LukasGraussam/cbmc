#include <assert.h>
#include <stddef.h>

int main()
{
  int n;
  __CPROVER_assume(5 <= n && n < 10);
  int *c = alloca(n * sizeof(int));
  assert(c);
  return 0;
}

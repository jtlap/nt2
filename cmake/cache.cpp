#include <unistd.h>

int gcd(int a, int b )
{
  if(b == 0) return a; else return gcd(b, a%b);
}

int lcm(int a, int b )
{
  if(b ==0) return 0;
  return (a*b)/gcd(a,b);
}

int main()
{
  int L1,L2,L3,value,cache;

  value = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
  L1 = value ? value : 1;

  value = sysconf(_SC_LEVEL2_CACHE_LINESIZE);
  L2 = value ? value : 1;

  value = sysconf(_SC_LEVEL3_CACHE_LINESIZE);
  L3 = value ? value : 1;
  
  cache = lcm( L3, lcm(L2,L1) );
  return (cache>1 ? cache : 16);
}


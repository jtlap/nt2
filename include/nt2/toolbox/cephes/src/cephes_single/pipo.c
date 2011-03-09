#include<stdio.h>
extern float cephes_chbevlf(float,float*,int);

#ifdef ANSIC
float ephes_chbevlf( float x, const float *array, int n )
#else
float ephes_chbevlf( x, array, n )
float x;
float *array;
int n;
#endif
{
  float b0, b1, b2;
  const float *p;
  int i;
  p = array;
  b0 = *p++;
  b1 = 0.0f;
  i = n - 1;
  
  do
    {
      b2 = b1;
      b1 = b0;
      b0 = x * b1  -  b2  + *p++;
    }
  while( --i );
 
  return( 0.5f*(b0-b2) );
}

int main()
{
  float a[] = {1,2,3};
  float z =ephes_chbevlf(1.0f,&a[0],3);
  printf("%f\n", z);
  float z1 =cephes_chbevlf(1.0f,&a[0],3);
  printf("%f\n", z1);
  return 0;
}

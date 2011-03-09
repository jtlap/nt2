/*#define ANSIC*/

#ifdef ANSIC
float cephes_chbevlf( float x, float *array, int n )
#else
float cephes_chbevlf( x, array, n )
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

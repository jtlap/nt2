int drand();
double cephes_exp(), cephes_frexp(), cephes_ldexp();
volatile double x, y, z;

main()
{
int i, e;

for( i=0; i<100000; i++ )
  {
    drand(&x);
    x = cephes_exp( 10.0*(x - 1.5) );
    y = cephes_frexp( x, &e );
    z = cephes_ldexp( y, e );
    if( z != x )
      abort();
  }
}

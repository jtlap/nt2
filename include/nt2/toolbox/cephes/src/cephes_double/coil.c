/* Program to calculate the inductance of a coil
 *
 * Reference: E. Jahnke and F. Emde, _Tables of Functions_,
 * 4th edition, Dover, 1945, pp 86-89.
 */

double cephes_sin(), cephes_cos(), cephes_atan(), cephes_ellpe(), cephes_ellpk();

double d;
double l;
double N;

/* double PI = 3.14159265358979323846; */
extern double PI;

main()
{
double a, f, tana, sina, K, E, m, L, t;

printf( "Self inductance of circular solenoidal coil\n" );

loop:
getnum( "diameter in centimeters", &d );
if( d < 0.0 )
	exit(0);  /* escape gracefully */
getnum( "length in centimeters", &l );
if( d < 0.0 )
	exit(0);
getnum( "total number of turns", &N );
if( d < 0.0 )
	exit(0);
tana = d/l;        /* form factor */
a = cephes_atan( tana );
sina = cephes_sin(a);     /* modulus of the elliptic functions (k) */
m = cephes_cos(a);        /* subroutine argument = 1 - k^2 */
m = m * m;
K = cephes_ellpk(m);
E = cephes_ellpe(m);
tana = tana * tana;  /* square of cephes_tan(a) */

f = ((K + (tana - 1.0) * E)/sina  -  tana)/3.0;
L = 4.e-9 * PI * N * N * d * f;
printf( "L = %.4e Henries\n", L );
goto loop;
}


/* Get value entered on keyboard
 */
getnum( str, pd )
char *str;
double *pd;
{
char s[40];

printf( "%s (%.10e) ? ", str, *pd );
gets(s);
if( s[0] != '\0' )
	{
	sscanf( s, "%lf", pd );
	printf( "%.10e\n", *pd );
	}
}

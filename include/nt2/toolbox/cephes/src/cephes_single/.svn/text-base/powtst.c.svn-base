#include <stdio.h>
#include "mconf.h"
extern float MAXNUMF, MAXLOGF, MINLOGF;

int
main()
{
float exp1, minnum, x, y, z, e;
exp1 = cephes_expf(1.0F);

minnum = cephes_powif(2.0F,-149);

x = exp1;
y = MINLOGF + cephes_logf(0.501);
/*y = MINLOGF - 0.405;*/
z = cephes_powf(x,y);
e = (z - minnum) / minnum;
printf("%.16e %.16e\n", z, e);

x = exp1;
y = MAXLOGF;
z = cephes_powf(x,y);
e = (z - MAXNUMF) / MAXNUMF;
printf("%.16e %.16e\n", z, e);

x = MAXNUMF;
y = 1.0F/MAXLOGF;
z = cephes_powf(x,y);
e = (z - exp1) / exp1;
printf("%.16e %.16e\n", z, e);


x = exp1;
y = MINLOGF;
z = cephes_powf(x,y);
e = (z - minnum) / minnum;
printf("%.16e %.16e\n", z, e);


exit(0);
}

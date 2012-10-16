#include "mconf.h"

extern double cephes_acos ( double x );
extern long double cephes_acosl ( long double x )
{
    return cephes_acos(x);
}

extern double cephes_acosh ( double xx );
extern long double cephes_acoshl ( long double xx )
{
    return cephes_acosh(xx);
}

extern int cephes_airy ( double xx, double *ai, double *aip, double *bi, double *bip );
extern int cephes_airyl ( long double xx, long double *ai, long double *aip, long double *bi, long double *bip )
{
    return cephes_airy(xx, (double*)ai, (double*)aip, (double*)bi, (double*)bip);
}

extern double cephes_asin ( double xx );
extern long double cephes_asinl ( long double xx )
{
    return cephes_asin(xx);
}

extern double cephes_asinh ( double xx );
extern long double cephes_asinhl ( long double xx )
{
    return cephes_asinh(xx);
}

extern double cephes_atan2 ( double y, double x );
extern long double cephes_atan2l ( long double y, long double x )
{
    return cephes_atan2(y, x);
}

extern double cephes_atan ( double xx );
extern long double cephes_atanl ( long double xx )
{
    return cephes_atan(xx);
}

extern double cephes_atanh ( double xx );
extern long double cephes_atanhl ( long double xx )
{
    return cephes_atanh(xx);
}

extern double cephes_bdtrc ( int k, int n, double pp );
extern long double cephes_bdtrcl ( int k, int n, long double pp )
{
    return cephes_bdtrc(k, n, pp);
}

extern double cephes_bdtr ( int k, int n, double pp );
extern long double cephes_bdtrl ( int k, int n, long double pp )
{
    return cephes_bdtr(k, n, pp);
}

extern double cephes_bdtri ( int k, int n, double yy );
extern long double cephes_bdtril ( int k, int n, long double yy )
{
    return cephes_bdtri(k, n, yy);
}

extern double cephes_beta ( double aa, double bb );
extern long double cephes_betal ( long double aa, long double bb )
{
    return cephes_beta(aa, bb);
}

extern double cephes_cabs ( cmplx *z );
extern long double cephes_cabsl ( cmplxl *z )
{
    return cephes_cabs((cmplx*)z);
}

extern void cephes_cacos ( cmplx *z, cmplx *w );
extern void cephes_cacosl ( cmplxl *z, cmplxl *w )
{
    cephes_cacos((cmplx*)z, (cmplx*)w);
}

extern void cephes_cadd ( cmplx *a, cmplx *b, cmplx *c );
extern void cephes_caddl ( cmplxl *a, cmplxl *b, cmplxl *c )
{
    cephes_cadd((cmplx*)a, (cmplx*)b, (cmplx*)c);
}

extern void cephes_casin ( cmplx *z, cmplx *w );
extern void cephes_casinl ( cmplxl *z, cmplxl *w )
{
    cephes_casin((cmplx*)z, (cmplx*)w);
}

extern void cephes_catan ( cmplx *z, cmplx *w );
extern void cephes_catanl ( cmplxl *z, cmplxl *w )
{
    cephes_catan((cmplx*)z, (cmplx*)w);
}

extern double cephes_cbrt ( double xx );
extern long double cephes_cbrtl ( long double xx )
{
    return cephes_cbrt(xx);
}

extern void cephes_cchsh ( double xx, double *c, double *s );
extern void cephes_cchshl ( long double xx, long double *c, long double *s )
{
    cephes_cchsh(xx, (double*)c, (double*)s);
}

extern void cephes_ccos ( cmplx *z, cmplx *w );
extern void cephes_ccosl ( cmplxl *z, cmplxl *w )
{
    cephes_ccos((cmplx*)z, (cmplx*)w);
}

extern void cephes_ccot ( cmplx *z, cmplx *w );
extern void cephes_ccotl ( cmplxl *z, cmplxl *w )
{
    cephes_ccot((cmplx*)z, (cmplx*)w);
}

extern void cephes_cdiv ( cmplx *a, cmplx *b, cmplx *c );
extern void cephes_cdivl ( cmplxl *a, cmplxl *b, cmplxl *c )
{
    cephes_cdiv((cmplx*)a, (cmplx*)b, (cmplx*)c);
}

extern double cephes_ceil ( double x );
extern long double cephes_ceill ( long double x )
{
    return cephes_ceil(x);
}

extern void cephes_cexp ( cmplx *z, cmplx *w );
extern void cephes_cexpl ( cmplxl *z, cmplxl *w )
{
    cephes_cexp((cmplx*)z, (cmplx*)w);
}

extern double cephes_chbevl ( double x, double *array, int n );
extern long double cephes_chbevll ( long double x, long double *array, int n )
{
    return cephes_chbevl(x, (double*)array, n);
}

extern double cephes_chdtrc ( double dff, double xx );
extern long double cephes_chdtrcl ( long double dff, long double xx )
{
    return cephes_chdtrc(dff, xx);
}

extern double cephes_chdtr ( double dff, double xx );
extern long double cephes_chdtrl ( long double dff, long double xx )
{
    return cephes_chdtr(dff, xx);
}

extern double cephes_chdtri ( double dff, double yy );
extern long double cephes_chdtril ( long double dff, long double yy )
{
    return cephes_chdtri(dff, yy);
}

extern void cephes_clog ( cmplx *z, cmplx *w );
extern void cephes_clogl ( cmplxl *z, cmplxl *w )
{
    cephes_clog((cmplx*)z, (cmplx*)w);
}

extern void cephes_cmov ( short *a, short *b );
extern void cephes_cmovl ( short *a, short *b )
{
    cephes_cmov(a, b);
}

extern void cephes_cmul ( cmplx *a, cmplx *b, cmplx *c );
extern void cephes_cmull ( cmplxl *a, cmplxl *b, cmplxl *c )
{
    cephes_cmul((cmplx*)a, (cmplx*)b, (cmplx*)c);
}

extern void cephes_cneg ( cmplx *a );
extern void cephes_cnegl ( cmplxl *a )
{
    cephes_cneg((cmplx*)a);
}

extern double cephes_cosdg ( double xx );
extern long double cephes_cosdgl ( long double xx )
{
    return cephes_cosdg(xx);
}

extern double cephes_cos ( double xx );
extern long double cephes_cosl ( long double xx )
{
    return cephes_cos(xx);
}

extern double cephes_cosh ( double xx );
extern long double cephes_coshl ( long double xx )
{
    return cephes_cosh(xx);
}

extern double cephes_cotdg ( double x );
extern long double cephes_cotdgl ( long double x )
{
    return cephes_cotdg(x);
}

extern double cephes_cot ( double x );
extern long double cephes_cotl ( long double x )
{
    return cephes_cot(x);
}

extern void cephes_csin ( cmplx *z, cmplx *w );
extern void cephes_csinl ( cmplxl *z, cmplxl *w )
{
    cephes_csin((cmplx*)z, (cmplx*)w);
}

extern void cephes_csqrt ( cmplx *z, cmplx *w );
extern void cephes_csqrtl ( cmplxl *z, cmplxl *w )
{
    cephes_csqrt((cmplx*)z, (cmplx*)w);
}

extern void cephes_csub ( cmplx *a, cmplx *b, cmplx *c );
extern void cephes_csubl ( cmplxl *a, cmplxl *b, cmplxl *c )
{
    cephes_csub((cmplx*)a, (cmplx*)b, (cmplx*)c);
}

extern void cephes_ctan ( cmplx *z, cmplx *w );
extern void cephes_ctanl ( cmplxl *z, cmplxl *w )
{
    cephes_ctan((cmplx*)z, (cmplx*)w);
}

extern double cephes_ctans ( cmplx *z );
extern long double cephes_ctansl ( cmplxl *z )
{
    return cephes_ctans((cmplx*)z);
}

extern double cephes_dawsn ( double xxx );
extern long double cephes_dawsnl ( long double xxx )
{
    return cephes_dawsn(xxx);
}

extern int cephes_dprec ( void );
extern int cephes_dprecl ( void )
{
    return cephes_dprec();
}

extern double cephes_ellie ( double phia, double ma );
extern long double cephes_elliel ( long double phia, long double ma )
{
    return cephes_ellie(phia, ma);
}

extern double cephes_ellik ( double phia, double ma );
extern long double cephes_ellikl ( long double phia, long double ma )
{
    return cephes_ellik(phia, ma);
}

extern double cephes_ellpe ( double xx );
extern long double cephes_ellpel ( long double xx )
{
    return cephes_ellpe(xx);
}

extern int cephes_ellpj ( double uu, double mm, double *sn, double *cn, double *dn, double *ph );
extern int cephes_ellpjl ( long double uu, long double mm, long double *sn, long double *cn, long double *dn, long double *ph )
{
    return cephes_ellpj(uu, mm, (double*)sn, (double*)cn, (double*)dn, (double*)ph);
}

extern double cephes_ellpk ( double xx );
extern long double cephes_ellpkl ( long double xx )
{
    return cephes_ellpk(xx);
}

extern double cephes_erfc ( double aa );
extern long double cephes_erfcl ( long double aa )
{
    return cephes_erfc(aa);
}

extern double cephes_erf ( double xx );
extern long double cephes_erfl ( long double xx )
{
    return cephes_erf(xx);
}

extern double cephes_exp10 ( double xx );
extern long double cephes_exp10l ( long double xx )
{
    return cephes_exp10(xx);
}

extern double cephes_exp2 ( double xx );
extern long double cephes_exp2l ( long double xx )
{
    return cephes_exp2(xx);
}

extern double cephes_exp ( double xx );
extern long double cephes_expl ( long double xx )
{
    return cephes_exp(xx);
}

extern double cephes_expn ( int n, double xx );
extern long double cephes_expnl ( int n, long double xx )
{
    return cephes_expn(n, xx);
}

extern double cephes_fac ( int i );
extern long double cephes_facl ( int i )
{
    return cephes_fac(i);
}

extern double cephes_fdtrc ( int ia, int ib, double xx );
extern long double cephes_fdtrcl ( int ia, int ib, long double xx )
{
    return cephes_fdtrc(ia, ib, xx);
}

extern double cephes_fdtr ( int ia, int ib, int xx );
extern long double cephes_fdtrl ( int ia, int ib, int xx )
{
    return cephes_fdtr(ia, ib, xx);
}

extern double cephes_fdtri ( int ia, int ib, double yy );
extern long double cephes_fdtril ( int ia, int ib, long double yy )
{
    return cephes_fdtri(ia, ib, yy);
}

extern double cephes_floor ( double x );
extern long double cephes_floorl ( long double x )
{
    return cephes_floor(x);
}

extern void cephes_fresnl ( double xxa, double *ssa, double *cca );
extern void cephes_fresnll ( long double xxa, long double *ssa, long double *cca )
{
    cephes_fresnl(xxa, (double*)ssa, (double*)cca);
}

extern double cephes_frexp ( double x, int *pw2 );
extern long double cephes_frexpl ( long double x, int *pw2 )
{
    return cephes_frexp(x, pw2);
}

extern double cephes_gamma ( double xx );
extern long double cephes_gammal ( long double xx )
{
    return cephes_gamma(xx);
}

extern double cephes_gdtrc ( double aa, double bb, double xx );
extern long double cephes_gdtrcl ( long double aa, long double bb, long double xx )
{
    return cephes_gdtrc(aa, bb, xx);
}

extern double cephes_gdtr ( double aa, double bb, double xx );
extern long double cephes_gdtrl ( long double aa, long double bb, long double xx )
{
    return cephes_gdtr(aa, bb, xx);
}

extern double cephes_hyp2f0 ( double aa, double bb, double xx, int type, double *err );
extern long double cephes_hyp2f0l ( long double aa, long double bb, long double xx, int type, long double *err )
{
    return cephes_hyp2f0(aa, bb, xx, type, (double*)err);
}

extern double cephes_hyp2f1 ( double aa, double bb, double cc, double xx );
extern long double cephes_hyp2f1l ( long double aa, long double bb, long double cc, long double xx )
{
    return cephes_hyp2f1(aa, bb, cc, xx);
}

extern double cephes_hyperg ( double aa, double bb, double xx );
extern long double cephes_hypergl ( long double aa, long double bb, long double xx )
{
    return cephes_hyperg(aa, bb, xx);
}

extern double cephes_i0e ( double x );
extern long double cephes_i0el ( long double x )
{
    return cephes_i0e(x);
}

extern double cephes_i0 ( double x );
extern long double cephes_i0l ( long double x )
{
    return cephes_i0(x);
}

extern double cephes_i1e ( double xx );
extern long double cephes_i1el ( long double xx )
{
    return cephes_i1e(xx);
}

extern double cephes_i1 ( double xx );
extern long double cephes_i1l ( long double xx )
{
    return cephes_i1(xx);
}

extern double cephes_igamc ( double aa, double xx );
extern long double cephes_igamcl ( long double aa, long double xx )
{
    return cephes_igamc(aa, xx);
}

extern double cephes_igam ( double aa, double xx );
extern long double cephes_igaml ( long double aa, long double xx )
{
    return cephes_igam(aa, xx);
}

extern double cephes_igami ( double aa, double yy0 );
extern long double cephes_igamil ( long double aa, long double yy0 )
{
    return cephes_igami(aa, yy0);
}

extern double cephes_incbet ( double aaa, double bbb, double xxx );
extern long double cephes_incbetl ( long double aaa, long double bbb, long double xxx )
{
    return cephes_incbet(aaa, bbb, xxx);
}

extern double cephes_incbi ( double aaa, double bbb, double yyy0 );
extern long double cephes_incbil ( long double aaa, long double bbb, long double yyy0 )
{
    return cephes_incbi(aaa, bbb, yyy0);
}

extern double cephes_iv ( double v, double x );
extern long double cephes_ivl ( long double v, long double x )
{
    return cephes_iv(v, x);
}

extern double cephes_j0 ( double xx );
extern long double cephes_j0l ( long double xx )
{
    return cephes_j0(xx);
}

extern double cephes_j1 ( double xx );
extern long double cephes_j1l ( long double xx )
{
    return cephes_j1(xx);
}

extern double cephes_jn ( int n, double xx );
extern long double cephes_jnl ( int n, long double xx )
{
    return cephes_jn(n, xx);
}

extern double cephes_jv ( double nn, double xx );
extern long double cephes_jvl ( long double nn, long double xx )
{
    return cephes_jv(nn, xx);
}

extern double cephes_k0e ( double xx );
extern long double cephes_k0el ( long double xx )
{
    return cephes_k0e(xx);
}

extern double cephes_k0 ( double xx );
extern long double cephes_k0l ( long double xx )
{
    return cephes_k0(xx);
}

extern double cephes_k1e ( double xx );
extern long double cephes_k1el ( long double xx )
{
    return cephes_k1e(xx);
}

extern double cephes_k1 ( double xx );
extern long double cephes_k1l ( long double xx )
{
    return cephes_k1(xx);
}

extern double cephes_kn ( int nnn, double xx );
extern long double cephes_knl ( int nnn, long double xx )
{
    return cephes_kn(nnn, xx);
}

extern double cephes_ldexp ( double x, int pw2 );
extern long double cephes_ldexpl ( long double x, int pw2 )
{
    return cephes_ldexp(x, pw2);
}

extern int cephes_ldprec ( void );
extern int cephes_ldprecl ( void )
{
    return cephes_ldprec();
}

extern double cephes_lgam ( double xx );
extern long double cephes_lgaml ( long double xx )
{
    return cephes_lgam(xx);
}

extern double cephes_log10 ( double xx );
extern long double cephes_log10l ( long double xx )
{
    return cephes_log10(xx);
}

extern double cephes_log2 ( double xx );
extern long double cephes_log2l ( long double xx )
{
    return cephes_log2(xx);
}

extern double cephes_log ( double xx );
extern long double cephes_logl ( long double xx )
{
    return cephes_log(xx);
}

extern int cephes_mtherr ( char *name, int code );
extern int cephes_mtherrl ( char *name, int code )
{
    return cephes_mtherr(name, code);
}

extern double cephes_nbdtrc ( int k, int n, double pp );
extern long double cephes_nbdtrcl ( int k, int n, long double pp )
{
    return cephes_nbdtrc(k, n, pp);
}

extern double cephes_nbdtr ( int k, int n, double pp );
extern long double cephes_nbdtrl ( int k, int n, long double pp )
{
    return cephes_nbdtr(k, n, pp);
}

extern double cephes_ndtr ( double aa );
extern long double cephes_ndtrl ( long double aa )
{
    return cephes_ndtr(aa);
}

extern double cephes_ndtri ( double yy0 );
extern long double cephes_ndtril ( long double yy0 )
{
    return cephes_ndtri(yy0);
}

extern double cephes_onef2 ( double aa, double bb, double cc, double xx, double *err );
extern long double cephes_onef2l ( long double aa, long double bb, long double cc, long double xx, long double *err )
{
    return cephes_onef2(aa, bb, cc, xx, (double*)err);
}

extern double cephes_p1evl ( double xx, double *coef, int N );
extern long double cephes_p1evll ( long double xx, long double *coef, int N )
{
    return cephes_p1evl(xx, (double*)coef, N);
}

extern double cephes_pdtrc ( int k, double mm );
extern long double cephes_pdtrcl ( int k, long double mm )
{
    return cephes_pdtrc(k, mm);
}

extern double cephes_pdtr ( int k, double mm );
extern long double cephes_pdtrl ( int k, long double mm )
{
    return cephes_pdtr(k, mm);
}

extern double cephes_pdtri ( int k, double yy );
extern long double cephes_pdtril ( int k, long double yy )
{
    return cephes_pdtri(k, yy);
}

extern void cephes_poladd ( double a[], int na, double b[], int nb, double c[] );
extern void cephes_poladdl ( long double a[], int na, long double b[], int nb, long double c[] )
{
    cephes_poladd((double*)a, na, (double*)b, nb, (double*)c);
}

extern void cephes_polclr ( double *a, int n );
extern void cephes_polclrl ( long double *a, int n )
{
    cephes_polclr((double*)a, n);
}

extern int cephes_poldiv ( double a[], int na, double b[], int nb, double c[] );
extern int cephes_poldivl ( long double a[], int na, long double b[], int nb, long double c[] )
{
    return cephes_poldiv((double*)a, na, (double*)b, nb, (double*)c);
}

extern double cephes_poleva ( double *a, int na, double xx );
extern long double cephes_poleval ( long double *a, int na, long double xx )
{
    return cephes_poleva((double*)a, na, xx);
}

extern double cephes_polevl ( double xx, double *coef, int N );
extern long double cephes_polevll ( long double xx, long double *coef, int N )
{
    return cephes_polevl(xx, (double*)coef, N);
}

extern void cephes_polini ( int maxdeg );
extern void cephes_polinil ( int maxdeg )
{
    cephes_polini(maxdeg);
}

extern void cephes_polmov ( double *a, int na, double *b );
extern void cephes_polmovl ( long double *a, int na, long double *b )
{
    cephes_polmov((double*)a, na, (double*)b);
}

extern void cephes_polmul ( double a[], int na, double b[], int nb, double c[] );
extern void cephes_polmull ( long double a[], int na, long double b[], int nb, long double c[] )
{
    cephes_polmul((double*)a, na, (double*)b, nb, (double*)c);
}

extern void cephes_polprt ( double *a, int na, int d );
extern void cephes_polprtl ( long double *a, int na, int d )
{
    cephes_polprt((double*)a, na, d);
}

extern void cephes_polsbt ( double a[], int na, double b[], int nb, double c[] );
extern void cephes_polsbtl ( long double a[], int na, long double b[], int nb, long double c[] )
{
    cephes_polsbt((double*)a, na, (double*)b, nb, (double*)c);
}

extern void cephes_polsub ( double a[], int na, double b[], int nb, double c[] );
extern void cephes_polsubl ( long double a[], int na, long double b[], int nb, long double c[] )
{
    cephes_polsub((double*)a, na, (double*)b, nb, (double*)c);
}

extern double cephes_pow ( double x, double y );
extern long double cephes_powl ( long double x, long double y )
{
    return cephes_pow(x, y);
}

extern double cephes_powi ( double x, int nn );
extern long double cephes_powil ( long double x, int nn )
{
    return cephes_powi(x, nn);
}

extern double cephes_psi ( double xx );
extern long double cephes_psil ( long double xx )
{
    return cephes_psi(xx);
}

extern double cephes_redupi ( double xx );
extern long double cephes_redupil ( long double xx )
{
    return cephes_redupi(xx);
}

extern double cephes_rgamma ( double xx );
extern long double cephes_rgammal ( long double xx )
{
    return cephes_rgamma(xx);
}

extern int cephes_shichi ( double xx, double *si, double *ci );
extern int cephes_shichil ( long double xx, long double *si, long double *ci )
{
    return cephes_shichi(xx, (double*)si, (double*)ci);
}

extern int cephes_sici ( double xx, double *si, double *ci );
extern int cephes_sicil ( long double xx, long double *si, long double *ci )
{
    return cephes_sici(xx, (double*)si, (double*)ci);
}

extern double cephes_sindg ( double xx );
extern long double cephes_sindgl ( long double xx )
{
    return cephes_sindg(xx);
}

extern double cephes_sin ( double xx );
extern long double cephes_sinl ( long double xx )
{
    return cephes_sin(xx);
}

extern double cephes_sinh ( double xx );
extern long double cephes_sinhl ( long double xx )
{
    return cephes_sinh(xx);
}

extern double cephes_spence ( double xx );
extern long double cephes_spencel ( long double xx )
{
    return cephes_spence(xx);
}

extern int cephes_sprec ( void );
extern int cephes_sprecl ( void )
{
    return cephes_sprec();
}

extern double cephes_sqrt ( double xx );
extern long double cephes_sqrtl ( long double xx )
{
    return cephes_sqrt(xx);
}

extern double cephes_stdtr ( int k, double tt );
extern long double cephes_stdtrl ( int k, long double tt )
{
    return cephes_stdtr(k, tt);
}

extern double cephes_struve ( double vv, double xx );
extern long double cephes_struvel ( long double vv, long double xx )
{
    return cephes_struve(vv, xx);
}

extern double cephes_tandg ( double x );
extern long double cephes_tandgl ( long double x )
{
    return cephes_tandg(x);
}

extern double cephes_tan ( double x );
extern long double cephes_tanl ( long double x )
{
    return cephes_tan(x);
}

extern double cephes_tanh ( double xx );
extern long double cephes_tanhl ( long double xx )
{
    return cephes_tanh(xx);
}

extern double cephes_threef0 ( double aa, double bb, double cc, double xx, double *err );
extern long double cephes_threef0l ( long double aa, long double bb, long double cc, long double xx, long double *err )
{
    return cephes_threef0(aa, bb, cc, xx, (double*)err);
}

extern double cephes_y0 ( double xx );
extern long double cephes_y0l ( long double xx )
{
    return cephes_y0(xx);
}

extern double cephes_y1 ( double xx );
extern long double cephes_y1l ( long double xx )
{
    return cephes_y1(xx);
}

extern double cephes_yn ( int nn, double xx );
extern long double cephes_ynl ( int nn, long double xx )
{
    return cephes_yn(nn, xx);
}

extern double cephes_yv ( double vv, double xx );
extern long double cephes_yvl ( long double vv, long double xx )
{
    return cephes_yv(vv, xx);
}

extern double cephes_zetac ( double xx );
extern long double cephes_zetacl ( long double xx )
{
    return cephes_zetac(xx);
}

extern double cephes_zeta ( double xx, double qq );
extern long double cephes_zetal ( long double xx, long double qq )
{
    return cephes_zeta(xx, qq);
}

extern double cephes_expm1 ( double xx );
extern long double cephes_expm1l ( long double xx )
{
    return cephes_expm1(xx);
}

extern double cephes_cosm1 ( double xx );
extern long double cephes_cosm1l ( long double xx )
{
    return cephes_cosm1(xx);
}

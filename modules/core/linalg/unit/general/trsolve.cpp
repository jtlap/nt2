#include <nt2/include/functions/trsm.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/trsolve.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/table.hpp>
#include <nt2/include/functions/lu.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(trsm, NT2_REAL_TYPES )
{
  using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_t p,y(b);

nt2::table<T, nt2::upper_triangular_> u ;
nt2::table<T, nt2::lower_triangular_> l ;

nt2::tie(l,u,p) = nt2::lu(a);

y = nt2::trsolve(l,y);
y = nt2::trsolve(u,y);

NT2_TEST_EQUAL( y, x);
}


NT2_TEST_CASE_TPL(trsm_sne, NT2_REAL_TYPES )
{
  using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);
nt2_la_int na = nt2::width(a);

t_t y = nt2::mtimes(nt2::trans(a),b);

nt2::table<T,nt2::upper_triangular_ > r = nt2::qr(a,nt2::no_pivot_);
r= nt2::triu( r( _(1,na), _ ) );

y = nt2::trsolve(nt2::trans(r),y);
y = nt2::trsolve(r,y);

NT2_TEST_ULP_EQUAL( y, x,T(100));
}


NT2_TEST_CASE_TPL(trsm_swap, NT2_REAL_TYPES )
{
  using nt2::_;


typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_t p,y(b);
t_t temp;

nt2::table<T, nt2::upper_triangular_> u ;
nt2::table<T, nt2::lower_triangular_> l ;

nt2::tie(l,u,p) = nt2::lu(a);

temp = nt2::trsolve(l,y);
y = nt2::trsolve(u,temp);

NT2_TEST_EQUAL( y, x);
}

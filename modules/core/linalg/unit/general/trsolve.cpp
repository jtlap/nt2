#include <nt2/include/functions/trsm.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/trsolve.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/table.hpp>
#include <nt2/include/functions/lu.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(trsm_noshape, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_t p,y(b);

nt2::table<T> u ;
nt2::table<T> l ;

nt2::tie(l,u,p) = nt2::lu(a);

y = nt2::trsolve(l,y,'L');
y = nt2::trsolve(u,y,'U');

NT2_TEST_EQUAL( y, x);
}

NT2_TEST_CASE_TPL(trsm_noshape_complex, NT2_REAL_TYPES )
{
using nt2::_;

typedef std::complex<T>          cT;
typedef nt2::table<cT>            t_t;

t_t a = nt2::cons<cT>(nt2::of_size(3,3),cT(2,0),cT(1,0),cT(1,0),cT(1,0),cT(1,0),cT(1,0)
                                       ,cT(1,0),cT(1,0),cT(2,0));
t_t b = nt2::cons<cT>(nt2::of_size(3,1),cT(1,0),cT(2,0),cT(5,0));
t_t x = nt2::cons<cT>(nt2::of_size(3,1),cT(-1,0),cT(0,0),cT(3,0));

t_t p,y(b);

nt2::table<cT> u ;
nt2::table<cT> l ;

nt2::tie(l,u,p) = nt2::lu(a);

y = nt2::trsolve(l,y,'L');
y = nt2::trsolve(u,y,'U');

NT2_TEST_EQUAL( y, x);
}

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

NT2_TEST_CASE_TPL(trsm_transpose, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);
nt2_la_int na = nt2::width(a);

t_t y = nt2::mtimes(nt2::trans(a),b);

nt2::table<T,nt2::upper_triangular_ > r = nt2::qr(a);
r= nt2::triu( r( _(1,na), _ ) );

y = nt2::trsolve(nt2::trans(r),y);
y = nt2::trsolve(r,y);

NT2_TEST_ULP_EQUAL( y, x,T(100));
}


NT2_TEST_CASE_TPL(trsm_noalias, NT2_REAL_TYPES )
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


NT2_TEST_CASE_TPL(trsm_racces, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_t p,y(b);
t_t temp(nt2::of_size(15,1));

nt2::table<T, nt2::upper_triangular_> u ;
nt2::table<T, nt2::lower_triangular_> l ;

nt2::tie(l,u,p) = nt2::lu(a);

temp(_(3,5)) = nt2::trsolve(l,y);
temp(_(6,8)) = nt2::trsolve(u,temp(_(3,5)));

NT2_TEST_EQUAL( temp(_(6,8)), x);
}

NT2_TEST_CASE_TPL(trsm_racces1, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_t p,y(b);
t_t temp(nt2::of_size(15,1));

nt2::table<T, nt2::upper_triangular_> u ;
nt2::table<T, nt2::lower_triangular_> l ;

nt2::tie(l,u,p) = nt2::lu(a);

temp(_(6,8)) = nt2::trsolve(l,y);
temp(_(3,5)) = nt2::trsolve(u,temp(_(6,8)));

NT2_TEST_EQUAL( temp(_(3,5)), x);
}

template<class Expr>
void test_is_terminal_shared(Expr const&)
{
  std::cout << "is_terminal: " << (Expr::proto_arity_c == 0) << std::endl;
  std::cout << "is_terminal_shared: " << nt2::meta::is_terminal_shared<Expr const&>::value << std::endl;
}

NT2_TEST_CASE_TPL(trsm_racces2, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_t p,y(b);
t_t temp(nt2::of_size(15,1));

nt2::table<T, nt2::upper_triangular_> u ;
nt2::table<T, nt2::lower_triangular_> l ;

nt2::tie(l,u,p) = nt2::lu(a);

temp(_(9,11)) = nt2::trsolve(l,y);
temp(_(6,8)) = nt2::trsolve(u,temp(_(9,11)));

test_is_terminal_shared(nt2::trsolve(l, y).proto_base().child1);
test_is_terminal_shared(nt2::trsolve(u, nt2::trsolve(l, y)).proto_base().child1);

NT2_TEST_EQUAL( temp(_(6,8)), x);
}


NT2_TEST_CASE_TPL(trsm_swap1, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-2.5,-1,8);

t_t p,y(b);
t_t temp;

nt2::table<T, nt2::upper_triangular_> u ;
nt2::table<T, nt2::lower_triangular_> l ;

nt2::tie(l,u,p) = nt2::lu(a);

temp = nt2::trsolve(l,y);
temp = nt2::trsolve(u,temp+y);

NT2_TEST_EQUAL( temp, x);
}

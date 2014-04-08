#include <nt2/include/functions/trsm.hpp>
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
typedef nt2::table<nt2_la_int>         t_i;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_t y(b);

t_t l,u,p;

nt2::tie(l,u,p) = nt2::lu(a);

char lside = 'l';
char uplo = 'u';
char lplo = 'l';
char diag = 'n';
char notrans= 'n';


y = nt2::mtimes(p,b);

nt2::trsm(lside,lplo,notrans,diag,boost::proto::value(l),boost::proto::value(y));

nt2::trsm(lside,uplo,notrans,diag,boost::proto::value(u),boost::proto::value(y));

NT2_TEST_EQUAL( y, x);
}

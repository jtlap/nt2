//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/balance.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/inv.hpp>


NT2_TEST_CASE_TPL(balance_complex, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  typedef nt2::table<cT>           t_t;
  cT a0 =  cT(nt2::One<T>(),nt2::One<T>());
  t_t s = nt2::balance(a0);
  NT2_TEST_ULP_EQUAL(s,a0,1);
  typedef std::complex<T> cT;
  s = nt2::balance(a0, 'B');
  NT2_TEST_ULP_EQUAL(s,a0,1);
}
// NT2_TEST_CASE_TPL(balance,  NT2_REAL_TYPES)
// {
//   using nt2::_;
//   using nt2::tag::factorization::balance_;
//   typedef std::complex<T> cT;
//   typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
//   typedef nt2::table<cT> t_t;
//   typedef nt2::table<itype_t> it_t;
//   typedef nt2::table<T> rt_t
//   T bc[25] =  {
//     T(1.0), T(2.0), T(0.), T(0.), T(0.),
//     T(0.) ,T( 2.0),T( 0.), T(0.), T(0.),
//     T(1.),  T(100.),  T(10000.), T(4.), T(0.2),
//     T(.01),  T(1.),  T(100.), T(0.2), T(0.1),
//     T(.0001),  T(.01),  T(1.), T(0.), T(0.000)
//   };

//   int k = 0;
//   t_t b(nt2::of_size(5, 5));
//   for(int i=1; i <= 5; i++)
//     {
//       for(int j=1; j <= 5; j++)
//         {
//           b(i, j) = cT(bc[k++]);
//         }

//     }
//   typedef typename nt2::meta::call<balance_(t_t const&,char)>::type result_type;


//   result_type f = nt2::factorization::balance(b,'B');

//   nt2::display("b     ", b);
//   nt2::display("values", f.values());
//   rt_t s  = f.scale();
//   nt2::display("s    ", s);
//   std::cout << "ilo " << f.ilo() << std::endl;
//   std::cout << "ihi " << f.ihi() << std::endl;
//   t_t t  = f.t();
//   nt2::display("t    ", t);
//   it_t ipiv  = f.ipiv();
//   nt2::display("ipiv    ", ipiv);
//   t_t invt  = f.invt();
//   nt2::display("invt    ", invt);
//   t_t e = nt2::inv(t);
//   nt2::display("inv(t)  ", e);
//   t_t zz = nt2::mtimes(nt2::mtimes(nt2::inv(t), b), t);
//   NT2_TEST_ULP_EQUAL(zz, f.balanced(),T(10.0));
// }

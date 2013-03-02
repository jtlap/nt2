//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied symeig function"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL ( symeig, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t w, v, d, b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());
  NT2_DISPLAY(b);
  w = nt2::symeig(b);
  NT2_DISPLAY(w);

  nt2::tie(v, d) = nt2::symeig(b);
  NT2_DISPLAY(v);
  NT2_DISPLAY(d);
  NT2_DISPLAY(b);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(d, nt2::trans(v))), 10.0);

}
NT2_TEST_CASE_TPL ( symeig_m_test, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t v, d, z;

  T bb[9] = {-149,    -50,   -154,
             537,    180,    546,
             -27,     -9,    -25 };
  //Note that only the upper part is used!
  table_t b(nt2::of_size(3, 3));
  int k = 0;
  for(int i=1; i <= 3; ++i)
    {
      for(int j=1; j <= 3; ++j)
        {
          b(i, j) = bb[k++];
        }
    }
  NT2_DISPLAY(b);
  nt2::tie(v, d) = nt2::symeig(b);
  NT2_DISPLAY(v);
  NT2_DISPLAY(d);
  z =  mtimes(mtimes(v, d), nt2::trans(v));
  NT2_DISPLAY(z);
  std::cout <<        nt2::globalmax(nt2::ulpdist(nt2::triu(b), nt2::triu(z))) << std::endl;
  table_t zz = nt2::triu(z);
  table_t bbb= nt2::triu(b);
  NT2_DISPLAY(zz);
  NT2_DISPLAY(bbb);
  //    NT2_DISPLAY(nt2::triu(z));
//    NT2_DISPLAY(nt2::triu(b));
   NT2_TEST(isulpequal(nt2::triu(z), nt2::triu(b), T(16.0)));
}



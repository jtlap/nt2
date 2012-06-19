//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied tr_solve function"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/tr_solve.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/rif.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( tr_solve_expr, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t;

  t_t a(nt2::of_size(5, 5));
  for(int i=1; i <= 5; i++)
    {
      for(int j=1; j <= 5; j++)
        {
          a(i, j) =i >= j;
        }

    }
  NT2_DISPLAY(a);
  t_t x, b =  nt2::rif(5, 1, nt2::meta::as_<T>());
  NT2_DISPLAY(b);
  x = nt2::tr_solve(nt2::tril(a), b, 'L', 'N', 'N');
  NT2_DISPLAY(x);
  x = nt2::tr_solve(a, b, 'L', 'N', 'N');
  NT2_DISPLAY(x);
  x = nt2::tr_solve(nt2::triu(a), b, 'L', 'N', 'N');
  NT2_DISPLAY(x);
  x = nt2::tr_solve(a, b, 'U', 'N', 'N');
  NT2_DISPLAY(x);


}

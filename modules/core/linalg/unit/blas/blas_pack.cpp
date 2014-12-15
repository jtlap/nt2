//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_pack.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_pack, NT2_REAL_TYPES )
{
  using nt2::blas_pack;
  using nt2::reshape;
  using nt2::_;
  {
    nt2::table<T> a = triu(reshape(_(T(1), T(9)), 3, 3));
    nt2::table<T> b(nt2::of_size(1, 3));
    nt2::table<T> r = nt2::cons<T>(nt2::of_size(1, 6), 1, 4, 5, 7, 8, 9 );
    b = blas_pack('U', a);
    NT2_TEST_EQUAL(b, r);
    NT2_DISPLAY(a);
    NT2_DISPLAY(b);
  }
  {
    nt2::table<T> a = tril(reshape(_(T(1), T(9)), 3, 3));
    nt2::table<T> b(nt2::of_size(1, 3));
    nt2::table<T> r = nt2::cons<T>(nt2::of_size(1, 6), 1, 2, 3, 5, 6, 9 );
    b = blas_pack('L', a);
    NT2_TEST_EQUAL(b, r);
    NT2_DISPLAY(a);
    NT2_DISPLAY(b);
  }
}



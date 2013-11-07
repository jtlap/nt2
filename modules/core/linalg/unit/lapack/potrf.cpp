//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/potrf.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL(band, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T,nt2::positive_definite_> t_t;
  t_t a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
  t_t run(a);

  nt2_la_int info = nt2::potrf(run,'U');

  NT2_TEST_EQUAL(info,T(0));
  NT2_TEST_ULP_EQUAL(a,nt2::mtimes(nt2::trans(nt2::triu(run)),nt2::triu(run)), T(20) );

  run = a;

  info = nt2::potrf(run,'L');

 NT2_TEST_EQUAL(info,T(0));
 NT2_TEST_ULP_EQUAL(a,nt2::mtimes(nt2::tril(run),nt2::trans(nt2::tril(run))), T(20) );

}

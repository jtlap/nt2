//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 function prod"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/toolbox/exponential/include/functions/exp2.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( prod, NT2_REAL_TYPES)
{
  using nt2::table;
  using nt2::of_size;
  using nt2::prod;
  using nt2::_;
  typedef std::complex<T>  cT;

  std::size_t M = 5;

  table<cT> r, r1;
  table<cT> a = T(2)*nt2::ones(2, 3, nt2::meta::as_<cT>());

  r = prod(a(nt2::_));
  NT2_TEST_EQUAL(r(1),cT(1 <<nt2::numel(a))) ;
  NT2_DISPLAY(r);
  r = prod(a, 1);
  NT2_DISPLAY(r);
  NT2_TEST_EQUAL(r,T(4)*nt2::ones(1, 3, nt2::meta::as_<cT>())) ;
  r = prod(a, 2);
  NT2_DISPLAY(r);
  NT2_TEST_EQUAL(r,T(8)*nt2::ones(2, 1, nt2::meta::as_<cT>())) ;
  r = prod(a, 3);
  NT2_DISPLAY(r);
  NT2_TEST_EQUAL(r,T(2)*nt2::ones(2,3, nt2::meta::as_<cT>())) ;


}

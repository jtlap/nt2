//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/band.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

struct made_up_diagonal
{
  template<class Sig> struct result;

  template<class This, class A0, class A1>
  struct result<This(A0,A1)>
  {
    typedef typename nt2::meta::strip<A0>::type a0_t;
    typedef typename nt2::meta::as_logical<a0_t>::type type;
  };

  template < class A0, class A1>
  typename nt2::meta::as_logical<A0>::type
  operator()(const A0& i, const A1& j) const
  {
    return nt2::eq(i, j);
  }
};

NT2_TEST_CASE_TPL( whereij_scalar, NT2_TYPES)
{
  T e = nt2::whereij(made_up_diagonal(), T(42), T(69));
  NT2_TEST_EQUAL(e, T(42));
}

NT2_TEST_CASE_TPL( whereij_callable, NT2_TYPES)
{
  nt2::table<T> a = nt2::rif  ( nt2::of_size(3, 3), nt2::meta::as_<T>() )
              , b = nt2::zeros( nt2::of_size(3, 3), nt2::meta::as_<T>() )
              , res, ref;

  ref = a;
  for(int i=1;i<=3;++i) ref(i,i) = T(99);

  res = whereij(made_up_diagonal(), T(99), a);
  NT2_TEST_EQUAL(res, ref);

  ref = diagonal(a);
  res = whereij(made_up_diagonal(), a, b);
  NT2_TEST_EQUAL(res, ref);

  res = whereij(made_up_diagonal(), a, T(0));
  NT2_TEST_EQUAL(res, ref);
}

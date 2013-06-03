//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::sxfun function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/sxfun.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

struct plus_pfo
{
  plus_pfo(int value_) : value(value_)
  {
  }

  template<class Sig>
  struct result;

  template<class This, class T, class U>
  struct result<This(T, U)>
    : boost::dispatch::meta::strip<T>
  {
  };

  template<class T>
  T operator()(T const& a, T const& b) const
  {
    return a + b + nt2::splat<T>(value);
  }

  int value;
};

NT2_TEST_CASE_TPL( sxfun_6, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::reshape(a, 4, 1);
  nt2::table<T> c(nt2::of_size(4, 4));

  for(int i=1; i <= 4 ; ++i)
  {
    for(int j=1; j <= 4 ; ++j)
    {
      c(i, j) = i+j+1;
    }
  }
  NT2_TEST_EQUAL(nt2::sxfun(plus_pfo(1), a, b), c);
}

NT2_TEST_CASE_TPL( sxfun_7, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::ones(nt2::of_size(3, 1,3,1), nt2::meta::as_<T>()),
    b = nt2::ones(nt2::of_size(1, 3, 1,3), nt2::meta::as_<T>());

  NT2_TEST_EQUAL( sxfun(plus_pfo(2),  a, b), T(4)*ones(nt2::of_size(3, 3, 3, 3),  nt2::meta::as_<T>()));
}

struct fma_pfo
{
  fma_pfo(int value_) : value(value_)
  {
  }

  template<class Sig>
  struct result;

  template<class This, class T, class U, class V>
  struct result<This(T, U, V)>
    : boost::dispatch::meta::strip<T>
  {
  };

  template<class T>
  T operator()(T const& a, T const& b, T const& c) const
  {
    return a*b + c + nt2::splat<T>(value);
  }

  int value;
};

NT2_TEST_CASE_TPL( sxfun_9, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::reshape(a, 4, 1);
  nt2::table<T> c = nt2::_(T(1), T(4));
  nt2::table<T> d(nt2::of_size(4, 4));

  for(int i=1; i <= 4 ; ++i)
  {
    for(int j=1; j <= 4 ; ++j)
    {
      d(i, j) = i*j+j+1;
    }
  }
  NT2_TEST_EQUAL(nt2::sxfun(fma_pfo(1), a, b, c), d);
}

NT2_TEST_CASE_TPL( sxfun_10, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::ones(nt2::of_size(3, 1,3,1), nt2::meta::as_<T>()),
    b = nt2::ones(nt2::of_size(1, 3, 1,3), nt2::meta::as_<T>()),
    c = nt2::ones(nt2::of_size(3, 1, 1, 3), nt2::meta::as_<T>());

  NT2_TEST_EQUAL( sxfun(fma_pfo(2),  a, b, c), T(4)*ones(nt2::of_size(3, 3, 3, 3),  nt2::meta::as_<T>()));
}

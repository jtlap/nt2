/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::adjfun"

#include <nt2/table.hpp>
#include <nt2/include/functions/adjfun.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( adjfun, (double)(float)(int)(short)(char) )
{
  using nt2::_;
  using nt2::end_;
  using nt2::is_equal;
  using nt2::isempty;
  using nt2::adjfun;
  using nt2::functor;

  nt2::table<T> y( nt2::of_size(5,3) );

  for(std::size_t j=1;j <= nt2::size(y, 2);j++)
    for(std::size_t i=1;i <= nt2::size(y, 1);i++)
      y(i,j) = T(i + j)*T(i+j);

  NT2_TEST_EQUAL( adjfun(functor<nt2::tag::minus_>(), y)
                , y(_(2, end_), _)-y(_(1, end_-1), _)
                );

  NT2_TEST_EQUAL( adjfun(functor<nt2::tag::minus_>(), y, 1)
                , y(_(2, end_), _)-y(_(1, end_-1), _)
                );

  NT2_TEST_EQUAL( adjfun(functor<nt2::tag::minus_>(), y, 2)
                , y(_,_(2, end_), _)-y(_,_(1, end_-1), _)
                );

  NT2_TEST(isempty( adjfun(functor<nt2::tag::minus_>(), y, 3) ));
}

NT2_TEST_CASE_TPL( adjfun_scalar, NT2_TYPES )
{
  using nt2::isempty;
  using nt2::adjfun;

  NT2_TEST(nt2::isempty(nt2::adjfun(nt2::functor<nt2::tag::minus_>(), T(1)  ) ));
  NT2_TEST(nt2::isempty(nt2::adjfun(nt2::functor<nt2::tag::minus_>(), T(1),1) ));
  NT2_TEST(nt2::isempty(nt2::adjfun(nt2::functor<nt2::tag::minus_>(), T(1),2) ));
  NT2_TEST(nt2::isempty(nt2::adjfun(nt2::functor<nt2::tag::minus_>(), T(1),3) ));

  nt2::table<T, nt2::_2D> a2 = nt2::ones(3, 5, nt2::meta::as_<T>());
  NT2_TEST(nt2::isempty(nt2::adjfun(nt2::functor<nt2::tag::minus_>(), a2, 3) ));
}

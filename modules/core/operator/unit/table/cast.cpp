/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::cast function"

#include <nt2/table.hpp>
#include <nt2/include/functions/cast.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>

#include <boost/proto/debug.hpp>

NT2_TEST_CASE( generator )
{
  typedef double T;
  typedef nt2::settings S(nt2::_4D);
  nt2::table<T, S> a0;

  NT2_TEST_EXPR_TYPE( nt2::cast<float>(a0)
                    , boost::dispatch::meta::semantic_of<boost::mpl::_>
                    , (nt2::memory::container<float, S>)
                    );

  NT2_TEST_EXPR_TYPE( nt2::cast<nt2::int16_t>(a0)
                    , boost::dispatch::meta::semantic_of<boost::mpl::_>
                    , (nt2::memory::container<nt2::int16_t, S>)
                    );
}

template<class T, class U>
void assign_test()
{
  std::cout << "With U = [" << nt2::type_id<U>() << "]\n";
  static const std::size_t N = 11;
  nt2::table<T> a0(nt2::of_size(N));
  for(std::size_t i=0; i!=N; ++i)
    a0(i+1) = T(roll<U>());

  boost::proto::display_expr( nt2::cast<U>(a0) );
  nt2::table<U> a1 = nt2::cast<U>(a0);
  for(std::size_t i=0; i!= N; ++i)
  {
    std::cout << a0(i+1) << "\n";
    NT2_TEST_EQUAL( a1(i+1), nt2::cast(a0(i+1), nt2::meta::as_<U>()) );
  }
};

NT2_TEST_CASE_TPL( assign, BOOST_SIMD_TYPES )
{
  #define M0(r, data, elem) assign_test<T, elem>();
  BOOST_PP_SEQ_FOR_EACH(M0, ~, BOOST_SIMD_TYPES)
  #undef M0
}

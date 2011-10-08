/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::extent"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/container/extent/extent.hpp>
#include <nt2/core/settings/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#define M0(z,n,t) (nt2::BOOST_PP_CAT(BOOST_PP_CAT(_,n),D))
#define DYN_DIM_LIST BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

////////////////////////////////////////////////////////////////////////////////
// Does extent<_0D> behaves correctly ?
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( default_ctor_0d )
{
  using nt2::_0D;
  using nt2::container::extent;

  extent<_0D> x;

  NT2_TEST( x.empty() );
  NT2_TEST_EQUAL( x.size()  , 0);
  NT2_TEST_EQUAL( x.size(1) , 1);
  NT2_TEST_EQUAL( x.size(2) , 1);
  NT2_TEST_EQUAL( x.lower(0), 1);
  NT2_TEST_EQUAL( x.upper(0), 1);
  NT2_TEST_EQUAL( x(1)      , 1);
  NT2_TEST_EQUAL( x(2)      , 1);
  NT2_TEST_EQUAL( x(3)      , 1);
  NT2_TEST_EQUAL( x(4)      , 1);
}

NT2_TEST_CASE_TPL ( default_ctor, DYN_DIM_LIST )
{
  using nt2::container::extent;

  extent<T> x;
  std::size_t dims = T::static_size;

  NT2_TEST( !x.empty() );
  NT2_TEST_EQUAL( x.size()  , dims  );

  NT2_TEST_EQUAL( x(1)      , 0     );
  NT2_TEST_EQUAL( x.size(1) , 1     );
  NT2_TEST_EQUAL( x.size(2) , dims  );
  NT2_TEST_EQUAL( x.lower(1), 1     );
  NT2_TEST_EQUAL( x.lower(2), 1     );
  NT2_TEST_EQUAL( x.upper(1), 1     );
  NT2_TEST_EQUAL( x.upper(2), dims  );

  for(std::size_t i= 3; i<= dims;++i)
  {
    NT2_TEST_EQUAL( x(i)      , 1 );
    NT2_TEST_EQUAL( x.size(i) , 1 );
    NT2_TEST_EQUAL( x.lower(i), 1 );
    NT2_TEST_EQUAL( x.upper(i), 1 );
  }
}

NT2_TEST_CASE( default_ctor_static )
{
  using nt2::of_size_;
  using nt2::container::extent;

  extent< of_size_<9,7,5> > x;

  NT2_TEST( !x.empty() );
  NT2_TEST_EQUAL( x.size()  , 3  );

  NT2_TEST_EQUAL( x(1)      , 9 );
  NT2_TEST_EQUAL( x(2)      , 7 );
  NT2_TEST_EQUAL( x(3)      , 5 );

  NT2_TEST_EQUAL( x.size(1) , 1 );
  NT2_TEST_EQUAL( x.size(2) , 3 );
  NT2_TEST_EQUAL( x.size(3) , 1 );
  NT2_TEST_EQUAL( x.lower(1), 1 );
  NT2_TEST_EQUAL( x.lower(2), 1 );
  NT2_TEST_EQUAL( x.lower(3), 1 );
  NT2_TEST_EQUAL( x.upper(1), 1 );
  NT2_TEST_EQUAL( x.upper(2), 3 );
  NT2_TEST_EQUAL( x.upper(3), 1 );
}
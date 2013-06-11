//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/meta/is_pointing_to.hpp>
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL(pointing_with_pointer, BOOST_SIMD_TYPES)
{
  using boost::simd::meta::is_pointing_to;

  NT2_TEST(( is_pointing_to<T*,T>::value ));
}

NT2_TEST_CASE_TPL(pointing_with_iterator, BOOST_SIMD_TYPES)
{
  using std::vector;
  using boost::simd::meta::is_pointing_to;

  NT2_TEST(( is_pointing_to < typename vector<T>::iterator
                            , T
                            >::value
          ));

  NT2_TEST(( is_pointing_to < typename vector<T>::const_iterator
                            , T const
                            >::value
          ));
}

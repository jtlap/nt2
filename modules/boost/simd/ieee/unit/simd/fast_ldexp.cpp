//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - fast_ldexp/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/toolbox/ieee/include/functions/fast_ldexp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( fast_ldexp_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::fast_ldexp;
  using boost::simd::tag::fast_ldexp_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                                    ivT;

  for(unsigned int i = 0; i < cardinal_of<vT>::value; ++i)
    {
      std::cout << i << std::endl;
      NT2_TEST_EQUAL( boost::simd::fast_ldexp( boost::simd::One<vT>()
                                              , boost::simd::Two<ivT>()
                                              )[i]
                    , boost::simd::fast_ldexp( boost::simd::One<T>()
                                              , boost::simd::Two<iT>()
                                              )
                    );
    }
} // end of test for floating_

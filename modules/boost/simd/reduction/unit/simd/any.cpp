//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/reduction/include/functions/any.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mzero.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( any, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::True;
  using boost::simd::False;
  using boost::simd::tag::any_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION            ext_t;
  typedef native<T,ext_t>                         vT;
  typedef boost::simd::logical<T>                 lT;

  vT all_ok, none_ok, some_ok;
  for(std::size_t i=0;i<vT::static_size;++i)
  {
    none_ok[i] = T(0);
    some_ok[i] = all_ok[i] =T(1+i);
  }

  some_ok[vT::static_size/2] = T(0);

  NT2_TEST_EQUAL( boost::simd::any(all_ok) , True<lT>()  );
  NT2_TEST_EQUAL( boost::simd::any(some_ok), True<lT>()  );
  NT2_TEST_EQUAL( boost::simd::any(none_ok), False<lT>() );
}

NT2_TEST_CASE_TPL ( any_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::True;
  using boost::simd::Minf;
  using boost::simd::Inf;
  using boost::simd::Nan;
  using boost::simd::False;
  using boost::simd::Mzero;
  using boost::simd::tag::any_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION            ext_t;
  typedef native<T,ext_t>                         vT;
  typedef boost::simd::logical<T>                 lT;

  NT2_TEST_EQUAL( boost::simd::any(Inf<vT>()) , True<lT>()   );
  NT2_TEST_EQUAL( boost::simd::any(Minf<vT>()), True<lT>()   );
  NT2_TEST_EQUAL( boost::simd::any(Nan<vT>()) , True<lT>()   );
  NT2_TEST_EQUAL( boost::simd::any(Mzero<vT>()), False<lT>() );
}

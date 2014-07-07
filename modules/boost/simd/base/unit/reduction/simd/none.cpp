//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompnoneing file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/reduction/include/functions/none.hpp>
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

NT2_TEST_CASE_TPL ( none, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::none;
  using boost::simd::True;
  using boost::simd::False;
  using boost::simd::tag::none_;
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

  NT2_TEST_EQUAL( none(all_ok) , False<lT>()  );
  NT2_TEST_EQUAL( none(some_ok), False<lT>()  );
  NT2_TEST_EQUAL( none(none_ok), True<lT>() );
}

NT2_TEST_CASE_TPL ( none_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::none;
  using boost::simd::True;
  using boost::simd::Minf;
  using boost::simd::Inf;
  using boost::simd::Mzero;
  using boost::simd::Nan;
  using boost::simd::False;
  using boost::simd::tag::none_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION            ext_t;
  typedef native<T,ext_t>                         vT;
  typedef boost::simd::logical<T>                 lT;

  NT2_TEST_EQUAL( none(Inf<vT>()) , False<lT>()  );
  NT2_TEST_EQUAL( none(Minf<vT>()), False<lT>() );
  NT2_TEST_EQUAL( none(Nan<vT>()) , False<lT>() );
  NT2_TEST_EQUAL( none(Mzero<vT>()), True<lT>() );
}

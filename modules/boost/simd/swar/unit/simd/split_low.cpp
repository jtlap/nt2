//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/split_low.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( split_low, BOOST_SIMD_SIMD_SPLITABLE_TYPES )
{
  using boost::simd::split_low;
  using boost::simd::tag::split_low_;
  using boost::simd::native;
  using boost::simd::enumerate;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                      ext_t;
  typedef native<T,ext_t>                                   vT;
  typedef typename boost::dispatch::meta::upgrade<vT>::type uvT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<split_low_(vT)>::type
                  , uvT
                  );

  vT origin = enumerate<vT>(-1);
  uvT ref;

  for(std::size_t i=0;i<cardinal_of<uvT>::value;++i)
    ref[i] = origin[i];

  NT2_TEST_EQUAL(ref, split_low(origin) );
}


NT2_TEST_CASE_TPL( split_low_pack, BOOST_SIMD_SIMD_SPLITABLE_TYPES)
{
  using boost::simd::split_low;
  using boost::simd::tag::split_low_;
  using boost::simd::pack;
  using boost::simd::enumerate;
  using boost::simd::meta::cardinal_of;

  typedef pack<T>                                           vT;
  typedef typename boost::dispatch::meta::upgrade<vT>::type uvT;

  vT origin = enumerate<vT>(-1);
  uvT ref;

  for(std::size_t i=0;i<cardinal_of<uvT>::value;++i)
    ref[i] = origin[i];

  NT2_TEST_EQUAL(ref, split_low(origin) );
}

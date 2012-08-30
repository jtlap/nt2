//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - remquo/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/functions/remquo.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/remainder.hpp>
#include <boost/simd/include/functions/idivround.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( remquo_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::remquo;
  using boost::simd::tag::remquo_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::splat;
  
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<remquo_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  T a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  T b[10] = {1, 3, 4, 5, 6, 7, 8, 9, 10};
  vT r;
  ivT n;     
  T sr = 0;
  iT sn = 0; 
  
  for(int i=0; i < 10; ++i)
    {
      for(int j=0; j < 10; ++j)
        {
          remquo(splat<vT>(a[i]), splat<vT>(b[j]), r, n);
          remquo(a[i], b[j], sr, sn); 
          NT2_TEST_EQUAL(r[0], sr);
          NT2_TEST_EQUAL(n[0], sn); 
       }
   }
} // end of test for floating_

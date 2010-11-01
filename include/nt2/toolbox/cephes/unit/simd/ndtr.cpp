//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 cephes toolbox - ndtr - unit/simd Mode"

#include <nt2/toolbox/cephes/include/ndtr.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of cephes component ndtr using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
//NT2_TEST_CASE_TPL(ndtr, NT2_SIMD_TYPES )
//{
//  using nt2::ndtr;
//  using nt2::functors::ndtr;
// 
//  using nt2::simd::native;
//  using nt2::meta::cardinal_of;
//
//  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//  typedef native<T,ext_t>             n_t;
//
//  NT2_TEST( (boost::is_same<typename nt2::meta::call<cephes_(n_t)>::type,
//                            typename std::tr1::result_of<nt2::meta::floating<($self.const_n_t_type_list$)>::type
//                            >::value)
//          );
//  NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
//  for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i)
//    data[i] = i; // good value here for ndtr
//
//    n_t a0 = load<n_t>(&data[0],0);
//    n_t v  = ndtr(a0);
//    for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
//    {
//      NT2_TEST_EQUAL( v[j], ndtr(a0[j]) );
//    }
//  }
//}


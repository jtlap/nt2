//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 gsl_specfun toolbox - gsl_sf_zetam1 - unit/simd Mode"

#include <nt2/toolbox/gsl_specfun/include/gsl_sf_zetam1.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <../unit/sdk/simd/types.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of gsl_specfun component gsl_sf_zetam1 using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
//NT2_TEST_CASE_TPL(gsl_sf_zetam1, NT2_SIMD_TYPES )
//{
//  using nt2::gsl_sf_zetam1;
//  using nt2::functors::gsl_sf_zetam1;
// 
//  using nt2::simd::native;
//  using nt2::meta::cardinal_of;
//
//  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//  typedef native<T,ext_t>             n_t;
//
//  NT2_TEST( (boost::is_same<typename nt2::meta::call<gsl_specfun_(n_t)>::type,
//                            typename std::tr1::result_of<nt2::meta::floating<($self.const_n_t_type_list$)>::type
//                            >::value)
//          );
//  NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
//  for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i)
//    data[i] = i; // good value here for gsl_sf_zetam1
//
//    n_t a0 = load<n_t>(&data[0],0);
//    n_t v  = gsl_sf_zetam1(a0);
//    for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
//    {
//      NT2_TEST_EQUAL( v[j], gsl_sf_zetam1(a0[j]) );
//    }
//  }
//}


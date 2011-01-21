//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - arg - simd/unit Mode"

#include <nt2/include/functions/arg.hpp>
#include <nt2/sdk/unit/tests.hpp>   
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp> 
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp> 
#include <nt2/sdk/meta/as_real.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic component arg using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(arg, (nt2::uint64_t)
              (nt2::uint64_t)(nt2::int64_t)(double)
                (nt2::uint32_t)(nt2::int32_t)(float) 
                         )
{
 using nt2::arg; 
 using nt2::tag::arg_;
 using nt2::load;  
 using nt2::simd::native;
 using nt2::meta::cardinal_of; 

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<arg_(n_t)>::type call_type;

 typedef typename nt2::meta::as_real<T>::type rT;
 typedef native<rT,ext_t>            rn_t;
  
 NT2_TEST( (boost::is_same<call_type, rn_t>::value) );
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i)
   data[i] = i-T(cardinal_of<n_t>::value/2); // good value here for arg

 n_t a0 = load<n_t>(&data[0],0); 
 rn_t v  = nt2::arg(a0);
 for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
   { 
     NT2_TEST_EQUAL( v[j], arg(a0[j]) );
   } 
}

 

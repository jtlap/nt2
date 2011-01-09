//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - unit/simd Mode"

#include <nt2/toolbox/swar/include/split.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/include/functions/random.hpp>
#include <nt2/include/functions/boolean.hpp>
#include <nt2/include/functions/hmsb.hpp>
#include <nt2/include/functions/group.hpp> 
#include <nt2/include/functions/boolean.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(split, (float))//(int16_t)(uint16_t)
// (int32_t)(uint32_t)(int8_t)(uint8_t) )
{
 using nt2::split;
 using nt2::tag::split_;    
 using nt2::load;  
 using nt2::simd::native; 
 using nt2::meta::cardinal_of;

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<split_(n_t)>::type                   call_type;
 typedef typename nt2::meta::upgrade<T>::type                              utype;
 typedef nt2::simd::native<utype,ext_t>                                    ttype;
 typedef nt2::meta::is_floating_point<T>                                    rtag;
 typedef nt2::simd::native<typename  nt2::meta::double__<T>::type,ext_t>    dtype;
 typedef typename boost::mpl::if_c < rtag::value
                                  , dtype, ttype>::type                    rtype;
 typedef boost::fusion::tuple<rtype,rtype>                                  rn_t;


 NT2_TEST( (boost::is_same<call_type, rn_t>::value) );  
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 for(int j =  0;  j < 10; j++)
   {
     for(int i=0;i<2*cardinal_of<n_t>::value;++i){
       data[i] = i; // good value here for split
     }
     n_t a0 = load<n_t>(&data[0],0); 
     rtype v1, v0; 
     boost::fusion::tie(v0, v1) = split(a0);
     for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
       {
       std::cout << a0 << std::endl; 
       std::cout << v0 << "   " << v1 << std::endl;
       n_t a1 = nt2::group(v0, v1);
       NT2_TEST(nt2::all(nt2::eq(a0,a1))); 
       }
   }
}

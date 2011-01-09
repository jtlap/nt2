//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - unit/simd Mode"

#include <nt2/toolbox/swar/include/group.hpp>
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
#include <nt2/include/functions/boolean.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(group, //(double)(int16_t)(uint16_t)
		  //(int32_t)(uint32_t)(int64_t))
		  (uint64_t) )
{
 using nt2::group;
 using nt2::tag::group_;    
 using nt2::load;  
 using nt2::simd::native; 
 using nt2::meta::cardinal_of;

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<group_(n_t, n_t)>::type call_type;
 typedef typename nt2::meta::downgrade<T>::type                                   utype;
 typedef nt2::simd::native<utype,ext_t>                                           type1;
 typedef nt2::simd::native< typename nt2::meta::float__<T>::type, ext_t>               type2;
 typedef typename boost::mpl::if_c < boost::is_same<T,double>::value
                                        , type2
                                        , type1
                                        >::type rn_t;

 NT2_TEST( (boost::is_same<call_type, rn_t>::value) );  
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 for(int j =  0;  j < 10; j++)
   {
     for(int i=0;i<2*cardinal_of<n_t>::value;++i){
       data[i] = i; // good value here for group
     }
     n_t a0 = load<n_t>(&data[0],0); 
     n_t a1 = load<n_t>(&data[0],1);
     n_t a2, a3; 
     rn_t v  = group(a0, a1);
     for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
       {
       std::cout << a0 << "   " << a1 << std::endl; 
       std::cout << v << std::endl;
       boost::fusion::tie(a2, a3) = nt2::split(v);
       NT2_TEST(nt2::all(nt2::eq(a0,a2))); 
       NT2_TEST(nt2::all(nt2::eq(a1,a3))); 
       }
   }
}

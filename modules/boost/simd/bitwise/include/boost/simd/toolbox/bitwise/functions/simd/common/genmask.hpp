//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_GENMASK_HPP_INCLUDED
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <iostream>
#include <nt2/sdk/details/type_id.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else(is_nez(a0), Allbits<A0> (), Zero<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<logical_<A0>,X>))
                            )
  {
    typedef typename A0::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      std::cout << "this functor has not been properly specialized" << std::endl;
      std::cout << "for type : " << nt2::type_id<A0>() << std::endl; 
      //      return if_else(a0, Allbits<result_type>(), Zero<result_type>());
      static const size_t size = boost::simd::meta::cardinal_of<result_type>::value;
      typedef typename meta::scalar_of<result_type>::type sR;
      BOOST_SIMD_ALIGNED_TYPE(sR) tmp[size];
      for(size_t i = 0; i != size; ++i)
        tmp[i] = a0[i]?Allbits<sR>():Zero<sR>();
      return load<result_type>(&tmp[0], 0);
      
    }
  };
} } }


#endif

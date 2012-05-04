//============================================================================== 
// Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II 
// Copyright 2009 - 2011 LRI UMR 8623 CNRS/Univ Paris Sud XI 
// 
// Distributed under the Boost Software License, Version 1.0.  
// See accompanying file LICENSE.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt 
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_PUT_FIRST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_PUT_FIRST_HPP_INCLUDED

#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/simd/load.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::put_first_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))(scalar_< integer_<A1> >)
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      
      BOOST_SIMD_ALIGNED_TYPE(sA0) tmp[boost::simd::meta::cardinal_of<A0>::value];
      tmp[0] = a0[a1];
      for(A1 i = 1; i != A1(boost::simd::meta::cardinal_of<A0>::value); ++i)
        tmp[i] = a0[i];
      
      return load<A0>(&tmp[0], 0);
    }
  };
} } }


#endif

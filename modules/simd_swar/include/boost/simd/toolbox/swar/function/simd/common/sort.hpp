//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_SORT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_SORT_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>

#include <algorithm>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::sort_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      static const int size = meta::cardinal_of<A0>::value;
      BOOST_SIMD_ALIGNED_TYPE(stype) tmp[size];
      store(a0, &tmp[0], 0);
      
      std::sort(tmp, tmp + size);
      
      return load<A0>(&tmp[0], 0);
    }
  };
} } }


#endif

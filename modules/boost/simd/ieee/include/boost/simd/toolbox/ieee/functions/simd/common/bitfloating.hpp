//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_BITFLOATING_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_BITFLOATING_HPP_INCLUDED
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/sdk/simd/meta/is_real_convertible.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/is_gez.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitfloating_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_floating<A0>::type type;
      //A0 s = Signmask<A0>();
      //      type that = {select(isgez(type(a0)), a0, s-a0)};
      type r;
      A0 s = simd::native_cast<A0>(Signmask<type>());
//       std::cout << "in bitfloating" << std::endl;
//       std::cout << "a0                          " << a0 << std::endl;
//       std::cout << "is_gez(a0)                  " << is_gez(a0)<< std::endl;
//       std::cout << "simd::native_cast<type>(a0) " << simd::native_cast<type>(a0)<< std::endl;
      r = select(is_gez(a0) , simd::native_cast<type>(a0), simd::native_cast<type>(s-a0));
//       std::cout << "r             " << r<< std::endl;
//       std::cout << "out bitfloating" << std::endl;
      return r;
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitfloating_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<unsigned_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_floating<A0>::type type;
      return simd::native_cast<type>(a0);
    }
  };
} } }


#endif

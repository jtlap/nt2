//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_ANY_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_ANY_HPP_INCLUDED
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/hmsb.hpp>
#include <boost/simd/include/functions/split.hpp>
#include <boost/fusion/tuple.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::any_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return hmsb(is_nez(a0)) != 0;
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::any_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<uint8_<A0>,X>))
                            )
  {

    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename dispatch::meta::upgrade<stype>::type                 utype;
      typedef simd::native<utype,X>                                         ttype;
      ttype a0h, a0l;
      boost::simd::split(a0, a0h, a0l);
      return (hmsb(is_nez(a0h)) || hmsb(is_nez(a0l)));
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::any_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int8_<A0>,X>))
                            )
  {

    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename dispatch::meta::upgrade<stype>::type                 utype;
      typedef simd::native<utype,X>                                         ttype;
      ttype a0h, a0l;
      boost::fusion::tie(a0h, a0l) = split(a0);
      return (hmsb(is_nez(a0h)) || hmsb(is_nez(a0l)));
    }
  };
} } }


#endif

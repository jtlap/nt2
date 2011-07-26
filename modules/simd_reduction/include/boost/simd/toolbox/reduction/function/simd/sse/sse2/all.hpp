//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_ALL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_ALL_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/sdk/meta/upgrade.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/include/functions/hmsb.hpp>
#include <boost/simd/include/functions/split.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/fusion/tuple.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::all_, tag::cpu_
                            , (A0)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                            )
  {

    typedef bool result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      return hmsb(is_eqz(a0)) == 0;
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::all_, tag::cpu_
                            , (A0)
                            , ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                            )
  {

    typedef bool result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,boost::simd::tag::sse_>                                 ttype;
      ttype a0h, a0l;
      boost::fusion::tie(a0h, a0l) = split(a0);
      return (hmsb(is_eqz(a0h)) || hmsb(is_eqz(a0l))) == 0;
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::all_, tag::cpu_
                            , (A0)
                            , ((simd_<int8_<A0>,boost::simd::tag::sse_>))
                            )
  {

    typedef bool result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,boost::simd::tag::sse_>                                 ttype;
      ttype a0h, a0l;
      boost::fusion::tie(a0h, a0l) = split(a0);
      return (hmsb(is_eqz(a0h)) || hmsb(is_eqz(a0l)))== 0;
    }
  };
} } }


#endif

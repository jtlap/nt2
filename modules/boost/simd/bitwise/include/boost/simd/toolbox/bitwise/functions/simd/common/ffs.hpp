//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_FFS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_FFS_HPP_INCLUDED
#include <boost/simd/include/constants/digits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/meta/biggest_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/firstbitset.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/functions/shli.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/select.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types8_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<type8_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext;
      typedef simd::native<typename simd::meta::biggest_integer<ext>::type, ext> ltype;
      rtype v = firstbitset(a0);
      return b_and(is_nez(v), b_or(b_or((-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
                   ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
              ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))+One<rtype>());
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<type64_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0,unsigned>::type rtype;
      return  simd::native_cast<rtype>(map(dispatch::functor<boost::simd::tag::ffs_>(), simd::native_cast<rtype>(a0)));
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<type16_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext;
      typedef simd::native<typename simd::meta::biggest_integer<ext>::type, ext> ltype;
      rtype v = firstbitset(a0);
      return  b_and(is_nez(v), b_or(b_or(b_or((-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
                       ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
                  ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))
                            ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xFF00FF00FF00FF00ll>()))), 3))+One<rtype>());
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<type32_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext;
      typedef simd::native<typename simd::meta::biggest_integer<ext>::type, ext> ltype;
      rtype v = firstbitset(a0);
      return  b_and(is_nez(v), b_or(b_or(b_or(b_or((-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
                          ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
                       ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))
                  ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xFF00FF00FF00FF00ll>()))), 3))
               ,  shli(-( is_nez(b_and(v, boost::simd::integral_constant<ltype,0xFFFF0000FFFF0000ll>()))), 4))+One<rtype>());
    }
  };
} } }


#endif

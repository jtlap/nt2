//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_IDIVFLOOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_IDIVFLOOR_HPP_INCLUDED
#include <boost/simd/include/functions/scalar/idivceil.hpp>
#include <boost/simd/include/functions/rdivide.hpp>
#include <boost/simd/include/functions/scalar/ifloor.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::idivfloor_, tag::cpu_
                            , (A0)
                            , (scalar_< signed_<A0> >)
                        (scalar_< signed_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
        return -idivceil(static_cast<A0>(-a0),a1);
      else
      {
        typedef result_type type;
        return (a0) ? ((a0>0) ? Valmax<type>() : Valmin<type>()) : Zero<type>();
      }
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::idivfloor_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                        (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
        return rdivide(a0,a1);
      else
        return (a0) ? Valmax<result_type>() : Zero<result_type>();
    }
  };

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::idivfloor_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> > )(scalar_< floating_<A0> > )
                            )
  {
    typedef typename boost::dispatch::meta::as_integer < A0 >::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::ifloor(a0/a1);
    }
  };
} } }
  
#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif

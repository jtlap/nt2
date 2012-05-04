//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_IDIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_IDIVCEIL_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/idivceil.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/functions/scalar/sign.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/rdivide.hpp>
#include <boost/simd/include/functions/scalar/tofloat.hpp>
#include <boost/simd/include/functions/scalar/iceil.hpp>
#include <boost/simd/include/functions/scalar/ceil.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::idivceil_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A0> >)
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename boost::dispatch::meta::as_floating<result_type>::type ftype;
      ftype r = ceil(ftype(a0)/ftype(a1));
      if (r > Valmax<result_type>()) return Valmax<result_type>();
      else if (r <  Valmin<result_type>()) return Valmin<result_type>();
      else return result_type(r); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::idivceil_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A0> >)
                            )
  {
    
    typedef A0 result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return (a1) ? rdivide(A0(a0+(a1-One<result_type>())), a1) : Valmax<result_type>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::idivceil_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> > )
                            )
  {
    typedef A0 typ;
    typedef typename dispatch::meta::as_integer<typ>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return iceil(a0/a1);
    }
  };
} } }

#endif

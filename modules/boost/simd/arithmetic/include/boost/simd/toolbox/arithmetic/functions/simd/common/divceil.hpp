//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVCEIL_HPP_INCLUDED

#include <boost/simd/toolbox/arithmetic/functions/divceil.hpp>
#include <boost/simd/include/functions/group.hpp>
#include <boost/simd/include/functions/split.hpp>
#include <boost/simd/include/functions/iceil.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/rdivide.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return ceil(tofloat(a0)/tofloat(a1)); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                            , ((simd_<unsigned_<A0>,X>))
                              ((simd_<unsigned_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return rdivide(a0+a1-One<A0>(), a1); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                            , ((simd_<int16_<A0>,X>))
                              ((simd_<int16_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type           stype;
      typedef typename dispatch::meta::upgrade<stype>::type          itype;
      typedef simd::native<itype,X>                       ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::fusion::tie(a0l, a0h) = split(a0);
      boost::fusion::tie(a1l, a1h) = split(a1);
      return bitwise_cast<A0>(group(divceil(a0l, a1l),divceil(a0h, a1h)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                            , ((simd_<int8_<A0>,X>))
                              ((simd_<int8_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type           stype;
      typedef typename dispatch::meta::upgrade<stype>::type          itype;
      typedef simd::native<itype, X>                      ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::fusion::tie(a0l, a0h) = split(a0);
      boost::fusion::tie(a1l, a1h) = split(a1);
      return simd::bitwise_cast<A0>(group(divceil(a0l, a1l),divceil(a0h, a1h) ));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return ceil(a0/a1); }
  };
} } }

#endif

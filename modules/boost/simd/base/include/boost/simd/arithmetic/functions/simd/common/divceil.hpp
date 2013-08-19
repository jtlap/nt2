//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVCEIL_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/divceil.hpp>
#include <boost/simd/include/functions/simd/divs.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_gtz.hpp>
#include <boost/simd/include/functions/simd/seladd.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/simd/include/functions/simd/if_allbits_else.hpp>
#include <boost/simd/include/functions/simd/logical_andnot.hpp>
#include <boost/simd/include/functions/simd/ceil.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/idivceil.hpp>
#include <boost/simd/include/functions/simd/touints.hpp>
#include <boost/simd/include/functions/simd/toints.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <nt2/table.hpp>

namespace boost { namespace simd { namespace ext
{

// rationale //////////////////////
// SIMD integer division is lacking,  so there is two solutions
//   1 - simply mapping the simd fonctions on the scalar ones
//   2 - using floating division for integers that fit in them
//
// and of course taking the available faster solution
//  Here we implement divceil for 8 and 16 bits integers simd vectors
//  by splitting them in as much as necessary 32bits floating points
//  SIMD vectors (23 bits of mantissa is enough)
//  For 32 bits integers spliting them in 64 bits floating points
//  SIMD vectors could fit but is less performing than the map up
//  to sse4.2 at least (and also does not work for altivec).
//  For 64 bits integers we currently have no floating points SIMD
//  they can fit in so mapping is mandatory.
//

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                            , ((simd_< int32_<A0>, X>))
                              ((simd_< int32_<A0>, X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type                     stype;
      typedef typename dispatch::meta::upgrade<stype>::type          itype;
      typedef simd::native<itype,X>                                 ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::simd::split(a0, a0l, a0h );
      boost::simd::split(a1, a1l, a1h );
      ivtype d0 = idivceil(tofloat(a0l), tofloat(a1l));
      ivtype d1 = idivceil(tofloat(a0h), tofloat(a1h));
      return groups(d0, d1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                                   , ((simd_<int16_<A0>,X>))
                                     ((simd_<int16_<A0>,X>))
                                   )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type                     stype;
      typedef typename dispatch::meta::upgrade<stype>::type          itype;
      typedef simd::native<itype,X>                                 ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::simd::split(a0, a0l, a0h );
      boost::simd::split(a1, a1l, a1h );
      ivtype d0 = idivceil(tofloat(a0l), tofloat(a1l));
      ivtype d1 = idivceil(tofloat(a0h), tofloat(a1h));
      return groups(d0, d1);
    }
  };

 BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                                   , ((simd_<uint16_<A0>,X>))
                                     ((simd_<uint16_<A0>,X>))
                                   )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type                     stype;
      typedef typename dispatch::meta::upgrade<stype>::type          itype;
      typedef simd::native<itype,X>                                 ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::simd::split(a0, a0l, a0h );
      boost::simd::split(a1, a1l, a1h );
      ivtype d0 = touints(divceil(tofloat(a0l), tofloat(a1l)));
      ivtype d1 = touints(divceil(tofloat(a0h), tofloat(a1h)));
      return groups(d0, d1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                                   , ((simd_<ints8_<A0>,X>))
                                     ((simd_<ints8_<A0>,X>))
                                   )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type                     stype;
      typedef typename dispatch::meta::upgrade<stype>::type          itype;
      typedef simd::native<itype, X>                                ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::simd::split(a0, a0l, a0h );
      boost::simd::split(a1, a1l, a1h );
      ivtype d0 = divceil(a0l, a1l);
      ivtype d1 = divceil(a0h, a1h);
      return groups(d0, d1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divceil_, tag::cpu_, (A0)(X)
                                   , ((simd_<floating_<A0>,X>))
                                     ((simd_<floating_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::ceil(a0/a1);
    }
  };
} } }

#endif

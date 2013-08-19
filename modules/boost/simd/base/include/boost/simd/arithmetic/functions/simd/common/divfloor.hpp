//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVFLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVFLOOR_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/divfloor.hpp>
#include <boost/simd/include/functions/simd/floor.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/idivfloor.hpp>
#include <boost/simd/include/functions/simd/touints.hpp>
#include <boost/simd/include/functions/simd/toints.hpp>
#include <boost/simd/include/functions/simd/split.hpp>
#include <boost/simd/include/functions/simd/groups.hpp>

namespace boost { namespace simd { namespace ext
{
// rationale ///////////////////////////////
// see divceil.hpp in the same directory
//
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divfloor_, tag::cpu_, (A0)(X)
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
      ivtype d0 = idivfloor(tofloat(a0l), tofloat(a1l));
      ivtype d1 = idivfloor(tofloat(a0h), tofloat(a1h));
      return groups(d0, d1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divfloor_, tag::cpu_, (A0)(X)
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
      ivtype d0 = idivfloor(tofloat(a0l), tofloat(a1l));
      ivtype d1 = idivfloor(tofloat(a0h), tofloat(a1h));
      return groups(d0, d1);
    }
  };

 BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divfloor_, tag::cpu_, (A0)(X)
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
      ivtype d0 = touints(divfloor(tofloat(a0l), tofloat(a1l)));
      ivtype d1 = touints(divfloor(tofloat(a0h), tofloat(a1h)));
      return groups(d0, d1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divfloor_, tag::cpu_, (A0)(X)
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
      ivtype d0 = divfloor(a0l, a1l);
      ivtype d1 = divfloor(a0h, a1h);
      return groups(d0, d1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divfloor_, tag::cpu_, (A0)(X)
                                   , ((simd_<floating_<A0>,X>))
                                     ((simd_<floating_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::floor(a0/a1);
    }
  };
} } }

#endif

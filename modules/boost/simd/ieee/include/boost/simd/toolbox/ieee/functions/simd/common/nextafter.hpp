//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEXTAFTER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEXTAFTER_HPP_INCLUDED
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/constants/eps_related.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/next.hpp>
#include <boost/simd/include/functions/prev.hpp>
#include <boost/simd/include/functions/is_finite.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/negif.hpp>
#include <boost/simd/include/functions/copysign.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nextafter_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return seladd(neq(a0,a1),a0,seladd(gt(a1,a0),Mone<A0>(),Two<A0>()));
      //      return sel(eq(a0, a1),  a0, sel(gt(a1,a0), oneplus(a0), minusone(a0))); 
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nextafter_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<unsigned_<A0>,X>))((simd_<unsigned_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return sel(boost::simd::is_equal(a0,a1),
         a0,
         sel(gt(a1,a0),a0+One<A0>(),a0-One<A0>()));
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nextafter_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<real_<A0>,X>))((simd_<real_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type itype;
      A0 m;
      itype expon;
      boost::fusion::tie(m, expon) = fast_frexp(a0);
      expon =  seladd(boost::simd::is_equal(m, Mhalf<A0>()), expon, Mone<itype>());
      A0 diff =  fast_ldexp(One<A0>(), expon-Nbdigits<A0>());
      diff = b_and(sel(is_eqz(diff)||is_eqz(a0),  Mindenormal<A0>(), diff), is_finite(a0));
      A0 r = copysign(sel(boost::simd::is_equal(a0, Minf<A0>()), Valmin<A0>(), a0), a0);
      diff   =  b_and(negif(gt(a0, a1), diff), is_not_equal(a0, a1));
      return r+diff;
      //      return sel(islt(a0, a1), next(a0), sel(iseq(a0, a1),  a0, prev(a0)));
    }
  };
} } }


#endif

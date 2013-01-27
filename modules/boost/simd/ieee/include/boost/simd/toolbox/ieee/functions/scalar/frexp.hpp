//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED
#include <boost/simd/toolbox/ieee/functions/frexp.hpp>
#include <boost/simd/include/functions/scalar/is_invalid.hpp>
#include <boost/simd/include/functions/scalar/bitwise_notand.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/shri.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2)
                            , (scalar_< double_<A0> >)
                              (scalar_< double_<A0> >)
                                     (scalar_< int64_<A2> >)
    )
  {
    typedef int result_type;
    inline int operator()(A0 const& a0,A0 & r0,A2 & r1) const
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type      int_type;
      if (a0 == 0 || is_invalid(a0))
      {
        r0 = a0;
        r1 = Zero<A2>();
        return 0;
      }
      else
      {
        const int_type me = Maxexponent<A0>()-1;
        const int_type nmb= Nbmantissabits<A0>();
        const int_type n1 = ((2*me+3)<<nmb);
        const int_type n2 = me<<nmb;
        A0 ci_exp=simd::bitwise_cast<A0>(n1);
        r1 = simd::bitwise_cast<int_type>(b_and(ci_exp, a0));// extract exponent
        A0 x = b_notand(ci_exp, a0);                         // clear exponent in a0
        r1 = sub(shri(r1,nmb), me);                          // compute exponent
        r0 = b_or(x,n2);                                     // insert exponent+1 in x
        if (r1 > me) {r1 = 0; r0+= a0;}
        return 0;
      }
//       boost::simd::int32_t aa2 = 0;
//       a1 = ::frexp(a0, &aa2);
//       a2 =  aa2;
//       return 0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2)
                                     , (scalar_< floating_<A0> >)
                                     (scalar_< integer_<A2> >)
    )
  {
    typedef A0 result_type;
    inline A0 operator()(A0 const& a0,A2 & a2) const
    {
      A0 a1;
      frexp(a0, a1, a2);
      return a1;
//       boost::simd::int32_t aa2;
//       A0 aa1 = ::frexp(a0, &aa2);
//       a2 =  aa2;
//       return aa1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)
                                     , (scalar_< floating_<A0> >)
    )
  {
    typedef A0                                                      mantissa;
    typedef typename dispatch::meta::as_integer<A0,signed>::type    exponent;
    typedef boost::fusion::vector<mantissa,exponent>             result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      frexp(a0, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res));
      return res;
//       result_type res;
//       if (is_inf(a0))
//       {
//         boost::fusion::at_c<0>(res) = a0;
//         boost::fusion::at_c<1>(res) = 0;
//         return res;
//       }
//       boost::simd::int32_t r1t;
//       boost::fusion::at_c<0>(res) = ::frexp(a0, &r1t);
//       boost::fusion::at_c<1>(res) = r1t;
//       return res;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2),
                                     (scalar_< single_<A0> >)
                                     (scalar_< single_<A0> >)
                                     (scalar_< int32_<A2> >)
    )
  {
    typedef int result_type;
    inline int operator()(A0 const& a0,A0 & r0,A2 & r1) const
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type      int_type;
      if (a0 == 0 || is_invalid(a0))
      {
        r0 = a0;
        r1 = Zero<A2>();
        return 0;
      }
      else
      {
        const int_type me = Maxexponent<A0>()-1;
        const int_type nmb= Nbmantissabits<A0>();
        const int_type n1 = ((2*me+3)<<nmb);
        const int_type n2 = me<<nmb;
        A0 ci_exp=simd::bitwise_cast<A0>(n1);
        r1 = simd::bitwise_cast<int_type>(b_and(ci_exp, a0));// extract exponent
        A0 x = b_notand(ci_exp, a0);                         // clear exponent in a0
        r1 = sub(shri(r1,nmb), me);                          // compute exponent
        r0 = b_or(x,n2);                                     // insert exponent+1 in x
        if (r1 > me) {r1 = 0; r0+= a0;}
        return 0;
        //       if (is_inf(a0))
        //       {
        //         a2 = 0;
        //         a1 = a0;
        //       }
        //       else
        //         a1 = ::frexpf(a0, &a2);
        //       return 0;
      }
    }
  };

//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2)
//                             , (scalar_< single_<A0> >)
//                               (scalar_< int32_<A2> >)
//                             )
//   {
//     typedef A0 result_type;
//     inline result_type operator()(A0 const& a0,A2 & a2) const
//     {
//       if (is_inf(a0))
//       {
//         a2 = 0;
//         return a0;
//       }
//       return ::frexpf(a0, &a2);
//     }
//   };


//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)
//                             , (scalar_< single_<A0> >)
//                             )
//   {
//     typedef typename boost::dispatch::meta::as_floating<A0>::type mantissa;
//     typedef typename dispatch::meta::as_integer<A0,signed>::type                   exponent;
//     typedef boost::fusion::vector<mantissa,exponent>                            result_type;
//     BOOST_SIMD_FUNCTOR_CALL(1)
//     {
//       result_type res;
//       if (is_inf(a0))
//       {
//         boost::fusion::at_c<0>(res) = a0;
//         boost::fusion::at_c<1>(res) = 0;
//         return res;
//       }
//       boost::fusion::at_c<0>(res) = ::frexpf(a0, &boost::fusion::at_c<1>(res));
//       return res;
//     }
//   };
} } }

#endif

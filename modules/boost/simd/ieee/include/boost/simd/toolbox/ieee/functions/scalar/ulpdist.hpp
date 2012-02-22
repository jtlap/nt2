//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_ULPDIST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_ULPDIST_HPP_INCLUDED
#include <boost/simd/include/constants/eps.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/ldexp.hpp>
#include <boost/simd/include/functions/frexp.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/dist.hpp>
#include <boost/simd/include/functions/is_nan.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_
                                   , (A0)(A1)
                                   , (scalar_< arithmetic_<A0> >)
                                     (scalar_< arithmetic_<A1> >)
                             )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return ulpdist(A0(a0), A0(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return dist(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_
                            , (A0)
                            , (scalar_< bool_<A0> >)(scalar_< bool_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0^a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename boost::common_type<A0>::type type;
      typedef typename dispatch::meta::as_integer<A0>::type itype;
      if (a0 == a1)               return Zero<type>();
      if (is_nan(a0)&&is_nan(a1)) return Zero<type>();
      itype e1 = Zero<itype>(), e2 = Zero<itype>();
      type m1 = Zero<type>(), m2 = Zero<type>();
      boost::simd::frexp(a0, m1, e1);
      boost::simd::frexp(a1, m2, e2);
      itype expo = -boost::simd::max(e1, e2);
      A0 e = (e1 == e2) ? boost::simd::abs(m1-m2)
                            :   boost::simd::abs( boost::simd::ldexp(a0, expo)
                                                - boost::simd::ldexp(a1, expo)
                                                );
      A0 that = e/static_cast<A0>(Eps<type>());
      return that;
    }
  };
} } }


#endif

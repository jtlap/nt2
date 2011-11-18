//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_LDEXP_HPP_INCLUDED
#include <boost/simd/sdk/meta/size.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/functions/shli.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/is_finite.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/rshl.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::ldexp_, tag::cpu_,(A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<integer_<A1>,X>))
                                )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return rshl(a0, a1); }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ldexp_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return rshl(a0, a1); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::ldexp_, tag::cpu_,(A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , ((simd_<floating_<A0>,X>))
                                  ((simd_<integer_<A1>,X>))
                                )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename meta::scalar_of<result_type>::type             s_type;
      typedef typename dispatch::meta::as_integer<result_type, signed>::type  int_type;
      typedef typename meta::scalar_of<int_type>::type             sint_type;

      // clear exponent in x
      result_type const x = {b_andnot(a0, Ldexpmask<A0>())};

      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<A0>(), a0);
      e += shli(a1, Nbmantissabits<s_type>());
      return select( b_and(is_nez(a0),is_finite(a0))
                     , b_or(x, e)
                     , a0
                     );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ldexp_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type iA0; 
      return ldexp(a0, boost::simd::splat<iA0>(a1)); 
    }
  };
} } }

#endif

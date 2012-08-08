//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_MODULO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_MODULO_HPP_INCLUDED
#include <boost/simd/toolbox/operator/functions/modulo.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>

//////////////////////////////////////////////////////////////////////////////
// mixed scalar/simd modulo
//////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::modulo_, tag::cpu_,
                                    (A0)(A1)(X),
                                    ((simd_<arithmetic_ <A0>,X>))((scalar_<arithmetic_<A1> >))
                                   )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return boost::simd::modulo(a0, boost::simd::splat<A0>(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::modulo_, tag::cpu_,
                                     (A0)(A1)(X),
                                     ((scalar_<arithmetic_<A0> >))((simd_<arithmetic_<A1>,X>))
                                   )
  {
    typedef A1 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return boost::simd::modulo(boost::simd::splat<A1>(a0), a1);
    }
  };
} } }

#endif

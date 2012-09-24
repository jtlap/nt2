//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_SATURATE_HPP_INCLUDED

#include <boost/simd/toolbox/ieee/functions/saturate.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // Trivial case int/xxx : Just compare over Valmax/Valmin after conversion
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)
                                    , (scalar_<int_<A0> >)
                                      (target_< generic_<integer_<T> > >)
                                    )
  {
    typedef A0                                              result_type;
    typedef typename meta::scalar_of<T>::type               target_t;
    typedef typename boost::common_type<A0,target_t>::type  base_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      base_t a00 = static_cast<base_t>(a0);
      if      (a00 > Valmax<target_t>()) return result_type(Valmax<target_t>());
      else if (a00 < Valmin<target_t>()) return result_type(Valmin<target_t>());
      else                               return a0;
    }
  };

  //============================================================================
  // Trivial case uint/uint : Just compare over Valmax
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)
                                    , (scalar_<uint_<A0> >)
                                      (target_< generic_<uint_<T> > >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<T>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      return (a0 > Valmax<target_t>()) ? result_type(Valmax<target_t>()) : a0;
    }
  };

  //============================================================================
  // For uint/int, do the comparison after casting Valmax<T> to the unsigned
  // type to avoid warnings.
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)
                                    , (scalar_<uint_<A0> >)
                                      (target_< generic_<int_<T> > >)
                                    )
  {
    typedef A0                                result_type;
    typedef typename meta::scalar_of<T>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      A0 a00 = static_cast<A0>(Valmax<target_t>());
      return (a0 > a00) ? a00 : a0;
    }
  };
} } }

#endif

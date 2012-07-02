//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SATURATE_HPP_INCLUDED

#include <boost/simd/toolbox/ieee/functions/saturate.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)(X)
                                    , ((simd_<int_<A0>,X>))
                                      (target_< generic_<arithmetic_<T> > >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<T>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      const A0 vma = splat<A0>(Valmax<target_t>());
      const A0 vmi = splat<A0>(Valmin<target_t>());
      return select(gt(a0, vma), vma, select(lt(a0, vmi), vmi, a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)(X)
                                    , ((simd_<uint_<A0>,X>))
                                      (target_< generic_<integer_<T> > >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<T>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      const A0 vma = splat<A0>(Valmax<target_t>());
      return select(gt(a0, vma), vma, a0);
    }
  };
} } }

#endif

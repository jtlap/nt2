//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_SATURATE_HPP_INCLUDED

#include <boost/simd/ieee/functions/saturate.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)(X)
                                    , ((simd_< arithmetic_<A0>,X>))
                                      (target_< generic_<arithmetic_<T> > >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<T>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      result_type that;
      for(std::size_t i=0; i!=result_type::static_size; ++i)
        that[i] = saturate<target_t>(a0[i]);
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)(X)
                                    , ((simd_< floating_<A0>,X>))
                                      (target_< generic_<floating_<T> > >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<T>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)(X)
                                    , ((simd_<signed_<A0>,X>))
                                      (target_< generic_<integer_<T> > >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<T>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      const A0 vma = splat<A0>(Valmax<target_t>());
      const A0 vmi = splat<A0>(Valmin<target_t>());
      return min(vma, max(vmi, a0));
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
      return min(a0, vma);
    }
  };
} } }

#endif

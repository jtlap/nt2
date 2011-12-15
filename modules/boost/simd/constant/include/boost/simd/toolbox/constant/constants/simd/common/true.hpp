//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SIMD_COMMON_TRUE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SIMD_COMMON_TRUE_HPP_INCLUDED
#include <boost/simd/toolbox/constant/constants/true.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::True, tag::cpu_, (A0)(X)
                                    , ((target_< simd_< logical_<A0>,X> >))
                                    )
  {
    typedef typename A0::type                                       result_type;
    typedef typename result_type::value_type::value_type            base_type;
    typedef typename result_type::template rebind<base_type>::type  target_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return bitwise_cast<result_type>(Allbits<target_type>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::True, tag::cpu_, (A0)(X)
                                    , ((target_< simd_< arithmetic_<A0>,X> >))
                                    )
  {
    typedef typename A0::type base_type;
    typedef typename meta::as_logical<base_type>::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const& ) const
    {
      return True<result_type>();
    }
  };
} } }

#endif

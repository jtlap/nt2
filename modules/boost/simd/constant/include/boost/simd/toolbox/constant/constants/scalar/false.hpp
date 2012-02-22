//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SCALAR_FALSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SCALAR_FALSE_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::False, tag::cpu_, (A0)
                                    , ((target_< scalar_< logical_<A0> > >))
                                    )
  {
    typedef typename A0::type                                       result_type;
    typedef typename result_type::value_type                          base_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return result_type(false);
    }
  };
   BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::False, tag::cpu_, (A0)
                                    , ((target_< scalar_< arithmetic_<A0> > >))
                                    )
  {
    typedef typename A0::type                            base_type;
    typedef typename meta::as_logical<base_type>::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return result_type(false);
    }
  };
} } }

#endif

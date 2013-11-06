//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_IMPL_CONSTANT_TYPE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_IMPL_CONSTANT_TYPE_HPP_INCLUDED

#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

namespace boost { namespace simd { namespace details
{
  // Gather all constant type computation requested by pure_constant
  // implementations
  template<typename A0, typename Tag>
  struct constant_type
  {
    typedef typename A0::type                                       target_type;
    typedef typename dispatch::meta::scalar_of<target_type>::type   base_type;
    typedef typename dispatch::meta::property_of<base_type>::type   disp_type;
    typedef typename boost::mpl::apply<Tag,disp_type>::type         value_type;
    typedef typename meta::vector_of< typename value_type::value_type
                                    , target_type::static_size
                                    >::type                         type;
  };
} } }

#endif

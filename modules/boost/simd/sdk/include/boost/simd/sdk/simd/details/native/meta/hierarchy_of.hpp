/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_HIERARCHY_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_HIERARCHY_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/property_of.hpp>

namespace boost { namespace dispatch { namespace details
{
  template<class Scalar,class Extension, class Origin>
  struct hierarchy_of< simd::native<Scalar,Extension>, Origin >
  {
    typedef meta::simd_ < typename meta::
                          hierarchy_of< Scalar
                                      , Origin
                                      >::type::base
                        , Extension
                        >                                   type;
  };

  template<class Scalar,class Extension, class Origin>
  struct  property_of< simd::native<Scalar,Extension>, Origin >
        : property_of< Scalar, Origin > {};
} } }

#endif

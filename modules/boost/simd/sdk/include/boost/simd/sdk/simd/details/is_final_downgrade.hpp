//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_IS_FINAL_DOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_IS_FINAL_DOWNGRADE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

namespace boost { namespace simd { namespace details
{
  template<typename Type>
  struct  is_final_downgrade
        : boost::mpl::bool_< sizeof(Type) == 1 >
  {
  };

  template<>
  struct  is_final_downgrade<float>
        : boost::mpl::true_
  {
  };
} } }

#endif

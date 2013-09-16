//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_REGISTER_COUNT_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_REGISTER_COUNT_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/simd/sdk/simd/extensions/extensions.hpp>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief SIMD register file size

    Return an @mplint containing the current architecture SIMD register file
    size.

    @par Models:

    @mplint
  **/
  struct  register_count
        : boost::mpl::size_t<BOOST_SIMD_REGISTERS_COUNT>
  {};
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_DOWNGRADE_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/meta/is_final_downgrade.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace dispatch { namespace ext
{
  // Extension point for downgrade on pack<T,N>
  template<class T, std::size_t N, class Sign>
  struct downgrade< simd::pack<T,N>
                  , Sign
                  , typename  boost::disable_if
                              < simd::meta::
                                is_final_downgrade
                                  < typename meta::primitive_of<T>::type
                                  , typename simd::pack<T,N>::data_type::extension_type
                                  >
                              >::type
                  >
  {
    typedef typename downgrade<T, Sign>::type dT;
    typedef boost::simd::pack<dT, N*2> type;
  };

} } }

#endif

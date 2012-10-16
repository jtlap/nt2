//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_MAKE_SOA_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_MAKE_SOA_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_as.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    // Compute maximum cardinal in a sequence
    template<class T, class X>
    struct  max_cardinal_
          : meta::cardinal_as< typename max_value< T, meta::cardinal_as<mpl::_, X> >::type, X >::type
    {};

    // Build the sequence of proper native
    template<class T, class X>
    struct make_soa
    {
      template<class Sig>
      struct result;

      template<class This, class U>
      struct result<This(U)>
      {
        typedef typename meta::vector_of<U, max_cardinal_<T, X>::value>::type type;
      };
    };
  }
} }

#endif

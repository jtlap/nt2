//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_PAD_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_PAD_HPP_INCLUDED

/**
 * \file
 * \brief Define the nt2::pad function
**/

#include <nt2/sdk/meta/as.hpp>

namespace nt2
{
  namespace tag { struct padded_sequence_tag {}; }

  namespace details
  {
    template<typename T, typename Sequence, typename Strategy>
    struct padded_sequence
    {
      typedef tag::padded_sequence_tag  fusion_tag;
      typedef meta::as_<T>              value_type;
      typedef Sequence                  sequence_type;
      typedef Strategy                  strategy_type;

      padded_sequence( Sequence const& seq): seq_(seq) {}

      sequence_type const&  seq_;
    };
  }

  template<typename T,typename Sequence, typename Strategy>
  inline details::padded_sequence<T,Sequence const,Strategy>
  pad( Sequence const& seq, Strategy const& )
  {
    details::padded_sequence<T,Sequence const,Strategy> that(seq);
    return that;
  }
}

#include <nt2/core/utility/of_size/pad_fusion.hpp>

#endif

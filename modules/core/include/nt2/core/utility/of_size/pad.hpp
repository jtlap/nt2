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

namespace nt2
{
  namespace tag { struct padded_sequence_tag {}; }
  
  namespace details
  {
    template<typename Sequence, typename Value>
    struct padded_sequence
    {
      typedef tag::padded_sequence_tag fusion_tag;
      typedef Sequence  sequence_type;
      typedef Value     value_type;
          
      padded_sequence ( Sequence const& seq, Value const& v)
                      : seq_(seq), value_(v) {}

      sequence_type const&  seq_;
      value_type            value_;
    };
  }

  template<typename Sequence, typename Value>
  inline details::padded_sequence<Sequence,Value>
  pad( Sequence const& seq, Value const& v )
  {
    details::padded_sequence<Sequence,Value> that(seq,v);
    return that;
  }
}

#include <nt2/core/utility/of_size/pad_fusion.hpp>

#endif

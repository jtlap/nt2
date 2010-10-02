//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_CONCEPT_FUSION_BIDIRECTIONNAL_SEQUENCE_HPP_INCLUDED
#define NT2_SDK_CONCEPT_FUSION_BIDIRECTIONNAL_SEQUENCE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Boost.Fusion Forward Sequence concept
// Documentation:
// http://www.boost.org/doc/libs/release/libs/fusion/doc/html/fusion/sequence/concepts/bidirectional_sequence.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/error/concepts.hpp>
#include <boost/fusion/include/back.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/concepts/fusion_forward_sequence.hpp>

namespace nt2
{
  template<class S>
  struct  FusionBidirectionalSequence
        : FusionForwardSequence<S>
  {
    typedef typename boost::fusion::result_of::back<S>::type back_type;
    BOOST_CONCEPT_USAGE(FusionBidirectionalSequence)
    {
      back_type b = back(s);
      details::ignore_unused(b);
    }

    private:
    S s;
  };
}

#endif

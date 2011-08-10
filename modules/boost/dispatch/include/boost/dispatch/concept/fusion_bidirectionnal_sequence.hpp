//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_DISPATCH_CONCEPT_FUSION_BIDIRECTIONNAL_SEQUENCE_HPP_INCLUDED
#define BOOST_DISPATCH_CONCEPT_FUSION_BIDIRECTIONNAL_SEQUENCE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Boost.Fusion Forward Sequence concept
// Documentation:
// http://www.boost.org/doc/libs/release/libs/fusion/doc/html/fusion/sequence/concepts/bidirectional_sequence.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/error/concepts.hpp>
#include <boost/fusion/include/back.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>
#include <boost/dispatch/concepts/fusion_forward_sequence.hpp>

namespace boost { namespace dispatch
{
  template<class S>
  struct  FusionBidirectionalSequence
        : FusionForwardSequence<S>
  {
    typedef typename boost::fusion::result_of::back<S>::type back_type;
    BOOST_CONCEPT_USAGE(FusionBidirectionalSequence)
    {
      back_type b = back(s);
      ignore_unused(b);
    }

    private:
    S s;
  };
} }

#endif

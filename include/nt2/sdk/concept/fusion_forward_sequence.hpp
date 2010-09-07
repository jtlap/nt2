/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONCEPT_FUSION_FORWARD_SEQUENCE_HPP_INCLUDED
#define NT2_SDK_CONCEPT_FUSION_FORWARD_SEQUENCE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Boost.Fusion Forward Sequence concept
// Documentation:
// http://www.boost.org/doc/libs/release/libs/fusion/doc/html/fusion/sequence/concepts/forward_sequence.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/error/concepts.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/front.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>

namespace nt2
{
  template<class S> struct FusionForwardSequence
  {
    typedef typename boost::fusion::result_of::begin<S>::type begin_type;
    typedef typename boost::fusion::result_of::end<S>::type   end_type;
    typedef typename boost::fusion::result_of::size<S>::type  size_type;
    typedef typename boost::fusion::result_of::empty<S>::type empty_type;
    typedef typename boost::fusion::result_of::front<S>::type front_type;

    BOOST_CONCEPT_USAGE(FusionForwardSequence)
    {
      begin_type  b   = boost::fusion::begin(s);
      end_type    e   = boost::fusion::end(s);
      front_type  f   = boost::fusion::front(s);
                  sz  = boost::fusion::size(s);
                  y   = boost::fusion::empty(s);

      details::ignore_unused(f);
    }

    private:
    S s;
    size_type   sz;
    empty_type  y;
  };
}

#endif

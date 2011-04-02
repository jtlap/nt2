/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONCEPT_FUSION_ASSOCIATIVE_SEQUENCE_HPP_INCLUDED
#define NT2_SDK_CONCEPT_FUSION_ASSOCIATIVE_SEQUENCE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Boost.Fusion Associative Sequence concept
// Documentation:
// http://www.boost.org/doc/libs/release/libs/fusion/doc/html/fusion/sequence/concepts/associative_sequence.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/error/concepts.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/include/has_key.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>

namespace nt2
{
  template<class S> struct FusionAssociativeSequence
  {
    typedef typename boost::fusion::result_of::has_key<S,void>::type  has_type;
    typedef typename boost::fusion::result_of::at_key<S,void>::type   at_type;

    BOOST_CONCEPT_USAGE(FusionAssociativeSequence)
    {
              h = boost::fusion::has_key<void>(s);
      at_type a = boost::fusion::at_key<void>(s);
      details::ignore_unused(a);
    }

    private:
    S s;
    has_type h;
  };
}

#endif

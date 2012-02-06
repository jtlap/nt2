//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_COLON_COLON_HPP_INCLUDED
#define NT2_CORE_CONTAINER_COLON_COLON_HPP_INCLUDED

#include <nt2/include/functions/colon.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace nt2 { namespace container
{
  //==========================================================================
  // colon_ is an helper class that handles the _ placeholders behavior
  //==========================================================================
  struct colon_
  {
    // colon_ acts as an anything-goes sink for tie
    template<class T> colon_ const& operator=(T const&) const { return *this; }

    // colon also acts as : generator
    template<class Begin, class End>
    typename meta::call<nt2::tag::colon_(Begin,End)>::type
    operator()(Begin const& b, End const& e) const
    {
      return nt2::colon(b,e);
    }

    template<class Begin, class Step, class End>
    typename meta::call<nt2::tag::colon_(Begin,Step,End)>::type
    operator()(Begin const& b, Step const& s, End const& e) const
    {
      return nt2::colon(b,s,e);
    }
  };
} }

namespace nt2
{
  //==========================================================================
  /*!
   * _ is a multi-purpose placeholder in \nt2:
   *
   *   - it acts as \matlab \c : in indexing expression
   *   - it enables \c :(b,s,e) to mimic \matlab \c b:s:e iota notation
   *   - it acts as a sink in tie expressions
   **/
  //==========================================================================
  container::colon_ const _ = {};
}

#endif

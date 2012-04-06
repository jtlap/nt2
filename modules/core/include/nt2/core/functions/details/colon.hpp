//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_COLON_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // colon actual functor : precompute step and just iterate over
  //============================================================================
  template<class T> struct colon
  {
    colon() {}
    colon( T const& l, T const& s) : lower_(l), step_(s) {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;
      return nt2::fma ( nt2::enumerate<type>(p)
                      , nt2::splat<type>(step_)
                      , nt2::splat<type>(lower_)
                      );
    }

    T lower_, step_;
  };

  //============================================================================
  // unity_colon actual functor : just forward form lower bound
  //============================================================================
  template<class T> struct unity_colon
  {
    unity_colon() {}
    unity_colon( T const& l ) : lower_(l) {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;
      return  nt2::enumerate<type>(p+lower_);
    }

    T lower_;
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_GENERATIVE_CONSTANT_ADAPTOR_HPP_INCLUDED
#define NT2_CORE_UTILITY_GENERATIVE_CONSTANT_ADAPTOR_HPP_INCLUDED

#include <boost/dispatch/functor/meta/make_functor.hpp>

namespace nt2 { namespace details
{
  template<class Functor> struct constant_generator
  {
    template<class Pos, class Size, class Target> typename Target::type
    operator()(Pos const&, Size const&, Target const& t) const
    {
      typename boost::dispatch::make_functor<Functor,Target>::type callee;
      return callee(t);
    }
  };
} }

#endif


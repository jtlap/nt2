//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_CONSTANT_ADAPTOR_HPP_INCLUDED
#define NT2_SDK_META_CONSTANT_ADAPTOR_HPP_INCLUDED

/*!
  @file
  @brief Define the constant_ fucntor adaptor
**/

#include <boost/dispatch/functor/meta/make_functor.hpp>

namespace nt2 { namespace meta
{
  /*!
    @brief Adapt a tag to be a constant-compliant functor

    Generative functions require its embedded functor to have a very specific
    interface:
      * it exposes a result_type that contains the value expected as an output
      * a ternary operator() taking a Position,Size and actual Target that
        computes the actual value to store.
   **/
  template<class Functor, class Base> struct constant_
  {
    typedef typename boost::dispatch::make_functor<Functor,Base>::type f_t;
    typedef typename meta::call<Functor(meta::as_<Base>)>::type   result_type;

    template<class Pos, class Size, class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const&, Size const&, Target const& t) const
    {
      return f_t()(t);
    }
  };
} }

#endif

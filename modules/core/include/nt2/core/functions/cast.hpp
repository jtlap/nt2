//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CAST_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CAST_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct cast_ : ext::elementwise_<cast_>
    {
      typedef ext::elementwise_<cast_> parent;
    };
  }

  template<class T, class A0>
  BOOST_FORCEINLINE
  typename meta::call<tag::cast_(A0 const&, meta::as_<T> const&)>::type
  cast(A0 const& a0)
  {
    return typename make_functor<tag::cast_, A0>::type()(a0, meta::as_<T>());
  }
}

#endif

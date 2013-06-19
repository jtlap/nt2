//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MAGMA_MAGMA_HPP_INCLUDED
#define NT2_SDK_MAGMA_MAGMA_HPP_INCLUDED

#include <boost/dispatch/functor/forward.hpp>

namespace nt2 { namespace tag
{
  template<class T> struct magma_ : T
  {
    typedef T parent;
  };
} }

#ifdef NT2_USE_MAGMA
BOOST_DISPATCH_COMBINE_SITE( nt2::tag::magma_<tag::cpu_> )
#endif

#endif

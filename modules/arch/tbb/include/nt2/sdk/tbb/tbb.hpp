//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_TBB_HPP_INCLUDED
#define NT2_SDK_TBB_TBB_HPP_INCLUDED

#include <boost/dispatch/functor/forward.hpp>

namespace nt2 { namespace tag
{
  template<class T> struct tbb_ : T
  {
    typedef T parent;
  };
} }

BOOST_DISPATCH_COMBINE_SITE( nt2::tag::tbb_<tag::cpu_> )
#include <tbb/tbb.h>

#endif

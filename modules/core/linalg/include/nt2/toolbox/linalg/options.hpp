//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_OPTIONS_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_OPTIONS_HPP_INCLUDED

#include <nt2/sdk/meta/policy.hpp>

namespace nt2
{
  namespace ext
  {
    struct pivot_     : boost::mpl::true_   {};
    struct no_pivot_  : boost::mpl::false_  {};
    struct matrix_    : boost::mpl::true_   {};
    struct vector_    : boost::mpl::false_  {};
  }

  nt2::policy<ext::pivot_>     const pivot_;
  nt2::policy<ext::no_pivot_>  const no_pivot_;
  nt2::policy<ext::matrix_>    const matrix_;
  nt2::policy<ext::vector_>    const vector_;
}

#endif

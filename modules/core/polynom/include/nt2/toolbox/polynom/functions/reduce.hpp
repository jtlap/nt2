//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_REDUCE_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_REDUCE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/**
 * @brief Perform polynomial format reduction
 *
 *   reduce(p) returns the same polynomial as the input insuring
 *   that the first element of the polynomial is non zero (or the
 *   polynomial is empty)
 *   The second parameter is a relative threshold on what can be considered as zero
 *   (neglectable) or an overflow threshold _ that consider that iteratively from
 *   first index p(i) is neglectable if any p(j)/pi() is infinite.
 *
 **/
namespace nt2 { namespace tag
  {
    struct reduce_: ext::elementwise_<reduce_> { typedef ext::elementwise_<reduce_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::reduce_,reduce, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::reduce_,reduce, 2)
}
#endif

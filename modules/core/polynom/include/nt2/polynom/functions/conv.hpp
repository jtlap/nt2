//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_CONV_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_CONV_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2 {  namespace tag
  {
    struct conv_ :  ext::unspecified_<conv_>
    {
      typedef ext::unspecified_<conv_>  parent;
    };
  }

  /**
   * @brief Perform characteristic conv computation
   *
   * convolves vectors a and b.  the resulting vector is
   * numel max(cons(numel(a)+numel(b)-1,numel(a),numel(b))). if a and b are
   * vectors of polynomial coefficients, convolving them is almost
   * equivalent to multiplying the two polynom.
   *
   * c = conv(a, b, shape) returns a subsection of the convolution with size
   * specified by shape:
   *   'f'  - (default) returns the 'full' convolution,
   *   's'  - returns the central part of the convolution
   *             that is the 'same' size as a.
   *   'v' - returns only those ('valid') parts of the convolution
   *             that are computed without the zero-padded edges.
   *             numel(c) is max(numel(a)-max(0,numel(b)-1),0).
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::conv_, conv, 2)

}

#endif

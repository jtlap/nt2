//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTIONS_TCHEBEVAL_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTIONS_TCHEBEVAL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    struct tchebeval_ : ext::elementwise_<tchebeval_> { typedef ext::elementwise_<tchebeval_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::tchebeval_, tchebeval, 2)
}


#endif

// modified by jt the 25/12/2010

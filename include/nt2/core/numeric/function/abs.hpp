/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_NUMERIC_FUNCTION_ABS_HPP_INCLUDED
#define NT2_CORE_NUMERIC_FUNCTION_ABS_HPP_INCLUDED

//#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
//#include <nt2/core/numeric/preprocessor/include.hpp>

namespace nt2
{
  namespace functors
  {
    struct abs_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION( functors::abs_, abs, 1)
}

#include <nt2/core/numeric/function/details/scalar/abs.hpp>
//#include NT2_INCLUDE(abs.hpp)

#endif

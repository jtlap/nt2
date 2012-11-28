//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ELSE_ZERO_HPP_INCLUDED
#define NT2_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ELSE_ZERO_HPP_INCLUDED
#include <boost/simd/toolbox/boolean/functions/if_else_zero.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Bring the tag if_else_zero_ of functor if_else_zero
     *        in namespace nt2::tag for toolbox nt2.boolean
    **/
    using boost::simd::tag::if_else_zero_;
  }

  using boost::simd::if_else_zero;
  using boost::simd::ifelsezero;
  using boost::simd::ifnot_zero_else;
  using boost::simd::ifnotzeroelse;
}
#endif

// modified by jt the 25/12/2010

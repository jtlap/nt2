/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGONOMETRIC_SELECTION_TAGS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGONOMETRIC_SELECTION_TAGS_HPP_INCLUDED
#include <boost/mpl/bool.hpp>

namespace nt2
{


  // tags allowing to choose angle unit in trigonometric functions
  struct radian_tag{};
  struct degree_tag{};
  struct pi_tag{};

  // tags allowing to choose computation standard for trigonometric and/or exponential functions
  struct fast_tag{};        // extra-speed
                            // but very small validity range with trigo
                            //     no rouding for exp2(n) or exp10(n) if n is a flint
  struct accu_tag{};        // full range and precision at expanse of slowness
  struct trig_tag{};        // nt2 implementation choices

 // tags allowing to choose log and exp bases in exponential functions
  struct natural_tag{};
  struct two_tag{};
  struct ten_tag{};
}


#endif

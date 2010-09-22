/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_NUMERIC_FUNCTION_DETAILS_SCALAR_IMPL_MISC_SELECTION_TAGS_HPP_INCLUDED
#define NT2_CORE_NUMERIC_FUNCTION_DETAILS_SCALAR_IMPL_MISC_SELECTION_TAGS_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

namespace nt2
{
  typedef boost::mpl::false_ not_simd_type;
  typedef boost::mpl::true_      simd_type;

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

// /////////////////////////////////////////////////////////////////////////////
// End of selection_tags.hpp
// /////////////////////////////////////////////////////////////////////////////

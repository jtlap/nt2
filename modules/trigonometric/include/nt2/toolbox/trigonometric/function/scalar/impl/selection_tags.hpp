/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_SELECTION_TAGS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_SELECTION_TAGS_HPP_INCLUDED
#include <nt2/toolbox/common/tags.hpp>

namespace nt2
{
  // tags allowing to choose angle unit in trigonometric functions
  struct radian_tag{};
  struct degree_tag{};
  struct pi_tag{};

  struct trig_tag{};        // nt2 implementation speed choice for trigo obsolete ?

  struct small{};          //cephes
  struct medium{};         //fdlibm medium
  struct big{};            //big complete reduction
  struct direct_small{};
  struct direct_medium{};   
  struct direct_big{};   
  struct clipped_pio4{};
  struct clipped_small{};   
  struct clipped_medium{};   
}


#endif

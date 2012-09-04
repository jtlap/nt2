/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_SELECTION_TAGS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_SELECTION_TAGS_HPP_INCLUDED
#include <nt2/sdk/meta/tags.hpp>

namespace nt2
{
  struct fast{};
  struct regular{}; 
  // tags allowing to choose angle unit in trigonometric functions
  struct radian_tag{};
  struct degree_tag{};
  struct pi_tag{};

  struct trig_tag{};        // nt2 implementation speed choice for trigo obsolete ?

  struct verysmall     { typedef regular type; };          //abs less tan pi/2
  struct small_        { typedef regular type; };          //cephes
  struct medium        { typedef regular type; };          //fdlibm medium
  struct big           { typedef regular type; };          //big complete reduction
  struct direct_small  { typedef regular type; };
  struct direct_medium { typedef regular type; };   
  struct direct_big    { typedef regular type; };   
  struct clipped_pio4  { typedef fast    type; };
  struct clipped_small { typedef regular type; };   
  struct clipped_medium{ typedef regular type; };   
}


#endif

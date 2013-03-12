//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_SELECTION_TAGS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_SELECTION_TAGS_HPP_INCLUDED
#include <nt2/sdk/meta/tags.hpp>

namespace nt2
{
  struct fast       {};
  struct regular    {};

  // tags allowing to choose angle unit in trigonometric functions
  struct radian_tag {};
  struct degree_tag {};
  struct pi_tag     {};

  struct trig_tag {};        // nt2 implementation speed choice for trigo obsolete ?

  struct very_small_       { typedef regular type; };          //abs less tan pi/2
  struct small_           { typedef regular type; };          //cephes
  struct medium_          { typedef regular type; };          //fdlibm medium_
  struct big_             { typedef regular type; };          //big_ complete reduction
  struct direct_small_    { typedef regular type; };
  struct direct_medium_   { typedef regular type; };
  struct direct_big_      { typedef regular type; };
  struct clipped_pio4_    { typedef fast    type; };
  struct clipped_small_   { typedef regular type; };
  struct clipped_medium_  { typedef regular type; };
}


#endif

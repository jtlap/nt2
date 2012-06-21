//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DISPLAY_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DISPLAY_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::display function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct display_ : tag::formal_
    {
      typedef tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::display_,display,1)
  NT2_FUNCTION_IMPLEMENTATION(tag::display_,display,2)
}


//============================================================================
// All-in-one NT2_DISP macro
//============================================================================
#define NT2_DISPLAY(x) ::nt2::display(BOOST_PP_STRINGIZE(x),x)

#endif

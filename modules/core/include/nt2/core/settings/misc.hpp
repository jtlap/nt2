/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_SETTINGS_MISC_HPP_INCLUDED 
#define NT2_CORE_SETTINGS_MISC_HPP_INCLUDED 

namespace nt2
{
  //============================================================================
  /*! 
   *  Generic settings used to specify current composite settings use a 
   *  default behavior.
   **/
  //============================================================================
  struct none_ {};

  //============================================================================
  /*! 
   *  Generic settings used to pass a numeric value to other composite settings.
   **/
  //============================================================================
  template<std::ptrdiff_t N>
  struct with_{};
}

#endif

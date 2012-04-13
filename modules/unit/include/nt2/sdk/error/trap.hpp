//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_TRAP_HPP_INCLUDED
#define NT2_SDK_ERROR_TRAP_HPP_INCLUDED

/**
* @file
* @brief Provides portable, conditionnal breakpoint traps
**/

#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/config/attributes.hpp>
#include <nt2/sdk/error/details/trap.hpp>

namespace nt2
{
  /**
  * @brief Runtime conditionnal breakpoint trap
  *
  * If @c cond evaluates to true, triggers a breakpoint trap.
  *
  * @param cond Conditionnal trigger for the breakpoint trap
  **/
  NT2_FORCE_INLINE void trap(bool cond) { if(!cond) NT2_DEBUG_TRAP(); }

  /**
  * @brief Runtime inconditionnal breakpoint trap
  *
  * Triggers a breakpoint trap.
  **/
  NT2_FORCE_INLINE void trap() { NT2_DEBUG_TRAP(); }

  /**
  * @brief Compile-time conditionnal breakpoint trap
  *
  * If @c Condition::value evaluates true, triggers a breakpoint trap.
  *
  * @tparam Condition Compile-time boolean integral constant
  **/
  template<class Condition>
  NT2_FORCE_INLINE void
  trap( typename boost::enable_if_c<Condition::value>::type* = 0 )
  {
    NT2_DEBUG_TRAP();
  }

#if !defined(DOXYGEN_ONLY)
  template<class Condition> NT2_FORCE_INLINE
  void trap( typename boost::disable_if_c<Condition::value>::type* = 0 ) {}
#endif
}

#endif

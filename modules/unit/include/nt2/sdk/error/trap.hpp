//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_TRAP_HPP_INCLUDED
#define NT2_SDK_ERROR_TRAP_HPP_INCLUDED

/*!
 * \file
 * \brief Implement a cross-platform system for conditionnal breakpoint traps
 */

#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/config/attributes.hpp>
#include <nt2/sdk/error/details/trap.hpp>

namespace nt2
{

  //==============================================================================
  /*!
   * \ingroup error
   * If \c cond is true, triggers a breakpoint trap.
   *
   * \param cond Runtime boolean value
   */
  //==============================================================================
  NT2_FORCE_INLINE void trap(bool cond) { if(!cond) NT2_DEBUG_TRAP(); }

  //==============================================================================
  /*!
   * \ingroup error
   * Triggers a breakpoint trap unconditionnaly
   */
  //==============================================================================
   NT2_FORCE_INLINE void trap()          { NT2_DEBUG_TRAP();           }

   //==============================================================================
   /*!
    * \ingroup error
    * If \c Condition::value is true, triggers a breakpoint trap.
    *
    * \tparam Condition Compile-time boolean integral constant
    */
   //==============================================================================
  template<class Condition> NT2_FORCE_INLINE
  void trap( typename boost::enable_if_c<Condition::value>::type* = 0 )
  {
    NT2_DEBUG_TRAP();
  }

  template<class Condition> NT2_FORCE_INLINE
  void trap( typename boost::disable_if_c<Condition::value>::type* = 0) {}
}

#endif

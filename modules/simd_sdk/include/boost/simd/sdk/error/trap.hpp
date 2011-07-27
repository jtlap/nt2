//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_ERROR_TRAP_HPP_INCLUDED
#define BOOST_SIMD_SDK_ERROR_TRAP_HPP_INCLUDED

/*!
 * \file
 * \brief Implement a cross-platform system for conditionnal breakpoint traps
 */

#include <boost/utility/enable_if.hpp>
#include <boost/simd/sdk/config/attributes.hpp>
#include <boost/simd/sdk/error/details/trap.hpp>

namespace boost { namespace simd
{

  //==============================================================================
  /*!
   * \ingroup error
   * If \c cond is true, triggers a breakpoint trap.
   *
   * \param cond Runtime boolean value
   */
  //==============================================================================
  BOOST_SIMD_FORCE_INLINE void trap(bool cond) { if(!cond) BOOST_SIMD_SDK_DEBUG_TRAP(); }

  //==============================================================================
  /*!
   * \ingroup error
   * Triggers a breakpoint trap unconditionnaly
   */
  //==============================================================================
   BOOST_SIMD_FORCE_INLINE void trap()          { BOOST_SIMD_SDK_DEBUG_TRAP();           }

   //==============================================================================
   /*!
    * \ingroup error
    * If \c Condition::value is true, triggers a breakpoint trap.
    *
    * \tparam Condition Compile-time boolean integral constant
    */
   //==============================================================================
  template<class Condition> BOOST_SIMD_FORCE_INLINE
  void trap( typename boost::enable_if_c<Condition::value>::type* = 0 )
  {
    BOOST_SIMD_SDK_DEBUG_TRAP();
  }

  template<class Condition> BOOST_SIMD_FORCE_INLINE
  void trap( typename boost::disable_if_c<Condition::value>::type* = 0) {}
} }

#endif

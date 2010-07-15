/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_TRAP_HPP_INCLUDED
#define NT2_SDK_ERRORS_TRAP_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Template based SIGTRAP emitter
// Documentation: http://nt2.lri.fr/sdk/errors/trap.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/errors/details/trap.hpp>

namespace nt2 { namespace sys
{
  template<class Condition> static inline
  typename boost::enable_if_c<Condition::value>::type trap()
  {
    NT2_DEBUG_TRAP();
  }

  template<class Condition> static inline
  typename boost::disable_if_c<Condition::value>::type trap() {}
} }

#endif

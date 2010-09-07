/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_CALL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// User-overloadable call meta-function
// Documentation:http://nt2.lri.fr/extension/custom_function.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/unknown.hpp>
#include <nt2/sdk/error/static_assert.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Call to non-categorizable types ends up in error
  //////////////////////////////////////////////////////////////////////////////
  template<class Function,class I>
  struct call<Function,tag::unknown,I>
  {
    NT2_STATIC_ASSERT( (false), UNIMPLEMENTED_FUNCTOR, (Function) );
  };
} }

#endif

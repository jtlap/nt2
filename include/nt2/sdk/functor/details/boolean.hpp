/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_BOOLEAN_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_BOOLEAN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// boolean operators implementation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

#define NT2_MAKE_BOOLEAN(TAG,N,IMPL)                                \
template<class Category,class Info> struct call<TAG,Category,Info>  \
{                                                                   \
  typedef bool result_type;                                         \
  NT2_FUNCTOR_CALL(N) { return IMPL; }                              \
}                                                                   \
/**/

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Generating implemetnation from the macro
  //////////////////////////////////////////////////////////////////////////////
  NT2_MAKE_BOOLEAN(logical_not_       , 1,(!a0)     );
  NT2_MAKE_BOOLEAN(is_equal_          , 2,(a0 == a1));
  NT2_MAKE_BOOLEAN(is_not_equal_      , 2,(a0 != a1));
  NT2_MAKE_BOOLEAN(is_less_           , 2,(a0 <  a1));
  NT2_MAKE_BOOLEAN(is_greater_        , 2,(a0 >  a1));
  NT2_MAKE_BOOLEAN(is_less_equal_     , 2,(a0 <= a1));
  NT2_MAKE_BOOLEAN(is_greater_equal_  , 2,(a0 >= a1));
  NT2_MAKE_BOOLEAN(logical_and_       , 2,(a0 && a1));
  NT2_MAKE_BOOLEAN(logical_or_        , 2,(a0 || a1));
} }

#undef NT2_MAKE_BOOLEAN

#endif

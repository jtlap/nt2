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

////////////////////////////////////////////////////////////////////////////////
// Generates all binary comparison operators
////////////////////////////////////////////////////////////////////////////////
#define NT2_MAKE_BOOLEAN(TAG,IMPL)                                                  \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0)(A1),(fundamental_<A0>)(fundamental_<A1>)); \
namespace nt2 { namespace ext                                                       \
{                                                                                   \
  template<class Dummy>                                                             \
  struct  call<TAG(tag::fundamental_,tag::fundamental_), tag::cpu_, Dummy>          \
        : callable                                                                  \
  {                                                                                 \
    typedef bool result_type;                                                       \
    NT2_FUNCTOR_CALL(2) { return IMPL; }                                            \
  };                                                                                \
} }                                                                                 \
/**/

NT2_MAKE_BOOLEAN(tag::is_equal_          , (a0 == a1));
NT2_MAKE_BOOLEAN(tag::is_not_equal_      , (a0 != a1));
NT2_MAKE_BOOLEAN(tag::is_less_           , (a0 <  a1));
NT2_MAKE_BOOLEAN(tag::is_greater_        , (a0 >  a1));
NT2_MAKE_BOOLEAN(tag::is_less_equal_     , (a0 <= a1));
NT2_MAKE_BOOLEAN(tag::is_greater_equal_  , (a0 >= a1));
NT2_MAKE_BOOLEAN(tag::logical_and_       , (a0 && a1));
NT2_MAKE_BOOLEAN(tag::logical_or_        , (a0 || a1));

#undef NT2_MAKE_BOOLEAN

////////////////////////////////////////////////////////////////////////////////
// Logical not implementation
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::logical_not_,tag::cpu_,(A0),(fundamental_<A0>));

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call<tag::logical_not_(tag::fundamental_), tag::cpu_, Dummy>
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(1) { return !a0; }
  };
} }

#endif

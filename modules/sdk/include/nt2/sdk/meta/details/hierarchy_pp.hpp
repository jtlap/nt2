//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_HIERARCHY_PP_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_HIERARCHY_PP_HPP_INCLUDED

#include <nt2/sdk/details/preprocessor.hpp>

//==============================================================================
// Build a simple hierarchy element
//==============================================================================
#define NT2_HIERARCHY_CLASS(Name, Parent)     \
struct Name : Parent                          \
{                                             \
  typedef Parent  parent;                     \
  typedef Name    origin;                     \
}                                             \
/**/

//==============================================================================
// Build a template based hierarchy element
//==============================================================================
#define NT2_HIERARCHY_CLASS_TPL(Name, Parent) \
template<class T> struct Name : Parent        \
{                                             \
  typedef Parent  parent;                     \
  typedef T origin;                        \
}                                             \
/**/

//==============================================================================
// Build a template based hierarchy element with a template parent
//==============================================================================
#define NT2_HIERARCHY_CLASS_TPL_META(Name, Parent)          \
template<class T> struct Name : NT2_PP_STRIP(Parent)::type  \
{                                                           \
  typedef typename NT2_PP_STRIP(Parent)::type parent;       \
  typedef T                                origin;       \
}                                                           \
/**/

//==============================================================================
// User level macro to define a new hierarchy element taking advantage of the
// type hierarchy lattice system.
//==============================================================================
#define NT2_REGISTER_HIERARCHY_PARENT(Name, Base)                               \
namespace nt2                                                                   \
{                                                                               \
  namespace meta                                                                \
  {                                                                             \
    template<class T> struct Name : Name< typename T::parent >                  \
    {                                                                           \
      typedef Name< typename T::parent > parent;                                \
      typedef typename T::origin         origin;                                \
    };                                                                          \
                                                                                \
    template<class T> struct Name< unspecified_<T> > : unspecified_<T>          \
    {                                                                           \
      typedef unspecified_<T> parent;                                           \
      typedef T               origin;                                           \
    };                                                                          \
    template<class T> struct Name< unknown_<T> > : NT2_PP_REMOVE_TYPENAME(Base) \
    {                                                                           \
      typedef Base parent;                                                      \
      typedef T    origin;                                                      \
    };                                                                          \
  }                                                                             \
}                                                                               \
/**/

//==============================================================================
// Defines a classic hierarchy ending up going into unknown_
//==============================================================================
#define NT2_REGISTER_HIERARCHY(Name)                                           \
NT2_REGISTER_HIERARCHY_PARENT(Name, unknown_<T>)                               \
/**/

#endif

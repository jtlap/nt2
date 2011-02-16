/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_HIERARCHY_OF_HPP_INCLUDED
#define NT2_SDK_META_HIERARCHY_OF_HPP_INCLUDED

#include <climits>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/hierarchy.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // implementation details for hierarchy_of on integers
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Enable = void>
  struct  hierarchy_of
  {
    typedef meta::unspecified_<typename meta::strip<T>::type> type;
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // hierarchy_of computes the entry point of a given type inside the type
  // hierarchy lattice.
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Enable = void>
  struct  hierarchy_of
        : details::hierarchy_of<typename meta::strip<T>::type>
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Overload for types with inner hierarchy tag
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  hierarchy_of< T
                      , typename
                        enable_if_type<typename meta::strip<T>::type
                                                    ::nt2_hierarchy_tag
                                      >::type
                      >
  {
    typedef typename meta::strip<T>::type::nt2_hierarchy_tag type;
  };
} }

#include <nt2/sdk/meta/details/hierarchy_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// User level macro to define a new hierarchy element taking advantage of the
// type hierarchy lattice system.
////////////////////////////////////////////////////////////////////////////////
#define NT2_REGISTER_HIERARCHY(Name)                                \
namespace nt2                                                       \
{                                                                   \
  namespace tag { template<class T> struct Name {}; }               \
  namespace meta                                                    \
  {                                                                 \
    template<class T> struct Name : Name< typename T::parent >      \
    {                                                               \
      typedef Name< typename T::parent > parent;                    \
      typedef tag::Name<typename T::type> type;                     \
    };                                                              \
                                                                    \
    template<class T> struct Name< unknown_<T> > : unknown_<T> {};  \
  }                                                                 \
}                                                                   \
/**/

#endif

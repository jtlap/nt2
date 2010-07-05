/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_CATEGORY_OF_HPP_INCLUDED
#define NT2_SDK_META_CATEGORY_OF_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Retrieves the type category as defined by the Categorizable Concept
//* TODO Documentation: http://nt2.lri.fr/sdk/meta/category_of.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/has_xxx.hpp>
#include <nt2/sdk/meta/unknown.hpp>

namespace nt2 { namespace details
{
  BOOST_MPL_HAS_XXX_TRAIT_DEF(nt2_category_tag)

  //////////////////////////////////////////////////////////////////////////////
  // Try to find a nt2_category_tag in T. If none are found and no explicit
  // specialization of category_of is available, T is considered to have an
  // unknown_ category.
  //////////////////////////////////////////////////////////////////////////////
  template< class T
          , bool EnableIf = details::has_nt2_category_tag<T>::value
          >
  struct category_of_impl
  {
    typedef typename T::nt2_category_tag type;
  };

  template<class T>
  struct category_of_impl<T,false>
  {
    typedef tag::unknown type;
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // User interface for category_of
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  category_of
        : details::category_of_impl<T> {};

  //////////////////////////////////////////////////////////////////////////////
  // Specialization for volatile and cv-qualifiers
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct category_of<         T&      > : category_of<T> {};
  template<class T> struct category_of<         T const&> : category_of<T> {};
  template<class T> struct category_of<         T const > : category_of<T> {};
  template<class T> struct category_of<volatile T       > : category_of<T> {};
  template<class T> struct category_of<volatile T&      > : category_of<T> {};
  template<class T> struct category_of<volatile T const&> : category_of<T> {};
  template<class T> struct category_of<volatile T const > : category_of<T> {};

  //* TODO : add scalar specialization in functor/
} }

#endif

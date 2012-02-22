//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IS_ITERATOR_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_ITERATOR_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::is_iterator \metafunction
 */

#include <boost/mpl/bool.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>

//============================================================================
// Fix a couple of things for restrict pointers
// FIXME: integrate upstream
//============================================================================
#if defined(_MSC_VER) || defined(__GNUC__)
#ifdef _MSC_VER
#define BOOST_DISPATCH_RESTRICT __restrict
#else
#define BOOST_DISPATCH_RESTRICT __restrict__
#endif
namespace boost
{
  template<class T>
  struct is_pointer<T BOOST_DISPATCH_RESTRICT>
   : mpl::true_
  {
  };

  namespace detail
  {
    template<class T>
    struct iterator_traits<T BOOST_DISPATCH_RESTRICT>
     : boost::detail::iterator_traits<T>
    {
    };
  }
}
#undef BOOST_DISPATCH_RESTRICT
#endif

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * Checks if a given type models the \iterator concept.
   *
   * \model
   *
   * \metafunction
   *
   * \semantic
   *
   * For any type \c T,
   *
   * \code
   *  typedef boost::dispatch::meta::is_iterator<T>::type v;
   * \endcode
   *
   * evaluates to \true_ if \c T is a type modeling the \iterator concept.
   * Such types includes standard conforming iterator classes and non-function
   * pointers.
   *
   * \usage
   *
   * \include is_iterator.cpp
   */
  //============================================================================
  template<class T, class Enable=void>
  struct  is_iterator : boost::is_pointer<T>  {};

  //============================================================================
  // Overload for function pointers (which are not iterator)
  //============================================================================
  template<class T>
  struct  is_iterator < T
                      , typename boost::
                        enable_if_c< boost::
                                     is_function<typename boost::
                                                 remove_pointer<T>::type
                                                >::value
                                      >::type
                      >
        : boost::mpl::false_ {};

  //============================================================================
  // Overload for standard conforming iterators
  //============================================================================
  template<class T>
  struct  is_iterator < T
                      , typename
                        enable_if_type< typename
                                        strip<T>::type::iterator_category
                                      >::type
                      >
        : boost::mpl::true_ {};
} } }

#endif

//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_CARDINAL_OF_HPP_INCLUDED
#define NT2_SDK_META_CARDINAL_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the nt2::meta::cardinal_of \metafunction
 */

#include <boost/mpl/size_t.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  /*!
   * \ingroup extensions
   * Extension point for \ref nt2::meta::cardinal specialized upon a \c Type
   * and its \c Hierarchy.
   *
   * \tparam Type Hierarchizable type to specialize for.
   * \tparam Hierarchy Hierarchy of type
   *
   * \usage
   *
   * For any type modeling a multi-valued register, this extension can be
   * specialized to provide a compile-time integral constant equals to this
   * type valuation.
   *
   * \see nt2::simd::native
   *
   */
  //============================================================================
  template<class Type,class Hierarchy>
  struct cardinal_of_impl : boost::mpl::size_t<1> {};
} }

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * \metafunction computing the number of values of type \c T to fit in a
   * register.
   *
   * \tparam T Hierarchizable type
   *
   * \par Model:
   *
   * \metafunction
   *
   * \par Semantic:
   *
   * \usage
   *
   * \include cardinal_of.cpp
   */
  //============================================================================
  template<class T>
  struct  cardinal_of
        : ext::cardinal_of_impl < typename meta::strip<T>::type
                                , typename hierarchy_of<T>::type
                                > {};
} }

#endif

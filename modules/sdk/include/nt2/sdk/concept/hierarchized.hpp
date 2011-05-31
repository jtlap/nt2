//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONCEPT_HIERARCHIZABLE_HPP_INCLUDED
#define NT2_SDK_CONCEPT_HIERARCHIZABLE_HPP_INCLUDED

/*!
 * \file
 * \brief Define the \ref nt2::Hierarchizable Concept
 */

#include <nt2/sdk/error/concepts.hpp>
#include <nt2/sdk/meta/hierarchy.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(DOXYGEN_ONLY)
namespace nt2
{
  //============================================================================
  /*!
   * \ingroup concepts
   * A model of Hierarchizable is a type with a non-unspecified hierarchy. Such
   * type are recognized by \nt2 and usually are able to be used in all \nt2
   * functions or meta-functions.
   *
   *  \par Expressions Requirements:
   *
   *  For any \c T, model of \ref Hierarchizable.
   *
   * \code
   * is_same<typename hierarchy_of<T>::type, unspecified_<T> >::value == false
   * \endcode
   *
   *  \par Models:
   *
   *  - all fundamental types (\c int,\c float, ...)
   *  - \ref nt2::simd::pack
   *  - \ref nt2::container::table
   */
  //============================================================================
  template<class T> struct Hierarchizable {};
}
#else
namespace nt2
{
  template< class T
          , bool Enable =
            !boost::is_same < typename meta::hierarchy_of<Hierarchized>::type
                            , meta::unspecified_<Hierarchized>
                            >::value
          >
  struct Hierarchizable
  {
    BOOST_CONCEPT_USAGE(Hierarchizable) {}
  };

  template<class T> struct Hierarchizable<T,false>
  {
    BOOST_CONCEPT_USAGE(Hierarchizable) { T::type_has_unspecified_category(); }
  };
}

#endif
#endif

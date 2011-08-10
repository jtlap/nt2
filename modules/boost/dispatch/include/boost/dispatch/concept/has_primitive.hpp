//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_CONCEPT_HAS_PRIMITIVE_HPP_INCLUDED
#define BOOST_DISPATCH_CONCEPT_HAS_PRIMITIVE_HPP_INCLUDED

/*!
 * \file
 * \brief Define the \ref boost::dispatch::HasPrimitive Concept
 */

#include <boost/dispatch/error/concepts.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace dispatch
{
  //============================================================================
  /*!
   * \ingroup concepts
   * A model of HasPrimitive is a type from which a Fundamental type, i.e. a
   * type which Hierarchy is \ref boost::dispatch::tag::fundamental_, can be extracted.
   *
   * \par Notations:
   *
   *  - \c T Model of \ref HasPrimitive.
   *
   *  \par Expressions Requirements:
   *
   *  - \c primitive_of<T>::type verifies
   *  \c boost::dispatch::meta::is_fundamental<Primitive>::value \c == \c true
   *
   *  \par Models:
   *
   *  - all fundamental types (\c int,\c float, ...)
   *  - \ref boost::dispatch::simd::native
   *  - all models of \readableiterator
   *  - all models of \singlepassrange
   */
  //============================================================================
  template<class T> struct HasPrimitive {};
} }
#else
namespace boost { namespace dispatch
{
  template< class T
          , bool Enable =
            meta::is_fundamental<typename meta::primitive_of<T>::type>::value
          >
  struct HasPrimitive
  {
    BOOST_CONCEPT_USAGE(HasPrimitive) {}
  };

  template<class T> struct HasPrimitive<T,false>
  {
    void type_has_unknown_category();
    BOOST_CONCEPT_USAGE(HasPrimitive) { type_has_unknown_category(t); }

    private:
    T t;
  };
} }

#endif
#endif

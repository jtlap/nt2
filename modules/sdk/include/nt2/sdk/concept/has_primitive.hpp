//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONCEPT_HAS_PRIMITIVE_HPP_INCLUDED
#define NT2_SDK_CONCEPT_HAS_PRIMITIVE_HPP_INCLUDED

/*!
 * \file
 * Define the hasPrimitive Concept
 */

#include <nt2/sdk/error/concepts.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>

#if defined(DOXYGEN_ONLY)
namespace nt2
{
  //============================================================================
  /*!
   * \ingroup concepts
   * A model of HasPrimitive is a type from which a primitive type, i.e. a
   * type which hierarchy is \ref nt2::tag::fundamental_, can be extracted.
   *
   * \par Notations:
   *
   *  - \c T Model of \ref HasPrimitive.
   *  - \c Primitive A type veryfying:
   *  \code nt2::meta::is_fundamental<Primitive>::value == true \endcode
   *
   *  \par Expressions Requirements:
   *
   *  \par Models:
   *
   *  - all fundamental types (\c int,\c float, ...)
   *  - \ref nt2::simd::native
   *  - all models of \readableiterator
   *  - all models of \singlepassrange
   */
  //============================================================================
  template<class T> struct HasPrimitive {};
}
#endif

namespace nt2
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
}

/*
    +-----------------------------+-------------------------------------------------+-------------+
    | Expression                  | Return Type                                     | Semantics   |
    +=============================+=================================================+=============+
    |  ``primitive_of<T>::type``  | Primitive                                       | unspecified |
    +-----------------------------+-------------------------------------------------+-------------+
 */

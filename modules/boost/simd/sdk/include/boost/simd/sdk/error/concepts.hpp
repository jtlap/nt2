//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_ERROR_CONCEPTS_HPP_INCLUDED
#define BOOST_SIMD_SDK_ERROR_CONCEPTS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros controlling the handling of Concepts checks
 */

#include <boost/concept_check.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error_config
 * If \c BOOST_SIMD_SDK_USE_CONCEPTS is used, Concepts conformance will be checked at
 * compile time to enforce structer typing rules. As Concepts checking increases
 * compile time, it has to be used conservatively.
 */
//==============================================================================
#define BOOST_SIMD_SDK_USE_CONCEPTS

//==============================================================================
/*!
 * \ingroup error
 * This macro, used at any scope, verify that the concept checking template
 * specialization \c CONCEPT is satisfied.
 *
 * \param CONCEPT Cocnept checking template to assert.
 */
//==============================================================================
#define BOOST_SIMD_SDK_CONCEPT_ASSERT(CONCEPT)

//==============================================================================
/*!
 * \ingroup error
 *
 * This macro, that can be used as a function return type, checks that all the
 * concept checking templates in the \c CONCEPTS preprocessor list are satisifed.
 * If they are, the function is allowed to be defined with a return type equals
 * to \c TYPE.
 *
 * \param CONCEPTS
 * \param TYPE
 */
//==============================================================================
#define BOOST_SIMD_SDK_CONCEPT_REQUIRE(CONCEPTS,TYPE)
#endif

#if defined(BOOST_SIMD_SDK_USE_CONCEPTS) && !defined(DOXYGEN_ONLY)
#define BOOST_SIMD_SDK_CONCEPT_ASSERT(CONCEPT) BOOST_CONCEPT_ASSERT(CONCEPT)
#define BOOST_SIMD_SDK_CONCEPT_REQUIRE(CONCEPTS,TYPE)  BOOST_CONCEPT_REQUIRE(CONCEPT,TYPE)

#elif !defined(DOXYGEN_ONLY)
#define BOOST_SIMD_SDK_CONCEPT_ASSERT(CONCEPT)
#define BOOST_SIMD_SDK_CONCEPT_REQUIRE(CONCEPTS,TYPE)
#endif

#endif

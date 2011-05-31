//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_DETAILS_PREPROCESSOR_HPP_INCLUDED
#define NT2_SDK_DETAILS_PREPROCESSOR_HPP_INCLUDED

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/expand.hpp>

/*!
 * \file
 * \brief Defines some short-cut for frequently used PP macros
 */

/*!
 * \defgroup preprocessor Preprocessor Utilities
 * \ingroup sdk
 *
 * This module gathers frequently used preprocessor macros and macros functions
 * that extend Boost.Preprocessor features in NT2 context.
 */

//==============================================================================
/*!
 * \ingroup preprocessor
 * Evaluates a macros into a printable string for debugging purpose.
 *
 * \param MACRO Macro to expand
 */
//==============================================================================
#define NT2_PP_DEBUG(MACRO) BOOST_PP_STRINGIZE( (MACRO) )

//==============================================================================
// Enumeration macro for index and value. Used internally
//==============================================================================
#define NT2_PP_INDEX(z,n,t)             n
#define NT2_PP_TEXT(z,n,t)              t

//==============================================================================
/*!
 * \ingroup preprocessor
 * Evaluates as the comma separated enumeration of \c N times the symbol \c V.
 *
 * \param N Number of iterations to generate
 * \param V Symbol to replicate
 *
 * \par Example Usage:
 *
 * \include pp_enum_value.cpp
 *
 * This produces the folowing output
 * \code (6 , 6 , 6 , 6 , 6) \endcode
 */
//==============================================================================
#define NT2_PP_ENUM_VALUE(N,V)          BOOST_PP_ENUM(N,NT2_PP_TEXT,V)

//==============================================================================
/*!
 * \ingroup preprocessor
 * Evaluates as a string usuable as a valid include directive.by concatenating
 * a base root \c PATH to a \c FILE. Both \c PATH and \c FILE can actually be
 * macros, thus creating the effect of a programmable include directive.
 *
 * \param PATH Root path to the file to include
 * \param FILE File to include
 *
 * \par Example Usage:
 *
 * \include pp_include.cpp
 */
//==============================================================================
#define NT2_PP_INCLUDE(PATH,FILE) BOOST_PP_STRINGIZE(PATH()FILE)

#define NT2_PP_DETAILS_APPLY(macro, args)   NT2_PP_DETAILS_APPLY_I(macro, args)
#define NT2_PP_DETAILS_APPLY_I(macro, args) macro args
#define NT2_PP_DETAILS_STRIP_PARENS_I(...) 1,1
#define NT2_PP_DETAILS_EVAL(test, x) NT2_PP_DETAILS_EVAL_I(test, x)
#define NT2_PP_DETAILS_EVAL_I(test, x) NT2_PP_DETAILS_MAYBE_STRIP_PARENS(NT2_PP_DETAILS_TEST_ARITY test, x)
#define NT2_PP_DETAILS_TEST_ARITY(...) NT2_PP_DETAILS_APPLY(NT2_PP_DETAILS_TEST_ARITY_I, (__VA_ARGS__, 2, 1))
#define NT2_PP_DETAILS_TEST_ARITY_I(a,b,c,...) c
#define NT2_PP_DETAILS_MAYBE_STRIP_PARENS(cond, x) NT2_PP_DETAILS_MAYBE_STRIP_PARENS_I(cond, x)
#define NT2_PP_DETAILS_MAYBE_STRIP_PARENS_I(cond, x) BOOST_PP_CAT(NT2_PP_DETAILS_MAYBE_STRIP_PARENS_, cond)(x)
#define NT2_PP_DETAILS_MAYBE_STRIP_PARENS_1(x) x
#define NT2_PP_DETAILS_MAYBE_STRIP_PARENS_2(x) NT2_PP_DETAILS_APPLY(NT2_PP_DETAILS_MAYBE_STRIP_PARENS_2_I, x)
#define NT2_PP_DETAILS_MAYBE_STRIP_PARENS_2_I(...) __VA_ARGS__

//==============================================================================
/*!
 * \ingroup preprocessor
 * For any symbol \c X, this macro returns the same symbol from which potential
 * outer parens have been removed. If no outer parens are found, this macros
 * evaluates to \c X itself without error.
 *
 * The original implementation of this macro is from Steven Watanbe as shown
 * in http://article.gmane.org/gmane.comp.lib.boost.user/61011
 *
 * \param X Symbol to strip parens from
 *
 * \par Example Usage:
 *
 * \include pp_strip.cpp
 *
 * This produces the following output
 * \code
 * (no parens)
 * (with parens)
 * \endcode
 */
//==============================================================================
#define NT2_PP_STRIP(X) NT2_PP_DETAILS_EVAL((NT2_PP_DETAILS_STRIP_PARENS_I X), X)
//==============================================================================

// Boost.Preprocessor author P. Mensodines confirmed on an Boost email thread
// (subject ``check if a token is a keyword (was "BOOST_PP_IS_UNARY()")'')
// that it is OK to used `PP_IS_UNARY()` to check if tokens match predefined
// "keyword" as it is done by the macros below (even if `PP_IS_UNARY()` is
// technically only part of Boost.Preprocessor private API).

// `checking_prefix ## tokens` expand to unary (e.g., `(1)`) iff `tokens` start
// with keyword to check.
#define NT2_PP_DETAILS_KEYWORD_FACILITY_IS_FRONT(tokens, checking_prefix) \
    BOOST_PP_IS_UNARY(BOOST_PP_CAT(checking_prefix, tokens))

// `is_front_macro(tokens)` is 1 iff `tokens` start with keyword to remove.
// `removing_prefix ## <keyword-to-remove>` must expand to nothing.
#define NT2_PP_DETAILS_KEYWORD_FACILITY_REMOVE_FRONT( \
        tokens, is_front_macro, removing_prefix) \
    BOOST_PP_EXPAND( /* without EXPAND doesn't expand on MSVC */ \
        BOOST_PP_IIF(is_front_macro(tokens), \
            BOOST_PP_CAT \
        , \
            tokens BOOST_PP_TUPLE_EAT(2) \
        )(removing_prefix, tokens) \
    )

#define NT2_PP_DETAILS_KEYWORD_TYPENAME_IS_typename (1) /* unary */
#define typename_NT2_PP_DETAILS_KEYWORD_TYPENAME_IS (1) /* unary */
#define NT2_PP_DETAILS_KEYWORD_TYPENAME_REMOVE_typename /* nothing */
#define typename_NT2_PP_DETAILS_KEYWORD_TYPENAME_REMOVE /* nothing */

#define NT2_PP_DETAILS_KEYWORD_IS_TYPENAME_FRONT(tokens) \
    NT2_PP_DETAILS_KEYWORD_FACILITY_IS_FRONT(tokens, \
            NT2_PP_DETAILS_KEYWORD_TYPENAME_IS_)

//==============================================================================
/*!
 * \ingroup preprocessor
 * For any symbol \c X, this macro returns the same symbol from which a potential
 * leading \c typename keyword has been removed. If no typename keyword is present,
 * this macros evaluates to \c X itself without error.
 *
 * The original implementation of this macro is from Lorenzo Caminiti.
 *
 * \param X Symbol to remove \c typename from
 */
//==============================================================================
#define NT2_PP_REMOVE_TYPENAME(X) \
    NT2_PP_DETAILS_KEYWORD_FACILITY_REMOVE_FRONT(X, \
            NT2_PP_DETAILS_KEYWORD_IS_TYPENAME_FRONT, \
            NT2_PP_DETAILS_KEYWORD_TYPENAME_REMOVE_)
            

#endif

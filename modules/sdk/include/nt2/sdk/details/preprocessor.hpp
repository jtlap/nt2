/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DETAILS_PREPROCESSOR_HPP_INCLUDED
#define NT2_SDK_DETAILS_PREPROCESSOR_HPP_INCLUDED

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some short-cut for frequently used PP macros
// Documentation: http://nt2.lri.fr/sdk/details/preprocessor.html
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Turn a macro into a printable screen for debugging
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_DEBUG(N) BOOST_PP_STRINGIZE( (N) )

////////////////////////////////////////////////////////////////////////////////
// Enumeration macro for index
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_INDEX(z,n,t)             n

////////////////////////////////////////////////////////////////////////////////
// Enumeration macro for text
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_TEXT(z,n,t)              t

////////////////////////////////////////////////////////////////////////////////
// Enumerate v n times
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_ENUM_VALUE(n,v)          BOOST_PP_ENUM(n,NT2_PP_TEXT,v)

////////////////////////////////////////////////////////////////////////////////
// Enumerate v n-1 times
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_ENUM_SHIFTED_VALUE(n,v)  BOOST_PP_ENUM_SHIFTED(n,NT2_PP_TEXT,v)

////////////////////////////////////////////////////////////////////////////////
// Programmable include directive
// Documentation: http://nt2.lri.fr/sdk/details/include.html
////////////////////////////////////////////////////////////////////////////////
#define NT2_PP_INCLUDE(Base,File) BOOST_PP_STRINGIZE(Base()File)

////////////////////////////////////////////////////////////////////////////////
// Strip potential parens around macro parameters.
//        **!** SERIOUS STUFF BY STEVEN WATANABE SO YEAH IT WORKS**!**
// Details are in http://article.gmane.org/gmane.comp.lib.boost.user/61011
////////////////////////////////////////////////////////////////////////////////
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

#define NT2_PP_STRIP(x) NT2_PP_DETAILS_EVAL((NT2_PP_DETAILS_STRIP_PARENS_I x), x)

#endif

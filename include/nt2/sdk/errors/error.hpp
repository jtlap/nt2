/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_ERRORS_ERROR_HPP_INCLUDED
#define NT2_NT2_SDK_ERRORS_ERROR_HPP_INCLUDED

#include <nt2/sdk/errors/details/error.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

////////////////////////////////////////////////////////////////////////////////
// Local macro for enumerating eception infos
////////////////////////////////////////////////////////////////////////////////
#define NT2_ERROR_GENERATOR(r,d,e)                          \
<< BOOST_PP_TUPLE_ELEM(2,0,e)( BOOST_PP_TUPLE_ELEM(2,1,e) ) \
/**/

////////////////////////////////////////////////////////////////////////////////
// Always throw through BOOST_THROW_EXCEPTION and delegate inside
////////////////////////////////////////////////////////////////////////////////
#define NT2_ERROR( Error, InfoSeq )                                             \
BOOST_THROW_EXCEPTION ( Error()                                                 \
                        BOOST_PP_SEQ_FOR_EACH(NT2_ERROR_GENERATOR, _, InfoSeq)  \
                      )                                                         \
/**/

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_CATEGORY_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_CATEGORY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Basic category registration
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

////////////////////////////////////////////////////////////////////////////////
// Use this macro to put a type in the scalar familly
////////////////////////////////////////////////////////////////////////////////
#define NT2_CATEGORY_SCALAR_FAMILY 1

#define NT2_PRIMITIVE_TYPES (bool                                      \
                           , char, signed char, unsigned char          \
                           , short, unsigned short                     \
                           , int, unsigned int                         \
                           , long, unsigned long                       \
                           , long long, unsigned long long             \
                           , float, double)
#define NT2_NB_PRIMITIVE_TYPES 14

////////////////////////////////////////////////////////////////////////////////
// Family tags for call/validate writings
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  struct scalar_      {};
  struct arithmetic_  {};
} }

////////////////////////////////////////////////////////////////////////////////
// scalar_ metafunction for building a category
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class T, std::size_t R>
  struct  scalar_
        : nt2::tag::category<scalar_<T,R>,NT2_CATEGORY_SCALAR_FAMILY,R>
  {
    typedef nt2::tag::scalar_ tag(T);
  };
} }

namespace nt2 { namespace meta
{
  /////////////////////////////////////////////////////////////////////////////
  // Register all arithmetic types by giving them a category
  //////////////////////////////////////////////////////////////////////////////
  #define M0(r, data, elem)                                            \
  template<>                                                           \
  struct category_of<elem> : functors::scalar_<tag::arithmetic_,1> {};
  
  BOOST_PP_SEQ_FOR_EACH(M0, ~, BOOST_PP_TUPLE_TO_SEQ(NT2_NB_PRIMITIVE_TYPES, NT2_PRIMITIVE_TYPES))
  #undef M0
} }

#endif

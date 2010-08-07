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

////////////////////////////////////////////////////////////////////////////////
// Use this macro to put a type in the scalar familly
////////////////////////////////////////////////////////////////////////////////
#define NT2_CATEGORY_SCALAR_FAMILY 1

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
  template<>
  struct category_of<bool     > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<double   > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<float    > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<int8_t   > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<uint8_t  > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<int16_t  > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<uint16_t > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<int32_t  > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<uint32_t > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<int64_t  > : functors::scalar_<tag::arithmetic_,1> {};
  template<>
  struct category_of<uint64_t > : functors::scalar_<tag::arithmetic_,1> {};
} }

#endif

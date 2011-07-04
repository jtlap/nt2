/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONCEPT_CATEGORIZABLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONCEPT_CATEGORIZABLE_HPP_INCLUDED

#include <boost/simd/sdk/meta/unknown.hpp>
#include <boost/simd/sdk/error/concepts.hpp>
#include <boost/simd/sdk/meta/category_of.hpp>
#include <boost/type_traits/is_same.hpp>

////////////////////////////////////////////////////////////////////////////////
// Categorizable concept: defines types with a NT2 category tag
// Documentation: http://nt2.lri.fr/sdk/concept/categorizable.hpp
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd
{
  template< class T
          , bool Enable = boost::is_same< typename
                                          meta::category_of<T>::type::tag
                                        , tag::unknown
                                        >::value
          >
  struct Categorizable
  {
    BOOST_CONCEPT_USAGE(Categorizable) {}
  };

  template<class T> struct Categorizable<T,false>
  {
    void type_has_unknown_category();
    BOOST_CONCEPT_USAGE(Categorizable) { type_has_unknown_category(t); }

    private:
    T t;
  };
} }

#endif

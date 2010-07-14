/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_DOMINANT_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_DOMINANT_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/utility/result_of.hpp>
#include <nt2/sdk/meta/category_of.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/sdk/meta/na.hpp>
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

namespace nt2 { namespace details
{
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template<std::size_t N, class... Args> struct dominant;
  #else
  template< std::size_t N
          , BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_ARITY
                                        , class A
                                        , = meta::na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct dominant;
  #endif

  template<class A0> struct dominant<1,A0> : meta::category_of<A0> {};

  template<class A0,class A1>
  struct  dominant<2,A0,A1>
        : boost::mpl::eval_if_c<  ( meta::category_of<A0>::type::rank
                                  < meta::category_of<A1>::type::rank
                                  )
                                , meta::category_of<A1>
                                , meta::category_of<A0>
                                >
  {};

  template<class A0,class A1,class A2>
  struct  dominant<3,A0,A1,A2>
        : boost::mpl::eval_if_c<  ( dominant<2,A0,A1>::type::rank
                                  < meta::category_of<A2>::type::rank
                                  )
                                , meta::category_of<A2>
                                , dominant<2,A0,A1>
                                >
  {};

  template<class A0,class A1,class A2,class A3>
  struct  dominant<4,A0,A1,A2,A3>
        : boost::mpl::eval_if_c<  ( dominant<2,A0,A1>::type::rank
                                  < dominant<2,A2,A3>::type::rank
                                  )
                                , dominant<2,A2,A3>
                                , dominant<2,A0,A1>
                                >
  {};
} }

#endif

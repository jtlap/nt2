//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DISPLAY_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DISPLAY_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::display function
 */

#include <nt2/include/functor.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <iostream>

namespace nt2 
{ 
  namespace tag { struct display_ : ext::unspecified_<display_> { typedef ext::unspecified_<display_> parent; }; }

  nt2::functor<nt2::tag::display_> display = {};
}

namespace nt2 { namespace ext
{
  #define M1(z, n, t) (A##n)
  #define M2(z, n, t) (unspecified_<A##n>)
  
  #define M0(z, n, t)                                                          \
  NT2_REGISTER_DISPATCH_TO( nt2::tag::display_, tag::cpu_                      \
                          , BOOST_PP_REPEAT(n, M1, ~)                          \
                          , BOOST_PP_REPEAT(n, M2, ~)                          \
                          , (nt2::ext::implement<nt2::tag::display_, A0>)      \
                          )                                                    \
  /**/
  BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY), M0, ~)
  #undef M0
  #undef M1
  #undef M2
  
  template<class Dummy>
  struct implement< nt2::tag::display_, Dummy>
  {
    typedef void result_type;

    #define M1(z, n, t) BOOST_PP_IF(n, << " " << , ) a##n

    #define M0(z, n, t)                                                        \
    template<BOOST_PP_ENUM_PARAMS(n, class A)>                                 \
    result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)) const  \
    {                                                                          \
      std::cout << BOOST_PP_REPEAT(n, M1, ~) << std::endl;                     \
    }                                                                          \
    /**/
    
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY), M0, ~)
    #undef M0
    #undef M1
  };
} }

#endif

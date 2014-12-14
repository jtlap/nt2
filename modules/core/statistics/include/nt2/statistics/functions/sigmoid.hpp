//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_SIGMOID_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_SIGMOID_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief sigmoid generic tag

     Represents the sigmoid function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sigmoid_ : ext::elementwise_<sigmoid_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sigmoid_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_sigmoid_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::sigmoid_, Site> dispatching_sigmoid_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::sigmoid_, Site>();
   }
   template<class... Args>
   struct impl_sigmoid_;
  }
  /*!
    Computes the sigmoid function: \f$1/(1-e^{-x}\f$

    @par Semantic:

    For every parameters of floating type T0

    @code
    T0 r = sigmoid(x);
    @endcode

    @see @funcref{fast_sigmoid},
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sigmoid_, sigmoid, 1)
}

#endif


//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_D_REALPOW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_D_REALPOW_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_realpow generic tag

     Represents the d_realpow function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_realpow_ : ext::elementwise_<d_realpow_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_realpow_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_realpow_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_realpow_, Site> dispatching_d_realpow_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_realpow_, Site>();
   }
   template<class... Args>
   struct impl_d_realpow_;
  }
  /*!
    Returns power function,  but
    asserts if the result is to be complex

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = d_realpow(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = pow(a0, a1);
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_realpow_, d_realpow, 2)
}

#endif


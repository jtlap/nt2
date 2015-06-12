//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_SIN_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_SIN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief d_sin generic tag

     Represents the d_sin function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_sin_ : ext::elementwise_<d_sin_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_sin_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_sin_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_sin_, Site> dispatching_d_sin_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_sin_, Site>();
   }
   template<class... Args>
   struct impl_d_sin_;
  }
  /*!
    sinine of the input in degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_sin(x);
    @endcode

    is similar to:

    @code
    T0 r = sin(deginrad<T0>()*x);
    @endcode

    @see @funcref{fast_d_sin}, @funcref{sind_sin}, @funcref{sin}, @funcref{sinpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_sin_, d_sin, 1)
}

#endif


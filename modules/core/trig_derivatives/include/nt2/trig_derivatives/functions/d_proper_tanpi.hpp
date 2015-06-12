//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_PROPER_TANPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_PROPER_TANPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_proper_tanpi generic tag

     Represents the d_proper_tanpi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_proper_tanpi_ : ext::elementwise_<d_proper_tanpi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_proper_tanpi_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_proper_tanpi_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_proper_tanpi_, Site> dispatching_d_proper_tanpi_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_proper_tanpi_, Site>();
   }
   template<class... Args>
   struct impl_d_proper_tanpi_;
  }
  /*!
    tangent of angle in \f$\pi\f$ multiples,
    restricted between -0.5 and +0.5.
    This function is the inverse of @c atanpi and so is
    such that @c d_proper_tanpi(0.5) is inf
    and @c d_proper_tanpi(-0.5) is -inf

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_proper_tanpi(x);
    @endcode

    is similar to:

    @code
    T0 r = tanpi(x);
    @endcode

    provided input is in \f$]-0.5,  0.5[\f$

    @see @funcref{tanpi}, @funcref{fast_tanpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_proper_tanpi_, d_proper_tanpi, 1)
}

#endif

// modified by jt the 25/12/2010



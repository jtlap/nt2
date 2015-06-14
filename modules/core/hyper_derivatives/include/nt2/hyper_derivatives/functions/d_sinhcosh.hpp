//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPER_DERIVATIVES_FUNCTIONS_D_SINHCOSH_HPP_INCLUDED
#define NT2_HYPER_DERIVATIVES_FUNCTIONS_D_SINHCOSH_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for d_sinhcosh function
    struct d_sinhcosh_ : ext::elementwise_<d_sinhcosh_>
    {
      typedef ext::elementwise_<d_sinhcosh_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_sinhcosh_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::d_sinhcosh_, Site> dispatching_d_sinhcosh_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::d_sinhcosh_, Site>();
    }
    template<class... Args>
    struct impl_d_sinhcosh_;
  }
  /*!
    @brief Derivative of sinh and cosh
    @see @funcref{acosh}
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::d_sinhcosh_, d_sinhcosh, 1)

  /*!
    @brief Derivative of sinh and cosh
    @see @funcref{acosh}
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::d_sinhcosh_, d_sinhcosh,(A0 const&)(A1&),2)

  /*!
    @brief Derivative of sinh and cosh
    @see @funcref{acosh}
   **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::d_sinhcosh_, d_sinhcosh,(A0 const&)(A1&)(A2&),3)

    }

#endif


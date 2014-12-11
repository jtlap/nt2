//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_SYR2K_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_SYR2K_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements rotm function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines rotm function tag
    struct blas_syr2k_ : ext::abstract_<blas_syr2k_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_syr2k_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_syr2k_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_syr2k_, Site> dispatching_blas_syr2k_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_syr2k_, Site>();
    }
    template<class... Args>
    struct impl_blas_syr2k_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_syr2k_, blas_syr2k
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(A6&)
                                  , 7
                                  );

}

#endif


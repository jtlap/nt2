//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_SWAP_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_SWAP_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_swap function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_swap function tag
    struct blas_swap_ : ext::abstract_<blas_swap_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_swap_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_swap_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_swap_, Site> dispatching_blas_swap_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_swap_, Site>();
    }
    template<class... Args>
    struct impl_blas_swap_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_swap_, blas_swap
                                  , (const A0&)(A1&)(const A2&)(A3&)(const A4&)
                                  , 5
                                  );

}

#endif


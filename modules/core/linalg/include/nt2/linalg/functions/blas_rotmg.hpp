//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_ROTMG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_ROTMG_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_rotmg function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_rotmg function tag
    struct blas_rotmg_ : ext::abstract_<blas_rotmg_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_rotmg_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_rotmg_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_rotmg_, Site> dispatching_blas_rotmg_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_rotmg_, Site>();
    }
    template<class... Args>
    struct impl_blas_rotmg_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_rotmg_, blas_rotmg
                                  , (A0&)(A1&)(A2&)(A3&)(A4&)
                                  , 5
                                  );

}

#endif


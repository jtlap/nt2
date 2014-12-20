//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_SYRK_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_SYRK_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements syrk function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines syrk function tag
    struct syrk_ : ext::abstract_<syrk_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<syrk_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_syrk_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::syrk_, Site> dispatching_syrk_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::syrk_, Site>();
    }
    template<class... Args>
    struct impl_syrk_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::syrk_, syrk
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(A5&)
                                  , 6
                                  );

 } }

#endif


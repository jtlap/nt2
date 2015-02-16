//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_QR1UP_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_QR1UP_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements qr1up function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines qr1up function tag
    struct qr1up_ : ext::abstract_<qr1up_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<qr1up_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_qr1up_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::qr1up_, Site> dispatching_qr1up_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::qr1up_, Site>();
    }
    template<class... Args>
    struct impl_qr1up_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::qr1up_, qr1up
                                  , (A0&)(A1&)(A2&)(A3&)
                                  , 4
                                  );

}

#endif


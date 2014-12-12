//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_I_AMAX_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_I_AMAX_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_i_amax function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_i_amax function tag
    struct blas_i_amax_ : ext::abstract_<blas_i_amax_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_i_amax_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_i_amax_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_i_amax_, Site> dispatching_blas_i_amax_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_i_amax_, Site>();
    }
    template<class... Args>
    struct impl_blas_i_amax_;
  }

  /*!
    @brief blas_i_amax return the  the first position of the maximum
    of the manhattan moduli of the elements of x

    @code
    asum ( n, x, incx)
    @endcode

    @param n number of elements to use
    @param x input vector
    @param incx step through x    @brief

    @return the index of the first occurenxe of the maximum of
    abs(real(x(_(1, incx, (n-1)*incx+1))))+abs(imag(x(_(1, incx, (n-1)*incx+1))))
    values
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_i_amax_, blas_i_amax
                                  , (const A0&)(const A1&)(const A2&)
                                  , 3
                                  );


}

#endif


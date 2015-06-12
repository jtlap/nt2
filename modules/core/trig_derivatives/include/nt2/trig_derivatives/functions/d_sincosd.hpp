//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_SINCOSD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_SINCOSD_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for d_sincosd function
    struct d_sincosd_ : ext::elementwise_<d_sincosd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_sincosd_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_sincosd_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::d_sincosd_, Site> dispatching_d_sincosd_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::d_sincosd_, Site>();
    }
    template<class... Args>
    struct impl_d_sincosd_;
  }
  /*!
    Computes simultaneously the sind and cosd of the input

    @par Semantic:

    @code
    T0 s, c;
    tie(s, c) = d_sincosd(x);
    @endcode

    is similar to:

    @code
    T0 s =  sind(x);
    T0 c =  cosd(x);
    @endcode

    @see @funcref{fast_d_sincosd}, @funcref{sincos}, @funcref{sincospi}
    @param a0 angle in degree

    @return A Fusion Sequence containing the sind and cosd of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::d_sincosd_, d_sincosd, 1)

  /*!
    Computes simultaneously the sind and cosd of the input

    @par Semantic:

    @code
    T0 s, c;
    s = d_sincosd(x, c);
    @endcode

    is similar to:

    @code
    T0 s =  sind(x);
    T0 c =  cosd(x);
    @endcode

    @param a0 angle in degree
    @param a1 L-Value that will receive the sind of @c a0

    @return A Fusion Sequence containing the cosd of @c a0
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::d_sincosd_, d_sincosd,(A0 const&)(A1&),2)

  /*!
    Computes simultaneously the sind and cosd of the input

    @par Semantic:

    @code
    T0 s, c;
    d_sincosd(x, s, c);
    @endcode

    is similar to:

    @code
    T0 s =  sind(x);
    T0 c =  cosd(x);
    @endcode

    @param a0 angle in degree
    @param a1 L-Value that will receive the sind of @c a0
    @param a2 L-Value that will receive the cosd of @c a0

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::d_sincosd_, d_sincosd,(A0 const&)(A1&)(A2&),3)

    }

#endif


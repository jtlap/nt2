//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_D_ATAND_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_D_ATAND_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_atand generic tag

     Represents the d_atand function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_atand_ : ext::elementwise_<d_atand_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_atand_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_atand_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_atand_, Site> dispatching_d_atand_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_atand_, Site>();
   }
   template<class... Args>
   struct impl_d_atand_;
  }
  /*!
    inverse tangent in degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_atand(a0);
    @endcode

    Returns the arc @c r in the interval
    \f$[-90, 90[\f$ such that <tt>tand(r) == x</tt>.

    @see @funcref{atan2}, @funcref{atan}, @funcref{atanpi}, @funcref{nbd_atan2}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_atand_, d_atand, 1)
}

#endif



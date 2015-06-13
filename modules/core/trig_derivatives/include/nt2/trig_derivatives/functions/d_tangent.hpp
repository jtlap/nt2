//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_D_TANGENT_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_D_TANGENT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_tangent generic tag

     Represents the d_tangent function in generic contexts.

     @par Models:
        Hierarchy
   **/
    template <class T> struct d_tangent_ : ext::elementwise_< d_tangent_<T> >
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_< d_tangent_<T> > parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_HEADER( dispatching( ext::adl_helper(), *(d_tangent_*)0, static_cast<Args&&>(args)... ) )
      {
        return dispatching( ext::adl_helper(), d_tangent_(), static_cast<Args&&>(args)... );
      }
    };
  }
  /*!
    d_tangent.

    @par Semantic:

    For template selector @c Range in proper selector types choice
    and for every parameter of floating type  T0:

    @code
    T0 r = d_tangent<Range>(x);
    @endcode

    is similar to:

    @code
    T0 r =  sine<Range>(x)/cosine<Range>(x);;
    @endcode

    @see @funcref{fast_tan}, @funcref{tan}, @funcref{tand}, @funcref{tanpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::d_tangent_<A0> , d_tangent, (A1 const&), 2)
}

#endif


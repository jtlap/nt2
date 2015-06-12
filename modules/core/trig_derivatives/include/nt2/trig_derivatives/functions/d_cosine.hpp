//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_COSINE_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_COSINE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief d_cosine generic tag

     Represents the d_cosine function in generic contexts.

     @par Models:
        Hierarchy
   **/
    template <class T>
    struct d_cosine_ : ext::elementwise_< d_cosine_<T> >
    {
      typedef ext::elementwise_< d_cosine_<T> > parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_HEADER( dispatching( ext::adl_helper(), *(d_cosine_*)0, static_cast<Args&&>(args)... ) )
      {
        return dispatching( ext::adl_helper(), d_cosine_(), static_cast<Args&&>(args)... );
      }
    };
  }

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::d_cosine_<A0> , d_cosine, (A1 const&), 2)
}

#endif



//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_EYEPLUS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_EYEPLUS_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
      struct eyeplus_ :  ext::abstract_<eyeplus_>
      {
        typedef ext::abstract_<eyeplus_> parent;
        template<class... Args>
        static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
        BOOST_AUTO_DECLTYPE_BODY( dispatching_eyeplus_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
      };
  }
  namespace ext
  {
      template<class Site>
      BOOST_FORCEINLINE generic_dispatcher<tag::eyeplus_, Site> dispatching_eyeplus_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
      {
        return generic_dispatcher<tag::eyeplus_, Site>();
      }
      template<class... Args>
      struct impl_eyeplus_;
  }

  /**
   * @brief Perform eyeplus(a, l)computation
   *
   * For any given matrix expression computes eye(right_size,  right_type) + a*l .
   * l defaults to 1.
   *
   * @param    a Matrix expression to factorize
   * @param    l scalar factor to apply to a
   *
   * @return an expression for the result
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::eyeplus_, eyeplus, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::eyeplus_, eyeplus, 2)

}

#endif

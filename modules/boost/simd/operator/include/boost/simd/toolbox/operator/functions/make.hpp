//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MAKE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MAKE_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/preprocessor/repeat.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_make make
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/make.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::make_(A0,A0)>::type
 *     make(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of make
 * \param a1 the second parameter of make
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag make_ of functor make 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct make_ : ext::unspecified_<make_> { typedef ext::unspecified_<make_> parent; };
  }
} }

namespace boost { namespace dispatch
{
  /* We specialize functor directly due to arity limitations, and we only dispatch on the target.
   * We also avoid having to dispatch return type deduction, and we cast all arguments to the scalar
   * matching the target. */
  template<class Site>
  struct functor<boost::simd::tag::make_, Site>
  {
    template<class Sig>
    struct result;

    #define M1(z,n,t) static_cast<typename meta::scalar_of<typename Target::type>::type>(a##n)

    #define M0(z,n,t)                                                                      \
    template<class This, BOOST_PP_ENUM_PARAMS(n, class A), class Target>                   \
    struct result<This(BOOST_PP_ENUM_PARAMS(n, A), Target)>                                \
      : meta::strip<Target>::type                                                          \
    {                                                                                      \
    };                                                                                     \
                                                                                           \
    template<BOOST_PP_ENUM_PARAMS(n, class A), class Target>                               \
    typename Target::type                                                                  \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a), Target const&) const           \
    {                                                                                      \
      typename meta::dispatch_call<boost::simd::tag::make_(Target), Site>::type callee;    \
      return callee(BOOST_PP_ENUM(n, M1, ~));                                              \
    }

    BOOST_DISPATCH_PP_REPEAT_POWER_OF_2(M0, ~)
    #undef M0
    #undef M1
  };
} }

namespace boost { namespace simd
{
  #define M0(z,n,t)                                                                        \
  template<class T, BOOST_PP_ENUM_PARAMS(n, class A)> BOOST_DISPATCH_FORCE_INLINE          \
  T make(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))                                      \
  {                                                                                        \
    typename boost::dispatch::make_functor<tag::make_, T>::type callee;                    \
    return callee(BOOST_PP_ENUM_PARAMS(n, a), boost::dispatch::meta::as_<T>());            \
  }

  BOOST_DISPATCH_PP_REPEAT_POWER_OF_2(M0, ~)
  #undef M0
} }

#endif

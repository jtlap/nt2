//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SATURATE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_saturate saturate
 *
 * \par Description
 * saturate the value a0 in the template parameter type T,
 * but the value returned is of type A0
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/saturate.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::saturate_(A0)>::type
 *     saturate(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of saturate
 *
 * \param T template parameter of saturate
 *
 * \return a value of the same type as the parameter
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
     * \brief Define the tag saturate_ of functor saturate
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct saturate_ : ext::elementwise_<saturate_>
    {
      typedef ext::elementwise_<saturate_> parent;
    };
  }

  // Explicit version : saturate(x, class_)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::saturate_, saturate, 2)

  // Implicit version : saturate<T>(x)
  template<class T,class A0> BOOST_FORCEINLINE
  typename boost::dispatch::meta::
                  call< tag::saturate_( A0 const&
                                      , boost::dispatch::meta::as_<T>
                                      )
                      >::type
  saturate(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::saturate_, A0>::type callee;
    return callee(a0,boost::dispatch::meta::as_<T>());
  }
} }

#endif

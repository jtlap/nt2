//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_ARITH_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_ARITH_HPP_INCLUDED

/*!
 * \file
**/

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_arith arith
 *
 * \par Description
 * arithmetic sequences with optionnal start
 * (default 0) and step (default 1).
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/arith.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class Target>
 *   meta::call<tag::arith_(as_<Target>)>::type
 *   arith();
 *   template <class A0, class Target>
 *   meta::call<tag::arith_(A0,as_<Target>)>::type
 *   arith(const A0 & seed);
 *   template <class A0, class A1, class Target>
 *   meta::call<tag::arith_(A0, A1, as_<Target>)>::type
 *   arith(const A0 & seed, const A1& step);
 * }
 * \endcode
 *
 * \param seed the initial value of the SIMD enumeration
 *
 * \return a vector \c v of the same value type as Target which values are
 * given by:
 *
 * \code
 * v = [ seed seed+step ... seed + (cardinal -1)*step ]
 * \endcode
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag arith_ of functor arith
     *        in namespace boost::simd::tag for toolbox boost.simd.arith
    **/
    struct arith_ : ext::unspecified_<arith_> { typedef ext::unspecified_<arith_> parent; };
  }

  template<class T> BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            call<tag::arith_(boost::dispatch::meta::as_<T>)
                            >::type
  arith()
  {
    typename boost::dispatch::make_functor<tag::arith_>::type callee;
    return callee(boost::dispatch::meta::as_<T>());
  }

  template<class T,class A0> BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            call<tag::arith_( A0 const&
                                , boost::dispatch::meta::as_<T>
                                )
                            >::type
  arith(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::arith_, A0>::type callee;
    return callee(a0,boost::dispatch::meta::as_<T>());
  }

  template<class T,class A0, class A1> BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            call<tag::arith_( A0 const&,
                                  A1 const&,
                                  boost::dispatch::meta::as_<T>
                                )
                            >::type
  arith(A0 const& a0, A1 const& a1)
  {
    typename boost::dispatch::make_functor<tag::arith_, A0>::type callee;
    return callee(a0,a1,boost::dispatch::meta::as_<T>());
  }
} }

#endif

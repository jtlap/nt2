//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_REAL_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_REAL_SPLAT_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_real_splat Real_splat
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/real_splat.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::real_splat_(A0)>::type
 *     Real_splat();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Real_splat
 *
 * \return type T value
 *
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag Real_splat of functor Real_splat
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    template<boost::simd::uint32_t F,boost::simd::uint64_t D>
    struct Realpattern : ext::constant_< Realpattern<F, D> >
    {
      template<class Target, class Dummy=void>
      struct apply {};

      template<class T,class Dummy>
      struct apply<boost::dispatch::meta::single_<T>,Dummy> : meta::single_<F> {};

      template<class T, class Dummy>
      struct apply<boost::dispatch::meta::double_<T>,Dummy> : meta::double_<D> {};
    };
  }
  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint64_t D, boost::simd::uint32_t F>
  inline Target real_constant()
  {
    boost::dispatch::functor< tag::Realpattern<F,D> > callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of float
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint32_t F>
  inline Target single_constant()
  {
    typename dispatch::make_functor<tag::Realpattern<F,0>, Target>::type callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of double
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint64_t D>
  inline Target double_constant()
  {
    typename dispatch::make_functor<tag::Realpattern<0,D>, Target>::type callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns dependant on target type
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, uint64_t Value> inline Target Const()
  {
    typedef tag::Realpattern<boost::simd::uint32_t(Value),Value> patterns;
    typename dispatch::make_functor<patterns, Target>::type callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif

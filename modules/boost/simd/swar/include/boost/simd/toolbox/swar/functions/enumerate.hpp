//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_ENUMERATE_HPP_INCLUDED

/*!
 * \file
**/

#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_enumerate enumerate
 *
 * \par Description
 * enumerate values starting from a given seed.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/enumerate.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class Target>
 *   meta::call<tag::enumerate_(A0,as_<Target>)>::type
 *   enumerate(const A0 & seed);
 * }
 * \endcode
 *
 * \param seed the initial value of the SIMD enumeration
 *
 * \return a vector \c v of the same value type as Target which values are
 * given by:
 *
 * \code
 * v = [ seed seed+1 ... seed + cardinal -1 ]
 * \endcode
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag enumerate_ of functor enumerate
     *        in namespace boost::simd::tag for toolbox boost.simd.enumerate
    **/
    struct enumerate_ : ext::unspecified_<enumerate_> { typedef ext::unspecified_<enumerate_> parent; };
  }

  template<class T,class A0> BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            call<tag::enumerate_( A0 const&
                                , boost::dispatch::meta::as_<T>
                                )
                            >::type
  enumerate(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::enumerate_, A0>::type callee;
    return callee(a0,boost::dispatch::meta::as_<T>());
  }

  template<class T,class A0, class A1> BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            call<tag::enumerate_( A0 const&, 
                                  A1 const&, 
                                  boost::dispatch::meta::as_<T>
                                )
                            >::type
  enumerate(A0 const& a0, A1 const& a1)
  {
    typename boost::dispatch::make_functor<tag::enumerate_, A0>::type callee;
    return callee(a0,a1,boost::dispatch::meta::as_<T>());
  }  
} }

#endif

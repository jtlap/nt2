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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SATURATE_TO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SATURATE_TO_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_saturate_to saturate_to
 *
 * \par Description
 * saturate_to the value a0 in the template parameter type T,
 * but the value returned is of type A0
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/saturate_to.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::saturate_to_(A0)>::type
 *     saturate_to(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of saturate_to
 * 
 * \param T template parameter of saturate_to
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
     * \brief Define the tag saturate_to_ of functor saturate_to 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct saturate_to_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }


  template<class T, class A0>
  BOOST_FORCEINLINE typename boost::dispatch::meta::
    call<tag::saturate_to_(A0 const&,
                        boost::dispatch::meta::as_<T> const&)>::type
    saturate_to(A0 const& a0)
    {
      return typename boost::dispatch::make_functor<tag::saturate_to_, A0>::type()(a0, boost::dispatch::meta::as_<T>());
    }   
} }

#endif

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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_LOAD_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/dispatch/meta/as.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_load load
 *
 * \par Description
 * Load data of type T from the memory zone given by (a0,a1)
 * with or without a re-alignment offset
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/load.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class T, class A0, class A1> inline
 *   typename boost::dispatch::meta::call<tag::load_ ( A0 const&, A1 const&
 *                                                 , boost::dispatch::meta::as_<T>
 *                                                  )
 *                                       >::type
 *   load(A0 const& a0, A1 const& a1 = 0 );
 *   template<class T, int Offset, class A0, class A1> inline
 *   typename boost::dispatch::meta::call<tag::load_ ( A0 const&, A1 const&
 *                                                 , boost::dispatch::meta::as_<T>
 *                                                 , boost::mpl::int_<Offset>
 *                                                 )
 *                                        >::type
 *   load(A0 const& a0, A1 const& a1 = 0 );
 * }
 * \endcode
 *
 * \param T type to load
 * \param Offset offset with aligned memory
 * 
 * \param a0 base address
 * \param a1 offset to load at
 * 
 * \return object of type T
 *  
**/

namespace boost { namespace simd
{
  namespace tag {
    /*!
     * \brief Define the tag load_ of functor load 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct load_ : ext::elementwise_<load_> { typedef ext::elementwise_<load_> parent; };
  }
  //////////////////////////////////////////////////////////////////////////////
  // Load a data of type T from the memory zone given by (a0,a1)
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class A0,class A1>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::load_ ( A0 const&, A1 const&
                                                , boost::dispatch::meta::as_<T>
                                                )
                            >::type
  load(A0 const& a0,A1 const& a1)
  {
    typename boost::dispatch::make_functor<tag::load_, A0>::type callee;
    return callee(a0,a1,boost::dispatch::meta::as_<T>());
  }
  
  template<class T,class A0>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::load_ ( A0 const&, int const&
                                                , boost::dispatch::meta::as_<T>
                                                )
                            >::type
  load(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::load_, A0>::type callee;
    return callee(a0,0,boost::dispatch::meta::as_<T>());
  }

  //////////////////////////////////////////////////////////////////////////////
  // Load a data of type T from the memory zone given by (a0,a1) and a sub-type
  // level offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T,int Offset, class A0,class A1>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::load_ ( A0 const&, A1 const&
                                                , boost::dispatch::meta::as_<T>
                                                , boost::mpl::int_<Offset>
                                                )
                            >::type
  load(A0 const& a0,A1 const& a1 = 0)
  {
    typename boost::dispatch::make_functor<tag::load_, A0>::type callee;
    return callee(a0,a1,boost::dispatch::meta::as_<T>(),boost::mpl::int_<Offset>());
  }
  
  template<class T,int Offset, class A0,class A1>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::load_ ( A0 const&, int const&
                                                , boost::dispatch::meta::as_<T>
                                                , boost::mpl::int_<Offset>
                                                )
                            >::type
  load(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::load_, A0>::type callee;
    return callee(a0,0,boost::dispatch::meta::as_<T>(),boost::mpl::int_<Offset>());
  }
} }

#endif

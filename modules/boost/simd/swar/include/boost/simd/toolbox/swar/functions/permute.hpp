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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_PERMUTE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_PERMUTE_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
// #include <iostream>
// #include <nt2/sdk/meta/type_id.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_permute permute
 *
 * \par Description
 * returns a vector the elements of which are
 * those of a0 in permute order
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/permute.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::permute_(A0)>::type
 *     permute(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the  parameter of permute
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * \par
 * This is a swar operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation is a transform of an SIMD vector, that will return
 * vectors obtained on a non necessarily elementwise basis from the inputs
 * elements
 * \par
 * If usable and used in scalar mode, it reduces to the operation
 * on a one element vector.
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag permute_ of functor permute 
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct permute_ : ext::unspecified_<permute_> { typedef ext::unspecified_<permute_> parent; };
  }
  //  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::permute_, permute, 9)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::permute_, permute, 5)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::permute_, permute, 3)
  namespace details {
    template < int T> struct zut_ { static const int value = T; }; 
  }
//   template < int i0, int i1, int i2,  int i3,
//              int i4, int i5, int i6,  int i7,  class T>
//   inline T permute(const T & a0)
//   {
//     typedef details::zut_<i0> I0;
//     typedef details::zut_<i1> I1;
//     typedef details::zut_<i2> I2;
//     typedef details::zut_<i3> I3;
//     typedef details::zut_<i0> I4;
//     typedef details::zut_<i1> I5;
//     typedef details::zut_<i2> I6;
//     typedef details::zut_<i3> I7;
// //     std::cout << "--" << nt2::type_id<I0>() << std::endl;
// //     std::cout << "--" << nt2::type_id(I0()) << std::endl; 
//     return permute(a0, I0(), I1(), I2(), I3(), I4(), I5(), I6(), I7()); 
//    }
  template < int i0, int i1, int i2,  int i3,  class T>
  inline T permute(const T & a0)
  {
    typedef details::zut_<i0> I0;
    typedef details::zut_<i1> I1;
    typedef details::zut_<i2> I2;
    typedef details::zut_<i3> I3;
//     std::cout << "--" << nt2::type_id<I0>() << std::endl;
//     std::cout << "--" << nt2::type_id(I0()) << std::endl; 
    return permute(a0, I0(), I1(), I2(), I3()); 
   }
  template < int i0, int i1,  class T>
  inline T permute(const T & a0)
  {
    typedef details::zut_<i0> I0;
    typedef details::zut_<i1> I1;
    return permute(a0, I0(), I1()); 
   }
} }

#endif



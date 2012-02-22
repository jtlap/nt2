//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ISROW_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ISROW_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core_isrow isrow
 *
 * \par Description
 * Returns true or false according a0 is an "row" container
 * (1Xn) or not.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/isrow.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg is_row
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     bool isrow(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of isrow
 * 
 * \return a bool value
 *  
**/

namespace nt2
{
  namespace tag
  {
    struct isrow_ : ext::unspecified_<isrow_>
    {
      typedef ext::unspecified_<isrow_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isrow_, isrow, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isrow_, is_row, 1)
}

#endif


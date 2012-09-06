//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ISVECTORALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ISVECTORALONG_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core_isvectoralong isvectoralong
 *
 * \par Description
 * Returns true or false according a0 is an "vector" container
 * along the chosen dimension.
 * isrow(a0)    ==  isvectoralong(a0, 1)
 * iscolumn(a0) ==  isvectoralong(a0, 2)
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/isvectoralong.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1>
 *     bool isvectoralong(const A0 & a0, const A1& dim);
 * }
 * \endcode
 *
 * \param a0 the first parameter of isvectoralong
 *
 * \return a bool value
 *
**/

namespace nt2
{
  namespace tag
  {
    struct isvectoralong_ : ext::unspecified_<isvectoralong_>
    {
      typedef ext::unspecified_<isvectoralong_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isvectoralong_, isvectoralong, 2)
}

#endif


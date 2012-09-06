//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ISDIAGONAL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ISDIAGONAL_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core_isdiagonal isdiagonal
 *
 * \par Description
 * Returns true or false according a0 is an "vector" container
 * (1Xn or nX1) or not.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/isdiagonal.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg is_vector
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     bool isdiagonal(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of isdiagonal
 * 
 * \return a bool value
 *  
**/

namespace nt2
{
  namespace tag
  {
    struct isdiagonal_ : ext::unspecified_<isdiagonal_>
    {
      typedef ext::unspecified_<isdiagonal_> parent;
    };
  }

    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isdiagonal_, isdiagonal, 1)
    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isdiagonal_, is_diagonal, 1)
    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isdiagonal_, isdiagonal, 2)
    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isdiagonal_, is_diagonal, 2)
    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isdiagonal_, isalmostdiagonal, 2)
    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isdiagonal_, is_almost_diagonal, 2)   
}

#endif


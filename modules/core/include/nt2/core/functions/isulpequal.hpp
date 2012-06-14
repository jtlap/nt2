//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ISULPEQUAL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ISULPEQUAL_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core_isulpequal isequal
 *
 * \par Description
 * Returns true or false according a0 and a1 have element that differ
 * by more than d ulps. d default to 0.5
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/isulpequal.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg eq
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     bool isulpequal(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of isulpequal
 * 
 * \return a bool value
 *  
**/

namespace nt2
{
  namespace tag
  {
    struct isulpequal_ : ext::unspecified_<isulpequal_>
    {
      typedef ext::unspecified_<isulpequal_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isulpequal_, isulpequal, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isulpequal_, areulpequal, 2)      
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isulpequal_, isulpequal, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isulpequal_, areulpequal, 3)      
}

#endif


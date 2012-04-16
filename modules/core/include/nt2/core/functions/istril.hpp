//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ISTRIL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ISTRIL_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core_istril istril
 *
 * \par Description
 * Returns true or false according a0 is a lower triangular matrix
 * or not.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/istril.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg is_tril
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     bool istril(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of istril
 * 
 * \return a bool value
 *  
**/

namespace nt2
{

  namespace tag
  {
    struct istril_ : ext::unspecified_<istril_>
    {
      typedef ext::unspecified_<istril_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::istril_, istril, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::istril_, is_tril, 1)

}

#endif


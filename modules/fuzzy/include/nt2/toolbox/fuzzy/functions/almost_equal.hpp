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
#ifndef NT2_TOOLBOX_FUZZY_FUNCTIONS_ALMOST_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTIONS_ALMOST_EQUAL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup fuzzy
 * \defgroup fuzzy_almost_equal almost_equal
 *
 * \par Description
 * \f$ a0 \in \quad ]a_1-\mathop{\mathrm{predecessor}}(a_1,|a_2|),a_1-\mathop{\mathrm{successor}}(a_1,|a_2|)[\f$
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/almost_equal.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::almost_equal_(A0,A0,A0)>::type
 *     almost_equal(const A0 & a0,const A0 & a1,const A0 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of almost_equal
 * \param a1 the second parameter of almost_equal
 * \param a2 the third parameter of almost_equal
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * This is a predicate operation. Such operations return bool in scalar mode,
 * but not in SIMD mode.
 * \par
 * The return type in SIMD mode is the common type of the parameters and is
 * a 'signed boolean' type. This means that in this case True has all its bits
 * sets to one. This is to facilitate masking operations. You are invited to
 * consult the rationale.
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag almost_equal_ of functor almost_equal 
     *        in namespace nt2::tag for toolbox fuzzy
    **/
    struct almost_equal_ : ext::elementwise_<almost_equal_> {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::almost_equal_, almost_equal, 3)
}

#endif

// modified by jt the 25/12/2010

/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_COND_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_COND_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_cond cond
 *
 * \par Description
 * Elementary Least square
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/cond.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \param a the matrix a 
 *
 * \param p the norm in which cond is computed
 *          p can be 1, 2 inf or 'fro'
 * 
 * \par Notes
 *   Call the dedicated lapack routines available on the target.
 * \par
 *  
**/
//==============================================================================
// cond actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag cond_ of functor cond
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct cond_ :  tag::formal_ { typedef tag::formal_ parent; };
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cond_, cond, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cond_, cond, 2)

}

#endif


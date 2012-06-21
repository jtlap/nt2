/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_MPOWER_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_MPOWER_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mpower mpower
 *
 * \par Description
 * suqre root of a matrix
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/mpower.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \param a the matrix or vector expression a 
 *
 * \param type of mpower required
 * 
 * \par Notes
 *   Call the dedicated lapack routines available on the target.
 * \par
 *  
**/

namespace nt2
{
  namespace tag
  {         
    /*!
     * \brief Define the tag mpower_ of functor mpower
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct mpower_ :  tag::formal_ { typedef tag::formal_ parent; };
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mpower_, mpower, 2)
    
} 

#endif


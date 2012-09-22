/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_ROT90_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_ROT90_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_rot90 rot90
 *
 * \par Description
 * rotate matrix by mutiples of 90°
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/rot90.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 *  
**/
//==============================================================================
// rot90 actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag rot90_ of functor rot90
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct rot90_   :  tag::formal_ { typedef tag::formal_ parent; };

  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rot90_, rot90, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rot90_, rot90, 1)

}

#endif

/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_NULL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_NULL_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_null null
 *
 * \par Description
 * null space of a0 up to epsilon
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/null.hpp>
 * \endcode
 * 
 * 
 *  
**/
//==============================================================================
// null actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag null_ of functor null
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct null_ :  tag::formal_ { typedef tag::formal_ parent; };
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::null_, null, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::null_, null, 2)

}

#endif

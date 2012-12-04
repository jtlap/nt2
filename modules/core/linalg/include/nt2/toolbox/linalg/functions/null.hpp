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
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * @brief null:  null space of a matrix expression.
 *    z = null(a) is an orthonormal basis for the null space of a obtained
 *    from the singular value decomposition.  that is,  a*z has negligible
 *    elements, size(z,2) is the nullity of a,
 *    and transconj(z)*z = eye(size(transconj(z)*z)).
 *
 *    null(a, tol) changes the tolerance to which a*z is considered null
 *    the default is eps(w(1)) where w(1) is the smalest singular vale of
 *    a
 *
 **/

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

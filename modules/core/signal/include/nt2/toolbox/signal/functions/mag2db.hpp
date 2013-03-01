/*******************************************************************************
 *         Copyright 2003-2013 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
/*!
 * \file
 **/
#ifndef NT2_TOOLBOX_SIGNAL_FUNCTIONS_MAG2DB_HPP_INCLUDED
#define NT2_TOOLBOX_SIGNAL_FUNCTIONS_MAG2DB_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct mag2db_ : ext::elementwise_<mag2db_>
    {
      typedef ext::elementwise_<mag2db_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::mag2db_, mag2db, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::mag2db_, mag2db, 2)
}

#endif

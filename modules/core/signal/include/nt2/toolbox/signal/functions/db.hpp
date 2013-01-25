!/*******************************************************************************
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
#ifndef NT2_TOOLBOX_SIGNAL_FUNCTIONS_DB_HPP_INCLUDED
#define NT2_TOOLBOX_SIGNAL_FUNCTIONS_DB_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup signal
 * \defgroupsignal_db db
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag db_ of functor db
     *        in namespace nt2::tag for toolbox signal
    **/
    struct db_ : ext::elementwise_<db_> { typedef ext::elementwise_<db_> parent; };


  }
  namespace details
  {
    struct voltage_{};
    struct power_{};
  }
  meta::as_<details::voltage_>    const voltage_    = {};
  meta::as_<details::power_>      const power_      = {};

  NT2_FUNCTION_IMPLEMENTATION(tag::db_, db, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::db_, db, 2)
}



#endif

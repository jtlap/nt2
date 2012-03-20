//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_DETAILS_EXCEPTION_HPP_INCLUDED
#define NT2_SDK_ERROR_DETAILS_EXCEPTION_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the \ref nt2::exception class
 */

#include <boost/exception/exception.hpp>
#include <stdexcept>
#include <string>

namespace nt2
{
  //============================================================================
  /*!
   * \ingroup error
   * exception is the base abstract class for all NT2 exceptions. It implements
   * the classical STD compliant interface, and is compatible with boost::exception.
   */
  //============================================================================
  struct exception : boost::exception, std::runtime_error
  {
    exception(const std::string& msg) : boost::exception(), std::runtime_error(msg) {}
  };
}

#endif

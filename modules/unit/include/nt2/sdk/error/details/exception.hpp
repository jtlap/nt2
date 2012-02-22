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
 * \brief Defines the \ref boost::dispatch::exception class
 */

#include <iosfwd>
#include <string>
#include <boost/exception/all.hpp>

//==============================================================================
/*!
 * \ingroup error
 * Define a new Boost.Dispatch exception information carrier. Information carriers are
 * used to feed informations from the throwing site to the exception instance
 * in a safe way.
 *
 * \param NAME Name of the diagnostic carrier
 * \param TYPE Type of the information gathered by the carrier
 */
//==============================================================================
#define NT2_ERROR_INFO(NAME,TYPE)                                     \
typedef boost::error_info<struct BOOST_PP_CAT(tag_,NAME),TYPE>  NAME  \

namespace nt2
{
  //============================================================================
  /*!
   * \ingroup error
   * exception is the base abstract class for all Boost.Dispatch exceptions. It implements
   * the classical STD compliant interface, is compatible with boost::exception
   * and can be directly streamed for easy display.
   */
  //============================================================================
  struct exception : boost::exception, std::runtime_error
  {
    exception(const std::string& msg) : boost::exception(), std::runtime_error(msg) {}

    //==========================================================================
    /*!
     * Stream exception information context to an output stream. This abstract
     * member function has to be overloaded when defining a new exception
     * sub-class.
     *
     * \param os an output stream to send the exception context to.
     */
    //==========================================================================
    virtual void display(std::ostream& os) const throw() = 0;
  };

  //============================================================================
  /*!
   * \ingroup error
   * Stream an exception information to an output stream.
   *
   * \param os an output stream to send the exception context to.
   * \param e  exception instance to stream out.
   *
   * \return The updated output stream
   */
  //============================================================================
  std::ostream& operator<<( std::ostream& os, exception const& e );
}

#endif

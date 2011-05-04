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

//==============================================================================
// Exception interface with std::exception and boost::exception
//==============================================================================
#include <iosfwd>
#include <boost/exception/all.hpp>

//==============================================================================
// Define a new NT2 exception informations diagnostic holder
//==============================================================================
#define NT2_ERROR_INFO(NAME,TYPE)                                     \
typedef boost::error_info<struct BOOST_PP_CAT(tag_,NAME),TYPE>  NAME  \

namespace nt2
{
  //==============================================================================
  // Exception base class
  //==============================================================================
  struct exception : virtual boost::exception, virtual std::exception
  {
    virtual ~exception() throw() {}
    virtual const char* what() const throw();
    virtual void display(std::ostream& os) const throw() =0;
  };

  std::ostream& operator<<( std::ostream& os, exception const& e );
}

#endif

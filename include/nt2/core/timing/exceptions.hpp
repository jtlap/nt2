/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_TIMING_EXCEPTIONS_HPP_INCLUDED
#define NT2_CORE_TIMING_EXCEPTIONS_HPP_INCLUDED

#include <nt2/sdk/errors/details/exception.hpp>

namespace nt2 { namespace time
{
  struct unbalanced_timing : virtual nt2::exception
  {
    virtual void display(std::ostream& os) const throw()
    {
      os  << "Unbalanced timer use\n";
    }
  };
} }

#endif

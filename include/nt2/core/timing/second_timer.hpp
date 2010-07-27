/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_TIMING_SECOND_TIMER_HPP_INCLUDED
#define NT2_CORE_TIMING_SECOND_TIMER_HPP_INCLUDED

#include <nt2/core/timing/tic.hpp>

namespace nt2 { namespace time
{
  /*!
    second_timer is a RAII-based timing class that performs safe timing
    in a given code block and prevent the misuse of the tic/toc functions pair.

    @example second_timer.cpp
   **/
  struct second_timer
  {
    /*!
      @ingroup Constructors and Destructors

      Creates an instance of second_timer, links it to an user-defined variable
      that will contains the result of the timing when the current instance will
      go out of scope and starts a timing section calling tic. The display
      parameters controls if the inner toc call will display the elapsed time
      automatically or not.
     **/
     second_timer(double& e, bool d = true) : elapsed(e), display(d) { tic(); }

    /*!
      @ingroup Constructors and Destructors

      When a second_timer instance is destroyed, complete the second-based timing
      section, store it into the user-defined variable and, depending on the display
      state, displays the measurement.
     **/
    ~second_timer () { elapsed = toc(display); }

    double& elapsed;
    bool display;
  };
} }

#endif

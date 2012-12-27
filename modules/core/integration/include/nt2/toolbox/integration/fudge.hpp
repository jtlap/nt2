/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUDGE_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUDGE_HPP_INCLUDED
#include <nt2/include/functions/is_invalid.hpp>

namespace nt2
{
  namespace details
  {
    template < class FUNC, int IND, class VT, class INPUT, bool test = true>
    struct fudge
    {
      static void fdg(const  FUNC & f, VT&y, size_t& fcnt, const bool & singular,
                      const INPUT& x, const INPUT& shift)
      {
        size_t i =  IND;
        if ((singular) && nt2::is_invalid(y(i)))// Fudge to avoid nans or infinities.
        {
          y(i) = f(x+shift); ++fcnt;
        }
      }
    };

    template < class FUNC, int IND, class VT, class INPUT>
    struct fudge < FUNC, IND, VT, INPUT, false>
    {
      static void fdg(const  FUNC &, VT&, size_t& , const bool &,
                      const INPUT&, const INPUT&) {}
    };

  }

}


#endif

/*******************************************************************************
 *         Copyright 2003-2013 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_SIGNAL_FUNCTIONS_GENERIC_DB2POW_HPP_INCLUDED
#define NT2_TOOLBOX_SIGNAL_FUNCTIONS_GENERIC_DB2POW_HPP_INCLUDED
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/functions/log10.hpp>



namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db2pow_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
    )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return a1*nt2::exp10(a0/Ten<result_type>());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db2pow_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
    )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::exp10(a0/Ten<result_type>());
    }
  };

} }


#endif

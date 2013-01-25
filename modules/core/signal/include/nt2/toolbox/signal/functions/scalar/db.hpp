/*******************************************************************************
 *         Copyright 2003-2013 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_SIGNAL_FUNCTIONS_GENERIC_DB_HPP_INCLUDED
#define NT2_TOOLBOX_SIGNAL_FUNCTIONS_GENERIC_DB_HPP_INCLUDED
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/functions/log10.hpp>



namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db_, tag::cpu_
                              , (A0)
                              , (generic_< arithmetic_<A0> >)
    )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return Ten<result_type>()*nt2::log10(sqr_abs(a0));
    }
   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db_, tag::cpu_
                              , (A0)
                              , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A0> >)
    )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return Ten<result_type>()*nt2::log10(sqr_abs(a0)/a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db_, tag::cpu_
                              , (A0)
                              , (generic_< arithmetic_<A0> >)
                              (target_< unspecified_<A0> >)
    )
  {

    typedef A0 result_type;
    typedef meta::as_<details::voltage_> volt_t;
    typedef meta::as_<details::power_>   power_t;
    BOOST_FORCEINLINE result_type operator()(const A0& e, const & volt_t) const
    {
      return nt2::db(a0);
    }
    BOOST_FORCEINLINE result_type operator()(const A0& e, const & power_t) const
    {
      return Ten<result_type>()*nt2::log10(sqr_abs(a0)/a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db_, tag::cpu_
                              , (A0)
                              , (generic_< arithmetic_<A0> >)
    )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::exp10(a0/Twenty<result_type>());
    }
  };

} }


#endif
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of db.hpp<2>
// /////////////////////////////////////////////////////////////////////////////

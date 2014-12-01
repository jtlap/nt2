//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_UNIFCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_UNIFCDF_HPP_INCLUDED
#include <nt2/statistics/functions/unifcdf.hpp>

#include <nt2/include/functions/is_not_greater.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/options.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( unifcdf_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
      {
        return max(Zero<A0>(), min(One<A0>(), a0));
      }
  };

  BOOST_DISPATCH_IMPLEMENT  ( unifcdf_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return eval(a0, A1());
    }
  private:
    BOOST_FORCEINLINE static
    result_type eval(A0 const& a0, const nt2::policy<ext::lower_>&)
    {
      return unifcdf(a0);
    }
    BOOST_FORCEINLINE static
    result_type eval(A0 const& a0, const nt2::policy<ext::upper_>&)
    {
      return oneminus(unifcdf(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( unifcdf_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(3)
    {
      A0 z = a2-a1;
      return nt2::if_allbits_else( is_lez(z)
                                 , nt2::if_zero_else( lt(a0,a1)
                                                    , nt2::if_else( is_not_greater(a0,a2)
                                                                  , (a0-a1)/z
                                                                  , One<A0>()
                                                                  )
                                                    )
                                 );
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( unifcdf_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                              (unspecified_<A3>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1,
                                             A2 const& a2, A3 const&) const
    {
      return eval(a0, a1, a2, A3());
    }
  private:
    BOOST_FORCEINLINE static
      result_type eval(A0 const& a0, A1 const& a1,
                       A2 const& a2, const nt2::policy<ext::lower_>&)
    {
      return unifcdf(a0, a1, a2);
    }
    BOOST_FORCEINLINE static
      result_type eval(A0 const& a0, A1 const& a1,
                       A2 const& a2, const nt2::policy<ext::upper_>&)
    {
      A0 z = a2-a1;
      return nt2::if_allbits_else( is_lez(z)
                                 , nt2::if_else( lt(a0,a1)
                                               , One<A0>()
                                               , nt2::if_else_zero( is_not_greater(a0,a2)
                                                                  , (a2-a0)/z
                                                                  )
                                               )
                                 );
    }
  };
} }

#endif

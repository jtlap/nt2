/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFCDF_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/unifcdf.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/is_ngt.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        return nt2::if_zero_else(nt2::is_ltz(a0),
                                 nt2::if_else(boost::simd::is_ngt(a0,One<A0>()),
                                              a0,
                                              One<A0>()
                                              )
                                 ); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(3)
      {
        BOOST_AUTO_TPL(z, a2-a1);
        return nt2::if_allbits_else(is_lez(z),
                                    nt2::if_zero_else(lt(a0,a1),
                                                      nt2::if_else(boost::simd::is_ngt(a0,a2),
                                                                   (a0-a1)/z,
                                                                   One<A0>()
                                                                   )
                                                      )
                                    ); 
      }
  };

} }

#endif

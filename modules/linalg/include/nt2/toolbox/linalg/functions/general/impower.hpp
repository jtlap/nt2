/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_IMPOWER_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_IMPOWER_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/impower.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/power.hpp>
#include <nt2/include/functions/round.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/constants/one.hpp>
#include <iostream>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::impower_, tag::cpu_
                              , (A0)(A1)
                            , (ast_<A0>)
                              (scalar_<arithmetic_<A1> >)
                            )
  {
    typedef typename A0::value_type       value_type;
    typedef typename A0::index_type       index_type;
    typedef table<value_type, index_type> result_type;
    NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(is_flint(a1), "impower requires the second argument to be int or flint"); 
      BOOST_ASSERT_MSG(is_square(a0),"impower requires the first input to be a square matrix");
      if(is_ltz(a1))
        return nt2::inv(nt2::impower(a0, -a1)); 
      else {
        value_type m = nt2::round(a1); //MAYBE UNECESSARY
        result_type q, t;
        // tie(q, t) = schur(a0,'N'/*"complex"*/); // t is complex schur form.        result_type e, v;
        if (false && isdiagonal(t))
          {
            t = nt2::from_diag(nt2::pow(diag_of(t), m));
            return nt2::mtimes(q, nt2::mtimes(t, nt2::trans(nt2::conj(q))));
          }
        else
          { //use iterative method
            result_type r = nt2::eye(nt2::size(a0), meta::as_<value_type>());
            //            NT2_DISP(a0); 
            result_type a00 = a0;
            result_type a01;  // a01 MUST DISAPPEAR IF ALIASING PB ARE SOLVED
            //            NT2_DISP(a00); 
            while (true)
              {
                // old m "<< m << std::endl;
                //                NT2_DISP(r); 
                if (m < nt2::One<A1>()) return r; 
                if (nt2::is_odd(m))
                  {
                    result_type r1 = nt2::mtimes(a00, r);// r1 MUST DISAPPEAR IF ALIASING PB ARE SOLVED
                    r =  r1; 
                  }
                a01 =  nt2::mtimes(a00, a00);
                a00 =  a01; 
                m =  nt2::trunc(m/2); //Half<value_type>(); or >> 1
//                 NT2_DISP(a00); 
//                 std::cout <<" m "<< m << std::endl; 
              }
            return r;
          }
      }
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::impower_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_<fundamental_<A0> >)
                              (scalar_<fundamental_<A1> >) 
                            )
  {
    typedef typename nt2::meta::as_floating<A0>::type result_type; 
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::pow(a0, a1); 
    }
  };  
} }

#endif

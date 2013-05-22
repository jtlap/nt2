//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SCALAR_FIBONACCI_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SCALAR_FIBONACCI_HPP_INCLUDED

#include <nt2/combinatorial/functions/fibonacci.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/scalar/round.hpp>
#include <nt2/include/functions/scalar/pow.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/gold.hpp>
#include <nt2/include/constants/cgold.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::fibonacci_, tag::cpu_,
                             (A0)(A1),
                             ((scalar_<arithmetic_<A0> >))
                             ((scalar_<arithmetic_<A0> >))
                             ((scalar_<integer_<A1> >))
                            )
  {
    typedef A0  result_type;
    inline result_type operator()(A0 const& a, const A0 & b, const A1 & n) const
    {
      const A0 gold1 = -rec(nt2::Gold<result_type>());
      nt2::container::table<A0> m = nt2::cons(of_size(2, 2),
                                              nt2::One<result_type>(), nt2::Gold<result_type>(),
                                              nt2::One<result_type>(),gold1
                                             );
      BOOST_AUTO_TPL(nm1, nt2::minusone(n));
      nt2::container::table<A0> c = nt2::linsolve(m, catv(a, b));
      BOOST_AUTO_TPL(f, c(1)*nt2::pow(nt2::Gold<result_type>(), nm1)+c(2)*nt2::pow(gold1, nm1));
      if (nt2::is_flint(a) && nt2::is_flint(b))
        return nt2::round(f);
      else
        return f;
    }

  };

} }
#endif

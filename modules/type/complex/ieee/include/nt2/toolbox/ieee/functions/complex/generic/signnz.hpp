//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTIONS_COMPLEX_GENERIC_SIGNNZ_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTIONS_COMPLEX_GENERIC_SIGNNZ_HPP_INCLUDED

#include <nt2/toolbox/ieee/functions/signnz.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::signnz_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return if_else(is_eqz(a0), nt2::One<A0>(), nt2::sign(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::signnz_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename nt2::meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::if_else(nt2::is_eqz(a0),
                          nt2::One<result_type>(),
                          result_type(nt2::Zero<result_type>(), nt2::signnz(nt2::imag(a0)))
                         );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::signnz_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::signnz(nt2::real(a0)));
    }
  };

} }

#endif

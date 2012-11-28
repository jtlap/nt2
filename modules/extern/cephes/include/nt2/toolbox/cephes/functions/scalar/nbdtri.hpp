//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CEPHES_FUNCTIONS_SCALAR_NBDTRI_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTIONS_SCALAR_NBDTRI_HPP_INCLUDED
#include <nt2/toolbox/cephes/functions/nbdtri.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/functions/scalar/is_lez.hpp>
#include <nt2/include/constants/infinites.hpp>

extern "C" { extern double cephes_nbdtri(int,int,double); }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::nbdtri_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)(scalar_< arithmetic_<A2> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      return nt2::cephes::nbdtri(a0, a1, double(a2));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is real
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::nbdtri_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)(scalar_< floating_<A2> >)
                            )
  {

    typedef typename meta::strip<A2>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      if (is_lez(a0)||is_lez(a1)) return nt2::Nan<A2>();
      return cephes_nbdtri(a0, a1, double(a2)); }
  };
} }


#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_EXTRACT_HPP_INCLUDED

#include <nt2/toolbox/operator/functions/extract.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::extract_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_ < arithmetic_<A0> > >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(extract(nt2::real(a0), a1), extract(nt2::imag(a0), a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::extract_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_ < arithmetic_<A0> > >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename meta::scalar_of<A0>::type stype;
    typedef stype BOOST_SIMD_MAY_ALIAS const& result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return reinterpret_cast<stype BOOST_SIMD_MAY_ALIAS const*>(&a0)[a1];
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::extract_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_ < arithmetic_<A0> > >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename meta::scalar_of<A0>::type stype;
    typedef stype BOOST_SIMD_MAY_ALIAS const& result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return reinterpret_cast<stype BOOST_SIMD_MAY_ALIAS const*>(&a0)[a1];
    }
  };

} }

#endif

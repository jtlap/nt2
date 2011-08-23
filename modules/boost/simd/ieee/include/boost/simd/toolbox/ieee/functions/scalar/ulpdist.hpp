//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_ULPDIST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_ULPDIST_HPP_INCLUDED
#include <boost/simd/include/constants/eps_related.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>

#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/ldexp.hpp>
#include <boost/simd/include/functions/frexp.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/dist.hpp>
#include <boost/simd/include/functions/is_nan.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename dispatch::meta::result_of<dispatch::meta::arithmetic(A0,A1)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return dist(a0, a1);
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is bool_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< bool_<A0> >)(scalar_< bool_<A1> >)
                            )
  {

    typedef typename dispatch::meta::result_of<dispatch::meta::arithmetic(A0,A1)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return dist(a0, is_nez(a1));
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< real_<A1> >)
                            )
  {

    typedef typename dispatch::meta::result_of<dispatch::meta::arithmetic(A0,A1)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::result_of<dispatch::meta::arithmetic(A0, A1) >::type type;
      typedef typename dispatch::meta::as_integer<A0>::type itype;
      if (a0 == a1)               return Zero<type>();
      if (is_nan(a0)&&is_nan(a1)) return Zero<type>();
      itype e1, e2;
      type m1, m2;
      boost::fusion::tie(m1, e1) = boost::simd::frexp(type(a0));
      boost::fusion::tie(m2, e2) = boost::simd::frexp(type(a1));
      itype expo = -boost::simd::max(e1, e2);
      double e = (e1 == e2) ? boost::simd::abs(m1-m2)
      : boost::simd::abs(boost::simd::ldexp(a0, expo)-boost::simd::ldexp(a1, expo));
      return type(e/Eps<type>());
    }
  };
} } }


#endif

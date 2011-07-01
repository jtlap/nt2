//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_FMA_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_FMA_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>

#include <nt2/include/functions/two_add.hpp>
#include <nt2/include/functions/two_prod.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::fma_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)(scalar_< arithmetic_<A2> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1,A2)>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      return a0*a1+a2;
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::fma_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< double_<A0> >)(scalar_< double_<A1> >)(scalar_< double_<A2> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1,A2)>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
//       A0 p, rp, s, rs;
//       boost::fusion::tie(p, rp) = two_prod(a0, a1);
//       boost::fusion::tie(s, rs) = two_add(p, a2);
//       return s+(rp+rs);
      //      fma is incorrect this is Bugzilla Bug 3268 for glibc
      return a0*a1+a2;
      //         return ::fma(a0, a1, a2);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::fma_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< float_<A0> >)(scalar_< float_<A1> >)(scalar_< float_<A2> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1,A2)>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
//       A0 p, rp, s, rs;
//       boost::fusion::tie(p, rp) = two_prod(a0, a1);
//       boost::fusion::tie(s, rs) = two_add(p, a2);
//       return s+(rp+rs);
      //       fma is incorrect this is Bugzilla Bug 3268 for glibc
      return a0*a1+a2;
      //         return ::fma(a0, a1, a2);
    }
  };
} }


#endif

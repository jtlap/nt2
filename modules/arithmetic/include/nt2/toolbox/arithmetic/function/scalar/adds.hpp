//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_ADDS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_ADDS_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/include/functions/saturate.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::adds_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::upgrade<A0>::type utype; 
      return nt2::saturate<A0>(utype(a0)+utype(a1)); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::adds_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::min(Valmax<A0>(), a0+a1); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::adds_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< int64_<A0> >)(scalar_< int64_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      bool gtza0 = is_gtz(a0);
      bool gtza1 = is_gtz(a1);
      A0 a0pa1 = a0+a1;
      if (gtza0 && gtza1 && (lt(a0pa1, nt2::max(a0, a1))))
	{
	  return Valmax<A0>();
	}
      else if (!gtza0 && !gtza1 && (is_gtz(a0pa1) || (gt(a0pa1, nt2::min(a0, a1)))))
	{
	  return Valmin<A0>();
	}
      else
	{
	  return a0pa1;
	}
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint64_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::adds_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< uint64_<A0> >)(scalar_< uint64_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 a0pa1 = a0+a1;
      if (lt(a0pa1, nt2::max(a0, a1)))
	{
	  return Valmax<A0>();
	}
      else
	{
	  return a0pa1;
	}
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::adds_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< uint32_<A0> >)(scalar_< uint32_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 a0pa1 = a0+a1;
      if (lt(a0pa1, nt2::max(a0, a1)))
	{
	  return Valmax<A0>();
	}
      else
	{
	  return a0pa1;
	}
    }
  };
} }


#endif

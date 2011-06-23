//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_IDIVROUND_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_IDIVROUND_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/iround2even.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/group.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/tofloat.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::idivround_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    { return iround(tofloat(a0)/tofloat(a1)); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::idivround_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<unsigned_<A0>,X>))((simd_<unsigned_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    { return rdivide(a0+a1/Two<A0>(), a1); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::idivround_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int16_<A0>,X>))((simd_<int16_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type           stype;
      typedef typename meta::upgrade<stype>::type itype;
      typedef typename simd::native<itype,X>                 ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::fusion::tie(a0l, a0h) = split(a0);
      boost::fusion::tie(a1l, a1h) = split(a1);
      return simd::native_cast<A0>(group(idivround(a0l, a1l),
                               idivround(a0h, a1h)));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::idivround_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int8_<A0>,X>))((simd_<int8_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type           stype;
      typedef typename meta::upgrade<stype>::type itype;
      typedef typename simd::native<itype, X>                 ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::fusion::tie(a0l, a0h) = split(a0);
      boost::fusion::tie(a1l, a1h) = split(a1);
      return simd::native_cast<A0>(group(idivround(a0l, a1l),
                               idivround(a0h, a1h) ));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::idivround_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<real_<A0>,X>))((simd_<real_<A0>,X>))
                            )
  {

    typedef typename meta::as_integer<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    { return iround2even(a0/a1); }
  };
} }


#endif

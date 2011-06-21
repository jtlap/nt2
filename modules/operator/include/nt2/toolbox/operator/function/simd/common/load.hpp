//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_LOAD_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for no SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd types
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::load_, tag::cpu_
                            , (A0)(A1)(T)(X)
                            , (iterator_<fundamental_<A0> >)(scalar_< fundamental_<A1> >)((target_< simd_< fundamental_<T>, X > >))
                            )
  {

    typedef typename meta::strip<A2>::type::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      type that;
      std::memcpy(&that, reinterpret_cast<type const*>(a0) + a1, sizeof that);
      return that;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd types with an offset
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::load_, tag::cpu_
                            , (A0)(A1)(T)(Offset)(X)
                            , (iterator_<fundamental_<A0> >)(scalar_< fundamental_<A1> >)((target_< simd_< fundamental_<T>, X > >))(mpl_integral_< integer_<Offset> >)
                            )
  {

    typedef typename meta::strip<A2>::type::type result_type;

    NT2_FUNCTOR_CALL(4)
    {
      typedef typename NT2_RETURN_TYPE(4)::type type;
      type that;
      std::memcpy(&that, reinterpret_cast<type const*>(a0 + A3::value) + a1, sizeof that);
      return that;
    }
  };
} }


#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_RDIVIDE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_RDIVIDE_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/rdivide.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/functions/group.hpp>
#include <boost/simd/include/functions/split.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/functions/toint.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/fusion/tuple.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rdivide_, tag::cpu_, (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      const A0 iseqza1 = is_eqz(a1);
      const A0 c = b_and(eq(a0,Valmin<A0>()),eq(a1, Mone<A0>()));
      const A0 aa1 = a1+(iseqza1&One<A0>()); 
      const A0 r1 = (a0-c)/aa1; //a1!= 0
      const A0 v2 = select(is_ltz(a1),Valmin<A0>(),Valmax<A0>()); 
      const A0 r2 = select(is_eqz(a0),Zero<A0>(),v2); //a1 == 0
      return select(iseqza1, r2, r1);
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rdivide_, tag::cpu_, (A0)(X)
				     , ((simd_<unsigned_<A0>,X>))
				     ((simd_<unsigned_<A0>,X>))
				     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      const A0 iseqza1 = is_eqz(a1);
      const A0 aa1 = a1+(iseqza1&One<A0>()); 
      const A0 r1 = a0/aa1; //a1!= 0
      const A0 r2 = select(is_eqz(a0),Zero<A0>(),Valmax<A0>()); 
      return select(iseqza1, r2, r1);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rdivide_, tag::cpu_, (A0)(X)
                            , ((simd_<int8_<A0>,X>))
                              ((simd_<int8_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type  stype;
      typedef typename dispatch::meta::upgrade<stype>::type itype;
      typedef simd::native<itype, X>              ivtype;
      ivtype a0l, a0h, a1l, a1h;

      split(a0, a0l, a0h);
      split(a1, a1l, a1h);
      return simd::native_cast<A0>(group( boost::simd::rdivide(a0l, a1l)
                                        , boost::simd::rdivide(a0h, a1h) ));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rdivide_, tag::cpu_, (A0)(X)
                            , ((simd_<int16_<A0>,X>))
                              ((simd_<int16_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type    stype;
      typedef typename dispatch::meta::upgrade<stype>::type   itype;
      typedef simd::native<itype,X>                 ivtype;
      ivtype a0l, a0h, a1l, a1h;

      split(a0,a0l, a0h);
      split(a1,a1l, a1h);
      A0 r1 = simd::native_cast<A0>( group( toint(tofloat(a0l)/tofloat(a1l)), 
					    toint(tofloat(a0h)/tofloat(a1h))
					    )
				     ); 
      const A0 iseqza1 = is_eqz(a1);
      const A0 t1 = b_and(eq(a0,Valmin<A0>()),eq(a1, Mone<A0>()));
      const A0 t2 = b_and(iseqza1, is_eqz(a0));
      return select(t1,
		    Valmax<A0>(), 
		    select(t2,
			   Zero<A0>(),
			   select(iseqza1, 
				  select(is_ltz(a1),
					 Valmax<A0>(),
					 Valmin<A0>()
					 ),
				  r1)
			   )
		    ); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rdivide_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0/a1; 
      //      return b_or(b_and(is_eqz(a0), is_eqz(a1)), a0/a1);
    }
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_PUT_FIRST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_PUT_FIRST_HPP_INCLUDED
#include <boost/dispatch/meta/as_real.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/shli.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::put_first_, tag::cpu_
			      , (A0)(A1)
			      , ((simd_<double_<A0>,tag::sse_>))
		  	        ((scalar_< integer_<A1> >))  
			    )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2)
      {
	if(a1)
	  {
	    A0 that = { _mm_unpackhi_pd(a0,a0)};
	    return that;
	  }
	return a0;
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type8_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::put_first_, tag::cpu_
			      , (A0)(A1)
			      , ((simd_<type8_<A0>,tag::sse_>))
			        ((scalar_< integer_<A1> >))
			      )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2)
      {
	typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64;
	if(a1 > 7)
	  {
	    A0 t = { _mm_srli_si128(simd::native_cast<type64>(a0), 8 )};
	    return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-8) << 3));
	  }
	return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 3));
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type64_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::put_first_, tag::cpu_
			      , (A0)(A1)
			      , ((simd_<type64_<A0>,tag::sse_>))
			        ((scalar_< integer_<A1> >))
			      )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2)
      {
	typedef typename meta::as_real<A0>::type rtype;
	if(a1)
	  {
	    return simd::native_cast<A0>(_mm_unpackhi_pd(simd::native_cast<rtype>(a0),simd::native_cast<rtype>(a0)));
	  }
	return a0;
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type16_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::put_first_, tag::cpu_
			      , (A0)(A1)
			      , ((simd_<type16_<A0>,tag::sse_>))
			        ((scalar_< integer_<A1> >))
			      )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2)
      {
	typedef simd::native<typename meta::double__<A0>::type,tag::sse_>   rtype;
	typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64;
	if(a1 > 3)
	  {
	    A0 t = { _mm_srli_si128(simd::native_cast<type64>(a0), 8 )};
	    return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-4) << 4));
	  }
	return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 4));
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type32_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::put_first_, tag::cpu_
			      , (A0)(A1)
			      , ((simd_<type32_<A0>,tag::sse_>))
			        ((scalar_< integer_<A1> >))
			      )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2)
      {
	typedef simd::native<typename meta::double__<A0>::type,tag::sse_>   rtype;
	typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64;
	if(a1 > 1)
	  {
	    type64 z = simd::native_cast<type64>(a0);
	    z = _mm_srli_si128(z, 8 ); 
	    A0 t = simd::native_cast<A0>(z);
	    return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-2) << 5));
	  }
	return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 5));
      }
  };
} } }


#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Disributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_MIN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_MIN_HPP_INCLUDED
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/arg.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>
// as matlab min for complex is first on magnitudes and if equality on arguments

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::min_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_ < arithmetic_<A0> > > )
                              (generic_< complex_ < arithmetic_<A1> > > )
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      rtype absa0 = boost::simd::abs(a0);
      rtype absa1 = boost::simd::abs(a1);
      result_type r = select(lt(absa0, absa1), a0, a1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), a0, a1), r); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::min_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      result_type ca0 = result_type(Zero<rtype>(), a0); 
      rtype absa0 = boost::simd::abs(a0);
      rtype absa1 = boost::simd::abs(a1);
      result_type r = select(lt(absa0, absa1), ca0, a1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), ca0, a1), r); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A0>::type rtype;
      result_type ca1 = result_type(Zero<rtype>(), a1); 
      rtype absa0 = boost::simd::abs(a0);
      rtype absa1 = boost::simd::abs(a1);
      result_type r = select(lt(absa0, absa1), a0, a1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), a0, ca1), r); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< imaginary_< arithmetic_<A0> > >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      rtype absa0 = boost::simd::abs(a0);
      rtype absa1 = boost::simd::abs(a1);
      result_type r =  select(lt(absa0, absa1), a0, a1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), a0, a1), r); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef A0 rtype; 
      rtype absa0 = boost::simd::abs(a0);
      rtype absa1 = boost::simd::abs(a1);
      result_type ca1 = result_type(Zero<rtype>(), a1());
      result_type ca0 = result_type(a0, Zero<rtype>()); 
      result_type r = select(lt(absa0, absa1), ca0, ca1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), ca0, ca1), r); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< imaginary_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)
                             
                            )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef A1 rtype; 
      rtype absa0 = boost::simd::abs(a0);
      rtype absa1 = boost::simd::abs(a1);
      result_type ca0 = result_type(Zero<rtype>(), a0());
      result_type ca1 = result_type(a1, Zero<rtype>()); 
      result_type r = select(lt(absa0, absa1), ca0, ca1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), ca0, ca1), r); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef A0 rtype; 
      rtype absa0 = boost::simd::abs(a0);
      rtype absa1 = boost::simd::abs(a1);
      result_type ca0 = result_type(Zero<rtype>(), a0());
      result_type r = select(lt(absa0, absa1), ca0, a1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), ca0, a1), r); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)
                             
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef A1 rtype; 
      rtype absa0 = boost::simd::abs(a0);
      rtype absa1 = boost::simd::abs(a1);
      result_type ca1 = result_type(a1, Zero<rtype>());
      result_type r = select(lt(absa0, absa1), a0, ca1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), a0, ca1), r); 
    }
  };  
} } }

#endif

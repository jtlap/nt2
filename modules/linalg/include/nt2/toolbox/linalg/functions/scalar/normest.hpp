/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_SCALAR_NORMEST_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_SCALAR_NORMEST_HPP_INCLUDED
#include <nt2/include/functions/normest.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/vecnorm.hpp>
#include <nt2/include/functions/mtimes.hpp>
//#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/none.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/sqrteps.hpp>


namespace nt2 { namespace ext
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normest_, tag::cpu_,
                                       (A0)(A1), 
                                       ((ast_<A0>))
                                       (scalar_<floating_<A1> > )
                                       )
  {
    typedef typename A0::value_type                   value_type;
    typedef typename meta::as_real<value_type>::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& s, const A1 &tol) const
    {
      typedef table<result_type> tab_t;
      typedef table<value_type>  vtab_t;
      vtab_t x =  nt2::asum1(s, 1)(_);
      size_t cnt = 0;
      result_type e =  nt2::vecnorm(x);
      if (is_eqz(e)) return e;
      x /= e;
      result_type e0 =  Zero<result_type>();
      while (nt2::abs(e-e0) > tol*e)
        {
          e0 = e;
          vtab_t  sx = nt2::mtimes(s, x);
          //if (nt2::none(nt2::abs(sx(_)))){ sx = nt2::ones/*rand*/(nt2::size(sx)); }
          x = nt2::mtimes(trans(s), sx); 
          result_type normx =  nt2::vecnorm(x);
          e = normx/nt2::vecnorm(sx); 
          x /= normx;
          if (++cnt > 100) break; 
        }
      return e;     
    }
  private:
    template < class S>
    static S trans(const S& a)
    {
      S ta = zeros(width(a), height(a), meta::as_<value_type>());
      for (int i = 1; i <= height(a); ++i)
        for (int j = 1; j <= width(a); ++j)
          ta(j, i) = a(i, j);
      return ta;
    }
    
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normest_, tag::cpu_,
                              (A0), 
                              ((ast_<A0>))
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::as_real<value_type>::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0) const
    {
      return nt2::normest(a0, Sqrteps<result_type>()); 
    }
  }; 
  
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normest_, tag::cpu_,
                              (A0), 
                              (scalar_<arithmetic_<A0> > )
                              )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0) const
    {
      return nt2::abs(a0); 
    }
  }; 
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normest_, tag::cpu_,
                              (A0)(A1), 
                              (scalar_<arithmetic_<A0> > )
                              (scalar_<floating_<A1> >)
                              )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0, const A1 &) const
    {
      return nt2::abs(a0); 
    }
  };
} }


#endif


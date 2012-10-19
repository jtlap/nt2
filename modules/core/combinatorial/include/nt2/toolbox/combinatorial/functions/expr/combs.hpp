/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_EXPR_COMBS_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_EXPR_COMBS_HPP_INCLUDED
#include <nt2/toolbox/combinatorial/functions/combs.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/table.hpp>



namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::combs_, tag::cpu_,
                             (A0)(A1),
                             (unspecified_<A0>)       
                             (scalar_ < integer_<A1> > )
                             )
  {
    typedef typename A0::value_type                   value_type; 
    //    typedef nt2::container::table<value_type>        result_type; 
    typedef nt2::memory::container<value_type, nt2::_2D>    term;
    typedef boost::dispatch::meta::terminal_of_shared<term> result;
    typedef typename result::type                           result_type;
    inline result_type operator()(A0 const& v0,  const A1 & m0) const
    {
      result_type p =  result::make();
      size_t m = m0; 
      size_t n = nt2::length(v0);
      if (n == m)
        {
          p = nt2::rowvect(v0);
          return p;
        }
      else if (m == 1u)
        {
          p = nt2::colvect(v0);
          return p;
        }
      else
        {
          result_type v =  result::make();
          v = nt2::rowvect(v0);
          
          p = nt2::zeros(0, 0, meta::as_<value_type>()); 
          if ((m < n) && (m > 1u))
            {
              for (size_t k = 1;  k <= n-m+1;  ++k)
                { std::cout << "avant" << std::endl; 
                  result_type q  =  result::make(); q = nt2::combs(v(nt2::_(k+1, n)),m-1);
                
                  NT2_DISPLAY(size(q)); 
                  NT2_DISPLAY(q);
                  NT2_DISPLAY(p);
                  NT2_DISPLAY(k); 
                  NT2_DISPLAY(v); 
                  NT2_DISPLAY(v(nt2::ones(size(q,1),1, meta::as_<int32_t>()),k));
                  NT2_DISPLAY(size(v(nt2::ones(size(q,1),1, meta::as_<int32_t>()),k)));
                  NT2_DISPLAY(size(q)); 
                  NT2_DISPLAY(size(nt2::cath(v(nt2::ones(size(q,1),1, meta::as_<int32_t>()),k), q)));
                    
                  NT2_DISPLAY(nt2::cath(v(nt2::ones(size(q,1),1, meta::as_<int32_t>()),k), q));
                  std::cout << "après " <<  k << " <=  " <<  n-m+1 << std::endl;
                  result_type tmp =  result::make(); tmp = nt2::cath(v(nt2::ones(size(q,1),1, meta::as_<int32_t>()),k), q);
                  NT2_DISPLAY(size(tmp)); 
                  NT2_DISPLAY(tmp); 
                  if (isempty(p))
                    p =  tmp;
                  else
                    {
                      result_type tmp1 =  result::make(); tmp1 =  nt2::catv(p,tmp);
                      p =  tmp1; 
                    }
                  NT2_DISPLAY(p); 
                }
            }
          std::cout << "last "<< std::endl;
          NT2_DISPLAY(p);
          NT2_DISPLAY(size(p)); 
          return p; 
        } 
    }
  };
} }
#endif

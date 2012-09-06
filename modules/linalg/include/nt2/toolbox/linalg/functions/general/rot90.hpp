/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_ROT90_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_ROT90_HPP_INCLUDED
#include <nt2/include/functions/rot90.hpp>
//#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/table.hpp>

namespace nt2{ namespace ext 
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rot90_, tag::cpu_,
                                     (A0)(A1), 
                                     ((ast_<A0>))
                                     (scalar_<integer_<A1> > )
                                     )
  {
    typedef typename A0::value_type value_type;
    typedef table<value_type> result_type; 
    NT2_FUNCTOR_CALL(2)
      {
        int k = ((a1%4)+4)%4; 
        if(k == 1)  return nt2::fliplr(trans(a0));
        if(k == 2)  return nt2::fliplr(nt2::flipud(a0));
        if(k == 3)  return trans(flipud(a0));
        return a0;
      }
  private:
    
    template < class S>
    static result_type trans(const S& a)
      {
        result_type aa  = a; 
        result_type ta(of_size(width(aa), height(aa)));
        for (size_t i = 1; i <= height(aa); ++i)
          for (size_t j = 1; j <= width(aa); ++j)
            ta(j, i) = aa(i, j);
        return ta;
      }
  };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rot90_, tag::cpu_,
                                     (A0), 
                                     ((ast_<A0>))
                                     )
  {
    typedef typename A0::value_type value_type;
    typedef table<value_type> result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        return nt2::fliplr(trans(a0));
      }
  private:
    
    template < class S>
      static result_type trans(const S& a)
      {
        result_type aa  = a; 
        result_type ta(of_size(width(aa), height(aa)));
        for (size_t i = 1; i <= height(aa); ++i)
          for (size_t j = 1; j <= width(aa); ++j)
            ta(j, i) = aa(i, j);
        return ta;
      }
  };
} }


#endif

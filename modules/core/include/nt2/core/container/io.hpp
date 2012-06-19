/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_IO_HPP_INCLUDED
#define NT2_CORE_CONTAINER_IO_HPP_INCLUDED

#include <cstddef>
#include <iostream>
#include <boost/preprocessor/stringize.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/include/functions/schedule.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/core/container/dsl/expression.hpp>

namespace nt2
{
  namespace details
  {
    // INTERNAL ONLY
    // Display a 2D page from an expression
    template<class Xpr, class Pos> inline
    void print_expr ( std::ostream& os
                    , const char* name , Xpr const& xpr
                    , Pos& p           , boost::mpl::int_<2> const&
                    )
    {
      typedef typename Xpr::value_type          value_type;
      typedef typename Xpr::index_type::type    index_type;

      // Display int and not char
      typedef typename boost::mpl::
              if_c<(    boost::is_same<value_type,int8_t>::value
                    ||  boost::is_same<value_type,uint8_t>::value
                    )
                  , int
                  , value_type
                  >::type                       display_t;

      // Base index for making the linear index properly C based
      const std::ptrdiff_t b = boost::mpl::at_c<index_type,0>::type::value;

      // Display the name
      if(name)
      {
        os << name;
        if(Pos::static_size > 2)
        {
          // .. and the potential (:,:,...) indicator
          os << "(:,:";
          for(std::size_t i=2;i<Pos::static_size;++i) os << "," << p[i];
          os << ")";
        }
        os << " = \n\n";
      }

      // Display the current 2D page
      for ( p[0]  = nt2::first_index<1>(xpr);
            p[0] <= nt2::last_index<1>(xpr);
          ++p[0]
          )
      {
        if(name)
          os  << "     ";

        for ( p[1]  = nt2::first_index<2>(xpr);
              p[1] <= nt2::last_index<2>(xpr);
            ++p[1]
            )
        {
          os  << display_t(xpr(nt2::sub2ind(nt2::extent(xpr),p,index_type())+b))
              << " ";
        }

        os << "\n";
      }
    }

    // INTERNAL ONLY
    // Display a nD page from an expression by recursively calls itself
    template<class Xpr, class Pos, int N> inline
    void print_expr ( std::ostream& os
                    , const char* name , Xpr const& xpr
                    , Pos& p           , boost::mpl::int_<N> const&
                    )
    {
      typedef typename Xpr::value_type          value_type;
      typedef typename boost::mpl::if_c < sizeof(value_type) == 1
                                        , int
                                        , value_type
                                        >::type     display_t;

      // Walk through the current dimension
      for ( p[N-1] = nt2::first_index<N>(xpr);
            p[N-1] < nt2::last_index<N>(xpr);
          ++p[N-1]
          )
      {
        print_expr(os,name,xpr,p,boost::mpl::int_<N-1>());
        os << "\n";
      }

      // Extract last iteration to not end up with a huge pile of \n at the end
      p[N-1] = nt2::last_index<N>(xpr);
      print_expr(os,name,xpr,p,boost::mpl::int_<N-1>());
    }

    // INTERNAL ONLY
    // Perform the needed checks for expression stream insertion
    template<class Xpr,class R> inline
    void disp ( const char* name, std::ostream& os
              , nt2::container::expression<Xpr,R> const& xpr
              )
    {
      if(!nt2::isempty(xpr))
      {
        // We schedule xpr to be sure everything is evaluated if needed.
        typedef nt2::container::expression<Xpr,R> expr_t;
        typedef typename make_functor<tag::run_, expr_t>::type               run_t;
        typedef typename meta::call<tag::schedule_(expr_t const&, run_t)>::type scheduled;

        scheduled s = schedule(xpr, run_t());

        // We print expression based on their runtime ndims so the various
        // ans(:,:,...) are not tainted by useless 1's
        switch(nt2::ndims(s))
        {
          case 1:

#define M0(z,n,t)                                         \
case n: boost::array<std::ptrdiff_t,n> p##n;              \
        print_expr(os,name,s,p##n,boost::mpl::int_<n>()); \
        break;                                            \
/**/

          BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

#undef M0
          default: break;
        }
      }
      else
      {
        // Display the lonely empty matrix
        if(name) os << name << " = \n     ";

        // "[]" is used for 0x0 or 0x1 table
        if( (nt2::ndims(xpr) < 3) && ( !nt2::size(xpr,2) ) )
        {
          os << "[]\n";
        }
        else
        {
          os  << "     Empty array: " << nt2::size(xpr,1);
          for(std::size_t i=2;i<=nt2::ndims(xpr);++i)
            os << "-by-" << nt2::size(xpr,i);
          os << "\n";
        }
      }
    }
  }

  //============================================================================
  // Stream insertion operator for nt2 expressions
  // By design, this is equivalent to disp(xpr)
  //============================================================================
  template<class Xpr,class R> std::ostream&
  operator<<(std::ostream& os, nt2::container::expression<Xpr,R> const& xpr)
  {
    details::disp(0, os, xpr);
    return os;
  }
}

#endif

//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SOLVERS_MRDIVIDE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SOLVERS_MRDIVIDE_HPP_INCLUDED

#include <nt2/linalg/functions/mrdivide.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>

namespace nt2 { namespace ext
{

  //============================================================================
  // MRDIVIDE
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( mrdivide_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::mrdivide_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type                                 ctype_t;
    typedef typename nt2::meta::as_real<ctype_t>::type                   type_t;
    typedef nt2::memory::container<tag::table_, type_t, nt2::_2D>    o_semantic;
    BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1 const& a1 ) const
    {
      eval(a0,a1,N0(),N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - x = mrdivide(b, a)
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      // it is patent that this can be improved as soon as issue #903 will be addressed
      boost::proto::child_c<0>(a1) =
        ctrans(linsolve( ctrans(boost::proto::child_c<1>(a0))
                       , ctrans(boost::proto::child_c<0>(a0))
                       )
              );
    }
    //==========================================================================
    /// INTERNAL ONLY - [x, r]= mrdivide(b, a)
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      // it is patent that this can be improved as soon as issue #903 will be addressed
      NT2_AS_TERMINAL_OUT(o_semantic, x, boost::proto::child_c<0>(a1));
      type_t r;
      tie(x, r) = linsolve( ctrans(boost::proto::child_c<1>(a0))
                          , ctrans(boost::proto::child_c<0>(a0))
                          );

      boost::proto::child_c<0>(a1) = ctrans(x);
      boost::proto::child_c<1>(a1) = r;
    }

  };
} }

#endif

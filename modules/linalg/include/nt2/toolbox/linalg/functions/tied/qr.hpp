//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_QR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_QR_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/qr.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/qr.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(l, u, p) = qr(...) at assign time and resolve to optimized call
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qr_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::qr_, N0>))
                              ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type  child0;
    typedef typename meta::strip<child0>::type                      dest_t;
    typedef typename meta::
            call< nt2::tag::
                  factorization::qr_(dest_t&,char,nt2::details::in_place_)
                >::type                                             fact_t;
    
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy data in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      char nop = (N1::value < 3) ? 'N':  'P'; ; 
      // Factorize in place
      fact_t f = factorization::qr(boost::proto::child_c<0>(a1),nop, in_place_);
      char ch =  choice(a0, N0()); 
      decomp(f, a1, N1());
    }

  private:
    struct matrix_{};
    struct vector_{}; 
    //==========================================================================
    // INTERNAL ONLY
    // get 'Vector',  'Matrix'
    //==========================================================================
    BOOST_FORCEINLINE
    char choice(A0 const &, boost::mpl::long_<1> const &) const
    {
      return 'M'; 
    }

    BOOST_FORCEINLINE
    char choice(A0 const & a0, boost::mpl::long_<2> const &) const
    {
      return boost::proto::value(boost::proto::child_c<1>(a0));
    }
    
   
    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.qr();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.q();
      boost::proto::child_c<1>(a1) = f.r();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<3> const&) const
    {
      typedef typename boost::proto::result_of::child_c<A1&, 2>::type tab_type;
      typedef typename meta::strip<tab_type>::type type; 
      typedef typename type::value_type value_type; 
      boost::proto::child_c<0>(a1) = f.q();
      boost::proto::child_c<1>(a1) = f.r();
      perm<A1, fact_t, value_type>::get(a1, f);   
    }

    template <class B1,  class B2, class B3 = typename B2::type_t> struct perm
    {
      BOOST_FORCEINLINE
      static void get(B1 & a1,  const B2 & f)
      {
        boost::proto::child_c<2>(a1) = f.p();
      }
    }; 
      
    template <class B1,  class B2> struct perm < B1, B2, typename B2::itype_t>
    {
      BOOST_FORCEINLINE
      static void get(B1 & a1,  const B2 & f)
      {
        boost::proto::child_c<2>(a1) = f.jp();
      }
    }; 
  };
} }

#endif

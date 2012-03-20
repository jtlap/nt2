//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_POSITION_ALIGNMENT_HPP_INCLUDED
#define NT2_CORE_UTILITY_POSITION_ALIGNMENT_HPP_INCLUDED

#include <nt2/core/settings/forward/alignment.hpp>
#include <nt2/core/settings/forward/index.hpp>
#include <nt2/core/settings/forward/storage_order.hpp>
#include <nt2/core/utility/position/position.hpp>

namespace nt2
{
  template<typename Seq, typename B, typename SO, typename A>
  inline position<Seq, B, SO, aligned_>
  as_aligned( position<Seq, B, SO, A> const& p )
  {
    return position<Seq, B, SO, aligned_>(p.seq_);
  }

  template<typename Seq1, typename Seq2, typename B, typename SO, typename A >
  inline position<Seq2, B, SO, aligned_>
  as_aligned( position<Seq1, B, SO, A> const& p, Seq2 const& s )
  {
    return position<Seq2, B, SO, aligned_>(s);
  }

  template<typename Seq>
  inline position<Seq, nt2::index_<1l, 1l>, matlab_order_, aligned_>
  as_aligned( Seq const& s )
  {
    return position<Seq, nt2::index_<1l, 1l>, matlab_order_, aligned_>(s);
  }

  template<typename Seq, typename B>
  inline position<Seq, B, matlab_order_, aligned_>
  as_aligned( Seq const& s, B const& b )
  {
    return position<Seq, B, matlab_order_, aligned_>(s);
  }

  template<typename Seq, typename B, typename SO>
  inline position<Seq, B, SO, aligned_>
  as_aligned( Seq const& s, B const& b, SO const& so )
  {
    return position<Seq, B, SO, aligned_>(s);
  }
}

namespace nt2
{
  template<typename Seq, typename B, typename SO, typename A>
  inline position<Seq, B, SO, unaligned_>
  as_unaligned( position<Seq, B, SO, A> const& p )
  {
    return position<Seq, B, SO, unaligned_>(p.seq_);
  }

  template<typename Seq1, typename Seq2, typename B, typename SO, typename A >
  inline position<Seq2, B, SO, unaligned_>
  as_unaligned( position<Seq1, B, SO, A> const& p, Seq2 const& s )
  {
    return position<Seq2, B, SO, unaligned_>(s);
  }

  template<typename Seq>
  inline position<Seq, nt2::index_<1l, 1l>, matlab_order_, unaligned_>
  as_unaligned( Seq const& s )
  {
    return position<Seq, nt2::index_<1l, 1l>, matlab_order_, unaligned_>(s);
  }

  template<typename Seq, typename B>
  inline position<Seq, B, matlab_order_, unaligned_>
  as_unaligned( Seq const& s, B const& b )
  {
    return position<Seq, B, matlab_order_, unaligned_>(s);
  }

  template<typename Seq, typename B, typename SO>
  inline position<Seq, B, SO, unaligned_>
  as_unaligned( Seq const& s, B const& b, SO const& so )
  {
    return position<Seq, B, SO, unaligned_>(s);
  }
}

#endif

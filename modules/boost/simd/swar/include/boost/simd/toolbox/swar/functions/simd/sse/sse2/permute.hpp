//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_PERMUTE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_PERMUTE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/swar/functions/permute.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd
{
  namespace details
  {
    template <class A0, int i0, int i1>  struct perm64sse2
    {
    };

    template <int i0, int i1>  struct perm64sse2< boost::simd::native<uint64_t, boost::simd::tag::sse_>, i0, i1>
    {
      typedef native<uint64_t, boost::simd::tag::sse_> value_type; 
      static inline value_type eval(const value_type& a)
      {
        typedef native<int64_t, boost::simd::tag::sse_> itype;
        return bitwise_cast<value_type>(permute<i0, i1>(bitwise_cast<itype>(a))); 
      }
    }; 

    template <int i0, int i1>  struct perm64sse2< boost::simd::native<int64_t, boost::simd::tag::sse_>, i0, i1>
    {
      typedef native<int64_t, boost::simd::tag::sse_> value_type;
      template < int i00, int i11>  struct selector
      {
        static const int value0 =  (i00 < 0) ? -1 : i00&1;
        static const int value1 =  (i11 < 0) ? -1 : i11&1;  
      };

      static inline value_type eval(const value_type& a)
      {
//         std::cout << "i0 i1 " << i0 << ",  " << i1 <<  std::endl; 
//         std::cout << "selector " << selector<i0, i1>::value0 << ",  " << selector<i0, i1>::value1 <<  std::endl; 
        return eval(a, selector<i0, i1>());
      }

      static inline value_type eval(const value_type& a, selector<0, 0> const &)
      {
        return  _mm_unpacklo_epi64(a, a);    
      }
      static inline value_type eval(const value_type& a, selector<0, 1> const &)
      {
        return a;    
      }
      static inline value_type eval(const value_type& a, selector<0, -1> const &)
      {
        return  _mm_unpacklo_epi64(a, Zero<value_type>());        
      }

      static inline value_type eval(const value_type& a, selector<1, 0> const &)
      {
        return _mm_shuffle_epi32(a, 78);    
      }
      static inline value_type eval(const value_type& a, selector<1, 1> const &)
      {
        return  _mm_unpackhi_epi64(a, a);    
      }
      static inline value_type eval(const value_type& a, selector<1, -1> const &)
      {
         return _mm_srli_si128(a, 8);    
      }

      static inline value_type eval(const value_type& a, selector<-1, 0> const &)
      {
        return _mm_slli_si128(a, 8);    
      }
      static inline value_type eval(const value_type& a, selector<-1, 1> const &)
      {
        return  _mm_unpackhi_epi64(Zero<value_type>(), a);    
      }
      static inline value_type eval(const value_type& a, selector<-1, -1> const &)
      {
        return Zero<value_type>();    
      }
    }; 

    template <int i0, int i1>  struct perm64sse2< boost::simd::native<double, boost::simd::tag::sse_>, i0, i1>
    {
      static const bool must_shuffle64 = (i0 > 0) || (i1 != 1 && i1 >= 0);
      static const bool must_zero64    = ((i0 | i1) < 0 && (i0 | i1) & 0x80);
      static const bool all_zero64     = (i0 <  0) && (i1 < 0); 
      static const int val64 = must_shuffle64 + 2*must_zero64 + 4*all_zero64;
      
      // val64 == 6 -> all zero
      // val64 == 3 -> shuffle and zero
      // val64 == 2 -> zero
      // val64 == 1 -> shuffle
      // val64 == 0 -> do nothing
      
      typedef boost::simd::native<double, boost::simd::tag::sse_> value_type;
      typedef boost::simd::native<int64_t,boost::simd::tag::sse_> ivt64;
      typedef boost::simd::native<int32_t,boost::simd::tag::sse_> ivt32; 
      template < int i>  struct selector { static const int value = i; };
      
      static inline value_type eval(const value_type& a)
      {
//         std::cout << "double spec" << std::endl;
//         std::cout << val64 << std::endl;
        return eval(a, selector<val64>());
      }
      
      static inline value_type eval(const value_type& a, selector<0> const &)
      {
        return  a;    
      }      
      static inline value_type eval(const value_type& a, selector<6> const &)
      {
        return  Zero<value_type>();    
      }      
      static inline value_type eval(const value_type& a, selector<2> const &)
      {
        ivt64 mask = boost::simd::make<value_type>(-int(i0>=0), -int(i1>=0));
        return  bitwise_and(a,mask);     
      }      
      static inline value_type eval(const value_type& a, selector<1> const &)
      {
        return shuf<i0, i1>(a, a);
      }      
      static inline value_type eval(const value_type& a, selector<3> const &)
      {
       return eval1(a, selector<(i0 <  0)>());  
      }      
      static inline value_type eval1(const value_type& a, selector<1> const &)
      {
        return shuf<0, 0>(Zero<value_type>(), a);  
      }      
      static inline value_type eval1(const value_type& a, selector<0> const &)
      {
        return shuf<1, 0>(a, Zero<value_type>());  
      }
      template < int i,  int j>
      static inline value_type shuf(const value_type& a, const value_type& b)
      {
        return _mm_shuffle_pd(a, b, (i&1) | (j&1)<<1);
      }
   }; 
    
    template <class A0, int i0, int i1, int i2, int i3>  struct perm32sse2
    {
    }; 

    template <int i0, int i1, int i2, int i3>  struct perm32sse2< boost::simd::native<uint32_t, boost::simd::tag::sse_>, i0, i1, i2, i3>
    {
      typedef native<uint32_t, boost::simd::tag::sse_> value_type; 
      static inline value_type eval(const value_type& a)
      {
        typedef native<int32_t, boost::simd::tag::sse_> itype;
        return bitwise_cast<value_type>(permute<i0, i1, i2, i3>(bitwise_cast<itype>(a))); 
      }
    }; 

    template <int i0, int i1, int i2, int i3>  struct perm32sse2< boost::simd::native<int32_t, boost::simd::tag::sse_>, i0, i1, i2, i3>
    {
      #define H0(i, inc) ((i&3)<<inc)
      #define H1(i, inc) ((i<0)?0:0xF)
      #define H2(i, inc) ((i&0x80)?0:0xF)
      /**/    
      typedef native<int64_t, boost::simd::tag::sse_> vt_64;
      typedef native<int32_t, boost::simd::tag::sse_> vt_32; 
      static const int p4_inds = H0(i0,0)|H0(i0,4)|H0(i0,8)|H0(i0,12); 
      static const int p4_zn = H1(i0,0)|H1(i0,4)|H1(i0,8)|H1(i0, 12); 
      static const int p4_za = H2(i0,0)|H2(i0,4)|H2(i0,8)|H2(i0, 12);
      #undef H0
      #undef H1
      #undef H2
      
      // Mask indicating 0 for don't care, 0xF for non-negative value of required zeroing
      static const int p4_zodc = p4_zn | ~ p4_za;
      static const bool must_shuffle32 = ((p4_inds ^ 0x00003210) & p4_zn) != 0;
      static const bool must_zero32    = (p4_za != 0xFFFF);
      static const bool all_zero32    = !p4_zn; 
      static const bool p64only =  ((p4_inds & 0x0101 & p4_zn) == 0                                                   // even indexes are even or negative
                                    && (~p4_inds & 0x1010 & p4_zn) == 0                                               // odd  indexes are odd  or negative
                                    && ((p4_inds ^ ((p4_inds + 0x0101) << 4)) & 0xF0F0 & p4_zn & (p4_zn << 4)) == 0   // odd index == preceding even index +1 or at least one of them negative
                                    && ((p4_zn ^ (p4_zn << 4)) & 0xF0F0 & p4_zodc & p4_zodc << 4) == 0);              // each pair of indexes are both negative or both positive or one of them don't care
      
      static const int val32        =   must_shuffle32 + 2*must_zero32 + 4*all_zero32 + 8*p64only; 
      // val32 == 9 -> perm 64 suffices
      // val32 == 14 -> all zero
      // val32 == 3 -> shuffle and zero
      // val32 == 2 -> zero
      // val32 == 1 -> shuffle
      // val32 == 0 -> do nothing
      
      typedef boost::simd::native<int32_t, boost::simd::tag::sse_> value_type; 
      template < int i>  struct selector { static const int value = i; };
      
      static inline value_type eval(const value_type& a)
      {
//         std::cout << "integer spec" << std::endl;
//         std::cout << val32 << std::endl;
        return eval(a, selector<val32>());
      }
      
      static inline value_type eval(const value_type& a, selector<0> const &)
      {
        return  a;    
      }
      static inline value_type eval(const value_type& a, selector<14> const &)
      {
        return  Zero<value_type>();    
      }
      
      static inline value_type eval(const value_type& a, selector<8+1> const &)
      {
        #define H0(i, j) ((i>=0)?i/2:(i&0x80)?i:((j>=0)?j/2:j))
        /**/
        return bitwise_cast<value_type>(permute<H0(i0, i1), H0(i2, i3)>(bitwise_cast<vt_64>(a)));
        #undef H0
      }
      
      static inline value_type eval(const value_type& a, selector<1> const &)
      {
        return details::shuffle<i0&3, i1&3, i2&3, i3&3>(a, a);
      }
      static inline value_type eval(const value_type& a, selector<2> const &)
      {
        value_type mask = boost::simd::make<value_type>(-int(i0>=0), -int(i1>=0), -int(i2>=0), -int(i3>=0));
        return  boost::simd::bitwise_and(a,mask);    
      }
      static inline value_type eval(const value_type& a, selector<3> const &)
      {
        return eval(eval(a, selector<1>()), selector<2>());  
      }    
    };    
    template <int i0, int i1, int i2, int i3>  struct perm32sse2< boost::simd::native<float, boost::simd::tag::sse_>, i0, i1, i2, i3>
    {
      static const int must_shuffle32 =  ((i0 > 0) || (i1 != 1 && i1 >= 0) || (i2 != 2 && i2 >= 0) || (i3 != 3 && i3 >= 0));
      static const int must_zero32    =  ((i0 | i1 | i2 | i3) < 0 && ((i0 | i1 | i2 | i3) & 0x80)); 
      static const int all_zero32     =  ((i0 & i1 & i2 & i3) < 0); 
      static const int zlsh32         =  ((i0 & i1) < 0 && (i2 | i3) >= 0);      // zero low half, shuffle high half
      static const int slzh32         =  ((i0 | i1) >= 0 && (i2 & i3) < 0);      // shuffle low half, zero high half
      static const int val32          =  must_shuffle32 + 2*must_zero32 + 4*all_zero32 + 8*zlsh32 + 16*slzh32; 
      // val32 == 6 -> all zero
      // val32 == 3 -> shuffle and zero
      // val32 == 2 -> zero
      // val32 == 1 -> shuffle
      // val32 == 0 -> do nothing
      
      typedef boost::simd::native<float, boost::simd::tag::sse_> value_type; 
      template < int i>  struct selector { static const int value = i; };
      
      static inline value_type eval(const value_type& a){
        return eval(a, selector<val32>());
      }
      
      static inline value_type eval(const value_type& a, selector<0> const &)
      {
        return a; 
      }
      static inline value_type eval(const value_type& a, selector<1> const &)
      {
        return details::shuffle<i0&3, i1&3, i2&3, i3&3>(a, a); 
      }
      static inline value_type eval(const value_type& a, selector<2> const &)
      {
        typedef typename boost::dispatch::meta::as_integer<value_type, signed>::type            itype; 
        itype mask = boost::simd::make<itype>(-int(i0>=0), -int(i1>=0), -int(i2>=0), -int(i3>=0));
        return  boost::simd::bitwise_and(a,mask);    
      }
      static inline value_type eval(const value_type& a, selector<3> const &)
      {
        return eval(eval(a, selector<1>()), selector<2>());  
      }
       static inline value_type eval(const value_type& a, selector<6> const &)
      {
        return  Zero<value_type>();    
      }
      static inline value_type eval(const value_type& a, selector<11> const &)
      {
        return details::shuffle<0, 1, (i2&3), (i3&3)>(Zero<value_type>(), a); 
      }
      static inline value_type eval(const value_type& a, selector<19> const &)
      {
        return details::shuffle<(i0&3), (i1&3), 2, 3>(a, Zero<value_type>()); 
      }
    };



    
  }
  namespace ext
  {
    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, boost::simd::tag::sse_
                                        , (A0)(I0)(I1)(I2)(I3)
                                        , ((simd_< type32_<A0>,boost::simd::tag::sse_>))
                                        ((unspecified_<I0>))
                                        ((unspecified_<I1>))
                                        ((unspecified_<I2>))
                                        ((unspecified_<I3>))
                                        )
    {
      typedef A0 result_type;
      
      result_type operator()(A0 const& a0, I0 const &, I1 const&, I2 const&, I3 const&) const
      {
//         std::cout << "sse2 32" << std::endl; 
        return details::perm32sse2<A0, I0::value, I1::value, I2::value, I3::value>::eval(a0); 
      }
    };
    
    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, boost::simd::tag::sse_
                                        , (A0)(I0)(I1)
                                        , ((simd_< type64_<A0>,boost::simd::tag::sse_>))
                                        ((unspecified_<I0>))
                                        ((unspecified_<I1>))
                                        )
    {
      typedef A0 result_type;
      
      result_type operator()(A0 const& a0, I0 const &, I1 const&) const
      {
//         std::cout << "sse2 64" << std::endl; 
        return details::perm64sse2<A0, I0::value, I1::value>::eval(a0); 
      }
    };
    
  }
} }


#endif
#endif

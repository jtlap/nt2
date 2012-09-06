//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_HYPER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_HYPER_HPP_INCLUDED

#include <nt2/core/functions/hyper.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/reshape.hpp>
//#include <nt2/include/functions/hypersstride.hpp>
#include <nt2/table.hpp>

// TO DO return properly an expression !
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hyper_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)
                              (scalar_<arithmetic_<A1> > )
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::extent_type                extt_t;
    typedef typename A0::value_type             value_type;
    typedef typename A0::index_type             index_type; 
    typedef typename meta::strip<extt_t>::type       ext_t;
    typedef table <value_type, index_type> result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& ind, A2 const& dim) const
     {
      size_t along = dim-1; 
      ext_t sizee = a0.extent();     
      sizee[along] = 1;
       switch(dim)
         {
         case 1 : return nt2::reshape(a0(ind, nt2::_), sizee);
         case 2 : return nt2::reshape(a0(nt2::_, ind, nt2::_), sizee);
         case 3 : return nt2::reshape(a0(nt2::_, nt2::_, ind, nt2::_), sizee);        
//          case 4 : return nt2::reshape(a0(nt2::_, nt2::_, nt2::_, ind, nt2::_), sizee);        
//          case 5 : return nt2::reshape(a0(nt2::_, nt2::_, nt2::_, nt2::_, ind), sizee);
         default : return a0;  
         }; 
     }
  }; 

  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hyper_, tag::cpu_,
//                               (A0)(A1)(A2),
//                               (ast_<A0>)
//                               (scalar_<arithmetic_<A1> > )
//                               (scalar_<integer_<A2> > )
//                               )
//   {
//     typedef typename A0::extent_type                extt_t;
//     typedef typename meta::strip<extt_t>::type       ext_t;
//     typedef typename  boost::proto::
//                       result_of::make_expr< nt2::tag::hyper_
//                                           , container::domain
//                                           , A0 const&
//                                           , size_t
//                                           , size_t
//                                           , size_t
//                                           , size_t
//                                           , box<ext_t>
//                                           >::type             result_type;

//     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& ind, A2 const& dim) const
//     {
//       BOOST_ASSERT_MSG(size_t(ind) < size(a0, dim), "index of hyoerplane must be less than size(a0, dim)"); 
//       typedef typename meta::call<nt2::tag::ind2sub_(ext_t,size_t)>::type  sub_t;
//       size_t along = dim-1; 
//       ext_t sizee = a0.extent();     
//       sizee[along] = 1;

//       ext_t ex1;     
//       for(size_t i=0; i < ext_t::size() ; ++i) ex1[i] = 1; 
//       ex1[along] = nt2::extent(a0)[along];
//       sub_t pos = ind2sub(ex1, ind);
// //       for(size_t i = 0; i < ext_t::size(); ++i) std::co-b½ut << nt2::extent(a0)[i] << "  ";  std::cout << std::endl;-A
// //       for(size_t i = 0; i < ext_t::size(); ++i) std::cout << pos [i] << "  ";  std::cout << std::endl;
//       size_t start = sub2ind(a0.extent(), pos);
//       size_t stride = nt2::hypersstride(a0, dim); 
//       std::cout << " stride   " << stride
//                 << " start  " << start
//                 << " ind    " << ind
//                 << " dim    " << dim <<  std::endl;
//       return boost::proto::make_expr<nt2::tag::hyper_, container::domain>
//         (boost::cref(a0),along, size_t(ind), start, stride, boxify(sizee));
//     }
//   };

} }

#endif

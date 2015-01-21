//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/include/functions/setbits.hpp>
#include <nt2/include/functions/rol.hpp>
#include <nt2/include/functions/bitwise_and.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/bitwise_xor.hpp>
#include <nt2/include/functions/shift_left.hpp>
#include <nt2/include/functions/shr.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/constants/allbits.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <boost/mpl/bool.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <boost/dispatch/meta/is_signed.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
using namespace nt2::bench;
using namespace nt2;

template<typename T> struct bitplane_reorder_scalar
{
  typedef unsigned short                                          raw_type;
  typedef unsigned short                                         size_type; //must be the same
//  typedef typename boost::dispatch::meta::as_integer<T>::type           iT;
  typedef typename boost::dispatch::meta::is_signed<raw_type>::type s_type;
  typedef boost::simd::native<raw_type,BOOST_SIMD_DEFAULT_EXTENSION>          vraw_type;
  typedef boost::simd::native<size_type,BOOST_SIMD_DEFAULT_EXTENSION>        vsize_type;

  bitplane_reorder_scalar(std::size_t n)
    :  size_(n)
  {
    input.resize(size_, 0);
    for(raw_type i = 0;i<input.size();++i) input[i]=i;
    output.resize(size_, 0);
  }

  void operator()()
  {
    using boost::simd::pack;
    using boost::simd::native;
    using boost::simd::aligned_store;
    using boost::simd::aligned_load;
    using boost::simd::load;
    using boost::simd::store;

    std::size_t step_size_=boost::simd::meta::cardinal_of<vraw_type>::value;

     const unsigned num_bits_per_plane = 1;
     const unsigned raw_type_num_bits = sizeof(raw_type)*CHAR_BIT;
     const unsigned num_planes = raw_type_num_bits/num_bits_per_plane;

     const unsigned segment_length = size_/num_planes;
     const unsigned type_width = CHAR_BIT*sizeof(raw_type);

//     const raw_type mask =  ~(Allbits<raw_type>() << (num_bits_per_plane));
     const vraw_type mask = complement(shl(Allbits<vraw_type>(), num_bits_per_plane));

     for(size_type index = 0; index <size_/step_size_; index += step_size_) //suppose size_ is supposed multiple of step_size_
     {
       vraw_type vinput =  aligned_load<vraw_type>(&input[index]);
       vraw_type value = nt2::rol(xor_if_signed(vinput, s_type()), 1);
       vsize_type vindex = enumerate<vsize_type>(index);
       std::cout << "vindex "<< vindex << std::endl;

       vsize_type output_bit_offset = (type_width - num_bits_per_plane) - (rem(vindex, num_planes)*num_bits_per_plane);

       for(size_type plane_index = 0; plane_index<num_planes; ++plane_index) {

        size_type input_bit_offset = plane_index*num_bits_per_plane;
        vraw_type extracted_bits = bitwise_and(shr(value, input_bit_offset), mask);

        vsize_type output_index = ((num_planes-1-plane_index)*segment_length) + (vindex/num_planes);
        std::cout << "output_index "<< output_index << std::endl;

        vraw_type voutput =  load<vraw_type>(&output[0], output_index);
        std::cout << "voutput "<< voutput << std::endl;
        voutput = nt2::setbits(voutput,
                               extracted_bits,
                               output_bit_offset,
                               num_bits_per_plane);
        store(voutput, &output[0], output_index);
      }
    }

    std::cout << " ===================== " << std::endl;
    for(int i = 0;i<16;++i){
      std::cout << i  << "-> output[i] "<< output[i] << std::endl;
    }
    std::cout << " ===================== " << std::endl;
    exit(0);
  }


  static vraw_type xor_if_signed(const vraw_type& _in, const boost::mpl::true_&)
  {
    //signed version
    const vraw_type mask = complement(shl(One<raw_type>(), sizeof(raw_type)*CHAR_BIT) - 1);
    return if_else(is_nez(bitwise_andnot(_in, mask)), bitwise_xor(_in, mask), _in);
  }

  static vraw_type xor_if_signed(const vraw_type& _in, const boost::mpl::false_&){
    //unsigned version
    return _in;
  }

  friend std::ostream& operator<<(std::ostream& os, bitplane_reorder_scalar<T> const& p)
  {
    return os << "(" << p.size()<< ")";
  }

  std::size_t size() const { return size_; }

  private:
  std::vector<raw_type> input, output;
  std::size_t size_;
};

NT2_REGISTER_BENCHMARK_TPL( bitplane_reorder_scalar, (float) )
{
  std::size_t size_min  = args("size_min", 16);
  std::size_t size_max  = args("size_max", 17);
  std::size_t size_step = args("size_step", 2);

  run_during_with< bitplane_reorder_scalar<float> > ( 1.
                                                   , geometric(size_min,size_max,size_step)
                                                   , cycles_per_element<stats::median_>()
                                                   );
}

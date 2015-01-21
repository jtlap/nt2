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
#include <nt2/include/constants/allbits.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <boost/mpl/bool.hpp>

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
  typedef unsigned short raw_type;
  typedef unsigned size_type;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::is_signed<raw_type>::type s_type;
  bitplane_reorder_scalar(std::size_t n)
                        :  size_(n)
  {
    input.resize(size_, 0);
    for(unsigned i = 0;i<input.size();++i) input[i]=i;
    output.resize(size_, 0);
  }

  void operator()()
  {
    const unsigned num_bits_per_plane = 1;
    const unsigned raw_type_num_bits = sizeof(raw_type)*CHAR_BIT;
    const unsigned num_planes = raw_type_num_bits/num_bits_per_plane;

    const unsigned segment_length = size_/num_planes;
    const unsigned type_width = CHAR_BIT*sizeof(raw_type);

    const raw_type mask = ~(Allbits<raw_type>() << (num_bits_per_plane));
    raw_type value = 0;

    for(size_type index = 0; index <size_; ++index)
    {
      value = xor_if_signed(input[index], s_type());
      value = nt2::rol(value, 1);
      std::cout << "index "<< index << std::endl;

      size_type output_bit_offset = (type_width - num_bits_per_plane) - ((index % num_planes)*num_bits_per_plane);

      for(size_type plane_index = 0; plane_index<num_planes; ++plane_index) {

        size_type input_bit_offset = plane_index*num_bits_per_plane;
        raw_type extracted_bits = (value >> input_bit_offset) & mask;

        size_type output_index = ((num_planes-1-plane_index)*segment_length) + (index/num_planes);

      std::cout << "output_index "<< output_index << std::endl;
        output[output_index] = nt2::setbits(output[output_index],
                                            extracted_bits,
                                            output_bit_offset,
                                            num_bits_per_plane);
      }
    }

    std::cout << " ===================== " << std::endl;
    for(int i = 0;i<16;++i){
      std::cout << i  << "-> output[i] "<< output[i] << std::endl;
    }
    std::cout << " ===================== " << std::endl;
    exit(0);
  }


  static iT xor_if_signed(const iT& _in, const boost::mpl::true_&)
  {
//    typedef typename meta::as_integer<T, signed> iT;
    //signed version
    static const T mask = ~(T(1 << ((sizeof(T)*CHAR_BIT) - 1)));
    if ( _in & ~mask )
      return _in ^ mask();
    else
        return _in;
  }

  static iT xor_if_signed(const iT& _in, const boost::mpl::false_&){
    //unsigned version
    return _in;
  }

  friend std::ostream& operator<<(std::ostream& os, bitplane_reorder_scalar<T> const& p)
  {
    return os << "(" << p.size()<< ")";
  }

  std::size_t size() const { return size_; }

  private:
  std::vector<iT> input, output;
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

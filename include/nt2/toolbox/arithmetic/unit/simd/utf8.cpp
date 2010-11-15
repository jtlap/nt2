#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/memory/allocator.hpp>

typedef nt2::int32_t char32;

namespace simd = nt2::simd;

template<typename In, typename Out>
Out u8_decode_step(In& begin, In end, Out out)
{
	In b = begin;

	unsigned char b0 = *(begin++);
	if((b0 & 0x80) == 0)
	{
		char32 r = b0;
		*out++ = r;
		return out;
	}

	if((b0 & 0xe0) == 0xc0)
	{
		char32 r = (b1 & 0x3f) | ((b0 & 0x1f) << 6);
		*out++ = r;
		return out;
	}

	unsigned char b2 = *(begin++);
	if((b0 & 0xf0) == 0xe0)
	{
		char32 r = (b2 & 0x3f) | ((b1 & 0x3f) << 6) | ((b0 & 0x0f) << 12);
		*out++ = r;
		return out;
	}

	unsigned char b3 = *(begin++);
	if((b0 & 0xf8) == 0xf0)
	{
		char32 r = (b3 & 0x3f) | ((b2 & 0x3f) << 6) | ((b1 & 0x3f) << 12) | ((b0 & 0x07) << 18);
		*out++ = r;
		return out;
	}
}

template<typename In, typename Out>
Out u8_decode_step_simd(In& begin, In end, Out out)
{
	typedef simd::pack<nt2::uint8_t> input;
	typedef input::const_iterator iterator;

	input b0 = nt2::load<input, 0>(&*begin, 0);
	input b1 = nt2::load<input, 1>(&*begin, 0);
	input b2 = nt2::load<input, 2>(&*begin, 0);
	input b3 = nt2::load<input, 3>(&*begin, 0);

	input r = nt2::where(
		b0 & 0x80 == 0,
		b0, b1
    /*nt2::where(
			(b0 & 0xe0) == 0xc0,
			(b1 & 0x3f) | (b0 & 0x1f << 6),
			nt2::where(
				(b0 & 0xf0) == 0xe0,
				(b2 & 0x3f) | (b1 & 0x3f << 6) | (b0 & 0x0f << 12),
				(b3 & 0x3f) | (b2 & 0x3f << 6) | (b1 & 0x3f << 12) | (b0 & 0x07 << 18)
			)
		)*/
	);

  std::cout << r << "\n";
/*	for(iterator it=r.begin(); it!=r.end() && *it; ++it)
	*out++ = *it;
*/

	return out;
}

template<typename In, typename Out>
Out u8_decode_simd(In begin, In end, Out out)
{
	while(begin != end)
  {
		out = u8_decode_step_simd(begin, end, out);
    std::advance(begin,16);
  }

	return out;
}
template<typename In, typename Out>
Out u8_decode(In begin, In end, Out out)
{
	while(begin != end)
  {
		out = u8_decode_step(begin, end, out);
    std::advance(begin,1);
  }

	return out;
}

int main()
{
	std::vector<unsigned char, nt2::memory::allocator<unsigned char> > v(32);
  for(int i=0;i<32;++i) v[i] = 1+i;
	u8_decode_simd(v.begin(), v.end(), std::ostream_iterator<unsigned char>(std::cout, ", "));
	std::cout << std::endl;

  for(int i=0;i<32;++i) v[i] = 1+i;
  u8_decode(v.begin(), v.end(), std::ostream_iterator<unsigned int>(std::cout, ", "));
	std::cout << std::endl;
}


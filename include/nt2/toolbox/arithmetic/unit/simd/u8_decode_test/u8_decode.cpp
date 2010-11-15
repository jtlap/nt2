#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/memory/allocator.hpp>

typedef unsigned int char32;

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
	
	unsigned char b1 = *(begin++);
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
	typedef simd::pack<unsigned char, 16> input;
	typedef simd::pack<char32,        16> output;
	
	input b0 = nt2::load<input, 0>(&*begin, 0);
	input b1 = nt2::load<input, 1>(&*begin, 0);
	input b2 = nt2::load<input, 2>(&*begin, 0);
	input b3 = nt2::load<input, 3>(&*begin, 0);
	
	output r = nt2::where(
		b0 & 0x80 == 0,
		b0,
		nt2::where(
			(b0 & 0xe0) == 0xc0,
			(b1 & 0x3f) | (output(b0 & 0x1f) << 6),
			nt2::where(
				(b0 & 0xf0) == 0xe0,
				(b2 & 0x3f) | (output(b1 & 0x3f) << 6) | (output(b0 & 0x0f) << 12),
				(b3 & 0x3f) | (output(b2 & 0x3f) << 6) | (output(b1 & 0x3f) << 12) | (output(b0 & 0x07) << 18)
			)
		)
	);
	
	for(char32* it=r.begin(); it!=r.end() && *it; ++it)
		*out++ = *it;
	return out;
}

template<typename In, typename Out>
Out u8_decode(In begin, In end, Out out)
{
	while(begin != end)
		out = u8_decode_step_simd(begin, end, out);
		
	return out;
}

int main()
{
	std::vector<unsigned char, nt2::memory::allocator<unsigned char> > v(16 * 100);
	u8_decode(v.begin(), v.end(), std::ostream_iterator<unsigned int>(std::cout, ", "));
	std::cout << std::endl;
}

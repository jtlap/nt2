//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MANDELBROT_UTILS_HPP_INCLUDED
#define MANDELBROT_UTILS_HPP_INCLUDED

#include <nt2/table.hpp>
#include <fstream>

namespace utils
{

    template<class T>
    void save_pgm( nt2::table<T> const& t
                 , std::size_t const& h, std::size_t const& w
                 , std::string const& file_name
                 )
    {
      std::ofstream file;
      file.open(file_name.c_str());
      file << "P2\n" << h << " " << w << "\n255\n";
      for(std::size_t i=1;i<=h;i++)
      {
        for(std::size_t j=1;j<=w;j++)
          file << (int)(unsigned char) t(i,j) << " ";
        file << "\n";
      }
    }

    template<class T>
    void save_pgm( std::vector<T, boost::simd::allocator<int> > const& t
                 , std::size_t const& h, std::size_t const& w
                 , std::string const& file_name
                 )
    {
      std::ofstream file;
      file.open(file_name.c_str());
      file << "P2\n" << h << " " << w << "\n255\n";
      for(std::size_t i=0;i<h;i++)
      {
        for(std::size_t j=0;j<w;j++)
          file << (int)(unsigned char) t[j+w*i] << " ";
        file << "\n";
      }
    }
    template<class T>
    void save_pgm( std::vector<T> const& t
                 , std::size_t const& h, std::size_t const& w
                 , std::string const& file_name
                 )
    {
      std::ofstream file;
      file.open(file_name.c_str());
      file << "P2\n" << h << " " << w << "\n255\n";
      for(std::size_t i=0;i<h;i++)
      {
        for(std::size_t j=0;j<w;j++)
          file << (int)(unsigned char) t[j+w*i] << " ";
        file << "\n";
      }
    }
}

#endif

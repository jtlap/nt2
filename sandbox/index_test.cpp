#include <nt2/table.hpp>

int main()
{
    using nt2::table;
    using nt2::of_size;
    using nt2::_;

    const std::size_t M = 6;
    const std::size_t N = 12;

    typedef double T;
    table<T> y;

    table<T> x(of_size(M,N));

    for(std::size_t j = 1; j <= N; ++j)
        for(std::size_t i = 1; i <= M; ++i)
            x(i,j) = T(i-1+M*(j-1));

    y  = x(_,_) - x(_,_) + x(_,_);
    NT2_DISP(y);
}

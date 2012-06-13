#include <iostream>
#include <nt2/sdk/timing/cycle_timer.hpp>

int main()
{
  nt2::details::cycles_t elapsed;

  {
    nt2::time::cycle_timer timer(elapsed, false);
    sleep(1);
  }

  std::cout << "Frequency is roughly " << elapsed/1e9 << "GHz\n";
}

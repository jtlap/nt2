#include <iostream>
#include <nt2/sdk/timing/second_timer.hpp>

int main()
{
  double elapsed;

  {
    nt2::time::second_timer timer(elapsed);
    sleep(3);
  }
}

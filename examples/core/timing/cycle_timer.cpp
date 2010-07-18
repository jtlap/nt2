#include <iostream>
#include <nt2/include/timing.hpp>

using namespace std;

int main()
{
  int wait;
  double d;

  cout << "How many seconds do you want to wait ? ";
  cin >> wait;
  {
    nt2::time::cycle_timer s(d);
    sleep(wait);
  }
}



#include <nt2/sdk/config/reporter.hpp>

void custom_status()
{
  puts("| This status is a custom one.");
}

NT2_REGISTER_STATUS(custom_status);

int main()
{
  nt2::config::status();
}

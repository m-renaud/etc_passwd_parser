#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <unistd.h>

#include "etc_passwd_utils.hxx"


//===========================================================================
int main(int argc, char *argv[])
{
  std::ios::sync_with_stdio(false);

  using namespace mrr;

  etc_passwd_info info;
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
    return 1;
  }

  bool result = passwd_from_stream(argv[1], info);

  if (result)
  {
    generate_xml(info, std::cout, std::cerr);
  }
  else
  {
    std::cerr << "PARSE ERROR!" << std::endl;
    return 1;
  }

  return 0;
}

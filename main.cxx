#include <iostream>
#include <string>

#include "types.hxx"
#include "parser.hxx"

int main()
{
  using namespace mrr;

  std::string input;
  std::string temp;

  while(std::getline(std::cin, temp))
    input += temp + "\n";

  etc_pass_info info;
  bool result = parse_etc_pass(input.begin(), input.end(), info);

  if(result)
    std::cout << "Parsed fine." << std::endl;
  else
    std::cout << "No parse." << std::endl;

}

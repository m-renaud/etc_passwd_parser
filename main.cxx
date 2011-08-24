#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "passwd_utils.hxx"

void displayInfo(mrr::etc_pass_info const& epi);
void displayInfoAsXML(mrr::etc_pass_info const& epi);

//===========================================================================

int main()
{
  using namespace mrr;

  std::string input;
  std::string temp;

  //std::cin.setf(std::ios_base::skipws);

  etc_pass_info info;
  bool result = passwd_from_stream("test.txt", info);

  if (result)
    displayInfoAsXML(info);
  else
  {
    std::cerr << "PARSE ERROR!" << std::endl;
    return 1;
  }

  return 0;
}

//===========================================================================
void displayInfo(mrr::etc_pass_info const& epi)
{
  for(mrr::etc_pass_record const& epr : epi.records)
  {
    std::cout << "Username: " << epr.username << std::endl;
    std::cout << "Password: " << epr.password << std::endl;
    std::cout << "UID     : " << epr.uid      << std::endl;
    std::cout << "GID     : " << epr.gid      << std::endl;
    std::cout << "Uid Info: " << epr.uid_info << std::endl;
    std::cout << "Home Dir: " << epr.home_dir << std::endl;
    std::cout << "Shell   : " << epr.shell    << std::endl;
  }
}

//===========================================================================
void displayInfoAsXML(mrr::etc_pass_info const& epi)
{
  std::cout << "<etc_pass host=\"" << "\">" << std::endl;
  for(mrr::etc_pass_record const& epr : epi.records)
  {
    std::cout << "  <record>" << std::endl;
    std::cout << "    <username>" << epr.username << "</username>" << std::endl;
    std::cout << "    <uid>"      << epr.uid      << "</uid>"      << std::endl;
    std::cout << "    <gid>"      << epr.gid      << "</gid>"      << std::endl;
    std::cout << "    <uid_info>" << epr.uid_info << "</uid_info>" << std::endl;
    std::cout << "    <home_dir>" << epr.home_dir << "</home_dir>" << std::endl;
    std::cout << "    <shell>"    << epr.shell    << "</shell>"    << std::endl;
    std::cout << "  </record>" << std::endl;
  }
  std::cout << "</etc_pass>" << std::endl;

}

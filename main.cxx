#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <unistd.h>

#include "etc_passwd_utils.hxx"

void displayInfo(mrr::etc_passwd_info const& epi);
void displayInfoAsXML(mrr::etc_passwd_info const& epi);

//===========================================================================

int main(int argc, char *argv[])
{
  std::ios::sync_with_stdio(false);

  using namespace mrr;

  std::string input;
  std::string temp;

  etc_passwd_info info;
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
    return 1;
  }

  bool result = passwd_from_stream(argv[1], info);

  if (result)
  {
    displayInfoAsXML(info);
//    generate_xml(info, std::cout, std::cerr);
  }
  else
  {
    std::cerr << "PARSE ERROR!" << std::endl;
    return 1;
  }

  return 0;
}

//===========================================================================
void displayInfo(mrr::etc_passwd_info const& epi)
{
  for(mrr::etc_passwd_record const& epr : epi.records)
  {
    std::cout
      << "Username: " << epr.username << '\n'
      << "Password: " << epr.password << '\n'
    ;
    std::cout << "UID     : " << epr.uid      << std::endl;
    std::cout << "GID     : " << epr.gid      << std::endl;
    std::cout << "Uid Info: " << epr.uid_info << std::endl;
    std::cout << "Home Dir: " << epr.home_dir << std::endl;
    std::cout << "Shell   : " << epr.shell    << std::endl;
  }
}

//===========================================================================
void displayInfoAsXML(mrr::etc_passwd_info const& epi)
{
  char hostname[256];

  if(!gethostname(hostname, 256))
  {
    std::cout
    << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    << "<?xml-stylesheet type=\"text/xsl\" href=\"etc_pass.xsl\"?>"
    << "<etc_pass host=\"" << hostname << "\">"
    ;
    for(mrr::etc_passwd_record const& epr : epi.records)
    {
      std::cout
      << "<record>"
      << "<username>" << epr.username << "</username>"
      << "<uid>"      << epr.uid      << "</uid>"
      << "<gid>"      << epr.gid      << "</gid>"
      << "<uid_info>" << epr.uid_info << "</uid_info>"
      << "<home_dir>" << epr.home_dir << "</home_dir>"
      << "<shell>"    << epr.shell    << "</shell>"
      << "</record>"
      ;
    }
    std::cout << "</etc_pass>";
  }

}

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "types.hxx"
#include "parser.hxx"

#define USE_INPUT_STREAM_ITER

#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

typedef
  std::istreambuf_iterator<char>
  base_iter_type
;

typedef
  boost::spirit::multi_pass<base_iter_type>
  mp_iter_type
;

typedef
  boost::spirit::classic::position_iterator2<mp_iter_type>
  parse_iter_type
;

void displayInfo(mrr::etc_pass_info const& epi);
void displayInfoAsXML(mrr::etc_pass_info const& epi);


//===========================================================================
int main()
{
  using namespace mrr;

  std::string input;
  std::string temp;

  std::cin.setf(std::ios_base::skipws);

  // Create multipass iterators so the transient stream will be
  // buffered...
  mp_iter_type mp_beg = boost::spirit::make_default_multi_pass(
    base_iter_type(std::cin)
  );
  mp_iter_type mp_end = boost::spirit::make_default_multi_pass(
    base_iter_type()
  );

  // Create iterators that tracks the line and column position and
  // also buffers the last line read in...
  parse_iter_type begin(mp_beg, mp_end);
  begin.set_tab_chars(8);

  parse_iter_type end;

  //etc_pass_info info;
  START_STATE_RULE_RETTYPE info;
  bool result = parse_etc_pass(begin, end, info);

  if (result)
  {
    displayInfoAsXML(info);
  }
  else
  {
    boost::spirit::classic::file_position_base<std::string> const& pos
    = begin.get_position();

    std::ostringstream buf;
    buf
    << "Parse error @ line "<< pos.line << " column " << pos.column
    << std::endl
    << '\'' << begin.get_currentline() << '\''
    ;

    if (!begin.get_currentline().empty())
      buf << std::endl << std::setw(pos.column) << "" << "^here";

    std::cout << buf.str() << std::endl;
  }
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

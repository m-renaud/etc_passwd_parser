//===========================================================================

#include <istream>
#include <iterator>
#include <fstream>
#include <string>
#include <boost/spirit/include/support_istream_iterator.hpp>

#include "etc_passwd_utils.hxx"
#include "parser.hxx"

//===========================================================================

namespace mrr {

//===========================================================================

bool passwd_from_stream(
  std::string const& file_name,
  etc_pass_info& data
)
{
  using std::ifstream;
  using boost::spirit::basic_istream_iterator;

  ifstream is(file_name.c_str(), std::ios::binary);
  if (is.is_open())
  {
    is.unsetf(std::ios::skipws);
    basic_istream_iterator<char> begin(is);
    basic_istream_iterator<char> end;
    return parse_etc_pass(begin, end, data);
  }
  else
    return false;
}

bool passwd_from_stream(
  std::istream& is,
  etc_pass_info& data
)
{
  // Save the old flags...
  std::ios::fmtflags old = is.flags();
  is.unsetf(std::ios::skipws);

  // Parse...
  using boost::spirit::basic_istream_iterator;
  basic_istream_iterator<char> begin(is);
  basic_istream_iterator<char> end;
  bool const retval = parse_etc_pass(begin, end, data);

  // Restore flags...
  is.flags(old);

  return retval;
}

bool passwd_from_container(
  std::string& str,
  etc_pass_info& data
)
{
  std::string::iterator begin = str.begin();
  std::string::iterator end = str.end();
  return parse_etc_pass(begin, end, data);
}

//===========================================================================

} // namespace mrr

//===========================================================================

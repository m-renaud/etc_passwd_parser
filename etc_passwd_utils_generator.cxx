//===========================================================================

#include <istream>
#include <iterator>
#include <fstream>
#include <string>

#include "etc_passwd_utils.hxx"
#include "generator.hxx"

//===========================================================================

namespace mrr {

//===========================================================================

  bool generate_xml(etc_passwd_info& info, std::ostream& out, std::ostream& err)
  {
    std::ostream_iterator<char> begin(out);
    return generate_etc_passwd_xml(begin, info);
  }

//===========================================================================

} // namespace mrr

//===========================================================================

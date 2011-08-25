//===========================================================================

#include <istream>
#include <iterator>
#include <fstream>
#include <string>
#include <boost/spirit/include/support_istream_iterator.hpp>

#include "etc_passwd_utils.hxx"
#include "generator.hxx"

//===========================================================================

namespace mrr {

//===========================================================================

  bool generate_xml(etc_passwd_info& info, std::ostream& out, std::ostream& err)
  {
    return generate_etc_passwd_xml(out, info);
  }

//===========================================================================

} // namespace mrr

//===========================================================================

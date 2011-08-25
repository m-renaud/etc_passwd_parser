#ifndef MRR_ETC_PASSWD_UTILS_HXX__
#define MRR_ETC_PASSWD_UTILS_HXX__

#include <istream>
#include <string>
#include <ostream>

#include "types.hxx"

namespace mrr
{
  bool passwd_from_stream(std::string const& file_name, etc_passwd_info& data);

  bool passwd_from_stream(std::istream& is, etc_passwd_info& data);

  bool passwd_from_container(std::string& str, etc_passwd_info& data);

  bool generate_xml(etc_passwd_info& info, std::ostream& out, std::ostream& err);

} // namespace mrr


#endif // #ifndef MRR_ETC_PASSWD_UTILS_HXX__

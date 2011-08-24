#ifndef ETC_PASSWD_HXX__
#define ETC_PASSWD_HXX__

#include <istream>
#include <string>
#include <vector>

namespace mrr
{
  struct etc_pass_record;
  struct etc_pass_info;

  struct etc_pass_record
  {
    std::string username;
    std::string password;
    unsigned uid;
    unsigned gid;
    std::string uid_info;
    std::string home_dir;
    std::string shell;
  };

  struct etc_pass_info
  {
    std::vector<etc_pass_record> records;
  };

  bool passwd_from_stream(
    std::string const& file_name,
    etc_pass_info& data
  );

  bool passwd_from_stream(
    std::istream& is,
    etc_pass_info& data
  );
  
  bool passwd_from_container(
    std::string& str,
    etc_pass_info& data
  );

#if 0
  template <typename T, typename CharT>
  bool passwd_parse(std::basic_istream<T,CharT>& is, etc_pass_info& data);
#endif

} // namespace mrr


#endif // #ifndef ETC_PASSWD_HXX__

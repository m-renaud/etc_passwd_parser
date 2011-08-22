#ifndef __MRR_ETC_PASSWD_TYPES_HXX__
#define __MRR_ETC_PASSWD_TYPES_HXX__

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

} // namespace mrr

#endif // #ifndef __MRR_ETC_PASSWD_TYPES_HXX__

#ifndef MRR_TYPES_HXX__
#define MRR_TYPES_HXX__

#include <string>
#include <vector>

namespace mrr
{

struct etc_passwd_record
{
  std::string username;
  std::string password;
  unsigned uid;
  unsigned gid;
  std::string uid_info;
  std::string home_dir;
  std::string shell;
};

struct etc_passwd_info
{
  std::vector<etc_passwd_record> records;
};


} // namespace mrr

#endif // #ifndef MRR_TYPES_HXX__

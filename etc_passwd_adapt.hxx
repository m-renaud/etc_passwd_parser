#ifndef MRR_ETC_PASSWD_ADAPT_HXX__
#define MRR_ETC_PASSWD_ADAPT_HXX__

#include <vector>
#include <string>
#include <boost/fusion/include/adapt_struct.hpp>

#include "types.hxx"

BOOST_FUSION_ADAPT_STRUCT(
  mrr::etc_passwd_record,
  (std::string, username)
  (std::string, password)
  (unsigned, uid)
  (unsigned, gid)
  (std::string, uid_info)
  (std::string, home_dir)
  (std::string, shell)
)

BOOST_FUSION_ADAPT_STRUCT(
  mrr::etc_passwd_info,
  (std::vector<mrr::etc_passwd_record>, records)
)


#endif // #ifndef MRR_ETC_PASSWD_ADAPT_HXX__

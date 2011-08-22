#ifndef __MRR_ETC_PASSWD_PARSE_HXX__
#define __MRR_ETC_PASSWD_PARSE_HXX__

#define FUSION_MAX_VECTOR_SIZE 20

#include "types.hxx"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <vector>
#include <string>

BOOST_FUSION_ADAPT_STRUCT(
  mrr::etc_pass_record,
  (std::string, username)
  (std::string, password)
  (unsigned, uid)
  (unsigned, gid)
  (std::string, uid_info)
  (std::string, home_dir)
  (std::string, shell)
)

BOOST_FUSION_ADAPT_STRUCT(
  mrr::etc_pass_info,
  (std::vector<mrr::etc_pass_record>, records)
)


namespace mrr
{

  namespace qi = boost::spirit::qi;
//  namespace ascii = boost::spirit::ascii;

  template <typename Iter>
  struct parser : qi::grammar<Iter, etc_pass_info(), qi::eol_parser>
  {
    parser() : parser::base_type(start)
    {
      using qi::uint_;
      using qi::char_;
//      using qi::lexeme;
//      using qi::lit;
//      using qi::eol;
//      using ascii::alnum;

      string_field %= +(char_ - ':');

      record %= string_field
      >> ':' >> string_field
      >> ':' >> uint_
      >> ':' >> uint_
      >> ':' >> string_field
      >> ':' >> string_field
      >> ':' >> string_field
      ;

      start %= +record;

    }

    qi::rule<Iter, std::string()> string_field;
    qi::rule<Iter, etc_pass_record()> record;
    qi::rule<Iter, etc_pass_info(), qi::eol_parser> start;
  };

  template <typename Iter>
  bool parse_etc_pass(
    Iter first,
    Iter last,
    etc_pass_info& info
  )
  {
    parser<Iter> p;

    bool result = qi::phrase_parse(
      first,
      last,
      p,
      qi::eol,
      info
    );

    return (result && first == last);
  }

} // namespace mrr


#endif // #ifndef __MRR_ETC_PASSWD_PARSE_HXX__

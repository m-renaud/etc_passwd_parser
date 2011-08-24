#ifndef __MRR_ETC_PASSWD_PARSE_HXX__
#define __MRR_ETC_PASSWD_PARSE_HXX__

// TO FULLY DEBUG COMPILE WITH:
//   g++ -DBOOST_SPIRIT_DEBUG main.cxx
//   g++ -std=c++0x -DBOOST_SPIRIT_DEBUG main.cxx

// Matt notice how I debugged things...
//  I left the older macro definitions in as comments so you can see.

//#define START_STATE_RULE_NAME         string_field
//#define START_STATE_RULE_RETTYPE      std::string

//#define START_STATE_RULE_NAME         record
//#define START_STATE_RULE_RETTYPE      ::mrr::etc_pass_record

#define START_STATE_RULE_NAME         start_state
#define START_STATE_RULE_RETTYPE      ::mrr::etc_pass_info



#define FUSION_MAX_VECTOR_SIZE 20

#include "types.hxx"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <boost/spirit/include/phoenix.hpp>

#include <boost/spirit/repository/include/qi_flush_multi_pass.hpp>

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
  struct parser : qi::grammar<Iter, START_STATE_RULE_RETTYPE() >
  {
    parser() : parser::base_type(START_STATE_RULE_NAME)
    {
      using qi::uint_;
      using qi::char_;
      using qi::lit;
      using qi::eoi;
      using qi::omit;
      using boost::spirit::repository::flush_multi_pass;
//      using qi::lexeme;
//      using qi::lit;
//      using qi::eol;
//      using ascii::alnum;

      string_field %=
        +(char_ -(lit(':') | lit('\n') | lit("\r\n")))
      ;

      record %=
        string_field
        >> ':' >> string_field
        >> ':' >> uint_
        >> ':' >> uint_
        >> ':' >> string_field
        >> ':' >> string_field
        >> ':' >> string_field
      ;

      end_of_record %=
        (
          lit('\n')
          | lit("\r\n")
          | eoi
        )
        >> flush_multi_pass
      ;

      records %=
        record % end_of_record
      ;

      start_state = records;

#if 0
#define SRN(s)    s.name(#s); debug(s);
      SRN(string_field)
      SRN(record)
      SRN(end_of_record)
      SRN(records)
      SRN(start_state)
#undef SRN
#endif
    }

    qi::rule<Iter, std::string()> string_field, end_of_record;
    qi::rule<Iter, etc_pass_record()> record;
    qi::rule<Iter, std::vector<etc_pass_record>()> records;
    qi::rule<Iter, etc_pass_info()> start_state;
  };

  template <typename Iter>
  bool parse_etc_pass(
    Iter& first,
    Iter& last,
    //etc_pass_info& info
    START_STATE_RULE_RETTYPE& info
  )
  {
    parser<Iter> p;

    bool result = qi::parse(
      first,
      last,
      p,
      info
    );

    return result;
  }

} // namespace mrr


#endif // #ifndef __MRR_ETC_PASSWD_PARSE_HXX__

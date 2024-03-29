#ifndef MRR_ETC_PASSWD_PARSER_HXX_
#define MRR_ETC_PASSWD_PARSER_HXX_

// TO FULLY DEBUG COMPILE WITH:
//   g++ -DBOOST_SPIRIT_DEBUG main.cxx
//   g++ -std=c++0x -DBOOST_SPIRIT_DEBUG main.cxx

#define START_STATE_RULE_NAME         start_state
#define START_STATE_RULE_RETTYPE      ::mrr::etc_passwd_info

#define FUSION_MAX_VECTOR_SIZE 20

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_flush_multi_pass.hpp>

#include "etc_passwd_adapt.hxx"


namespace mrr
{

namespace qi = boost::spirit::qi;

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

    string_field_char %=
    char_ -(lit(':') | lit('\n') | lit("\r\n"))
    ;

    string_field_nonempty %=
    +string_field_char
    ;

    string_field %=
    *string_field_char
    ;

    record %=
    string_field_nonempty
    >> ':' >> string_field_nonempty
    >> ':' >> uint_
    >> ':' >> uint_
    >> ':' >> string_field
    >> ':' >> string_field_nonempty
    >> ':' >> string_field_nonempty
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

#define SRN(s)    s.name(#s); debug(s);
    SRN(string_field)
    SRN(record)
    SRN(end_of_record)
    SRN(records)
    SRN(start_state)
#undef SRN
    }

  qi::rule<Iter, char()> string_field_char;
  qi::rule<Iter, std::string()> string_field, string_field_nonempty, end_of_record;
  qi::rule<Iter, etc_passwd_record()> record;
  qi::rule<Iter, std::vector<etc_passwd_record>()> records;
  qi::rule<Iter, etc_passwd_info()> start_state;
};

template <typename Iter>
  inline bool parse_etc_pass(Iter& first, Iter& last,
			     START_STATE_RULE_RETTYPE& info)
{
  parser<Iter> p;
  return qi::parse(first, last, p, info);
}

} // namespace mrr


#endif // #ifndef MRR_ETC_PASSWD_PARSER_HXX_

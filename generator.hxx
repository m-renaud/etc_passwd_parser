#ifndef MRR_ETC_PASSWD_GENERATOR_HXX__
#define MRR_ETC_PASSWD_GENERATOR_HXX__

#define START_STATE_RULE_NAME         start_state
#define START_STATE_RULE_RETTYPE      ::mrr::etc_passwd_info


#define FUSION_MAX_VECTOR_SIZE 20

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

#include "etc_passwd_adapt.hxx"


namespace mrr
{
  namespace ka = boost::spirit::karma;

  template <typename Iter>
  struct generator : ka::grammar<Iter, START_STATE_RULE_RETTYPE() >
  {
    generator() : generator::base_type(START_STATE_RULE_NAME)
    {
      using ka::uint_;
      using ka::char_;
      using ka::lit;

      string_field =
        *char_
      ;

      record =
        lit("<record>")
        << lit("<username>") << string_field << lit("</username>")
        << lit("<password>") << string_field << lit("</password>")
        << lit("<uid>")      << uint_        << lit("</uid>")
        << lit("<gid>")      << uint_        << lit("</gid>")
        << lit("<uid_info>") << string_field << lit("</uid_info>")
        << lit("<home_dir>") << string_field << lit("</home_dir>")
        << lit("<shell>")    << string_field << lit("</shell>")
        << lit("</record>")
      ;


      records =
      << lit("<etc_pass>")
      << *record
      << lit("</etc_pass")
      ;

      start_state = records
      ;
    }

    ka::rule<Iter, std::string()> string_field;
    ka::rule<Iter, etc_passwd_record()> record;
    ka::rule<Iter, std::vector<etc_passwd_record>()> records;
    ka::rule<Iter, etc_passwd_info()> start_state;
  };

  template <typename Iter>
  inline bool generate_etc_passwd_xml(Iter& sink, START_STATE_RULE_RETTYPE& info)
  {
    generator<Iter> g;
    return ka::generate(sink, g, info);
  }

}
#endif // #define MRR_ETC_PASSWD_GENERATOR_HXX__

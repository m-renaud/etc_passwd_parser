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
      using ka::string;
      using ka::hex;
      using ka::space;
      using ka::print;

      // XML 1.x required escaped character entities...
      escaped_char_entities.add
        ('<', "&lt;")
        ('>', "&gt;")
        ('\'', "&apos;")
        ('"', "&quot;")
        ('&', "&amp;")
      ;

      // There is no need to escape quotation marks in #PCDATA...
      escaped_char_PCDATA_entities.add
        ('<', "&lt;")
        ('>', "&gt;")
        ('&', "&amp;")
      ;

      // Needed to escape (CDATA) (e.g., attribute) values...
      escape_attribute_value %=
        *(
          escaped_char_entities
          | print
          | ( lit("&#x") << hex << lit(';') )
        )
      ;

      // Needed to escape PCDATA (e.g., text between tags) values...
      escape_PCDATA %=
        *(
          escaped_char_PCDATA_entities
          | space
          | print
          | ( lit("&#x") << hex << lit(';') )
        )
      ;

      /*string_field =
        *char_
      ;*/

      record =
        lit("<record>")
        << lit("<username>") << escape_PCDATA << lit("</username>")
        << lit("<password>") << escape_PCDATA << lit("</password>")
        << lit("<uid>")      << uint_        << lit("</uid>")
        << lit("<gid>")      << uint_        << lit("</gid>")
        << lit("<uid_info>") << escape_PCDATA << lit("</uid_info>")
        << lit("<home_dir>") << escape_PCDATA << lit("</home_dir>")
        << lit("<shell>")    << escape_PCDATA << lit("</shell>")
        << lit("</record>")
      ;

      records =
        lit("<etc_pass>")
        << *record
        << lit("</etc_pass")
      ;

      start_state = 
        records
      ;

#define SNR(s) s.name(#s); debug(s);
      SNR(escape_PCDATA)
      SNR(escape_attribute_value)
      //SNR(string_field)
      SNR(record)
      SNR(records)
      SNR(start_state)
#undef SNR
    }

    //ka::rule<Iter, std::string()> string_field;
    ka::rule<Iter, etc_passwd_record()> record;
    ka::rule<Iter, std::vector<etc_passwd_record>()> records;
    ka::rule<Iter, START_STATE_RULE_RETTYPE()> start_state;

    // For escaping strings in XML...
    ka::rule<Iter, std::string()> escape_attribute_value, escape_PCDATA;
    ka::symbols<char, char const*> escaped_char_entities;
    ka::symbols<char, char const*> escaped_char_PCDATA_entities;
  };

  template <typename Iter>
  inline bool generate_etc_passwd_xml(Iter& sink, START_STATE_RULE_RETTYPE& info)
  {
    generator<Iter> g;
    return ka::generate(sink, g, info);
  }

}
#endif // #define MRR_ETC_PASSWD_GENERATOR_HXX__

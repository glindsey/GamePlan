#include "ErrorMacros.h"

#include <boost/format.hpp>
#include <cstdlib>

struct ErrorMacros::Impl
{
    static std::unique_ptr<ErrorMacros> instance;
    bool die_on_minor_error = false;
    bool die_on_major_error = false;
};

std::unique_ptr<ErrorMacros> ErrorMacros::Impl::instance;

ErrorMacros::ErrorMacros()
{
  //ctor
}

ErrorMacros::~ErrorMacros()
{
  //dtor
}

ErrorMacros& ErrorMacros::instance()
{
  if (Impl::instance.get() == nullptr)
  {
    Impl::instance.reset(new ErrorMacros());
  }

  return *(Impl::instance.get());
}

void ErrorMacros::print_trace(boost::basic_format<char>& desc,
                              char const* file,
                              int line,
                              char const* func)
{
  print_trace(desc.str(), file, line, func);
}

void ErrorMacros::print_trace(std::string desc,
                              char const* file,
                              int line,
                              char const* func)
{
  std::cout <<
    boost::format("%s:%d (%s): TRACE: %s")
      % file % line % func % desc << std::endl;
}

void ErrorMacros::minor_error(boost::basic_format<char>& desc,
                              char const* file,
                              int line,
                              char const* func)
{
  minor_error(desc.str(), file, line, func);
}

void ErrorMacros::minor_error(std::string desc,
                              char const* file,
                              int line,
                              char const* func)
{
  std::cout <<
    boost::format("%s:%d (%s): MINOR error: %s")
      % file % line % func % desc << std::endl;

  if (impl->die_on_minor_error)
  {
    std::cout << "Dying because die_on_minor_error is true." << std::endl;
    std::cout << "Press Enter to exit." << std::endl;
    getchar();
    exit(-3);
  }
}

void ErrorMacros::major_error(boost::basic_format<char>& desc,
                              char const* file,
                              int line,
                              char const* func)
{
  major_error(desc.str(), file, line, func);
}

void ErrorMacros::major_error(std::string desc,
                              char const* file,
                              int line,
                              char const* func)
{
  std::cout <<
    boost::format("%s:%d (%s): MAJOR error: %s")
      % file % line % func % desc << std::endl;

  if (impl->die_on_major_error)
  {
    std::cout << "Dying because die_on_major_error is true." << std::endl;
    std::cout << "Press Enter to exit." << std::endl;
    getchar();
    exit(-2);
  }
}

void ErrorMacros::fatal_error(boost::basic_format<char>& desc,
                              char const* file,
                              int line,
                              char const* func)
{
  fatal_error(desc.str(), file, line, func);
}

void ErrorMacros::fatal_error(std::string desc,
                              char const* file,
                              int line,
                              char const* func)
{
  std::cout <<
    boost::format("%s:%d (%s): FATAL error: %s")
      % file % line % func % desc << std::endl;

  std::cout << "Dying because this is an unrecoverable error." << std::endl;
  std::cout << "Press Enter to exit." << std::endl;
  getchar();
  exit(-1);
}

void ErrorMacros::set_error_handling_flags(bool minor, bool major)
{
  impl->die_on_minor_error = minor;
  impl->die_on_major_error = major;
}


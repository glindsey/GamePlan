#ifndef ERRORMACROS_H_INCLUDED
#define ERRORMACROS_H_INCLUDED

#include <boost/format.hpp>
#include <boost/noncopyable.hpp>
#include <cstdio>
#include <memory>
#include <sstream>

#define TRACE(s)                                                        \
{                                                                       \
  ErrorMacros::instance().print_trace(s, __FILE__, __LINE__, __func__); \
}

#define MINOR_ERROR(s)                                                  \
{                                                                       \
  ErrorMacros::instance().minor_error(s, __FILE__, __LINE__, __func__); \
}

#define MAJOR_ERROR(s)                                                  \
{                                                                       \
  ErrorMacros::instance().major_error(s, __FILE__, __LINE__, __func__); \
}

#define FATAL_ERROR(s)                                                  \
{                                                                       \
  ErrorMacros::instance().fatal_error(s, __FILE__, __LINE__, __func__); \
}

#ifndef NDEBUG

#define ASSERT_NOT_NULL(ptr)                                              \
{                                                                         \
  if (ptr == nullptr)                                                     \
  {                                                                       \
    FATAL_ERROR("Invalid null pointer: \"" #ptr "\"");                    \
  }                                                                       \
}                                                                         \

#define ASSERT_CONDITION(condition)                                       \
{                                                                         \
  if (!(condition))                                                       \
  {                                                                       \
    FATAL_ERROR("Assertion failed: \"" #condition "\"");                  \
  }                                                                       \
}                                                                         \

#else
#define ASSERT_NOT_NULL(ptr)
#define ASSERT_CONDITION(condition)
#endif

class ErrorMacros :
  public boost::noncopyable
{
  public:
    static ErrorMacros& instance();
    virtual ~ErrorMacros();

    void print_trace(std::string desc,
                     char const* file,
                     int line,
                     char const* func);

    void print_trace(boost::basic_format<char>& desc,
                     char const* file,
                     int line,
                     char const* func);

    void minor_error(std::string desc,
                     char const* file,
                     int line,
                     char const* func);

    void minor_error(boost::basic_format<char>& desc,
                     char const* file,
                     int line,
                     char const* func);

    void major_error(std::string desc,
                     char const* file,
                     int line,
                     char const* func);

    void major_error(boost::basic_format<char>& desc,
                     char const* file,
                     int line,
                     char const* func);

    void fatal_error(std::string desc,
                     char const* file,
                     int line,
                     char const* func);

    void fatal_error(boost::basic_format<char>& desc,
                     char const* file,
                     int line,
                     char const* func);

    void set_error_handling_flags(bool minor, bool major);

  protected:
  private:
    ErrorMacros();

    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // ERRORMACROS_H_INCLUDED

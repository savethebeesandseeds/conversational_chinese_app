#ifndef __UTILS_TOOL
#define __UTILS_TOOL
#include <string>

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args ){
  /* calculate size */
  int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
  /* veryfy errors */
  if( size_s <= 0 ){ throw std::runtime_error( "Error during string formatting." ); }
  /* cast size as size_t */
  size_t size = static_cast<size_t>( size_s );
  /* alocate buffer */
  std::unique_ptr<char[]> buf( new char[ size ] );
  /* string format buff */
  std::snprintf( buf.get(), size, format.c_str(), args ... );
  /* return as string */
  return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

#endif
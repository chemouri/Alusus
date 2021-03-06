/**
 * @file Core/Basic/Logger.h
 * Contains the header of class Core::Basic::Logger.
 *
 * @copyright Copyright (C) 2014 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <https://alusus.org/alusus_license_1_0>.
 */
//==============================================================================

#ifdef USE_LOGS

#ifndef CORE_BASIC_LOGGER_H
#define CORE_BASIC_LOGGER_H

namespace Core { namespace Basic
{

/**
 * @brief Provides logging mechanism with different logging levels.
 * @ingroup basic_utils
 *
 * This is a singleton class.
 */
class Logger
{
  //============================================================================
  // Member Variables

  /**
   * @brief A bitwise filter for logged events.
   *
   * Logger objects match their level with this filter using bitwise and and
   * only print messsages if the result was not zero. Default value for the
   * filter is -1 (display all).
   */
  public: static Int filter;

  /**
   * @brief The level of this logging object.
   * @sa filter
   */
  private: const Int level;


  //============================================================================
  // Constructor

  public: Logger(Int l) : level(l)
  {
  }


  //============================================================================
  // Member Functions

  /// Log an argument.
  public: template <class T> const Logger& operator << (const T &arg) const
  {
    if (this->level & Logger::filter) std::clog << arg;
    return *this;
  }

}; // class

} } // namespace

#endif

#endif

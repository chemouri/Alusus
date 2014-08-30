/**
 * @file Core/Standard/RedefinitionMsg.h
 * Contains the header of class Core::Processing::RedefinitionMsg.
 *
 * @copyright Copyright (C) 2014 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef PARSER_REDEFINITION_MSG_H
#define PARSER_REDEFINITION_MSG_H

namespace Core { namespace Standard
{

// TODO: DOC

class RedefinitionMsg : public Processing::BuildMsg
{
  //============================================================================
  // Type Info

  TYPE_INFO(RedefinitionMsg, Processing::BuildMsg, "Core.Standard", "Core", "alusus.net");


  //============================================================================
  // Member Variables

  private: Str name;


  //============================================================================
  // Constructor / Destructor

  public: RedefinitionMsg(Char const *n, Int l, Int c) : name(n), Processing::BuildMsg(l, c)
  {
  }

  public: virtual ~RedefinitionMsg()
  {
  }


  //============================================================================
  // Member Functions

  /// @sa Processing::BuildMsg::getCode()
  public: virtual const Str& getCode() const
  {
    static Str code("S1001");
    return code;
  }

  /// @sa Processing::BuildMsg::getSeverity()
  public: virtual Int getSeverity() const
  {
    return 1;
  }

  /// Get the name of the duplicate definition.
  public: const Str& getDefinitionName() const
  {
    return this->name;
  }

  /// @sa Processing::BuildMsg::getCode()
  public: virtual void buildDescription(Str &str) const
  {
    str = STR("Duplicate definition. [");
    str += this->name;
    str += "]";
  }

}; // class

} } // namespace

#endif

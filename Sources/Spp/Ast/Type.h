/**
 * @file Spp/Ast/Type.h
 * Contains the header of class Spp::Ast::Type.
 *
 * @copyright Copyright (C) 2017 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef SPP_AST_TYPE_H
#define SPP_AST_TYPE_H

namespace Spp { namespace Ast
{

using namespace Core;

class Type : public Core::Data::Node,
             public virtual Core::Basic::Bindings, public virtual Core::Data::MapContainer,
             public virtual Core::Data::Ast::Metadata,
             public virtual Core::Data::Clonable, public virtual Core::Data::Printable
{
  //============================================================================
  // Type Info

  TYPE_INFO(Type, Core::Data::Node, "Spp.Ast", "Spp", "alusus.net", (
    INHERITANCE_INTERFACES(
      Core::Basic::Bindings,
      Core::Data::MapContainer,
      Core::Data::Ast::Metadata,
      Core::Data::Clonable,
      Core::Data::Printable
    )
  ));


  //============================================================================
  // Member Variables

  private: SharedPtr<Block> body;


  //============================================================================
  // Implementations

  IMPLEMENT_METADATA(Type);

  IMPLEMENT_BINDINGS(Bindings,
                     (prodId, TiWord, VALUE, setProdId(value), &prodId),
                     (sourceLocation, Core::Data::SourceLocation, VALUE, setSourceLocation(value), &sourceLocation));

  IMPLEMENT_MAP_CONTAINER(MapContainer, (Block, body));

  IMPLEMENT_AST_MAP_PRINTABLE(Type);


  //============================================================================
  // Constructor / Destructor

  public: virtual ~Type()
  {
    DISOWN_SHAREDPTR(this->body);
  }


  //============================================================================
  // Member Functions

  public: void setBody(SharedPtr<Block> const &b)
  {
    UPDATE_OWNED_SHAREDPTR(this->body, b);
  }

  public: SharedPtr<Block> const& getBody() const
  {
    return this->body;
  }

  public: virtual Bool isImplicitlyCastableTo(
    Type const *type, ExecutionContext const *context, Core::Standard::RootManager *rootManager
  ) const = 0;

  public: virtual Bool isExplicitlyCastableTo(
    Type const *type, ExecutionContext const *context, Core::Standard::RootManager *rootManager
  ) const = 0;

}; // class

} } // namespace

#endif

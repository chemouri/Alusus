/**
 * @file Spp/GrammarFactory.h
 * Contains the header of class Spp::GrammarFactory.
 *
 * @copyright Copyright (C) 2020 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <https://alusus.org/alusus_license_1_0>.
 */
//==============================================================================

#ifndef SPP_GRAMMARFACTORY_H
#define SPP_GRAMMARFACTORY_H

namespace Spp
{

class GrammarFactory : public Core::Data::Grammar::Factory
{
  //============================================================================
  // Constructor & Destructor

  public: GrammarFactory()
  {
  }

  public: virtual ~GrammarFactory()
  {
  }


  //============================================================================
  // Member Functions

  /// Create the entire core grammar.
  public: void createGrammar(
    Core::Data::Ast::Scope *rootScope, Main::RootManager *manager, Ast::Helper *astHelper,
    CodeGen::AstProcessor *astProcessor, CodeGen::Generator *generator,
    LlvmCodeGen::TargetGenerator *targetGenerator
  );

  public: void cleanGrammar(Core::Data::Ast::Scope *rootScope);

}; // class

} // namespace

#endif

/**
 * @file Scg/CodeGeneration/FunctionLinkExpression.cpp
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#include <CodeGeneration/CodeGenerator.h>
#include <CodeGeneration/FunctionLinkExpression.h>
#include <CodeGeneration/FunctionalExpression.h>
#include <CodeGeneration/LowLinkExpression.h>
#include <Instructions/DeclareExtFunction.h>

namespace Scg
{
using namespace Core::Basic;
using namespace Core::Data;

FunctionLinkExpression::FunctionLinkExpression(CodeGenerator *gen,
    const SharedPtr<IdentifiableObject> &astRoot)
{
  auto astRootMeta = astRoot->getInterface<ParsingMetadataHolder>();

  if (astRootMeta == nullptr || astRootMeta->getProdId() != gen->getLinkId())
    throw EXCEPTION(SystemException,
                    "Function link expressions can be constructed from Main.Link only.");

  // Initialise tree browsers.
  static ReferenceSeeker seeker;
  static SharedPtr<Reference> funcExpNoRetReference = REF_PARSER->parseQualifier(
        STR("0~where(prodId=Expression.Exp)."
            "0~where(prodId=Expression.FunctionalExp)"),
        ReferenceUsageCriteria::MULTI_DATA);
  static SharedPtr<Reference> funcExpReference = REF_PARSER->parseQualifier(
        STR("0~where(prodId=Expression.Exp)."
            "0~where(prodId=Expression.LowLinkExp)"),
        ReferenceUsageCriteria::MULTI_DATA);

  // Try to parse a function link with no return value.
  SharedPtr<ParsedList> item;

  if ((item = getSharedPtr(seeker.tryGet(funcExpReference.get(), astRoot.get())).io_cast<ParsedList>()) != nullptr) {
    auto argsAndRet = LowLinkExpression(gen, item);

    if (argsAndRet.getSeparator().compare("=>") != 0) {
      gen->getBuildMsgStore()->add(std::make_shared<Core::Processing::CustomBuildMsg>(
                                     STR("Invalid separator between the arguments of the function"
                                         " and its return type. Must use '=>'"),
                                     STR("SCG1022"), 1, astRootMeta->getSourceLocation(),
                                     argsAndRet.getSeparator().c_str()));
    }

    this->arguments = new FunctionalExpression(
      gen, argsAndRet.getLHS().s_cast<ParsedList>());
    this->retType = gen->parseVariableType(argsAndRet.getRHS());
  } else if ((item = getSharedPtr(seeker.tryGet(funcExpNoRetReference.get(),
                                  astRoot.get())).io_cast<ParsedList>()) != nullptr)
    this->arguments = new FunctionalExpression(gen, item);

  // Stores the line and column numbers.
  this->sourceLocation = item->getSourceLocation();
}

//----------------------------------------------------------------------------

FunctionLinkExpression::~FunctionLinkExpression()
{
  if (this->arguments != 0) delete this->arguments;
}

//----------------------------------------------------------------------------

DeclareExtFunction *FunctionLinkExpression::toDeclareExtFunction()
{
  auto declExtFunc = this->arguments->toDeclareExtFunction(this->retType);
  declExtFunc->setSourceLocation(this->sourceLocation);
  return declExtFunc;
}
}

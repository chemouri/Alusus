/**
 * @file Scg/Operators/UnaryOperator.cpp
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#include <prerequisites.h>

// LLVM header files
#include <llvm/IR/IRBuilder.h>

// Scg files
#include <Containers/Block.h>
#include <Operators/Content.h>
#include <Operators/UnaryOperator.h>
#include <Types/DoubleType.h>
#include <Types/FloatType.h>
#include <Types/IntegerType.h>
#include <Values/Variable.h>

using namespace llvm;

namespace Scg
{
Expression::CodeGenerationStage UnaryOperator::GenerateCode()
{
  BLOCK_CHECK;

  // Special case '=' because we don't want to emit the LHS as an expression.
  auto irb = GetBlock()->GetIRBuilder();

  if (this->operatorType == INCREMENT || this->operatorType == DECREMENT)
  {
    auto operand = dynamic_cast<Content*>(GetOperand());
    if (operand == nullptr)
      throw EXCEPTION(InvalidOperationException, "The operand of a unary "
          "operator must be the content of a pointer.");
    auto operandType = operand->GetValueTypeSpec()->ToValueType(*GetModule());
    if (operandType != IntegerType::Get() &&
      operandType != FloatType::Get() &&
      operandType != DoubleType::Get())
      throw EXCEPTION(InvalidLhsException, "Left-hand side of increment/decrement "
      "operator must be numeric.");

    // Evaluates the expression of the operand, which should result in a
    // variable.
    auto variable = GetOperand()->GetGeneratedLlvmValue();
    if (this->operatorType == INCREMENT)
    {
      if (operandType == IntegerType::Get())
        this->llvmValue = irb->CreateAdd(variable, IntegerType::Get()->GetLlvmConstant(1));
      else if (operandType == FloatType::Get())
        this->llvmValue = irb->CreateFAdd(variable, FloatType::Get()->GetLlvmConstant(1));
      else if (operandType == DoubleType::Get())
        this->llvmValue = irb->CreateFAdd(variable, DoubleType::Get()->GetLlvmConstant(1));
    }
    else
    {
      if (operandType == IntegerType::Get())
        this->llvmValue = irb->CreateSub(variable, IntegerType::Get()->GetLlvmConstant(1));
      else if (operandType == FloatType::Get())
        this->llvmValue = irb->CreateFSub(variable, FloatType::Get()->GetLlvmConstant(1));
      else if (operandType == DoubleType::Get())
        this->llvmValue = irb->CreateFSub(variable, DoubleType::Get()->GetLlvmConstant(1));
    }

    this->llvmStoreInst = irb->CreateStore(this->llvmValue, operand->GetLlvmPointer());

    this->generatedLlvmValue = this->llvmValue;

    return Expression::GenerateCode();
  }

  throw EXCEPTION(UnreachableCodeException, "This code shouldn't be reached.");
}

//------------------------------------------------------------------------------

Expression::CodeGenerationStage UnaryOperator::PostGenerateCode()
{
  if (this->llvmStoreInst)
  {
    if (!this->llvmStoreInst->hasNUses(0))
      // Cannot delete the instruction yet; stay in PostCodeGeneration stage.
      return CodeGenerationStage::PostCodeGeneration;
    this->llvmStoreInst->eraseFromParent();
    this->llvmStoreInst = nullptr;
  }
  else if (this->llvmValue)
  {
    if (!this->llvmValue->hasNUses(0))
      // Cannot delete the instruction yet; stay in PostCodeGeneration stage.
      return CodeGenerationStage::PostCodeGeneration;
    // TODO: Is there a solution better than dynamic casting?
    auto asInst = dyn_cast<llvm::Instruction>(this->llvmValue);
    if (asInst != 0)
      asInst->eraseFromParent();
    else
      delete this->llvmValue;
    this->llvmValue = nullptr;
  }

  return CodeGenerationStage::None;
}

//----------------------------------------------------------------------------

std::string UnaryOperator::ToString()
{
  if (this->operatorType == INCREMENT)
    return GetOperand()->ToString() + "++";
  else
    return GetOperand()->ToString() + "--";
}
}

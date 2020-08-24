#include "llvm/ADT/APInt.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <vector>

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);

int main() {
  static std::unique_ptr<Module> TheModulej
  TheModule = std::make_unique<Module>("inputFile", TheContext);
  /*Declare that printf exists and has signature int (i8*, ...)**/
  std::vector<Type *> args;
  args.push_back(Type::getInt8PtrTy(TheContext));
  /*`true` specifies the function as variadic*/
  FunctionType *printfType =
      FunctionType::get(Builder.getInt32Ty(), args, true);
  Function::Create(printfType, Function::ExternalLinkage, "printf",
                   TheModule.get());
  /*begin codegen for `main`*/
  FunctionType *mainType = FunctionType::get(Builder.getInt32Ty(), false);
  Function *main = Function::Create(mainType, Function::ExternalLinkage, "main",
                                    TheModule.get());
  BasicBlock *entry = BasicBlock::Create(TheContext, "entry", main);
  Builder.SetInsertPoint(entry);
  /*Set up printf arguments*/
  std::vector<Value *> printArgs;
  Value *formatStr = Builder.CreateGlobalStringPtr("%d\n");
  printArgs.push_back(formatStr);
  /*We will be printing "20"*/
  printArgs.push_back(ConstantInt::get(TheContext, APInt(32, 20)));
  Builder.CreateCall(TheModule->getFunction("printf"), printArgs);
  /*return value for `main`*/
  Builder.CreateRet(ConstantInt::get(TheContext, APInt(32, 0)));
  /*Emit the LLVM IR to the console*/
  TheModule->print(outs(), nullptr);
}
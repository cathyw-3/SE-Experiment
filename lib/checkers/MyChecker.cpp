#include "checkers/MyChecker.h"

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");

void MyChecker::check() {
  readConfig();
  getEntryFunc();
  if (entryFunc != nullptr) {
    FunctionDecl *funDecl = manager->getFunctionDecl(entryFunc);
    std::cout << "The entry function is: "
              << funDecl->getQualifiedNameAsString() << std::endl;
    std::cout << "Here is its dump: " << std::endl;
    funDecl->dump();
  }
  LangOptions LangOpts;
  LangOpts.CPlusPlus = true;
  std::unique_ptr<CFG>& cfg = manager->getCFG(entryFunc);
  cfg->dump(LangOpts, true);
  //test
  //for (auto I = cfg->begin(), E = cfg->end() ; I != E ; ++I) {
    // Skip the entry block, because we already printed it.
    //if (&(**I) == &cfg->getEntry() || &(**I) == &cfg->getExit())
      //continue;

    //std::cout << (*I)->getBlockID() << std::endl;
  //}

  //getKind
  for (auto it_1 = cfg->begin(), end_1 = cfg->end(); it_1 != end_1; ++it_1) {
    //if (&(**it_1) == &cfg->getEntry() || &(**it_1) == &cfg->getExit())
      //continue;
    //it_1----CFGBlocks
    unsigned id = (*it_1)->getBlockID();
    std::cout << "Block " << id << std::endl;
    //std::cout << (*((*it_1)->end())).getKind() << std::endl;
    for (auto it_2 = (*it_1)->begin(), end_2 = (*it_1)->end(); it_2 != end_2; ++it_2) {
      //std::cout << "into it_2." << std::endl;
      unsigned kind = (*it_2).getKind();
      switch (kind) {
        case 0: std::cout << "Initializer" << std::endl; break;
        case 1: std::cout << "ScopeBegin" << std::endl; break;
        case 2: std::cout << "ScopeEnd" << std::endl; break;
        case 3: std::cout << "NewAllocator" << std::endl; break;
        case 4: std::cout << "LifetimeEnds" << std::endl; break;
        case 5: std::cout << "LoopExit" << std::endl; break;
        case 6: std::cout << "Statement" << std::endl; break;
        case 7: std::cout << "Constructor" << std::endl; break;
        case 8: std::cout << "CXXRecordTypedCall" << std::endl; break;
        case 9: std::cout << "STMT_BEGIN" << std::endl; break;
        case 10: std::cout << "STMT_END" << std::endl; break;
        case 11: std::cout << "AutomaticObjectDtor" << std::endl; break;
        case 12: std::cout << "DeleteDtor" << std::endl; break;
        case 13: std::cout << "BaseDtor" << std::endl; break;
        case 14: std::cout << "MemberDtor" << std::endl; break;
        case 15: std::cout << "TemporaryDtor" << std::endl; break;
        case 16: std::cout << "DTOR_BEGIN" << std::endl; break;
        case 17: std::cout << "DTOR_END" << std::endl; break;
      }
    }
    //Terminator
    unsigned t_kind = ((*it_1)->getTerminator()).getKind();
    switch (t_kind) {
      case 0: std::cout << "StmtBranch" << std::endl; break;
      case 1: std::cout << "TemporaryDtorsBranch" << std::endl; break;
      case 2: std::cout << "VirtualBaseBranch" << std::endl; break;
    }
    //Label
    if ((*it_1)->getLabel() != nullptr)
      std::cout << ((*it_1)->getLabel())->getStmtClassName() << std::endl;
  }
}

void MyChecker::readConfig() {
  std::unordered_map<std::string, std::string> ptrConfig =
      configure->getOptionBlock("TemplateChecker");
  request_fun = stoi(ptrConfig.find("request_fun")->second);
  maxPathInFun = 10;
}

void MyChecker::getEntryFunc() {
  std::vector<ASTFunction *> topLevelFuncs = call_graph->getTopLevelFunctions();
  for (auto fun : topLevelFuncs) {
    const FunctionDecl *funDecl = manager->getFunctionDecl(fun);
    if (funDecl->getQualifiedNameAsString() == "main") {
      entryFunc = fun;
      return;
    }
  }
  entryFunc = nullptr;
  return;
}

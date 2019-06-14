
#include "stdafx.h"
#include "..\..\FuuraSemantics.h"
#include "..\..\Calculatables.h"
#pragma warning(disable:4251) // (...) должен иметь dll-интерфейс для использования клиентами.


// Generated from Fuura.g4 by ANTLR 4.7.2


#include "FuuraListener.h"

#include "FuuraParser.h"


using namespace antlrcpp;
using namespace fuura::antlr::generated;
using namespace antlr4;

FuuraParser::FuuraParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

FuuraParser::~FuuraParser() {
  delete _interpreter;
}

std::string FuuraParser::getGrammarFileName() const {
  return "Fuura.g4";
}

const std::vector<std::string>& FuuraParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& FuuraParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- RootContext ------------------------------------------------------------------

FuuraParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FuuraParser::Opt_WSContext *> FuuraParser::RootContext::opt_WS() {
  return getRuleContexts<FuuraParser::Opt_WSContext>();
}

FuuraParser::Opt_WSContext* FuuraParser::RootContext::opt_WS(size_t i) {
  return getRuleContext<FuuraParser::Opt_WSContext>(i);
}

tree::TerminalNode* FuuraParser::RootContext::EOF() {
  return getToken(FuuraParser::EOF, 0);
}

FuuraParser::Full_exprContext* FuuraParser::RootContext::full_expr() {
  return getRuleContext<FuuraParser::Full_exprContext>(0);
}


size_t FuuraParser::RootContext::getRuleIndex() const {
  return FuuraParser::RuleRoot;
}

void FuuraParser::RootContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoot(this);
}

void FuuraParser::RootContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoot(this);
}

FuuraParser::RootContext* FuuraParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, FuuraParser::RuleRoot);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    opt_WS();
    setState(35);
    dynamic_cast<RootContext *>(_localctx)->stmt = full_expr();
    setState(36);
    opt_WS();
    setState(37);
    match(FuuraParser::EOF);
     dynamic_cast<RootContext *>(_localctx)->node =  std::move(dynamic_cast<RootContext *>(_localctx)->stmt->node); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_exprContext ------------------------------------------------------------------

FuuraParser::If_exprContext::If_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> FuuraParser::If_exprContext::IF() {
  return getTokens(FuuraParser::IF);
}

tree::TerminalNode* FuuraParser::If_exprContext::IF(size_t i) {
  return getToken(FuuraParser::IF, i);
}

std::vector<FuuraParser::Opt_WSContext *> FuuraParser::If_exprContext::opt_WS() {
  return getRuleContexts<FuuraParser::Opt_WSContext>();
}

FuuraParser::Opt_WSContext* FuuraParser::If_exprContext::opt_WS(size_t i) {
  return getRuleContext<FuuraParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> FuuraParser::If_exprContext::BR_OP() {
  return getTokens(FuuraParser::BR_OP);
}

tree::TerminalNode* FuuraParser::If_exprContext::BR_OP(size_t i) {
  return getToken(FuuraParser::BR_OP, i);
}

std::vector<tree::TerminalNode *> FuuraParser::If_exprContext::BR_CL() {
  return getTokens(FuuraParser::BR_CL);
}

tree::TerminalNode* FuuraParser::If_exprContext::BR_CL(size_t i) {
  return getToken(FuuraParser::BR_CL, i);
}

std::vector<tree::TerminalNode *> FuuraParser::If_exprContext::ELSE() {
  return getTokens(FuuraParser::ELSE);
}

tree::TerminalNode* FuuraParser::If_exprContext::ELSE(size_t i) {
  return getToken(FuuraParser::ELSE, i);
}

tree::TerminalNode* FuuraParser::If_exprContext::SEMIC() {
  return getToken(FuuraParser::SEMIC, 0);
}

std::vector<FuuraParser::Full_exprContext *> FuuraParser::If_exprContext::full_expr() {
  return getRuleContexts<FuuraParser::Full_exprContext>();
}

FuuraParser::Full_exprContext* FuuraParser::If_exprContext::full_expr(size_t i) {
  return getRuleContext<FuuraParser::Full_exprContext>(i);
}


size_t FuuraParser::If_exprContext::getRuleIndex() const {
  return FuuraParser::RuleIf_expr;
}

void FuuraParser::If_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIf_expr(this);
}

void FuuraParser::If_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIf_expr(this);
}

FuuraParser::If_exprContext* FuuraParser::if_expr() {
  If_exprContext *_localctx = _tracker.createInstance<If_exprContext>(_ctx, getState());
  enterRule(_localctx, 2, FuuraParser::RuleIf_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(40);
    match(FuuraParser::IF);
    setState(41);
    opt_WS();
    setState(42);
    match(FuuraParser::BR_OP);
    setState(43);
    opt_WS();
    setState(44);
    dynamic_cast<If_exprContext *>(_localctx)->condition = full_expr();
    setState(45);
    opt_WS();
    setState(46);
    match(FuuraParser::BR_CL);
    setState(47);
    opt_WS();
    setState(48);
    dynamic_cast<If_exprContext *>(_localctx)->expression = full_expr();

                            dynamic_cast<If_exprContext *>(_localctx)->node =  std::make_unique<fuura::language::OperatorIf>(std::move(dynamic_cast<If_exprContext *>(_localctx)->condition->node), std::move(dynamic_cast<If_exprContext *>(_localctx)->expression->node), getCurrentToken());
                        
    setState(66);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(50);
        opt_WS();
        setState(51);
        match(FuuraParser::ELSE);
        setState(52);
        opt_WS();
        setState(53);
        match(FuuraParser::IF);
        setState(54);
        opt_WS();
        setState(55);
        match(FuuraParser::BR_OP);
        setState(56);
        opt_WS();
        setState(57);
        dynamic_cast<If_exprContext *>(_localctx)->condition = full_expr();
        setState(58);
        opt_WS();
        setState(59);
        match(FuuraParser::BR_CL);
        setState(60);
        opt_WS();
        setState(61);
        dynamic_cast<If_exprContext *>(_localctx)->expression = full_expr();

                                _localctx->node->ElseIf(std::move(dynamic_cast<If_exprContext *>(_localctx)->condition->node), std::move(dynamic_cast<If_exprContext *>(_localctx)->expression->node), getCurrentToken());
                             
      }
      setState(68);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
    setState(69);
    opt_WS();
    setState(70);
    match(FuuraParser::ELSE);
    setState(71);
    opt_WS();
    setState(72);
    dynamic_cast<If_exprContext *>(_localctx)->expression = full_expr();
    setState(73);
    opt_WS();
    setState(74);
    match(FuuraParser::SEMIC);

                            _localctx->node->Else(std::move(dynamic_cast<If_exprContext *>(_localctx)->expression->node), getCurrentToken(), m_semantics->GetImplicitTypeCastFactory());
                        
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Full_exprContext ------------------------------------------------------------------

FuuraParser::Full_exprContext::Full_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FuuraParser::Not_exprContext *> FuuraParser::Full_exprContext::not_expr() {
  return getRuleContexts<FuuraParser::Not_exprContext>();
}

FuuraParser::Not_exprContext* FuuraParser::Full_exprContext::not_expr(size_t i) {
  return getRuleContext<FuuraParser::Not_exprContext>(i);
}

std::vector<FuuraParser::Opt_WSContext *> FuuraParser::Full_exprContext::opt_WS() {
  return getRuleContexts<FuuraParser::Opt_WSContext>();
}

FuuraParser::Opt_WSContext* FuuraParser::Full_exprContext::opt_WS(size_t i) {
  return getRuleContext<FuuraParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> FuuraParser::Full_exprContext::OR() {
  return getTokens(FuuraParser::OR);
}

tree::TerminalNode* FuuraParser::Full_exprContext::OR(size_t i) {
  return getToken(FuuraParser::OR, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Full_exprContext::AND() {
  return getTokens(FuuraParser::AND);
}

tree::TerminalNode* FuuraParser::Full_exprContext::AND(size_t i) {
  return getToken(FuuraParser::AND, i);
}


size_t FuuraParser::Full_exprContext::getRuleIndex() const {
  return FuuraParser::RuleFull_expr;
}

void FuuraParser::Full_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFull_expr(this);
}

void FuuraParser::Full_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFull_expr(this);
}

FuuraParser::Full_exprContext* FuuraParser::full_expr() {
  Full_exprContext *_localctx = _tracker.createInstance<Full_exprContext>(_ctx, getState());
  enterRule(_localctx, 4, FuuraParser::RuleFull_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(77);
    dynamic_cast<Full_exprContext *>(_localctx)->not_exprContext = not_expr();

                        dynamic_cast<Full_exprContext *>(_localctx)->node =  std::move(dynamic_cast<Full_exprContext *>(_localctx)->not_exprContext->node);
                    
    setState(95);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(91);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          setState(79);
          opt_WS();
          setState(80);
          match(FuuraParser::OR);
          setState(81);
          opt_WS();
          setState(82);
          dynamic_cast<Full_exprContext *>(_localctx)->next = dynamic_cast<Full_exprContext *>(_localctx)->not_exprContext = not_expr();

                                  dynamic_cast<Full_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Or, std::move(_localctx->node), std::move(dynamic_cast<Full_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 2: {
          setState(85);
          opt_WS();
          setState(86);
          match(FuuraParser::AND);
          setState(87);
          opt_WS();
          setState(88);
          dynamic_cast<Full_exprContext *>(_localctx)->next = dynamic_cast<Full_exprContext *>(_localctx)->not_exprContext = not_expr();

                                  dynamic_cast<Full_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::And, std::move(_localctx->node), std::move(dynamic_cast<Full_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        } 
      }
      setState(97);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Not_exprContext ------------------------------------------------------------------

FuuraParser::Not_exprContext::Not_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FuuraParser::Cmp_exprContext* FuuraParser::Not_exprContext::cmp_expr() {
  return getRuleContext<FuuraParser::Cmp_exprContext>(0);
}

tree::TerminalNode* FuuraParser::Not_exprContext::NOT() {
  return getToken(FuuraParser::NOT, 0);
}

FuuraParser::Opt_WSContext* FuuraParser::Not_exprContext::opt_WS() {
  return getRuleContext<FuuraParser::Opt_WSContext>(0);
}


size_t FuuraParser::Not_exprContext::getRuleIndex() const {
  return FuuraParser::RuleNot_expr;
}

void FuuraParser::Not_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNot_expr(this);
}

void FuuraParser::Not_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNot_expr(this);
}

FuuraParser::Not_exprContext* FuuraParser::not_expr() {
  Not_exprContext *_localctx = _tracker.createInstance<Not_exprContext>(_ctx, getState());
  enterRule(_localctx, 6, FuuraParser::RuleNot_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(106);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case FuuraParser::IF:
      case FuuraParser::TRUE:
      case FuuraParser::FALSE:
      case FuuraParser::ID:
      case FuuraParser::POSITIVE_INT:
      case FuuraParser::POSITIVE_FLOAT:
      case FuuraParser::MINUS:
      case FuuraParser::BR_OP: {
        enterOuterAlt(_localctx, 1);
        setState(98);
        dynamic_cast<Not_exprContext *>(_localctx)->cmp_exprContext = cmp_expr();

                            dynamic_cast<Not_exprContext *>(_localctx)->node =  std::move(dynamic_cast<Not_exprContext *>(_localctx)->cmp_exprContext->node);
                        
        break;
      }

      case FuuraParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(101);
        match(FuuraParser::NOT);
        setState(102);
        opt_WS();
        setState(103);
        dynamic_cast<Not_exprContext *>(_localctx)->cmp_exprContext = cmp_expr();

                            dynamic_cast<Not_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateUnaryOperation(fuura::language::UnaryOperation::Not, std::move(dynamic_cast<Not_exprContext *>(_localctx)->cmp_exprContext->node), getCurrentToken());
                        
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Cmp_exprContext ------------------------------------------------------------------

FuuraParser::Cmp_exprContext::Cmp_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FuuraParser::Add_exprContext *> FuuraParser::Cmp_exprContext::add_expr() {
  return getRuleContexts<FuuraParser::Add_exprContext>();
}

FuuraParser::Add_exprContext* FuuraParser::Cmp_exprContext::add_expr(size_t i) {
  return getRuleContext<FuuraParser::Add_exprContext>(i);
}

std::vector<FuuraParser::Opt_WSContext *> FuuraParser::Cmp_exprContext::opt_WS() {
  return getRuleContexts<FuuraParser::Opt_WSContext>();
}

FuuraParser::Opt_WSContext* FuuraParser::Cmp_exprContext::opt_WS(size_t i) {
  return getRuleContext<FuuraParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> FuuraParser::Cmp_exprContext::EQUAL() {
  return getTokens(FuuraParser::EQUAL);
}

tree::TerminalNode* FuuraParser::Cmp_exprContext::EQUAL(size_t i) {
  return getToken(FuuraParser::EQUAL, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Cmp_exprContext::NOT_EQUAL() {
  return getTokens(FuuraParser::NOT_EQUAL);
}

tree::TerminalNode* FuuraParser::Cmp_exprContext::NOT_EQUAL(size_t i) {
  return getToken(FuuraParser::NOT_EQUAL, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Cmp_exprContext::LESS() {
  return getTokens(FuuraParser::LESS);
}

tree::TerminalNode* FuuraParser::Cmp_exprContext::LESS(size_t i) {
  return getToken(FuuraParser::LESS, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Cmp_exprContext::GREATER() {
  return getTokens(FuuraParser::GREATER);
}

tree::TerminalNode* FuuraParser::Cmp_exprContext::GREATER(size_t i) {
  return getToken(FuuraParser::GREATER, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Cmp_exprContext::LESS_EQ() {
  return getTokens(FuuraParser::LESS_EQ);
}

tree::TerminalNode* FuuraParser::Cmp_exprContext::LESS_EQ(size_t i) {
  return getToken(FuuraParser::LESS_EQ, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Cmp_exprContext::GREATER_EQ() {
  return getTokens(FuuraParser::GREATER_EQ);
}

tree::TerminalNode* FuuraParser::Cmp_exprContext::GREATER_EQ(size_t i) {
  return getToken(FuuraParser::GREATER_EQ, i);
}


size_t FuuraParser::Cmp_exprContext::getRuleIndex() const {
  return FuuraParser::RuleCmp_expr;
}

void FuuraParser::Cmp_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCmp_expr(this);
}

void FuuraParser::Cmp_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCmp_expr(this);
}

FuuraParser::Cmp_exprContext* FuuraParser::cmp_expr() {
  Cmp_exprContext *_localctx = _tracker.createInstance<Cmp_exprContext>(_ctx, getState());
  enterRule(_localctx, 8, FuuraParser::RuleCmp_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(108);
    dynamic_cast<Cmp_exprContext *>(_localctx)->add_exprContext = add_expr();

                        dynamic_cast<Cmp_exprContext *>(_localctx)->node =  std::move(dynamic_cast<Cmp_exprContext *>(_localctx)->add_exprContext->node);
                    
    setState(150);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(146);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          setState(110);
          opt_WS();
          setState(111);
          match(FuuraParser::EQUAL);
          setState(112);
          opt_WS();
          setState(113);
          dynamic_cast<Cmp_exprContext *>(_localctx)->next = dynamic_cast<Cmp_exprContext *>(_localctx)->add_exprContext = add_expr();

                                  dynamic_cast<Cmp_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Equal, std::move(_localctx->node), std::move(dynamic_cast<Cmp_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 2: {
          setState(116);
          opt_WS();
          setState(117);
          match(FuuraParser::NOT_EQUAL);
          setState(118);
          opt_WS();
          setState(119);
          dynamic_cast<Cmp_exprContext *>(_localctx)->next = dynamic_cast<Cmp_exprContext *>(_localctx)->add_exprContext = add_expr();

                                  dynamic_cast<Cmp_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::NotEqual, std::move(_localctx->node), std::move(dynamic_cast<Cmp_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 3: {
          setState(122);
          opt_WS();
          setState(123);
          match(FuuraParser::LESS);
          setState(124);
          opt_WS();
          setState(125);
          dynamic_cast<Cmp_exprContext *>(_localctx)->next = dynamic_cast<Cmp_exprContext *>(_localctx)->add_exprContext = add_expr();

                                  dynamic_cast<Cmp_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Less, std::move(_localctx->node), std::move(dynamic_cast<Cmp_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 4: {
          setState(128);
          opt_WS();
          setState(129);
          match(FuuraParser::GREATER);
          setState(130);
          opt_WS();
          setState(131);
          dynamic_cast<Cmp_exprContext *>(_localctx)->next = dynamic_cast<Cmp_exprContext *>(_localctx)->add_exprContext = add_expr();

                                  dynamic_cast<Cmp_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Greater, std::move(_localctx->node), std::move(dynamic_cast<Cmp_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 5: {
          setState(134);
          opt_WS();
          setState(135);
          match(FuuraParser::LESS_EQ);
          setState(136);
          opt_WS();
          setState(137);
          dynamic_cast<Cmp_exprContext *>(_localctx)->next = dynamic_cast<Cmp_exprContext *>(_localctx)->add_exprContext = add_expr();

                                  dynamic_cast<Cmp_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::LessOrEqual, std::move(_localctx->node), std::move(dynamic_cast<Cmp_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 6: {
          setState(140);
          opt_WS();
          setState(141);
          match(FuuraParser::GREATER_EQ);
          setState(142);
          opt_WS();
          setState(143);
          dynamic_cast<Cmp_exprContext *>(_localctx)->next = dynamic_cast<Cmp_exprContext *>(_localctx)->add_exprContext = add_expr();

                                  dynamic_cast<Cmp_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::GreaterOrEqual, std::move(_localctx->node), std::move(dynamic_cast<Cmp_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        } 
      }
      setState(152);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Add_exprContext ------------------------------------------------------------------

FuuraParser::Add_exprContext::Add_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FuuraParser::Mul_exprContext *> FuuraParser::Add_exprContext::mul_expr() {
  return getRuleContexts<FuuraParser::Mul_exprContext>();
}

FuuraParser::Mul_exprContext* FuuraParser::Add_exprContext::mul_expr(size_t i) {
  return getRuleContext<FuuraParser::Mul_exprContext>(i);
}

std::vector<FuuraParser::Opt_WSContext *> FuuraParser::Add_exprContext::opt_WS() {
  return getRuleContexts<FuuraParser::Opt_WSContext>();
}

FuuraParser::Opt_WSContext* FuuraParser::Add_exprContext::opt_WS(size_t i) {
  return getRuleContext<FuuraParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> FuuraParser::Add_exprContext::PLUS() {
  return getTokens(FuuraParser::PLUS);
}

tree::TerminalNode* FuuraParser::Add_exprContext::PLUS(size_t i) {
  return getToken(FuuraParser::PLUS, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Add_exprContext::MINUS() {
  return getTokens(FuuraParser::MINUS);
}

tree::TerminalNode* FuuraParser::Add_exprContext::MINUS(size_t i) {
  return getToken(FuuraParser::MINUS, i);
}


size_t FuuraParser::Add_exprContext::getRuleIndex() const {
  return FuuraParser::RuleAdd_expr;
}

void FuuraParser::Add_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdd_expr(this);
}

void FuuraParser::Add_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdd_expr(this);
}

FuuraParser::Add_exprContext* FuuraParser::add_expr() {
  Add_exprContext *_localctx = _tracker.createInstance<Add_exprContext>(_ctx, getState());
  enterRule(_localctx, 10, FuuraParser::RuleAdd_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(153);
    dynamic_cast<Add_exprContext *>(_localctx)->mul_exprContext = mul_expr();

                        dynamic_cast<Add_exprContext *>(_localctx)->node =  std::move(dynamic_cast<Add_exprContext *>(_localctx)->mul_exprContext->node);
                    
    setState(171);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(167);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
          setState(155);
          opt_WS();
          setState(156);
          match(FuuraParser::PLUS);
          setState(157);
          opt_WS();
          setState(158);
          dynamic_cast<Add_exprContext *>(_localctx)->next = dynamic_cast<Add_exprContext *>(_localctx)->mul_exprContext = mul_expr();

                                  dynamic_cast<Add_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Add, std::move(_localctx->node), std::move(dynamic_cast<Add_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 2: {
          setState(161);
          opt_WS();
          setState(162);
          match(FuuraParser::MINUS);
          setState(163);
          opt_WS();
          setState(164);
          dynamic_cast<Add_exprContext *>(_localctx)->next = dynamic_cast<Add_exprContext *>(_localctx)->mul_exprContext = mul_expr();

                                  dynamic_cast<Add_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Subtract, std::move(_localctx->node), std::move(dynamic_cast<Add_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        } 
      }
      setState(173);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Mul_exprContext ------------------------------------------------------------------

FuuraParser::Mul_exprContext::Mul_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FuuraParser::Invert_exprContext *> FuuraParser::Mul_exprContext::invert_expr() {
  return getRuleContexts<FuuraParser::Invert_exprContext>();
}

FuuraParser::Invert_exprContext* FuuraParser::Mul_exprContext::invert_expr(size_t i) {
  return getRuleContext<FuuraParser::Invert_exprContext>(i);
}

std::vector<FuuraParser::Opt_WSContext *> FuuraParser::Mul_exprContext::opt_WS() {
  return getRuleContexts<FuuraParser::Opt_WSContext>();
}

FuuraParser::Opt_WSContext* FuuraParser::Mul_exprContext::opt_WS(size_t i) {
  return getRuleContext<FuuraParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> FuuraParser::Mul_exprContext::STAR() {
  return getTokens(FuuraParser::STAR);
}

tree::TerminalNode* FuuraParser::Mul_exprContext::STAR(size_t i) {
  return getToken(FuuraParser::STAR, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Mul_exprContext::SLASH() {
  return getTokens(FuuraParser::SLASH);
}

tree::TerminalNode* FuuraParser::Mul_exprContext::SLASH(size_t i) {
  return getToken(FuuraParser::SLASH, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Mul_exprContext::DIV() {
  return getTokens(FuuraParser::DIV);
}

tree::TerminalNode* FuuraParser::Mul_exprContext::DIV(size_t i) {
  return getToken(FuuraParser::DIV, i);
}

std::vector<tree::TerminalNode *> FuuraParser::Mul_exprContext::PERCENT() {
  return getTokens(FuuraParser::PERCENT);
}

tree::TerminalNode* FuuraParser::Mul_exprContext::PERCENT(size_t i) {
  return getToken(FuuraParser::PERCENT, i);
}


size_t FuuraParser::Mul_exprContext::getRuleIndex() const {
  return FuuraParser::RuleMul_expr;
}

void FuuraParser::Mul_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMul_expr(this);
}

void FuuraParser::Mul_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMul_expr(this);
}

FuuraParser::Mul_exprContext* FuuraParser::mul_expr() {
  Mul_exprContext *_localctx = _tracker.createInstance<Mul_exprContext>(_ctx, getState());
  enterRule(_localctx, 12, FuuraParser::RuleMul_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(174);
    dynamic_cast<Mul_exprContext *>(_localctx)->invert_exprContext = invert_expr();

                        dynamic_cast<Mul_exprContext *>(_localctx)->node =  std::move(dynamic_cast<Mul_exprContext *>(_localctx)->invert_exprContext->node);
                    
    setState(204);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(200);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          setState(176);
          opt_WS();
          setState(177);
          match(FuuraParser::STAR);
          setState(178);
          opt_WS();
          setState(179);
          dynamic_cast<Mul_exprContext *>(_localctx)->next = dynamic_cast<Mul_exprContext *>(_localctx)->invert_exprContext = invert_expr();

                                  // Попутно проверяет типы, навешивает преобразования на аргументы
                                  // и генерит исключения если типы несовместимы.
                                  dynamic_cast<Mul_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Multiply, std::move(_localctx->node), std::move(dynamic_cast<Mul_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 2: {
          setState(182);
          opt_WS();
          setState(183);
          match(FuuraParser::SLASH);
          setState(184);
          opt_WS();
          setState(185);
          dynamic_cast<Mul_exprContext *>(_localctx)->next = dynamic_cast<Mul_exprContext *>(_localctx)->invert_exprContext = invert_expr();

                                  // Аналогично.
                                  dynamic_cast<Mul_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::RealDivide, std::move(_localctx->node), std::move(dynamic_cast<Mul_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 3: {
          setState(188);
          opt_WS();
          setState(189);
          match(FuuraParser::DIV);
          setState(190);
          opt_WS();
          setState(191);
          dynamic_cast<Mul_exprContext *>(_localctx)->next = dynamic_cast<Mul_exprContext *>(_localctx)->invert_exprContext = invert_expr();

                                  dynamic_cast<Mul_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::IntegerDivide, std::move(_localctx->node), std::move(dynamic_cast<Mul_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        case 4: {
          setState(194);
          opt_WS();
          setState(195);
          match(FuuraParser::PERCENT);
          setState(196);
          opt_WS();
          setState(197);
          dynamic_cast<Mul_exprContext *>(_localctx)->next = dynamic_cast<Mul_exprContext *>(_localctx)->invert_exprContext = invert_expr();

                                  dynamic_cast<Mul_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::GetDivRemainder, std::move(_localctx->node), std::move(dynamic_cast<Mul_exprContext *>(_localctx)->next->node), getCurrentToken());
                              
          break;
        }

        } 
      }
      setState(206);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Invert_exprContext ------------------------------------------------------------------

FuuraParser::Invert_exprContext::Invert_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FuuraParser::Pow_exprContext* FuuraParser::Invert_exprContext::pow_expr() {
  return getRuleContext<FuuraParser::Pow_exprContext>(0);
}

tree::TerminalNode* FuuraParser::Invert_exprContext::MINUS() {
  return getToken(FuuraParser::MINUS, 0);
}

FuuraParser::Opt_WSContext* FuuraParser::Invert_exprContext::opt_WS() {
  return getRuleContext<FuuraParser::Opt_WSContext>(0);
}


size_t FuuraParser::Invert_exprContext::getRuleIndex() const {
  return FuuraParser::RuleInvert_expr;
}

void FuuraParser::Invert_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInvert_expr(this);
}

void FuuraParser::Invert_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInvert_expr(this);
}

FuuraParser::Invert_exprContext* FuuraParser::invert_expr() {
  Invert_exprContext *_localctx = _tracker.createInstance<Invert_exprContext>(_ctx, getState());
  enterRule(_localctx, 14, FuuraParser::RuleInvert_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(215);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(207);
      dynamic_cast<Invert_exprContext *>(_localctx)->pow_exprContext = pow_expr();

                          dynamic_cast<Invert_exprContext *>(_localctx)->node =  std::move(dynamic_cast<Invert_exprContext *>(_localctx)->pow_exprContext->node);
                      
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(210);
      match(FuuraParser::MINUS);
      setState(211);
      opt_WS();
      setState(212);
      dynamic_cast<Invert_exprContext *>(_localctx)->pow_exprContext = pow_expr();

                          dynamic_cast<Invert_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateUnaryOperation(fuura::language::UnaryOperation::Not, std::move(dynamic_cast<Invert_exprContext *>(_localctx)->pow_exprContext->node), getCurrentToken());
                      
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pow_exprContext ------------------------------------------------------------------

FuuraParser::Pow_exprContext::Pow_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FuuraParser::AtomContext *> FuuraParser::Pow_exprContext::atom() {
  return getRuleContexts<FuuraParser::AtomContext>();
}

FuuraParser::AtomContext* FuuraParser::Pow_exprContext::atom(size_t i) {
  return getRuleContext<FuuraParser::AtomContext>(i);
}

std::vector<FuuraParser::Opt_WSContext *> FuuraParser::Pow_exprContext::opt_WS() {
  return getRuleContexts<FuuraParser::Opt_WSContext>();
}

FuuraParser::Opt_WSContext* FuuraParser::Pow_exprContext::opt_WS(size_t i) {
  return getRuleContext<FuuraParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> FuuraParser::Pow_exprContext::CARET() {
  return getTokens(FuuraParser::CARET);
}

tree::TerminalNode* FuuraParser::Pow_exprContext::CARET(size_t i) {
  return getToken(FuuraParser::CARET, i);
}


size_t FuuraParser::Pow_exprContext::getRuleIndex() const {
  return FuuraParser::RulePow_expr;
}

void FuuraParser::Pow_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPow_expr(this);
}

void FuuraParser::Pow_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPow_expr(this);
}

FuuraParser::Pow_exprContext* FuuraParser::pow_expr() {
  Pow_exprContext *_localctx = _tracker.createInstance<Pow_exprContext>(_ctx, getState());
  enterRule(_localctx, 16, FuuraParser::RulePow_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(217);
    dynamic_cast<Pow_exprContext *>(_localctx)->atomContext = atom();

                        dynamic_cast<Pow_exprContext *>(_localctx)->node =  std::move(dynamic_cast<Pow_exprContext *>(_localctx)->atomContext->node);
                    
    setState(227);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(219);
        opt_WS();
        setState(220);
        match(FuuraParser::CARET);
        setState(221);
        opt_WS();
        setState(222);
        dynamic_cast<Pow_exprContext *>(_localctx)->next = dynamic_cast<Pow_exprContext *>(_localctx)->atomContext = atom();

                            dynamic_cast<Pow_exprContext *>(_localctx)->node =  m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::RaiseToPower, std::move(_localctx->node), std::move(dynamic_cast<Pow_exprContext *>(_localctx)->next->node), getCurrentToken());
                         
      }
      setState(229);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

FuuraParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FuuraParser::ArgumentContext* FuuraParser::AtomContext::argument() {
  return getRuleContext<FuuraParser::ArgumentContext>(0);
}

FuuraParser::Const_anyContext* FuuraParser::AtomContext::const_any() {
  return getRuleContext<FuuraParser::Const_anyContext>(0);
}

FuuraParser::If_exprContext* FuuraParser::AtomContext::if_expr() {
  return getRuleContext<FuuraParser::If_exprContext>(0);
}

tree::TerminalNode* FuuraParser::AtomContext::BR_OP() {
  return getToken(FuuraParser::BR_OP, 0);
}

std::vector<FuuraParser::Opt_WSContext *> FuuraParser::AtomContext::opt_WS() {
  return getRuleContexts<FuuraParser::Opt_WSContext>();
}

FuuraParser::Opt_WSContext* FuuraParser::AtomContext::opt_WS(size_t i) {
  return getRuleContext<FuuraParser::Opt_WSContext>(i);
}

FuuraParser::Full_exprContext* FuuraParser::AtomContext::full_expr() {
  return getRuleContext<FuuraParser::Full_exprContext>(0);
}

tree::TerminalNode* FuuraParser::AtomContext::BR_CL() {
  return getToken(FuuraParser::BR_CL, 0);
}


size_t FuuraParser::AtomContext::getRuleIndex() const {
  return FuuraParser::RuleAtom;
}

void FuuraParser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}

void FuuraParser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}

FuuraParser::AtomContext* FuuraParser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 18, FuuraParser::RuleAtom);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(246);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case FuuraParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(230);
        dynamic_cast<AtomContext *>(_localctx)->argumentContext = argument();
         dynamic_cast<AtomContext *>(_localctx)->node =  std::move(dynamic_cast<AtomContext *>(_localctx)->argumentContext->node);  
        break;
      }

      case FuuraParser::TRUE:
      case FuuraParser::FALSE:
      case FuuraParser::POSITIVE_INT:
      case FuuraParser::POSITIVE_FLOAT:
      case FuuraParser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(233);
        dynamic_cast<AtomContext *>(_localctx)->const_anyContext = const_any();
         dynamic_cast<AtomContext *>(_localctx)->node =  std::move(dynamic_cast<AtomContext *>(_localctx)->const_anyContext->node); 
        break;
      }

      case FuuraParser::IF: {
        enterOuterAlt(_localctx, 3);
        setState(236);
        dynamic_cast<AtomContext *>(_localctx)->if_exprContext = if_expr();
         dynamic_cast<AtomContext *>(_localctx)->node =  std::move(dynamic_cast<AtomContext *>(_localctx)->if_exprContext->node); 
        break;
      }

      case FuuraParser::BR_OP: {
        enterOuterAlt(_localctx, 4);
        setState(239);
        match(FuuraParser::BR_OP);
        setState(240);
        opt_WS();
        setState(241);
        dynamic_cast<AtomContext *>(_localctx)->full_exprContext = full_expr();
        setState(242);
        opt_WS();
        setState(243);
        match(FuuraParser::BR_CL);
         dynamic_cast<AtomContext *>(_localctx)->node =  std::move(dynamic_cast<AtomContext *>(_localctx)->full_exprContext->node); 
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentContext ------------------------------------------------------------------

FuuraParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FuuraParser::ArgumentContext::ID() {
  return getToken(FuuraParser::ID, 0);
}


size_t FuuraParser::ArgumentContext::getRuleIndex() const {
  return FuuraParser::RuleArgument;
}

void FuuraParser::ArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgument(this);
}

void FuuraParser::ArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgument(this);
}

FuuraParser::ArgumentContext* FuuraParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 20, FuuraParser::RuleArgument);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(248);
    match(FuuraParser::ID);

                    dynamic_cast<ArgumentContext *>(_localctx)->node =  std::make_unique<fuura::language::Argument>(_input->getText(_localctx->start, _input->LT(-1)), m_semantics->GetArgumentSet(), getCurrentToken());
                
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_anyContext ------------------------------------------------------------------

FuuraParser::Const_anyContext::Const_anyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FuuraParser::Const_integerContext* FuuraParser::Const_anyContext::const_integer() {
  return getRuleContext<FuuraParser::Const_integerContext>(0);
}

FuuraParser::Const_doubleContext* FuuraParser::Const_anyContext::const_double() {
  return getRuleContext<FuuraParser::Const_doubleContext>(0);
}

FuuraParser::Const_boolContext* FuuraParser::Const_anyContext::const_bool() {
  return getRuleContext<FuuraParser::Const_boolContext>(0);
}


size_t FuuraParser::Const_anyContext::getRuleIndex() const {
  return FuuraParser::RuleConst_any;
}

void FuuraParser::Const_anyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_any(this);
}

void FuuraParser::Const_anyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_any(this);
}

FuuraParser::Const_anyContext* FuuraParser::const_any() {
  Const_anyContext *_localctx = _tracker.createInstance<Const_anyContext>(_ctx, getState());
  enterRule(_localctx, 22, FuuraParser::RuleConst_any);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(260);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(251);
      dynamic_cast<Const_anyContext *>(_localctx)->const_integerContext = const_integer();

                      dynamic_cast<Const_anyContext *>(_localctx)->node =  std::move(dynamic_cast<Const_anyContext *>(_localctx)->const_integerContext->node);
                  
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(254);
      dynamic_cast<Const_anyContext *>(_localctx)->const_doubleContext = const_double();

                      dynamic_cast<Const_anyContext *>(_localctx)->node =  std::move(dynamic_cast<Const_anyContext *>(_localctx)->const_doubleContext->node);
                  
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(257);
      dynamic_cast<Const_anyContext *>(_localctx)->const_boolContext = const_bool();

                      dynamic_cast<Const_anyContext *>(_localctx)->node =  std::move(dynamic_cast<Const_anyContext *>(_localctx)->const_boolContext->node);
                  
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_integerContext ------------------------------------------------------------------

FuuraParser::Const_integerContext::Const_integerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FuuraParser::Const_integerContext::POSITIVE_INT() {
  return getToken(FuuraParser::POSITIVE_INT, 0);
}

tree::TerminalNode* FuuraParser::Const_integerContext::MINUS() {
  return getToken(FuuraParser::MINUS, 0);
}

FuuraParser::Opt_WSContext* FuuraParser::Const_integerContext::opt_WS() {
  return getRuleContext<FuuraParser::Opt_WSContext>(0);
}


size_t FuuraParser::Const_integerContext::getRuleIndex() const {
  return FuuraParser::RuleConst_integer;
}

void FuuraParser::Const_integerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_integer(this);
}

void FuuraParser::Const_integerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_integer(this);
}

FuuraParser::Const_integerContext* FuuraParser::const_integer() {
  Const_integerContext *_localctx = _tracker.createInstance<Const_integerContext>(_ctx, getState());
  enterRule(_localctx, 24, FuuraParser::RuleConst_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(264);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == FuuraParser::MINUS) {
      setState(262);
      match(FuuraParser::MINUS);
      setState(263);
      opt_WS();
    }
    setState(266);
    match(FuuraParser::POSITIVE_INT);

                    dynamic_cast<Const_integerContext *>(_localctx)->node =  std::make_unique<fuura::language::Constant<int>>(_input->getText(_localctx->start, _input->LT(-1)));
                
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_doubleContext ------------------------------------------------------------------

FuuraParser::Const_doubleContext::Const_doubleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FuuraParser::Const_doubleContext::POSITIVE_FLOAT() {
  return getToken(FuuraParser::POSITIVE_FLOAT, 0);
}

tree::TerminalNode* FuuraParser::Const_doubleContext::MINUS() {
  return getToken(FuuraParser::MINUS, 0);
}

FuuraParser::Opt_WSContext* FuuraParser::Const_doubleContext::opt_WS() {
  return getRuleContext<FuuraParser::Opt_WSContext>(0);
}


size_t FuuraParser::Const_doubleContext::getRuleIndex() const {
  return FuuraParser::RuleConst_double;
}

void FuuraParser::Const_doubleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_double(this);
}

void FuuraParser::Const_doubleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_double(this);
}

FuuraParser::Const_doubleContext* FuuraParser::const_double() {
  Const_doubleContext *_localctx = _tracker.createInstance<Const_doubleContext>(_ctx, getState());
  enterRule(_localctx, 26, FuuraParser::RuleConst_double);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == FuuraParser::MINUS) {
      setState(270);
      match(FuuraParser::MINUS);
      setState(271);
      opt_WS();
    }
    setState(274);
    match(FuuraParser::POSITIVE_FLOAT);

                    dynamic_cast<Const_doubleContext *>(_localctx)->node =  std::make_unique<fuura::language::Constant<double>>(_input->getText(_localctx->start, _input->LT(-1)));
                
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_boolContext ------------------------------------------------------------------

FuuraParser::Const_boolContext::Const_boolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FuuraParser::Const_boolContext::TRUE() {
  return getToken(FuuraParser::TRUE, 0);
}

tree::TerminalNode* FuuraParser::Const_boolContext::FALSE() {
  return getToken(FuuraParser::FALSE, 0);
}


size_t FuuraParser::Const_boolContext::getRuleIndex() const {
  return FuuraParser::RuleConst_bool;
}

void FuuraParser::Const_boolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_bool(this);
}

void FuuraParser::Const_boolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_bool(this);
}

FuuraParser::Const_boolContext* FuuraParser::const_bool() {
  Const_boolContext *_localctx = _tracker.createInstance<Const_boolContext>(_ctx, getState());
  enterRule(_localctx, 28, FuuraParser::RuleConst_bool);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    _la = _input->LA(1);
    if (!(_la == FuuraParser::TRUE

    || _la == FuuraParser::FALSE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }

                    dynamic_cast<Const_boolContext *>(_localctx)->node =  std::make_unique<fuura::language::Constant<bool>>(_input->getText(_localctx->start, _input->LT(-1)));
                
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Opt_WSContext ------------------------------------------------------------------

FuuraParser::Opt_WSContext::Opt_WSContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FuuraParser::Opt_WSContext::WS() {
  return getToken(FuuraParser::WS, 0);
}

FuuraParser::NothingContext* FuuraParser::Opt_WSContext::nothing() {
  return getRuleContext<FuuraParser::NothingContext>(0);
}


size_t FuuraParser::Opt_WSContext::getRuleIndex() const {
  return FuuraParser::RuleOpt_WS;
}

void FuuraParser::Opt_WSContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpt_WS(this);
}

void FuuraParser::Opt_WSContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpt_WS(this);
}

FuuraParser::Opt_WSContext* FuuraParser::opt_WS() {
  Opt_WSContext *_localctx = _tracker.createInstance<Opt_WSContext>(_ctx, getState());
  enterRule(_localctx, 30, FuuraParser::RuleOpt_WS);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(283);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case FuuraParser::WS: {
        enterOuterAlt(_localctx, 1);
        setState(281);
        match(FuuraParser::WS);
        break;
      }

      case FuuraParser::EOF:
      case FuuraParser::IF:
      case FuuraParser::ELSE:
      case FuuraParser::AND:
      case FuuraParser::OR:
      case FuuraParser::NOT:
      case FuuraParser::TRUE:
      case FuuraParser::FALSE:
      case FuuraParser::DIV:
      case FuuraParser::ID:
      case FuuraParser::POSITIVE_INT:
      case FuuraParser::POSITIVE_FLOAT:
      case FuuraParser::SEMIC:
      case FuuraParser::PLUS:
      case FuuraParser::MINUS:
      case FuuraParser::STAR:
      case FuuraParser::SLASH:
      case FuuraParser::PERCENT:
      case FuuraParser::CARET:
      case FuuraParser::EQUAL:
      case FuuraParser::NOT_EQUAL:
      case FuuraParser::GREATER:
      case FuuraParser::LESS:
      case FuuraParser::GREATER_EQ:
      case FuuraParser::LESS_EQ:
      case FuuraParser::BR_OP:
      case FuuraParser::BR_CL: {
        enterOuterAlt(_localctx, 2);
        setState(282);
        nothing();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NothingContext ------------------------------------------------------------------

FuuraParser::NothingContext::NothingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t FuuraParser::NothingContext::getRuleIndex() const {
  return FuuraParser::RuleNothing;
}

void FuuraParser::NothingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNothing(this);
}

void FuuraParser::NothingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FuuraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNothing(this);
}

FuuraParser::NothingContext* FuuraParser::nothing() {
  NothingContext *_localctx = _tracker.createInstance<NothingContext>(_ctx, getState());
  enterRule(_localctx, 32, FuuraParser::RuleNothing);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);

   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> FuuraParser::_decisionToDFA;
atn::PredictionContextCache FuuraParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN FuuraParser::_atn;
std::vector<uint16_t> FuuraParser::_serializedATN;

std::vector<std::string> FuuraParser::_ruleNames = {
  "root", "if_expr", "full_expr", "not_expr", "cmp_expr", "add_expr", "mul_expr", 
  "invert_expr", "pow_expr", "atom", "argument", "const_any", "const_integer", 
  "const_double", "const_bool", "opt_WS", "nothing"
};

std::vector<std::string> FuuraParser::_literalNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "';'", "'+'", "'-'", "'*'", 
  "'/'", "'%'", "'^'", "'.'", "','", "'='", "'!='", "'>'", "'<'", "'>='", 
  "'<='", "'('", "')'"
};

std::vector<std::string> FuuraParser::_symbolicNames = {
  "", "IF", "ELSE", "AND", "OR", "NOT", "TRUE", "FALSE", "DIV", "ID", "POSITIVE_INT", 
  "POSITIVE_FLOAT", "SEMIC", "PLUS", "MINUS", "STAR", "SLASH", "PERCENT", 
  "CARET", "DOT", "COMMA", "EQUAL", "NOT_EQUAL", "GREATER", "LESS", "GREATER_EQ", 
  "LESS_EQ", "BR_OP", "BR_CL", "WS"
};

dfa::Vocabulary FuuraParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> FuuraParser::_tokenNames;

FuuraParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x1f, 0x122, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x43, 0xa, 0x3, 0xc, 0x3, 
    0xe, 0x3, 0x46, 0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x5e, 0xa, 0x4, 0x7, 0x4, 
    0x60, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x63, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 
    0x6d, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x95, 0xa, 0x6, 
    0x7, 0x6, 0x97, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x9a, 0xb, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 
    0xaa, 0xa, 0x7, 0x7, 0x7, 0xac, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0xaf, 
    0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 
    0xcb, 0xa, 0x8, 0x7, 0x8, 0xcd, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0xd0, 
    0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0xda, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0xe4, 
    0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0xe7, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 
    0xb, 0xf9, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x5, 0xd, 0x107, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x10b, 0xa, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x5, 
    0xf, 0x113, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x11e, 0xa, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x2, 0x2, 0x13, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 
    0x22, 0x2, 0x3, 0x3, 0x2, 0x8, 0x9, 0x2, 0x12a, 0x2, 0x24, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4f, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x6c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x6e, 0x3, 0x2, 0x2, 0x2, 0xc, 0x9b, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0xb0, 0x3, 0x2, 0x2, 0x2, 0x10, 0xd9, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x14, 0xf8, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0xfa, 0x3, 0x2, 0x2, 0x2, 0x18, 0x106, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x112, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x118, 0x3, 0x2, 0x2, 0x2, 0x20, 0x11d, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x11f, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x5, 0x20, 0x11, 0x2, 0x25, 0x26, 
    0x5, 0x6, 0x4, 0x2, 0x26, 0x27, 0x5, 0x20, 0x11, 0x2, 0x27, 0x28, 0x7, 
    0x2, 0x2, 0x3, 0x28, 0x29, 0x8, 0x2, 0x1, 0x2, 0x29, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0x2b, 0x7, 0x3, 0x2, 0x2, 0x2b, 0x2c, 0x5, 0x20, 0x11, 
    0x2, 0x2c, 0x2d, 0x7, 0x1d, 0x2, 0x2, 0x2d, 0x2e, 0x5, 0x20, 0x11, 0x2, 
    0x2e, 0x2f, 0x5, 0x6, 0x4, 0x2, 0x2f, 0x30, 0x5, 0x20, 0x11, 0x2, 0x30, 
    0x31, 0x7, 0x1e, 0x2, 0x2, 0x31, 0x32, 0x5, 0x20, 0x11, 0x2, 0x32, 0x33, 
    0x5, 0x6, 0x4, 0x2, 0x33, 0x44, 0x8, 0x3, 0x1, 0x2, 0x34, 0x35, 0x5, 
    0x20, 0x11, 0x2, 0x35, 0x36, 0x7, 0x4, 0x2, 0x2, 0x36, 0x37, 0x5, 0x20, 
    0x11, 0x2, 0x37, 0x38, 0x7, 0x3, 0x2, 0x2, 0x38, 0x39, 0x5, 0x20, 0x11, 
    0x2, 0x39, 0x3a, 0x7, 0x1d, 0x2, 0x2, 0x3a, 0x3b, 0x5, 0x20, 0x11, 0x2, 
    0x3b, 0x3c, 0x5, 0x6, 0x4, 0x2, 0x3c, 0x3d, 0x5, 0x20, 0x11, 0x2, 0x3d, 
    0x3e, 0x7, 0x1e, 0x2, 0x2, 0x3e, 0x3f, 0x5, 0x20, 0x11, 0x2, 0x3f, 0x40, 
    0x5, 0x6, 0x4, 0x2, 0x40, 0x41, 0x8, 0x3, 0x1, 0x2, 0x41, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x42, 0x34, 0x3, 0x2, 0x2, 0x2, 0x43, 0x46, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x3, 0x2, 0x2, 
    0x2, 0x45, 0x47, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 
    0x47, 0x48, 0x5, 0x20, 0x11, 0x2, 0x48, 0x49, 0x7, 0x4, 0x2, 0x2, 0x49, 
    0x4a, 0x5, 0x20, 0x11, 0x2, 0x4a, 0x4b, 0x5, 0x6, 0x4, 0x2, 0x4b, 0x4c, 
    0x5, 0x20, 0x11, 0x2, 0x4c, 0x4d, 0x7, 0xe, 0x2, 0x2, 0x4d, 0x4e, 0x8, 
    0x3, 0x1, 0x2, 0x4e, 0x5, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x5, 0x8, 
    0x5, 0x2, 0x50, 0x61, 0x8, 0x4, 0x1, 0x2, 0x51, 0x52, 0x5, 0x20, 0x11, 
    0x2, 0x52, 0x53, 0x7, 0x6, 0x2, 0x2, 0x53, 0x54, 0x5, 0x20, 0x11, 0x2, 
    0x54, 0x55, 0x5, 0x8, 0x5, 0x2, 0x55, 0x56, 0x8, 0x4, 0x1, 0x2, 0x56, 
    0x5e, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x5, 0x20, 0x11, 0x2, 0x58, 0x59, 
    0x7, 0x5, 0x2, 0x2, 0x59, 0x5a, 0x5, 0x20, 0x11, 0x2, 0x5a, 0x5b, 0x5, 
    0x8, 0x5, 0x2, 0x5b, 0x5c, 0x8, 0x4, 0x1, 0x2, 0x5c, 0x5e, 0x3, 0x2, 
    0x2, 0x2, 0x5d, 0x51, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x57, 0x3, 0x2, 0x2, 
    0x2, 0x5e, 0x60, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0x60, 0x63, 0x3, 0x2, 0x2, 0x2, 0x61, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 
    0x62, 0x3, 0x2, 0x2, 0x2, 0x62, 0x7, 0x3, 0x2, 0x2, 0x2, 0x63, 0x61, 
    0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x5, 0xa, 0x6, 0x2, 0x65, 0x66, 0x8, 
    0x5, 0x1, 0x2, 0x66, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x7, 0x7, 
    0x2, 0x2, 0x68, 0x69, 0x5, 0x20, 0x11, 0x2, 0x69, 0x6a, 0x5, 0xa, 0x6, 
    0x2, 0x6a, 0x6b, 0x8, 0x5, 0x1, 0x2, 0x6b, 0x6d, 0x3, 0x2, 0x2, 0x2, 
    0x6c, 0x64, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x67, 0x3, 0x2, 0x2, 0x2, 0x6d, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0x5, 0xc, 0x7, 0x2, 0x6f, 0x98, 
    0x8, 0x6, 0x1, 0x2, 0x70, 0x71, 0x5, 0x20, 0x11, 0x2, 0x71, 0x72, 0x7, 
    0x17, 0x2, 0x2, 0x72, 0x73, 0x5, 0x20, 0x11, 0x2, 0x73, 0x74, 0x5, 0xc, 
    0x7, 0x2, 0x74, 0x75, 0x8, 0x6, 0x1, 0x2, 0x75, 0x95, 0x3, 0x2, 0x2, 
    0x2, 0x76, 0x77, 0x5, 0x20, 0x11, 0x2, 0x77, 0x78, 0x7, 0x18, 0x2, 0x2, 
    0x78, 0x79, 0x5, 0x20, 0x11, 0x2, 0x79, 0x7a, 0x5, 0xc, 0x7, 0x2, 0x7a, 
    0x7b, 0x8, 0x6, 0x1, 0x2, 0x7b, 0x95, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 
    0x5, 0x20, 0x11, 0x2, 0x7d, 0x7e, 0x7, 0x1a, 0x2, 0x2, 0x7e, 0x7f, 0x5, 
    0x20, 0x11, 0x2, 0x7f, 0x80, 0x5, 0xc, 0x7, 0x2, 0x80, 0x81, 0x8, 0x6, 
    0x1, 0x2, 0x81, 0x95, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x5, 0x20, 0x11, 
    0x2, 0x83, 0x84, 0x7, 0x19, 0x2, 0x2, 0x84, 0x85, 0x5, 0x20, 0x11, 0x2, 
    0x85, 0x86, 0x5, 0xc, 0x7, 0x2, 0x86, 0x87, 0x8, 0x6, 0x1, 0x2, 0x87, 
    0x95, 0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x5, 0x20, 0x11, 0x2, 0x89, 0x8a, 
    0x7, 0x1c, 0x2, 0x2, 0x8a, 0x8b, 0x5, 0x20, 0x11, 0x2, 0x8b, 0x8c, 0x5, 
    0xc, 0x7, 0x2, 0x8c, 0x8d, 0x8, 0x6, 0x1, 0x2, 0x8d, 0x95, 0x3, 0x2, 
    0x2, 0x2, 0x8e, 0x8f, 0x5, 0x20, 0x11, 0x2, 0x8f, 0x90, 0x7, 0x1b, 0x2, 
    0x2, 0x90, 0x91, 0x5, 0x20, 0x11, 0x2, 0x91, 0x92, 0x5, 0xc, 0x7, 0x2, 
    0x92, 0x93, 0x8, 0x6, 0x1, 0x2, 0x93, 0x95, 0x3, 0x2, 0x2, 0x2, 0x94, 
    0x70, 0x3, 0x2, 0x2, 0x2, 0x94, 0x76, 0x3, 0x2, 0x2, 0x2, 0x94, 0x7c, 
    0x3, 0x2, 0x2, 0x2, 0x94, 0x82, 0x3, 0x2, 0x2, 0x2, 0x94, 0x88, 0x3, 
    0x2, 0x2, 0x2, 0x94, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x95, 0x97, 0x3, 0x2, 
    0x2, 0x2, 0x96, 0x94, 0x3, 0x2, 0x2, 0x2, 0x97, 0x9a, 0x3, 0x2, 0x2, 
    0x2, 0x98, 0x96, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x3, 0x2, 0x2, 0x2, 
    0x99, 0xb, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9b, 
    0x9c, 0x5, 0xe, 0x8, 0x2, 0x9c, 0xad, 0x8, 0x7, 0x1, 0x2, 0x9d, 0x9e, 
    0x5, 0x20, 0x11, 0x2, 0x9e, 0x9f, 0x7, 0xf, 0x2, 0x2, 0x9f, 0xa0, 0x5, 
    0x20, 0x11, 0x2, 0xa0, 0xa1, 0x5, 0xe, 0x8, 0x2, 0xa1, 0xa2, 0x8, 0x7, 
    0x1, 0x2, 0xa2, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa4, 0x5, 0x20, 0x11, 
    0x2, 0xa4, 0xa5, 0x7, 0x10, 0x2, 0x2, 0xa5, 0xa6, 0x5, 0x20, 0x11, 0x2, 
    0xa6, 0xa7, 0x5, 0xe, 0x8, 0x2, 0xa7, 0xa8, 0x8, 0x7, 0x1, 0x2, 0xa8, 
    0xaa, 0x3, 0x2, 0x2, 0x2, 0xa9, 0x9d, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xa3, 
    0x3, 0x2, 0x2, 0x2, 0xaa, 0xac, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa9, 0x3, 
    0x2, 0x2, 0x2, 0xac, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xad, 0xab, 0x3, 0x2, 
    0x2, 0x2, 0xad, 0xae, 0x3, 0x2, 0x2, 0x2, 0xae, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0xaf, 0xad, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0x5, 0x10, 0x9, 0x2, 
    0xb1, 0xce, 0x8, 0x8, 0x1, 0x2, 0xb2, 0xb3, 0x5, 0x20, 0x11, 0x2, 0xb3, 
    0xb4, 0x7, 0x11, 0x2, 0x2, 0xb4, 0xb5, 0x5, 0x20, 0x11, 0x2, 0xb5, 0xb6, 
    0x5, 0x10, 0x9, 0x2, 0xb6, 0xb7, 0x8, 0x8, 0x1, 0x2, 0xb7, 0xcb, 0x3, 
    0x2, 0x2, 0x2, 0xb8, 0xb9, 0x5, 0x20, 0x11, 0x2, 0xb9, 0xba, 0x7, 0x12, 
    0x2, 0x2, 0xba, 0xbb, 0x5, 0x20, 0x11, 0x2, 0xbb, 0xbc, 0x5, 0x10, 0x9, 
    0x2, 0xbc, 0xbd, 0x8, 0x8, 0x1, 0x2, 0xbd, 0xcb, 0x3, 0x2, 0x2, 0x2, 
    0xbe, 0xbf, 0x5, 0x20, 0x11, 0x2, 0xbf, 0xc0, 0x7, 0xa, 0x2, 0x2, 0xc0, 
    0xc1, 0x5, 0x20, 0x11, 0x2, 0xc1, 0xc2, 0x5, 0x10, 0x9, 0x2, 0xc2, 0xc3, 
    0x8, 0x8, 0x1, 0x2, 0xc3, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x5, 
    0x20, 0x11, 0x2, 0xc5, 0xc6, 0x7, 0x13, 0x2, 0x2, 0xc6, 0xc7, 0x5, 0x20, 
    0x11, 0x2, 0xc7, 0xc8, 0x5, 0x10, 0x9, 0x2, 0xc8, 0xc9, 0x8, 0x8, 0x1, 
    0x2, 0xc9, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xca, 0xb2, 0x3, 0x2, 0x2, 0x2, 
    0xca, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xca, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xca, 
    0xc4, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xca, 
    0x3, 0x2, 0x2, 0x2, 0xcd, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcc, 0x3, 
    0x2, 0x2, 0x2, 0xce, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0xd0, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x5, 0x12, 0xa, 
    0x2, 0xd2, 0xd3, 0x8, 0x9, 0x1, 0x2, 0xd3, 0xda, 0x3, 0x2, 0x2, 0x2, 
    0xd4, 0xd5, 0x7, 0x10, 0x2, 0x2, 0xd5, 0xd6, 0x5, 0x20, 0x11, 0x2, 0xd6, 
    0xd7, 0x5, 0x12, 0xa, 0x2, 0xd7, 0xd8, 0x8, 0x9, 0x1, 0x2, 0xd8, 0xda, 
    0x3, 0x2, 0x2, 0x2, 0xd9, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xd4, 0x3, 
    0x2, 0x2, 0x2, 0xda, 0x11, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdc, 0x5, 0x14, 
    0xb, 0x2, 0xdc, 0xe5, 0x8, 0xa, 0x1, 0x2, 0xdd, 0xde, 0x5, 0x20, 0x11, 
    0x2, 0xde, 0xdf, 0x7, 0x14, 0x2, 0x2, 0xdf, 0xe0, 0x5, 0x20, 0x11, 0x2, 
    0xe0, 0xe1, 0x5, 0x14, 0xb, 0x2, 0xe1, 0xe2, 0x8, 0xa, 0x1, 0x2, 0xe2, 
    0xe4, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe7, 
    0x3, 0x2, 0x2, 0x2, 0xe5, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x3, 
    0x2, 0x2, 0x2, 0xe6, 0x13, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe5, 0x3, 0x2, 
    0x2, 0x2, 0xe8, 0xe9, 0x5, 0x16, 0xc, 0x2, 0xe9, 0xea, 0x8, 0xb, 0x1, 
    0x2, 0xea, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xec, 0x5, 0x18, 0xd, 0x2, 
    0xec, 0xed, 0x8, 0xb, 0x1, 0x2, 0xed, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xee, 
    0xef, 0x5, 0x4, 0x3, 0x2, 0xef, 0xf0, 0x8, 0xb, 0x1, 0x2, 0xf0, 0xf9, 
    0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 0x7, 0x1d, 0x2, 0x2, 0xf2, 0xf3, 0x5, 
    0x20, 0x11, 0x2, 0xf3, 0xf4, 0x5, 0x6, 0x4, 0x2, 0xf4, 0xf5, 0x5, 0x20, 
    0x11, 0x2, 0xf5, 0xf6, 0x7, 0x1e, 0x2, 0x2, 0xf6, 0xf7, 0x8, 0xb, 0x1, 
    0x2, 0xf7, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xe8, 0x3, 0x2, 0x2, 0x2, 
    0xf8, 0xeb, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xee, 0x3, 0x2, 0x2, 0x2, 0xf8, 
    0xf1, 0x3, 0x2, 0x2, 0x2, 0xf9, 0x15, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 
    0x7, 0xb, 0x2, 0x2, 0xfb, 0xfc, 0x8, 0xc, 0x1, 0x2, 0xfc, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0xfd, 0xfe, 0x5, 0x1a, 0xe, 0x2, 0xfe, 0xff, 0x8, 0xd, 
    0x1, 0x2, 0xff, 0x107, 0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 0x5, 0x1c, 
    0xf, 0x2, 0x101, 0x102, 0x8, 0xd, 0x1, 0x2, 0x102, 0x107, 0x3, 0x2, 
    0x2, 0x2, 0x103, 0x104, 0x5, 0x1e, 0x10, 0x2, 0x104, 0x105, 0x8, 0xd, 
    0x1, 0x2, 0x105, 0x107, 0x3, 0x2, 0x2, 0x2, 0x106, 0xfd, 0x3, 0x2, 0x2, 
    0x2, 0x106, 0x100, 0x3, 0x2, 0x2, 0x2, 0x106, 0x103, 0x3, 0x2, 0x2, 
    0x2, 0x107, 0x19, 0x3, 0x2, 0x2, 0x2, 0x108, 0x109, 0x7, 0x10, 0x2, 
    0x2, 0x109, 0x10b, 0x5, 0x20, 0x11, 0x2, 0x10a, 0x108, 0x3, 0x2, 0x2, 
    0x2, 0x10a, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x10c, 0x3, 0x2, 0x2, 
    0x2, 0x10c, 0x10d, 0x7, 0xc, 0x2, 0x2, 0x10d, 0x10e, 0x3, 0x2, 0x2, 
    0x2, 0x10e, 0x10f, 0x8, 0xe, 0x1, 0x2, 0x10f, 0x1b, 0x3, 0x2, 0x2, 0x2, 
    0x110, 0x111, 0x7, 0x10, 0x2, 0x2, 0x111, 0x113, 0x5, 0x20, 0x11, 0x2, 
    0x112, 0x110, 0x3, 0x2, 0x2, 0x2, 0x112, 0x113, 0x3, 0x2, 0x2, 0x2, 
    0x113, 0x114, 0x3, 0x2, 0x2, 0x2, 0x114, 0x115, 0x7, 0xd, 0x2, 0x2, 
    0x115, 0x116, 0x3, 0x2, 0x2, 0x2, 0x116, 0x117, 0x8, 0xf, 0x1, 0x2, 
    0x117, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 0x9, 0x2, 0x2, 0x2, 0x119, 
    0x11a, 0x8, 0x10, 0x1, 0x2, 0x11a, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x11b, 
    0x11e, 0x7, 0x1f, 0x2, 0x2, 0x11c, 0x11e, 0x5, 0x22, 0x12, 0x2, 0x11d, 
    0x11b, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x11e, 
    0x21, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x120, 0x3, 0x2, 0x2, 0x2, 0x120, 0x23, 
    0x3, 0x2, 0x2, 0x2, 0x13, 0x44, 0x5d, 0x61, 0x6c, 0x94, 0x98, 0xa9, 
    0xad, 0xca, 0xce, 0xd9, 0xe5, 0xf8, 0x106, 0x10a, 0x112, 0x11d, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

FuuraParser::Initializer FuuraParser::_init;

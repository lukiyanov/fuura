
#include "stdafx.h"
#include "..\..\FuuraSemantics.h"
#include "..\..\Calculatables.h"
#pragma warning(disable:4251) // (...) должен иметь dll-интерфейс для использования клиентами.


// Generated from Fuura.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"


namespace fuura::antlr::generated {


class  FuuraParser : public antlr4::Parser {
public:
  enum {
    IF = 1, ELSE = 2, AND = 3, OR = 4, NOT = 5, TRUE = 6, FALSE = 7, DIV = 8, 
    ID = 9, POSITIVE_INT = 10, POSITIVE_FLOAT = 11, SEMIC = 12, PLUS = 13, 
    MINUS = 14, STAR = 15, SLASH = 16, PERCENT = 17, CARET = 18, DOT = 19, 
    COMMA = 20, EQUAL = 21, NOT_EQUAL = 22, GREATER = 23, LESS = 24, GREATER_EQ = 25, 
    LESS_EQ = 26, BR_OP = 27, BR_CL = 28, WS = 29
  };

  enum {
    RuleRoot = 0, RuleIf_expr = 1, RuleFull_expr = 2, RuleNot_expr = 3, 
    RuleCmp_expr = 4, RuleAdd_expr = 5, RuleMul_expr = 6, RuleInvert_expr = 7, 
    RulePow_expr = 8, RuleAtom = 9, RuleArgument = 10, RuleConst_any = 11, 
    RuleConst_integer = 12, RuleConst_double = 13, RuleConst_bool = 14, 
    RuleOpt_WS = 15, RuleNothing = 16
  };

  FuuraParser(antlr4::TokenStream *input);
  ~FuuraParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  // Невладеющий указатель на настройки семантики.
  fuura::language::FuuraSemantics* m_semantics;


  class RootContext;
  class If_exprContext;
  class Full_exprContext;
  class Not_exprContext;
  class Cmp_exprContext;
  class Add_exprContext;
  class Mul_exprContext;
  class Invert_exprContext;
  class Pow_exprContext;
  class AtomContext;
  class ArgumentContext;
  class Const_anyContext;
  class Const_integerContext;
  class Const_doubleContext;
  class Const_boolContext;
  class Opt_WSContext;
  class NothingContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::Full_exprContext *stmt = nullptr;;
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    antlr4::tree::TerminalNode *EOF();
    Full_exprContext *full_expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RootContext* root();

  class  If_exprContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::OperatorIf> node;
    FuuraParser::Full_exprContext *condition = nullptr;;
    FuuraParser::Full_exprContext *expression = nullptr;;
    If_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IF();
    antlr4::tree::TerminalNode* IF(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BR_OP();
    antlr4::tree::TerminalNode* BR_OP(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BR_CL();
    antlr4::tree::TerminalNode* BR_CL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ELSE();
    antlr4::tree::TerminalNode* ELSE(size_t i);
    antlr4::tree::TerminalNode *SEMIC();
    std::vector<Full_exprContext *> full_expr();
    Full_exprContext* full_expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  If_exprContext* if_expr();

  class  Full_exprContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::Not_exprContext *not_exprContext = nullptr;;
    FuuraParser::Not_exprContext *next = nullptr;;
    Full_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Not_exprContext *> not_expr();
    Not_exprContext* not_expr(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Full_exprContext* full_expr();

  class  Not_exprContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::Cmp_exprContext *cmp_exprContext = nullptr;;
    Not_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Cmp_exprContext *cmp_expr();
    antlr4::tree::TerminalNode *NOT();
    Opt_WSContext *opt_WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Not_exprContext* not_expr();

  class  Cmp_exprContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::Add_exprContext *add_exprContext = nullptr;;
    FuuraParser::Add_exprContext *next = nullptr;;
    Cmp_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Add_exprContext *> add_expr();
    Add_exprContext* add_expr(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NOT_EQUAL();
    antlr4::tree::TerminalNode* NOT_EQUAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESS();
    antlr4::tree::TerminalNode* LESS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESS_EQ();
    antlr4::tree::TerminalNode* LESS_EQ(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER_EQ();
    antlr4::tree::TerminalNode* GREATER_EQ(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Cmp_exprContext* cmp_expr();

  class  Add_exprContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::Mul_exprContext *mul_exprContext = nullptr;;
    FuuraParser::Mul_exprContext *next = nullptr;;
    Add_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Mul_exprContext *> mul_expr();
    Mul_exprContext* mul_expr(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Add_exprContext* add_expr();

  class  Mul_exprContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::Invert_exprContext *invert_exprContext = nullptr;;
    FuuraParser::Invert_exprContext *next = nullptr;;
    Mul_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Invert_exprContext *> invert_expr();
    Invert_exprContext* invert_expr(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STAR();
    antlr4::tree::TerminalNode* STAR(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SLASH();
    antlr4::tree::TerminalNode* SLASH(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIV();
    antlr4::tree::TerminalNode* DIV(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PERCENT();
    antlr4::tree::TerminalNode* PERCENT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Mul_exprContext* mul_expr();

  class  Invert_exprContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::Pow_exprContext *pow_exprContext = nullptr;;
    Invert_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Pow_exprContext *pow_expr();
    antlr4::tree::TerminalNode *MINUS();
    Opt_WSContext *opt_WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Invert_exprContext* invert_expr();

  class  Pow_exprContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::AtomContext *atomContext = nullptr;;
    FuuraParser::AtomContext *next = nullptr;;
    Pow_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AtomContext *> atom();
    AtomContext* atom(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Pow_exprContext* pow_expr();

  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::ArgumentContext *argumentContext = nullptr;;
    FuuraParser::Const_anyContext *const_anyContext = nullptr;;
    FuuraParser::If_exprContext *if_exprContext = nullptr;;
    FuuraParser::Full_exprContext *full_exprContext = nullptr;;
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgumentContext *argument();
    Const_anyContext *const_any();
    If_exprContext *if_expr();
    antlr4::tree::TerminalNode *BR_OP();
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    Full_exprContext *full_expr();
    antlr4::tree::TerminalNode *BR_CL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtomContext* atom();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::Argument> node;
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgumentContext* argument();

  class  Const_anyContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::ICalculatable> node;
    FuuraParser::Const_integerContext *const_integerContext = nullptr;;
    FuuraParser::Const_doubleContext *const_doubleContext = nullptr;;
    FuuraParser::Const_boolContext *const_boolContext = nullptr;;
    Const_anyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Const_integerContext *const_integer();
    Const_doubleContext *const_double();
    Const_boolContext *const_bool();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Const_anyContext* const_any();

  class  Const_integerContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::Constant<int>> node;
    Const_integerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *POSITIVE_INT();
    antlr4::tree::TerminalNode *MINUS();
    Opt_WSContext *opt_WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Const_integerContext* const_integer();

  class  Const_doubleContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::Constant<double>> node;
    Const_doubleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *POSITIVE_FLOAT();
    antlr4::tree::TerminalNode *MINUS();
    Opt_WSContext *opt_WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Const_doubleContext* const_double();

  class  Const_boolContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<fuura::language::Constant<bool>> node;
    Const_boolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Const_boolContext* const_bool();

  class  Opt_WSContext : public antlr4::ParserRuleContext {
  public:
    Opt_WSContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WS();
    NothingContext *nothing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Opt_WSContext* opt_WS();

  class  NothingContext : public antlr4::ParserRuleContext {
  public:
    NothingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NothingContext* nothing();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace fuura::antlr::generated

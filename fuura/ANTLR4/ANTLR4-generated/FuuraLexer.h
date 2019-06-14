
#include "stdafx.h"
#include "..\..\FuuraSemantics.h"
#include "..\..\Calculatables.h"
#pragma warning(disable:4251) // (...) должен иметь dll-интерфейс для использования клиентами.


// Generated from Fuura.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"


namespace fuura::antlr::generated {


class  FuuraLexer : public antlr4::Lexer {
public:
  enum {
    IF = 1, ELSE = 2, AND = 3, OR = 4, NOT = 5, TRUE = 6, FALSE = 7, DIV = 8, 
    ID = 9, POSITIVE_INT = 10, POSITIVE_FLOAT = 11, SEMIC = 12, PLUS = 13, 
    MINUS = 14, STAR = 15, SLASH = 16, PERCENT = 17, CARET = 18, DOT = 19, 
    COMMA = 20, EQUAL = 21, NOT_EQUAL = 22, GREATER = 23, LESS = 24, GREATER_EQ = 25, 
    LESS_EQ = 26, BR_OP = 27, BR_CL = 28, WS = 29
  };

  FuuraLexer(antlr4::CharStream *input);
  ~FuuraLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace fuura::antlr::generated

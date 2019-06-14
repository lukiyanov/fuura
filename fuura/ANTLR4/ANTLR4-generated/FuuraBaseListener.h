
#include "stdafx.h"
#include "..\..\FuuraSemantics.h"
#include "..\..\Calculatables.h"
#pragma warning(disable:4251) // (...) должен иметь dll-интерфейс для использования клиентами.


// Generated from Fuura.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "FuuraListener.h"


namespace fuura::antlr::generated {

/**
 * This class provides an empty implementation of FuuraListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  FuuraBaseListener : public FuuraListener {
public:

  virtual void enterRoot(FuuraParser::RootContext * /*ctx*/) override { }
  virtual void exitRoot(FuuraParser::RootContext * /*ctx*/) override { }

  virtual void enterIf_expr(FuuraParser::If_exprContext * /*ctx*/) override { }
  virtual void exitIf_expr(FuuraParser::If_exprContext * /*ctx*/) override { }

  virtual void enterFull_expr(FuuraParser::Full_exprContext * /*ctx*/) override { }
  virtual void exitFull_expr(FuuraParser::Full_exprContext * /*ctx*/) override { }

  virtual void enterNot_expr(FuuraParser::Not_exprContext * /*ctx*/) override { }
  virtual void exitNot_expr(FuuraParser::Not_exprContext * /*ctx*/) override { }

  virtual void enterCmp_expr(FuuraParser::Cmp_exprContext * /*ctx*/) override { }
  virtual void exitCmp_expr(FuuraParser::Cmp_exprContext * /*ctx*/) override { }

  virtual void enterAdd_expr(FuuraParser::Add_exprContext * /*ctx*/) override { }
  virtual void exitAdd_expr(FuuraParser::Add_exprContext * /*ctx*/) override { }

  virtual void enterMul_expr(FuuraParser::Mul_exprContext * /*ctx*/) override { }
  virtual void exitMul_expr(FuuraParser::Mul_exprContext * /*ctx*/) override { }

  virtual void enterInvert_expr(FuuraParser::Invert_exprContext * /*ctx*/) override { }
  virtual void exitInvert_expr(FuuraParser::Invert_exprContext * /*ctx*/) override { }

  virtual void enterPow_expr(FuuraParser::Pow_exprContext * /*ctx*/) override { }
  virtual void exitPow_expr(FuuraParser::Pow_exprContext * /*ctx*/) override { }

  virtual void enterAtom(FuuraParser::AtomContext * /*ctx*/) override { }
  virtual void exitAtom(FuuraParser::AtomContext * /*ctx*/) override { }

  virtual void enterArgument(FuuraParser::ArgumentContext * /*ctx*/) override { }
  virtual void exitArgument(FuuraParser::ArgumentContext * /*ctx*/) override { }

  virtual void enterConst_any(FuuraParser::Const_anyContext * /*ctx*/) override { }
  virtual void exitConst_any(FuuraParser::Const_anyContext * /*ctx*/) override { }

  virtual void enterConst_integer(FuuraParser::Const_integerContext * /*ctx*/) override { }
  virtual void exitConst_integer(FuuraParser::Const_integerContext * /*ctx*/) override { }

  virtual void enterConst_double(FuuraParser::Const_doubleContext * /*ctx*/) override { }
  virtual void exitConst_double(FuuraParser::Const_doubleContext * /*ctx*/) override { }

  virtual void enterConst_bool(FuuraParser::Const_boolContext * /*ctx*/) override { }
  virtual void exitConst_bool(FuuraParser::Const_boolContext * /*ctx*/) override { }

  virtual void enterOpt_WS(FuuraParser::Opt_WSContext * /*ctx*/) override { }
  virtual void exitOpt_WS(FuuraParser::Opt_WSContext * /*ctx*/) override { }

  virtual void enterNothing(FuuraParser::NothingContext * /*ctx*/) override { }
  virtual void exitNothing(FuuraParser::NothingContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace fuura::antlr::generated

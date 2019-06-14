
#include "stdafx.h"
#include "..\..\FuuraSemantics.h"
#include "..\..\Calculatables.h"
#pragma warning(disable:4251) // (...) должен иметь dll-интерфейс для использования клиентами.


// Generated from Fuura.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "FuuraParser.h"


namespace fuura::antlr::generated {

/**
 * This interface defines an abstract listener for a parse tree produced by FuuraParser.
 */
class  FuuraListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterRoot(FuuraParser::RootContext *ctx) = 0;
  virtual void exitRoot(FuuraParser::RootContext *ctx) = 0;

  virtual void enterIf_expr(FuuraParser::If_exprContext *ctx) = 0;
  virtual void exitIf_expr(FuuraParser::If_exprContext *ctx) = 0;

  virtual void enterFull_expr(FuuraParser::Full_exprContext *ctx) = 0;
  virtual void exitFull_expr(FuuraParser::Full_exprContext *ctx) = 0;

  virtual void enterNot_expr(FuuraParser::Not_exprContext *ctx) = 0;
  virtual void exitNot_expr(FuuraParser::Not_exprContext *ctx) = 0;

  virtual void enterCmp_expr(FuuraParser::Cmp_exprContext *ctx) = 0;
  virtual void exitCmp_expr(FuuraParser::Cmp_exprContext *ctx) = 0;

  virtual void enterAdd_expr(FuuraParser::Add_exprContext *ctx) = 0;
  virtual void exitAdd_expr(FuuraParser::Add_exprContext *ctx) = 0;

  virtual void enterMul_expr(FuuraParser::Mul_exprContext *ctx) = 0;
  virtual void exitMul_expr(FuuraParser::Mul_exprContext *ctx) = 0;

  virtual void enterInvert_expr(FuuraParser::Invert_exprContext *ctx) = 0;
  virtual void exitInvert_expr(FuuraParser::Invert_exprContext *ctx) = 0;

  virtual void enterPow_expr(FuuraParser::Pow_exprContext *ctx) = 0;
  virtual void exitPow_expr(FuuraParser::Pow_exprContext *ctx) = 0;

  virtual void enterAtom(FuuraParser::AtomContext *ctx) = 0;
  virtual void exitAtom(FuuraParser::AtomContext *ctx) = 0;

  virtual void enterArgument(FuuraParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(FuuraParser::ArgumentContext *ctx) = 0;

  virtual void enterConst_any(FuuraParser::Const_anyContext *ctx) = 0;
  virtual void exitConst_any(FuuraParser::Const_anyContext *ctx) = 0;

  virtual void enterConst_integer(FuuraParser::Const_integerContext *ctx) = 0;
  virtual void exitConst_integer(FuuraParser::Const_integerContext *ctx) = 0;

  virtual void enterConst_double(FuuraParser::Const_doubleContext *ctx) = 0;
  virtual void exitConst_double(FuuraParser::Const_doubleContext *ctx) = 0;

  virtual void enterConst_bool(FuuraParser::Const_boolContext *ctx) = 0;
  virtual void exitConst_bool(FuuraParser::Const_boolContext *ctx) = 0;

  virtual void enterOpt_WS(FuuraParser::Opt_WSContext *ctx) = 0;
  virtual void exitOpt_WS(FuuraParser::Opt_WSContext *ctx) = 0;

  virtual void enterNothing(FuuraParser::NothingContext *ctx) = 0;
  virtual void exitNothing(FuuraParser::NothingContext *ctx) = 0;


};

}  // namespace fuura::antlr::generated

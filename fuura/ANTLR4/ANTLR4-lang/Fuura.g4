grammar Fuura;

@header{
#include "stdafx.h"
#include "..\..\FuuraSemantics.h"
#include "..\..\Calculatables.h"
#pragma warning(disable:4251) // (...) ������ ����� dll-��������� ��� ������������� ���������.
}

@parser::members
{
// ����������� ��������� �� ��������� ���������.
fuura::language::FuuraSemantics* m_semantics;
}

////////////////////////////////////////////////////////////////////////////////
// �������� ��������� ����� ���������.
// NB: ������ ��������� �������� � ���� ���������� � �������,
// � �� ����� ��� ��������� ����� ������� ������ �������� ������ ����������.
root
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
            opt_WS stmt=full_expr opt_WS EOF { $node = std::move($stmt.node); }
            ;

////////////////////////////////////////////////////////////////////////////////
// ����� �������.
/*
function_call
    returns
    [   std::unique_ptr<fuura::language::ICalculatable> node ]:
            ID
            opt_WS BR_OP               
                (opt_WS param=full_expr COMMA)*
            opt_WS BR_CL;
*/

////////////////////////////////////////////////////////////////////////////////
// �������� ���������.
if_expr
    returns [std::unique_ptr<fuura::language::OperatorIf> node]:
            IF opt_WS BR_OP opt_WS condition=full_expr opt_WS BR_CL
                opt_WS expression=full_expr
                    {
                        $node = std::make_unique<fuura::language::OperatorIf>(std::move($condition.node), std::move($expression.node), getCurrentToken());
                    }
            (opt_WS ELSE opt_WS IF opt_WS BR_OP opt_WS condition=full_expr opt_WS BR_CL
                opt_WS expression=full_expr
                    {
                        $node->ElseIf(std::move($condition.node), std::move($expression.node), getCurrentToken());
                    }
            )*
            opt_WS ELSE
                opt_WS expression=full_expr opt_WS SEMIC
                    {
                        $node->Else(std::move($expression.node), getCurrentToken(), m_semantics->GetImplicitTypeCastFactory());
                    }
             ;

////////////////////////////////////////////////////////////////////////////////
// ����������� ���� a and b, a or b.
full_expr
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
            not_expr
                {
                    $node = std::move($not_expr.node);
                }
            (
                (opt_WS OR opt_WS next=not_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Or, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS AND opt_WS next=not_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::And, std::move($node), std::move($next.node), getCurrentToken());
                    }
                )
            )*;

////////////////////////////////////////////////////////////////////////////////
// ����������� ���� not a. ���������� ����� "not not a" �� ���������.
not_expr
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
            cmp_expr
                {
                    $node = std::move($cmp_expr.node);
                }
            |(NOT opt_WS cmp_expr
                {
                    $node = m_semantics->GetOperationFactory().CreateUnaryOperation(fuura::language::UnaryOperation::Not, std::move($cmp_expr.node), getCurrentToken());
                }
            );

////////////////////////////////////////////////////////////////////////////////
// ������������ ��������� ���� ���������.
cmp_expr
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
            add_expr
                {
                    $node = std::move($add_expr.node);
                }
            (
                (opt_WS EQUAL opt_WS next=add_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Equal, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS NOT_EQUAL opt_WS next=add_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::NotEqual, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS LESS opt_WS next=add_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Less, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS GREATER opt_WS next=add_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Greater, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS LESS_EQ opt_WS next=add_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::LessOrEqual, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS GREATER_EQ opt_WS next=add_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::GreaterOrEqual, std::move($node), std::move($next.node), getCurrentToken());
                    }
                )
            )*;

////////////////////////////////////////////////////////////////////////////////
// ����������� ���� a + b, a - b, ��� ����� ��������� ����������.
add_expr
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
            mul_expr
                {
                    $node = std::move($mul_expr.node);
                }
            (
                (opt_WS PLUS opt_WS next=mul_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Add, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS MINUS opt_WS next=mul_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Subtract, std::move($node), std::move($next.node), getCurrentToken());
                    }
                )
            )*;

////////////////////////////////////////////////////////////////////////////////
// ����������� ���� a * b, a / b, a div b, a % b, ��� ����� ��������� ����������.
mul_expr
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
            invert_expr
                {
                    $node = std::move($invert_expr.node);
                }
            (
                (opt_WS STAR opt_WS next=invert_expr
                    {
                        // ������� ��������� ����, ���������� �������������� �� ���������
                        // � ������� ���������� ���� ���� ������������.
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::Multiply, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS SLASH opt_WS next=invert_expr
                    {
                        // ����������.
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::RealDivide, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS DIV opt_WS next=invert_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::IntegerDivide, std::move($node), std::move($next.node), getCurrentToken());
                    }
                | opt_WS PERCENT opt_WS next=invert_expr
                    {
                        $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::GetDivRemainder, std::move($node), std::move($next.node), getCurrentToken());
                    }
                )
            )*;

////////////////////////////////////////////////////////////////////////////////
// ����������� ���� -a. ���������� ����� "--a" �� ���������.
invert_expr
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
            pow_expr
                {
                    $node = std::move($pow_expr.node);
                }
            |(MINUS opt_WS pow_expr
                {
                    $node = m_semantics->GetOperationFactory().CreateUnaryOperation(fuura::language::UnaryOperation::Not, std::move($pow_expr.node), getCurrentToken());
                }
            );

////////////////////////////////////////////////////////////////////////////////
// ����������� ���� a ^ b, ��� ����� ��������� ����������.
pow_expr
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
            atom
                {
                    $node = std::move($atom.node);
                }
            (opt_WS CARET opt_WS next=atom
                {
                    $node = m_semantics->GetOperationFactory().CreateBinaryOperation(fuura::language::BinaryOperation::RaiseToPower, std::move($node), std::move($next.node), getCurrentToken());
                }
            )*;

////////////////////////////////////////////////////////////////////////////////
// ����������� �������� ���������� ����.
atom
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
              argument      { $node = std::move($argument.node);  }
            | const_any     { $node = std::move($const_any.node); }
            | if_expr       { $node = std::move($if_expr.node); }
            | BR_OP opt_WS full_expr opt_WS BR_CL { $node = std::move($full_expr.node); }
//            | function_call { $node = std::move($function_call.node); }
            ;

////////////////////////////////////////////////////////////////////////////////
// ��������, ������������ �����. ����� ���� ������ ����.
argument
    returns [std::unique_ptr<fuura::language::Argument> node]:
        ID
            {
                $node = std::make_unique<fuura::language::Argument>($text, m_semantics->GetArgumentSet(), getCurrentToken());
            };

////////////////////////////////////////////////////////////////////////////////
// ��������� ������, ������ ����.
const_any
    returns [std::unique_ptr<fuura::language::ICalculatable> node]:
          const_integer
            {
                $node = std::move($const_integer.node);
            }
        | const_double
            {
                $node = std::move($const_double.node);
            }
        | const_bool
            {
                $node = std::move($const_bool.node);
            };

////////////////////////////////////////////////////////////////////////////////
// ����� ���������.
const_integer
    returns [std::unique_ptr<fuura::language::Constant<int>> node]:
        ((MINUS opt_WS)? POSITIVE_INT)
            {
                $node = std::make_unique<fuura::language::Constant<int>>($text);
            };

////////////////////////////////////////////////////////////////////////////////
// ������������ ���������.
const_double
    returns [std::unique_ptr<fuura::language::Constant<double>> node]:
        ((MINUS opt_WS)? POSITIVE_FLOAT)
            {
                $node = std::make_unique<fuura::language::Constant<double>>($text);
            };

////////////////////////////////////////////////////////////////////////////////
// ������ ���������.
const_bool
    returns [std::unique_ptr<fuura::language::Constant<bool>> node]:
        (TRUE | FALSE)
            {
                $node = std::make_unique<fuura::language::Constant<bool>>($text);
            };

////////////////////////////////////////////////////////////////////////////////
// ���������� �������, ������� ����� ��� ����, ��� � ���.
opt_WS: WS | nothing;

////////////////////////////////////////////////////////////////////////////////
nothing:    ;

// ----------------- LEXER -----------------------------------------------------
// �� �� ��������� ������� ���������������.
fragment A: 'a' | 'A';
fragment B: 'b' | 'B';
fragment C: 'c' | 'C';
fragment D: 'd' | 'D';
fragment E: 'e' | 'E';
fragment F: 'f' | 'F';
fragment G: 'g' | 'G';
fragment H: 'h' | 'H';
fragment I: 'i' | 'I';
fragment J: 'j' | 'J';
fragment K: 'k' | 'K';
fragment L: 'l' | 'L';
fragment M: 'm' | 'M';
fragment N: 'n' | 'N';
fragment O: 'o' | 'O';
fragment P: 'p' | 'P';
fragment Q: 'q' | 'Q';
fragment R: 'r' | 'R';
fragment S: 's' | 'S';
fragment T: 't' | 'T';
fragment U: 'u' | 'U';
fragment V: 'v' | 'V';
fragment W: 'w' | 'W';
fragment X: 'x' | 'X';
fragment Y: 'y' | 'Y';
fragment Z: 'z' | 'Z';

IF:         I F;
ELSE:       E L S E;
AND:        A N D;
OR:         O R;
NOT:        N O T;
TRUE:       T R U E;
FALSE:      F A L S E;
DIV:        D I V;      // ������������� �������

ID:		([a-zA-Z] | '_') ([a-zA-Z] | '_' | [0-9])*;
POSITIVE_INT:	[0-9]+;
POSITIVE_FLOAT:	[0-9]+ DOT [0-9]+ (E (PLUS|MINUS)? [0-9]+)?;

SEMIC:      ';';    // ������������ ����� ���������
PLUS:       '+';
MINUS:      '-';
STAR:       '*';
SLASH:      '/';    // ������������ �������
PERCENT:    '%';    // ������� �� �������
CARET:      '^';    // ���������� � �������
DOT:        '.';    // ����������� ������� �����
COMMA:      ',';    // ����������� ���������� ������� ��� ������
EQUAL:      '=';    // �������� �� ���������, � �� ������������
NOT_EQUAL:  '!=';
GREATER:    '>';
LESS:       '<';
GREATER_EQ: '>=';
LESS_EQ:    '<=';

//QUOTE:      '"';

BR_OP: '(';
BR_CL: ')';

WS: [ \n\t\r]+;
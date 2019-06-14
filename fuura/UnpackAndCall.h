#pragma once
#include "Value.h"

namespace fuura::tools
{
	/**************************************************************************
		��������� ����� ������� �� ������� ���������� ��������� �����.
	**************************************************************************/

	// ------------------------------------------------------------------------
	template <int ArgCount, typename FunctionT> struct UnpackAndCall
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			static_assert(
				"��������� �������� ���� ������� ��� ������� ����� ����������"
				" ...��� �� ���������, ������ ��� ����� ���������� ��� ��� ������� �����."
			);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<0, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function();
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<1, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<2, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<3, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1], argValues[2]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<4, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1], argValues[2], argValues[3]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<5, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1], argValues[2], argValues[3], argValues[4]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<6, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1], argValues[2], argValues[3], argValues[4], argValues[5]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<7, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1], argValues[2], argValues[3], argValues[4], argValues[5], argValues[6]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<8, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1], argValues[2], argValues[3], argValues[4], argValues[5], argValues[6], argValues[7]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<9, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1], argValues[2], argValues[3], argValues[4], argValues[5], argValues[6], argValues[7], argValues[8]);
		}
	};

	// ------------------------------------------------------------------------
	template <typename FunctionT> struct UnpackAndCall<10, FunctionT>
	{
		static Value Do(FunctionT function, std::vector<Value>& argValues)
		{
			return function(argValues[0], argValues[1], argValues[2], argValues[3], argValues[4], argValues[5], argValues[6], argValues[7], argValues[8], argValues[9]);
		}
	};

	// ------------------------------------------------------------------------
}
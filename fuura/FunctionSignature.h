#pragma once
#include "Value.h"
#include "GetValueType.h"

namespace fuura::tools
{
	// ---------------------------------------------------------------------------
	// ������������ ������ ���������� � ���������� ��� ��������� � �������� N.
	// ��������� �������� � ����. �������� ������ FunctionSignature.
	// ---------------------------------------------------------------------------
	namespace
	{
		template <typename ...Args> struct ArgumentListTypeUnpacker;

		template <> struct ArgumentListTypeUnpacker<>
		{
			static fuura::ValueType GetType(size_t argumentIndex)
			{
				throw std::out_of_range("����� �� ������� ������ ���������� � tools::GetType().");
			}
		};

		template <typename This, typename ...Rest> struct ArgumentListTypeUnpacker<This, Rest...>
			: public ArgumentListTypeUnpacker<Rest...>
		{
			constexpr static fuura::ValueType GetType(size_t argumentIndex)
			{
				if (argumentIndex != 0)
					return ArgumentListTypeUnpacker<Rest...>::GetType(argumentIndex - 1);
				else
					return fuura::tools::GetValueType<This>();
			}
		};
	}

	///////////////////////////////////////////////////////////////////////////
	//
	//	������������ ��� ������� �� ��������� � ���������.
	//	-----------------------------------------------------------------------
	//	FunctionSignature<F>::Result				- ��� ���������� F.
	//	FunctionSignature<F>::ArgCount			- ���������� ���������� F.
	//	FunctionSignature<F>::GetArgumentType(2)	- �������� ��� ��������� F � �������� 2,
	//											�.�. ��������, ���� ������� � �������.
	///////////////////////////////////////////////////////////////////////////
	template <typename ...Args> struct FunctionSignature;

	template <typename ResultType, typename ...Args>
	struct FunctionSignature<ResultType(Args...)>
	{
		// ��� ���������� �������.
		using Result = ResultType;

		// ���������� ���������� �������.
		enum { ArgCount = sizeof ...(Args) };

		// �������� ��� ��������� ������� �� ��� ������. ��������� � 0.
		constexpr static fuura::ValueType GetArgumentType(size_t argumentIndex)
		{
			return ArgumentListTypeUnpacker<Args...>::GetType(argumentIndex);
		}
	};

	///////////////////////////////////////////////////////////////////////////
}
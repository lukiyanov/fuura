#pragma once

namespace fuura::tools
{
	/**************************************************************************
		���������� ��� �������� Args � ��� ������� ���������
		������� ���� Functor(int index, ValueType type).
	**************************************************************************/
	namespace
	{
		// --------------------------------------------------------------------
		template <int ArgCount, typename Functor, typename ...Args>
		struct ForEachImplementation;

		// --------------------------------------------------------------------
		// ����� ������.
		template <int ArgCount, typename Functor, typename This, typename ...Rest>
		struct ForEachImplementation<ArgCount, Functor, This, Rest...>
		{
			static void Iterate(Functor functor)
			{
				const auto type = tools::GetValueType<This>();
				const int currentIndex = ArgCount - sizeof ... (Rest) - 1;
				functor(currentIndex, type);

				ForEachImplementation<ArgCount, Functor, Rest...>::Iterate(functor);
			}
		};

		// --------------------------------------------------------------------
		// ��� ��������� ���������.
		template <int ArgCount, typename Functor>
		struct ForEachImplementation<ArgCount, Functor>
		{
			static void Iterate(Functor functor) {}
		};

		// --------------------------------------------------------------------
	}

	///////////////////////////////////////////////////////////////////////////
	//
	//	���������� ��� �������� Args � ��� ������� ��������� ������� ����
	//	Functor(int index, ValueType type).
	//
	///////////////////////////////////////////////////////////////////////////
	template <typename Functor, typename ...Args>
	struct ForEach
	{
		static void Do(Functor functor)
		{
			ForEachImplementation<sizeof ... (Args), Functor, Args...>::Iterate(functor);
		}
	};
}
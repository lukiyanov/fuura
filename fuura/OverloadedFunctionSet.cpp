#include "stdafx.h"
#include "ToString.h"
#include "OverloadedFunctionSet.h"
#include <algorithm>
using namespace std;
using namespace fuura::language;

// ----------------------------------------------------------------------------
// Проверяет, совпадают ли типы аргументов функций.
// Никак не проверяет возвращаемое значение.
// ----------------------------------------------------------------------------
bool HaveTheSameArgTypes(IFunctionWrapper& func1, IFunctionWrapper& func2)
{
	return func1.GetArgumentTypes() == func2.GetArgumentTypes();
}

// ----------------------------------------------------------------------------
void FunctionSetWithFixedArgumentCount::Insert(unique_ptr<IFunctionWrapper> function)
{
	// Ищем точное совпадение сигнатуры (кроме имени, которого мы не знаем).
	for (auto iter = m_functions.begin(), end = m_functions.end(); iter != end; ++iter)
	{
		if (HaveTheSameArgTypes(*function, **iter))
		{
			// Если нашли - генерируем исключение.
			string message = "Функция с такими аргументами уже есть в контейнере: " + FunctionToString(function.get());
			throw std::exception(message.c_str());
		}
	}

	// Не нашли - добавляем.
	m_functions.push_back(move(function));
}

// ----------------------------------------------------------------------------
void OverloadedFunctionSet::Insert(unique_ptr<IFunctionWrapper> function)
{
	auto argCount = function->GetArgumentCount();
	auto iter = m_functions.find(argCount);
	if (iter != m_functions.end())
	{
		// Блок функций с таким числом аргументов уже существует -> добавляем и выходим.
		iter->second.Insert(move(function));
		return;
	}

	// Блок функций с таким числом аргументов не существует -> создаём и сразу же добавляем.
	pair<int, FunctionSetWithFixedArgumentCount> pair;
	pair.first = argCount;
	pair.second.Insert(move(function));
	m_functions.insert(move(pair));
}

// ----------------------------------------------------------------------------
FunctionSetWithFixedArgumentCount * OverloadedFunctionSet::Find(size_t argCount)
{
	auto iter = m_functions.find(argCount);
	if (iter == m_functions.end())
		return nullptr;
	return &iter->second;
}

// ----------------------------------------------------------------------------

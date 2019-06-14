#include "stdafx.h"
#include "FunctionRegistry.h"
#include "Exception.h"
#include "ToString.h"
#include "FuuraSemantics.h"
#include "FunctionCall.h"
using namespace fuura;
using namespace fuura::language;
using namespace std;

// ----------------------------------------------------------------------------
namespace fuura::language
{
	// ------------------------------------------------------------------------
	// Возвращает строку вида: "имя(тип1, тип2, тип3)"
	// ------------------------------------------------------------------------
	string FunctionToString(list<unique_ptr<ICalculatable>>& argTypes, string_view name = "")
	{
		std::string str = name.data();
		str += '(';
		if (argTypes.size())
		{
			auto iter = argTypes.begin();
			str += tools::ToString((*iter)->GetType());
			++iter;
			for (auto end = argTypes.end(); iter != end; ++iter)
				str += ", " + tools::ToString((*iter)->GetType());
		}
		str += ')';
		return str;
	}
}

// ----------------------------------------------------------------------------
// Возвращает степень соответствия аргументов функции wrapper аргументам,
// переданным через args с учётом возможных преобразований типов,
// определяемых в typeCastFactory.
// ----------------------------------------------------------------------------
MatchState CalculateMatchState(IFunctionWrapper& wrapper, list<unique_ptr<ICalculatable>>& argTypes, TypeCastFactory& typeCastFactory)
{
	auto currentFuncArgs = wrapper.GetArgumentTypes();
	auto matchState = MatchState::FullMatch;
	auto originalArgsIter = argTypes.begin();
	for (size_t argNum = 0, argCount = argTypes.size(); argNum < argCount; ++argNum, ++originalArgsIter)
	{
		const ValueType expected = currentFuncArgs[argNum];
		const ValueType actual = (*originalArgsIter)->GetType();
		// Если на некотором аргументе типы не совпадают...
		if (expected != actual)
		{
			// Пытаемся найти преобразование из имеющегося типа к нужному...
			if (typeCastFactory.TypeCastExists(actual, expected))
			{
				// Если оно есть, то устанавливаем что функция пригодна, но требуется приведение типов.
				matchState = MatchState::MatchWithCast;
			}
			else
			{
				// Если преобразорвания нет, то устанавливаем что данная функция не подходит полностью.
				// И сразу же переходим к следующему варианту.
				matchState = MatchState::Mismatch;
				break;
			}
		}
	}

	return matchState;
}

// ----------------------------------------------------------------------------
// Добавляем к аргументам в args преобразования до типов types, пользуясь правилами преобразования из semantics.
// ----------------------------------------------------------------------------
void CastArgsTo(list<unique_ptr<ICalculatable>>& args, vector<ValueType>&& types, FuuraSemantics& semantics)
{
	auto& typeCastFactory = semantics.GetImplicitTypeCastFactory();

	auto argument = args.begin();
	for (auto type = types.begin(), end = types.end(); type != end; ++type, ++argument)
	{
		if ((*argument)->GetType() != *type)
			*argument = typeCastFactory.CreateTypeCast(move(*argument), *type);
	}
}

// ----------------------------------------------------------------------------
// Как происходит поиск подходящей функции:
//	1. Если функция с таким именем не найдена, генерируем исключение
//	2. Отбираем реализации с совпадающим числом аргументов
//	3. Если таких нет, генерируем исключение
//	4. Среди них ищем функцию с точным совпадением аргументов
//	5. Если нашли - возвращаем её
//	6. Ищем реализацию, типы аргументов которой можно получить из имеющихся приведением аргументов
//	7. Если таких несколько, генерируем исключение
//	8. Если таких нет, генерируем исключение
//	9. Возвращаем найденную реализацию
// --------------------------------------------------------------------
pair<MatchState, unique_ptr<IFunctionWrapper>> FunctionRegistry::FindFunction(string_view name, list<unique_ptr<ICalculatable>>& args, FuuraSemantics& semantics, antlr4::Token * tokenInfo)
{
	const auto nameLower = tools::ToLower(name);
	auto iter = m_functions.find(nameLower);

	// 1. Если функция с таким именем не найдена, генерируем исключение
	if (iter == m_functions.end())
	{
		throw SyntaxError(string("Функция с именем \"") + nameLower + "\" не найдена.",
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
	}

	// 2. Отбираем реализации с совпадающим числом аргументов
	const auto argCount = args.size();
	auto funcsFixed = iter->second.Find(argCount);

	//	3. Если таких нет, генерируем исключение
	if (!funcsFixed)
	{
		throw SyntaxError(string("Для функции с именем \"") + nameLower + "\" нет перегруженной реализации, принимающей " + tools::ToString(argCount) + " аргументов.",
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
	}
	
	//	4. Среди них ищем точное совпадение аргументов
	// (и заодно попутно ищем все подходящие варианты чтобы не просматривать массив дважды)
	auto& typeCastFactory = semantics.GetImplicitTypeCastFactory();

	// Используются если точное соответствие не найдено:
	IFunctionWrapper* matchWithCastWrapper = nullptr;		// Первый из вариантов, к которому можно привести аргументы
	bool notMonosemanticError = false;						// Существует 2 или более вариантов, к каждому из которых можно привести аргументы

	for (auto ppWrapper = funcsFixed->Begin(), end = funcsFixed->End(); ppWrapper != end; ++ppWrapper)
	{
		// Текущая функция.
		IFunctionWrapper& wrapper = **ppWrapper;

		// Определяем степень совпадения текущей функции реально существующим аргументам.
		auto matchState = CalculateMatchState(wrapper, args, typeCastFactory);

		// 5. Если нашли функцию с точным совпадением - возвращаем её копию.
		if (matchState == MatchState::FullMatch)
			return pair(MatchState::FullMatch, unique_ptr<IFunctionWrapper>(wrapper.Clone()));

		//	6. Ищем реализацию, типы аргументов которой можно получить из имеющихся приведением аргументов
		// При первом подходящем варианте, к которому можно привести, этот вариант запоминается.
		// При втором - устанавливается флаг неоднозначности, но ошибка пока не генерируется в надежде
		// найти далее точное соответствие аргументов.
		if (matchState == MatchState::MatchWithCast)
		{
			if (!matchWithCastWrapper)
				matchWithCastWrapper = &wrapper;
			else
				notMonosemanticError = true;
		}
	}

	// Прербраны все варианты. Точного соответствия не найдено.

	//	7. Если таких к которым можно привести преобразованиями аргументов несколько, генерируем исключение.
	if (notMonosemanticError)
	{
		throw SyntaxError(string("Неоднозначный вызов: ") + FunctionToString(args, name),
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
	}

	//	8. Если таких к которым можно привести преобразованиями аргументов нет вообще, генерируем исключение.
	if (!matchWithCastWrapper)
	{
		throw SyntaxError(string("Нет реализаций функции \"") + nameLower + "\", совместимой с вызовом: " + FunctionToString(args, name),
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
	}

	//	9. Возвращаем найденную реализацию
	return pair(MatchState::MatchWithCast, unique_ptr<IFunctionWrapper>(matchWithCastWrapper->Clone()));
}

// ----------------------------------------------------------------------------
unique_ptr<ICalculatable> FunctionRegistry::CreateFunction(string_view name, list<unique_ptr<ICalculatable>>& args, FuuraSemantics& semantics, antlr4::Token * tokenInfo)
{
	auto [match, func] = FindFunction(name, args, semantics, tokenInfo);
	if (match == MatchState::MatchWithCast)
		CastArgsTo(args, func->GetArgumentTypes(), semantics);
	return make_unique<FunctionCall>(move(func), args);
}

// ----------------------------------------------------------------------------

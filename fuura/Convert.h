#pragma once
#include <string>
#include <algorithm>

namespace fuura::tools
{
	// ---------------------------------------------------------------------------
	// ѕреобразует строку в нижний регистр
	// ---------------------------------------------------------------------------
	inline std::string ToLower(std::string_view str)
	{
		std::string result = str.data();
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		return std::move(result);
	}

	// ---------------------------------------------------------------------------
	// ѕреобразует строку к указанному типу.
	// ---------------------------------------------------------------------------
	template <typename T> T StrToType(const std::string& source);

	// ---------------------------------------------------------------------------
	template <> inline int StrToType(const std::string& source)
	{
		return std::stoi(source);
	}

	// ---------------------------------------------------------------------------
	template <> inline double StrToType(const std::string& source)
	{
		return std::stod(source);
	}

	// ---------------------------------------------------------------------------
	template <> inline bool StrToType(const std::string& source)
	{
		auto lower = ToLower(source);
		if (lower == "true")
			return true;
		if (lower == "false")
			return false;
		
		throw std::exception("Invalid bool constant.");
	}

	// ---------------------------------------------------------------------------
}
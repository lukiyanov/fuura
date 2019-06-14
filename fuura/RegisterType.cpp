#include "stdafx.h"
#include "RegisterType.h"
using namespace fuura::compilation;

const RegisterType RegisterType::Byte        { RegisterType::RegisterTypeEnum::Byte };
const RegisterType RegisterType::Word        { RegisterType::RegisterTypeEnum::Word };
const RegisterType RegisterType::DoubleWord  { RegisterType::RegisterTypeEnum::DoubleWord };
const RegisterType RegisterType::Float       { RegisterType::RegisterTypeEnum::Float };
const RegisterType RegisterType::DoubleFloat { RegisterType::RegisterTypeEnum::DoubleFloat };

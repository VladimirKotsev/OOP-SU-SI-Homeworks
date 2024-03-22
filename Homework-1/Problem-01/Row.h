#pragma once
#include "GlobalConstants.h"
#include "Field.h"

struct Row
{
	Field fields[GlobalConstants::MAX_FIELD_COUNT];
};
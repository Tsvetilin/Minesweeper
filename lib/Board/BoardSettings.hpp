#pragma once

#include "../Common/Common.hpp"
#include "../Common/Serializable.hpp"
#include "BoardSymbols.hpp"

enum class BoardLook {
	Default = 0,
	Fancy = 1,
};

enum class UncoverType {
	Default = 0, // As in original game
	Custom = 1,  // Uncover just the surrounding 8 
};

enum class ControlType {
	PrimitiveInput = 0,
	AdvancedArrowInput = 1,
};

struct Settings : public Serializable {
	BoardSize size;												// Board size
	BoardSymbols symbols;										// Board style
	UncoverType uncoverType = UncoverType::Default;				// Default / custom uncover
	ControlType controlType = ControlType::AdvancedArrowInput;	// Arrow / Input controls
	BoardLook boardLook = BoardLook::Default;				    // Fancy / default board look
};


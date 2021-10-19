// Copyright 2019 Berran Remzi

#include "AnalogButton.h"

AnalogButtonConfig_t* p_buttonConfig;

void AnalogButton_Init(AnalogButtonConfig_t* _config) {
	p_buttonConfig = _config;
}

static uint8_t AnalogButton_Compute(uint16_t _new_sample) {
	uint8_t _temp_command = 0;
	uint16_t abs_difference = abs(_new_sample - p_buttonConfig->p_analogButton[0]);

	for (uint8_t position = 0; position <= p_buttonConfig->count; position++) {
		if (abs_difference > abs(_new_sample - p_buttonConfig->p_analogButton[position])) {
			abs_difference = abs(_new_sample - p_buttonConfig->p_analogButton[position]);
			_temp_command = position;
		}
	}

	return _temp_command;
}

 uint8_t AnalogButton_IsPressed(void) {
	return AnalogButton_IsPressedMoreThan(0u);
}

 uint8_t AnalogButton_IsSinglePressed(void) {
	return (p_buttonConfig->button_press_counter == 1u);
}

 uint8_t AnalogButton_IsPressedMoreThan(uint16_t _more_than) {
	return (p_buttonConfig->button_press_counter > _more_than);
}

 uint8_t AnalogButton_IsPressedLessThan(uint16_t _less_than) {
	return (p_buttonConfig->button_press_counter < _less_than);
}

uint8_t AnalogButton_IsPressedBetween(uint16_t _more_than, uint16_t _less_than) {
	return ((AnalogButton_IsPressedMoreThan(_more_than)) && (AnalogButton_IsPressedLessThan(_less_than)));
}

void AnalogButton_LoadSample(uint16_t _new_sample) {
	uint8_t _new_command = AnalogButton_Compute(_new_sample);

	if (p_buttonConfig->last_valid_command == _new_command) {
		p_buttonConfig->button_press_counter++;
	}
	else {
		p_buttonConfig->button_press_counter = 0u;
	}

	p_buttonConfig->last_valid_command = _new_command;

	if (p_buttonConfig->button_press_counter > 0u) {
		p_buttonConfig->valid_command = _new_command;
	}
	else {
		p_buttonConfig->valid_command = 0u;
	}
}

uint8_t AnalogButton_ReadCommand(void) {
	return p_buttonConfig->last_valid_command;
}

Button_State_t Button_StateGet(uint8_t _button)
{
	Button_State_t returnValue = BUTTON_STATE_NOT_PRESSED;

	for (uint8_t i = 0; i < p_buttonConfig->count; i++) {
		if (p_buttonConfig->last_valid_command == _button) {
			returnValue = BUTTON_STATE_PRESSED;
		}
	}

	return returnValue;
}

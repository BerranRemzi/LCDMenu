// Copyright 2019 Berran Remzi
/**
 * @file AnalogButton.h
 * @brief this header file will contain all required
 * definitions and basic utilities functions.
 *
 * @author Berran Remzi
 *
 * @date 29.08.2020
 */
#ifndef ANALOG_BUTTON_H_
#define ANALOG_BUTTON_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/

	
/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * Button_State_t defines the possible states that a button may be in.  
 * Additional button states can be added to this enumeration.  Button_State_t
 * also defines a maximum value that can be used for boundary checking.
 */
typedef enum Button_State_t
{
   BUTTON_STATE_NOT_PRESSED,	/**< The not pressed electrical state */
   BUTTON_STATE_PRESSED,		/**< The pressed electrical state */
   BUTTON_STATE_MAX				/**< Maximum number of button states */
}Button_State_t;

/**
 * Defines the configuration data required to initialize the AnalogButton API.
 */
typedef struct AnalogButtonConfig_t
{
	const uint16_t* p_analogButton;
	const uint8_t count;
	uint8_t last_valid_command;
	uint8_t valid_command;
	uint16_t button_press_counter;
}AnalogButtonConfig_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

	void AnalogButton_Init(AnalogButtonConfig_t* _config);
	static uint8_t AnalogButton_Compute(uint16_t _new_sample);
	 uint8_t AnalogButton_IsPressed(void);
	 uint8_t AnalogButton_IsSinglePressed(void);
	 uint8_t AnalogButton_IsPressedMoreThan(uint16_t _more_than);
	 uint8_t AnalogButton_IsPressedLessThan(uint16_t _less_than);
	uint8_t AnalogButton_IsPressedBetween(
		uint16_t _more_than,
		uint16_t _less_than);
	void AnalogButton_LoadSample(uint16_t _new_sample);
	uint8_t AnalogButton_ReadCommand(void);
	Button_State_t Button_StateGet(uint8_t _button); /* Button_t Button */

#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif

#endif  /* ANALOG_BUTTON_H_ */

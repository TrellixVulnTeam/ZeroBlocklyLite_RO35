'use strict';

goog.provide('Blockly.Arduino.ZeroWorkshop_math');

goog.require('Blockly.Arduino');

Blockly.Arduino.define_macro = function() {
	var argument0 = Blockly.Arduino.valueToCode(this, 'MacroValue',Blockly.Arduino.ORDER_ATOMIC);
	var argument1 = (this.getFieldValue('MACRO'));

	//var argument2 = Blockly.Arduino.variableDB_.getName(block.getFieldValue('VAR11'), Blockly.Variables.NAME_TYPE);
	//Blockly.Arduino.variableDB_.getName(variables[x],Blockly.Variables.NAME_TYPE) + ';\n';

	Blockly.Arduino.definitions_['define_macro'+argument1] = '#define    ' + argument1 + "    " + argument0;

    //var code = 'xxxxxxxxxxxx;' + argument1 + ';\n';

    //return [code, Blockly.Arduino.ORDER_ATOMIC];
}

Blockly.Arduino.pin_definition = function() {
	var dropdown_pinname = this.getFieldValue('PinName');
    var dropdown_pintype = this.getFieldValue('PinType');
	
    if (dropdown_pintype == 'OUTPUT') {
        Blockly.Arduino.setups_['setup_output_'+dropdown_pinname] = 'pinMode('+dropdown_pinname+', OUTPUT);';
    }
    else if (dropdown_pintype == 'INPUT') {
        Blockly.Arduino.setups_['setup_input_'+dropdown_pinname] = 'pinMode('+dropdown_pinname+', INPUT);';
    }
    else if (dropdown_pintype == 'SERVO')  {
		Blockly.Arduino.definitions_['var_servo'+dropdown_pinname] = 'Servo servo_'+dropdown_pinname+';';
        Blockly.Arduino.setups_['setup_servo_'+dropdown_pinname] = 'servo_'+dropdown_pinname+'.attach('+dropdown_pinname+');';
    }


}


Blockly.Arduino.led = function() {
  var dropdown_pinname = this.getFieldValue('PinName');
  var dropdown_on_or_off = this.getFieldValue('on_or_off');

  var code;

    if (dropdown_on_or_off == 'led_on') {
        code = 'digitalWrite('+dropdown_pinname+','+'HIGH);\n'
    }
    else if (dropdown_on_or_off == 'led_off') {
        code = 'digitalWrite('+dropdown_pinname+','+'LOW);\n'
    }

return code;

}
Blockly.Arduino.math_number = function() {
  // Numeric value.
  var code = (this.getFieldValue('NUM'));
  // -4.abs() returns -4 in Dart due to strange order of operation choices.
  // -4 is actually an operator and a number.  Reflect this in the order.
  var order = code < 0 ?
      Blockly.Arduino.ORDER_UNARY_PREFIX : Blockly.Arduino.ORDER_ATOMIC;
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.math_number_t5 = function() {
  // Numeric value.
  var code = (this.getFieldValue('NUM'));
  // -4.abs() returns -4 in Dart due to strange order of operation choices.
  // -4 is actually an operator and a number.  Reflect this in the order.
  var order = code < 0 ?
      Blockly.Arduino.ORDER_UNARY_PREFIX : Blockly.Arduino.ORDER_ATOMIC;
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.math_arithmetic = function() {
  // Basic arithmetic operators, and power.
  var mode = this.getFieldValue('OP');
  var tuple = Blockly.Arduino.math_arithmetic.OPERATORS[mode];
  var operator = tuple[0];
  var order = tuple[1];
  var argument0 = Blockly.Arduino.valueToCode(this, 'A', order) || '0';
  var argument1 = Blockly.Arduino.valueToCode(this, 'B', order) || '0';
  var code;
  if (!operator) {
    code = 'pow(' + argument0 + ', ' + argument1 + ')';
    return [code, Blockly.Arduino.ORDER_UNARY_POSTFIX];
  }
  if(operator==' % '){
    //取余必须是整数
    argument0='(long) ('+argument0+')';
	argument1='(long) ('+argument1+')';
  }
  code = argument0 + operator + argument1;
  return [code, order];
};

Blockly.Arduino.math_bit = function() {
  var operator = this.getFieldValue('OP');;
  var order = Blockly.Arduino.ORDER_ATOMIC;
  var argument0 = Blockly.Arduino.valueToCode(this, 'A', order) || '0';
  var argument1 = Blockly.Arduino.valueToCode(this, 'B', order) || '0';
  var code = '('+argument0 + operator + argument1+')';
  return [code, order];
};

Blockly.Arduino.math_arithmetic.OPERATORS = {
  ADD: [' + ', Blockly.Arduino.ORDER_ADDITIVE],
  MINUS: [' - ', Blockly.Arduino.ORDER_ADDITIVE],
  MULTIPLY: [' * ', Blockly.Arduino.ORDER_MULTIPLICATIVE],
  DIVIDE: [' / ', Blockly.Arduino.ORDER_MULTIPLICATIVE],
  QUYU: [' % ', Blockly.Arduino.ORDER_MULTIPLICATIVE],//增加取余操作
  POWER: [null, Blockly.Arduino.ORDER_NONE]  // Handle power separately.
};

Blockly.Arduino.math_single = function() {
  // Math operators with single operand.
  var operator = this.getFieldValue('OP');
  var code;
  var arg;
  if (operator == 'NEG') {
    // Negation is a special case given its different operator precedents.
    arg = Blockly.Arduino.valueToCode(this, 'NUM',
        Blockly.Arduino.ORDER_UNARY_PREFIX) || '0';
    if (arg[0] == '-') {
      // --3 is not legal in Dart.
      arg = ' ' + arg;
    }
    code = '-' + arg;
    return [code, Blockly.Arduino.ORDER_UNARY_PREFIX];
  }
  if (operator == 'ABS' || operator.substring(0, 5) == 'ROUND') {
    arg = Blockly.Arduino.valueToCode(this, 'NUM',
        Blockly.Arduino.ORDER_UNARY_POSTFIX) || '0';
  } else if (operator == 'SIN' || operator == 'COS' || operator == 'TAN') {
    arg = Blockly.Arduino.valueToCode(this, 'NUM',
        Blockly.Arduino.ORDER_MULTIPLICATIVE) || '0';
  } else {
    arg = Blockly.Arduino.valueToCode(this, 'NUM',
        Blockly.Arduino.ORDER_NONE) || '0';
  }
  // First, handle cases which generate values that don't need parentheses.
  switch (operator) {
    case 'ABS':
      code = arg + '.abs()';
      break;
    case 'ROOT':
      code = 'Math.sqrt(' + arg + ')';
      break;
    case 'LN':
      code = 'Math.log(' + arg + ')';
      break;
    case 'EXP':
      code = 'Math.exp(' + arg + ')';
      break;
    case 'POW10':
      code = 'Math.pow(10,' + arg + ')';
      break;
    case 'ROUND':
      code = arg + '.round()';
      break;
    case 'ROUNDUP':
      code = arg + '.ceil()';
      break;
    case 'ROUNDDOWN':
      code = arg + '.floor()';
      break;
    case 'SIN':
      code = 'sin(' + arg + ' / 180.0 * 3.14159)';
      break;
    case 'COS':
      code = 'cos(' + arg + ' / 180.0 * 3.14159)';
      break;
    case 'TAN':
      code = 'tan(' + arg + ' / 180.0 * 3.14159)';
      break;
  }
  if (code) {
    return [code, Blockly.Arduino.ORDER_UNARY_POSTFIX];
  }
  // Second, handle cases which generate values that may need parentheses.
  switch (operator) {
    case 'LOG10':
      code = 'Math.log(' + arg + ') / Math.log(10)';
      break;
    case 'ASIN':
      code = 'asin(' + arg + ') / 3.14159 * 180';
      break;
    case 'ACOS':
      code = 'acos(' + arg + ') / 3.14159 * 180';
      break;
    case 'ATAN':
      code = 'atan(' + arg + ') / 3.14159 * 180';
      break;
    default:
      throw 'Unknown math operator: ' + operator;
  }
  return [code, Blockly.Arduino.ORDER_MULTIPLICATIVE];
};

Blockly.Arduino.math_trig = Blockly.Arduino.math_single;

Blockly.Arduino.math_to_int = function() {
  var argument0 = Blockly.Arduino.valueToCode(this, 'A',Blockly.Arduino.ORDER_NONE) || '0';
  var operator = this.getFieldValue('OP');
  var code=operator+'('+argument0+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.math_max_min = function() {
  var a = Blockly.Arduino.valueToCode(this, 'A',Blockly.Arduino.ORDER_NONE) || '0';
  var b = Blockly.Arduino.valueToCode(this, 'B',Blockly.Arduino.ORDER_NONE) || '0';
  var operator = this.getFieldValue('OP');
  var code=operator+'('+a+', '+b+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.math_random_int = function() {
  // Random integer between [X] and [Y].
  var argument0 = Blockly.Arduino.valueToCode(this, 'FROM',
      Blockly.Arduino.ORDER_NONE) || '0';
  var argument1 = Blockly.Arduino.valueToCode(this, 'TO',
      Blockly.Arduino.ORDER_NONE) || '0';
  var code = 'random(' + argument0 + ', ' + argument1 + ')';
  return [code, Blockly.Arduino.ORDER_UNARY_POSTFIX];
};

Blockly.Arduino.base_map = function() {
  var value_num = Blockly.Arduino.valueToCode(this, 'NUM', Blockly.Arduino.ORDER_NONE);
  var value_fl = Blockly.Arduino.valueToCode(this, 'fromLow', Blockly.Arduino.ORDER_ATOMIC);
  var value_fh = Blockly.Arduino.valueToCode(this, 'fromHigh', Blockly.Arduino.ORDER_ATOMIC);
  var value_tl = Blockly.Arduino.valueToCode(this, 'toLow', Blockly.Arduino.ORDER_ATOMIC);
  var value_th = Blockly.Arduino.valueToCode(this, 'toHigh', Blockly.Arduino.ORDER_ATOMIC);
  var code = 'map('+value_num+', '+value_fl+', '+value_fh+', '+value_tl+', '+value_th+')';
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino.math_constrain = function() {
  // Constrain a number between two limits.
  var argument0 = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_NONE) || '0';
  var argument1 = Blockly.Arduino.valueToCode(this, 'LOW',
      Blockly.Arduino.ORDER_NONE) || '0';
  var argument2 = Blockly.Arduino.valueToCode(this, 'HIGH',
      Blockly.Arduino.ORDER_NONE) || '0';
  var code = 'constrain(' + argument0 + ', ' + argument1 + ', ' +
	    argument2 + ')';
  return [code, Blockly.Arduino.ORDER_UNARY_POSTFIX];
};
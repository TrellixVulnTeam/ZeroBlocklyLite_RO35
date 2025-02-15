'use strict';

goog.provide('Blockly.Blocks.Zeroworkshop_math');

goog.require('Blockly.Blocks');


Blockly.Blocks.math.HUE = 230;
Blockly.Blocks.Zeroworkshop_math.HUE = 230;

Blockly.FieldTextInput.math_number_validator = function(text) {
  //return window.isNaN(text) ? null : String(text);
  return String(text);//不再校验
};



Blockly.Blocks['define_macro'] = {
  init: function() {
	this.setColour(Blockly.Blocks.math.HUE);
    this.appendValueInput("MacroValue")
        .setCheck(null)
        .appendField("define")
        .appendField(new Blockly.FieldTextInput("MacroName"), "MACRO")
        .appendField("as");
    this.setInputsInline(true);

    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};

Blockly.Blocks['pin_definition'] = {
  init: function() {
	this.setColour(Blockly.Blocks.math.HUE);
    this.appendDummyInput()
        .appendField("define")
        .appendField(new Blockly.FieldDropdown([["Speaker", "SP"],["Motor1+", "MOTOR1P"],["Motor2+", "MOTOR2P"],["Motor1-", "MOTOR1M"],["Motor2-", "MOTOR2M"],["A1", "ZW_A1"], ["A2", "ZW_A2"], ["A3", "ZW_A3"], ["A4", "ZW_A4"], ["B1", "ZW_B1"], ["B2", "ZW_B2"], ["B3", "ZW_B3"], ["B4", "ZW_B4"]]), "PinName")
        .appendField("as")
        .appendField(new Blockly.FieldDropdown([["input", "INPUT"], ["output", "OUTPUT"], ["servo", "SERVO"]]), "PinType");
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};


Blockly.Blocks['led'] = {
  init: function() {
  	//var = image_used;
    this.appendDummyInput()
        .appendField(new Blockly.FieldImage("../../media/ZeroWorkshop/playnote.jpg", 150, 100, "Stop停止"))
        .appendField("LED")
        .appendField(new Blockly.FieldDropdown([["B1", "ZW_B1"], ["B2", "ZW_B2"], ["B3", "ZW_B3"], ["B4", "ZW_B4"], ["A1", "ZW_A1"], ["A2", "ZW_A2"], ["A3", "ZW_A3"], ["A4", "ZW_A4"]]), "PinName")
        .appendField(new Blockly.FieldDropdown([["ON", "led_on"], ["OFF", "led_off"]]), "on_or_off");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(120);
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};

Blockly.Blocks['math_number'] = {
  /**
   * Block for numeric value.
   * @this Blockly.Block
   */
  init: function() {
    this.setColour("#DBB9EA");
    this.appendDummyInput()
        .appendField(new Blockly.FieldTextInput('0',
        Blockly.FieldTextInput.math_number_validator), 'NUM');
    this.setOutput(true, Number);
    this.setTooltip(Blockly.Msg.MATH_NUMBER_TOOLTIP);
  }
};

Blockly.Blocks['math_arithmetic'] = {
  /**
   * Block for basic arithmetic operator.
   * @this Blockly.Block
   */
  init: function() {
    var OPERATORS =
        [[Blockly.Msg.MATH_ADDITION_SYMBOL, 'ADD'],
         [Blockly.Msg.MATH_SUBTRACTION_SYMBOL, 'MINUS'],
         [Blockly.Msg.MATH_MULTIPLICATION_SYMBOL, 'MULTIPLY'],
         [Blockly.Msg.MATH_DIVISION_SYMBOL, 'DIVIDE'],
		 [Blockly.Msg.MATH_QUYU_SYMBOL, 'QUYU'],
         [Blockly.Msg.MATH_POWER_SYMBOL, 'POWER']];
    //this.setHelpUrl(Blockly.Msg.MATH_ARITHMETIC_HELPURL);
    this.setColour(Blockly.Blocks.math.HUE);
    this.setOutput(true, Number);
    this.appendValueInput('A')
        .setCheck(Number);
    this.appendValueInput('B')
        .setCheck(Number)
        .appendField(new Blockly.FieldDropdown(OPERATORS), 'OP');
    this.setInputsInline(true);
    // Assign 'this' to a variable for use in the tooltip closure below.
    var thisBlock = this;
    this.setTooltip(function() {
      var mode = thisBlock.getFieldValue('OP');
      var TOOLTIPS = {
        'ADD': Blockly.Msg.MATH_ARITHMETIC_TOOLTIP_ADD,
        'MINUS': Blockly.Msg.MATH_ARITHMETIC_TOOLTIP_MINUS,
        'MULTIPLY': Blockly.Msg.MATH_ARITHMETIC_TOOLTIP_MULTIPLY,
        'DIVIDE': Blockly.Msg.MATH_ARITHMETIC_TOOLTIP_DIVIDE,
		'QUYU':Blockly.Msg.MATH_MODULO_TOOLTIP,
        'POWER': Blockly.Msg.MATH_ARITHMETIC_TOOLTIP_POWER
      };
      return TOOLTIPS[mode];
    });
  }
};

Blockly.Blocks['math_bit'] = {
  init: function() {
    var OPERATORS =
        [['&', '&'],
         ['|', '|'],
        ['>>', '>>'],
        ['<<', '<<']];
    this.setColour(Blockly.Blocks.math.HUE);
    this.setOutput(true, Number);
    this.appendValueInput('A')
        .setCheck(Number);
    this.appendValueInput('B')
        .setCheck(Number)
        .appendField(new Blockly.FieldDropdown(OPERATORS), 'OP');
    this.setInputsInline(true);
	this.setTooltip("位运算");
  }
};

Blockly.Blocks['math_trig'] = {
  /**
   * Block for trigonometry operators.
   * @this Blockly.Block
   */
  init: function() {
    var OPERATORS =
        [[Blockly.Msg.MATH_TRIG_SIN, 'SIN'],
         [Blockly.Msg.MATH_TRIG_COS, 'COS'],
         [Blockly.Msg.MATH_TRIG_TAN, 'TAN'],
         [Blockly.Msg.MATH_TRIG_ASIN, 'ASIN'],
         [Blockly.Msg.MATH_TRIG_ACOS, 'ACOS'],
         [Blockly.Msg.MATH_TRIG_ATAN, 'ATAN']];
    //this.setHelpUrl(Blockly.Msg.MATH_TRIG_HELPURL);
    this.setColour(Blockly.Blocks.math.HUE);
    this.setOutput(true, Number);
    this.appendValueInput('NUM')
        .setCheck(Number)
        .appendField(new Blockly.FieldDropdown(OPERATORS), 'OP');
    // Assign 'this' to a variable for use in the tooltip closure below.
    var thisBlock = this;
    this.setTooltip(function() {
      var mode = thisBlock.getFieldValue('OP');
      var TOOLTIPS = {
        'SIN': Blockly.Msg.MATH_TRIG_TOOLTIP_SIN,
        'COS': Blockly.Msg.MATH_TRIG_TOOLTIP_COS,
        'TAN': Blockly.Msg.MATH_TRIG_TOOLTIP_TAN,
        'ASIN': Blockly.Msg.MATH_TRIG_TOOLTIP_ASIN,
        'ACOS': Blockly.Msg.MATH_TRIG_TOOLTIP_ACOS,
        'ATAN': Blockly.Msg.MATH_TRIG_TOOLTIP_ATAN
      };
      return TOOLTIPS[mode];
    });
  }
};

//取整等
Blockly.Blocks['math_to_int']= {
  init: function() {
	var OPERATORS =
        [[Blockly.LANG_MATH_TO_INT, 'int'],
		 [Blockly.Msg.MATH_ABS, 'abs'],
         [Blockly.Msg.MATH_SQ, 'sq'],
         [Blockly.Msg.MATH_SQRT, 'sqrt'],
		 [Blockly.Msg.MATH_LOG, 'log']];
    this.setColour(Blockly.Blocks.math.HUE);
    this.appendValueInput('A')
        .setCheck(Number)
        .appendField(new Blockly.FieldDropdown(OPERATORS), 'OP');
    this.setOutput(true, Number);
	var thisBlock = this;
    this.setTooltip(function() {
      var mode = thisBlock.getFieldValue('OP');
      var TOOLTIPS = {
        'sqrt': Blockly.Msg.MATH_SINGLE_TOOLTIP_ROOT,
        'abs': Blockly.Msg.MATH_SINGLE_TOOLTIP_ABS,
        'sq': Blockly.Msg.MATH_SINGLE_TOOLTIP_SQ,
        'log': Blockly.Msg.MATH_SINGLE_TOOLTIP_LN,
        'int': Blockly.Msg.MATH_SINGLE_TOOLTIP_TOINT
      };
      return TOOLTIPS[mode];
    });
  }
};
//最大最小值
Blockly.Blocks['math_max_min']= {
  init: function() {
	var OPERATORS =
        [[Blockly.MIXLY_MAX, 'max'],
		 [Blockly.MIXLY_MIN, 'min'],
        ];
    this.setColour(Blockly.Blocks.math.HUE);
    this.appendValueInput('A')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(new Blockly.FieldDropdown(OPERATORS), 'OP')
		.appendField('(');
	this.appendValueInput('B')
        .setCheck(Number)
		.setAlign(Blockly.ALIGN_RIGHT)
        .appendField(',');
	this.appendDummyInput('')
		.setAlign(Blockly.ALIGN_RIGHT)
		.appendField(')');
	this.setInputsInline(true);
    this.setOutput(true, Number);
	var thisBlock = this;
    this.setTooltip(function() {
      var mode = thisBlock.getFieldValue('OP');
      var TOOLTIPS = {
        'max': Blockly.MIXLY_TOOLTIP_MATH_MAX,
        'min': Blockly.MIXLY_TOOLTIP_MATH_MIN
      };
      return TOOLTIPS[mode];
    });
  }
};

Blockly.Blocks['math_random_int'] = {
  /**
   * Block for random integer between [X] and [Y].
   * @this Blockly.Block
   */
  init: function() {
    this.setColour(Blockly.Blocks.math.HUE);
    this.setOutput(true, Number);
    this.appendValueInput('FROM')
        .setCheck(Number)
        .appendField(Blockly.LANG_MATH_RANDOM_INT_INPUT_FROM);
    this.appendValueInput('TO')
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.LANG_MATH_RANDOM_INT_INPUT_TO);
    this.setInputsInline(true);
    this.setTooltip(Blockly.Msg.MATH_RANDOM_INT_TOOLTIP);
  }
};

Blockly.Blocks['math_constrain'] = {
  /**
   * Block for constraining a number between two limits.
   * @this Blockly.Block
   */
  init: function() {
    this.setColour(Blockly.Blocks.math.HUE);
    this.setOutput(true, Number);
    this.appendValueInput('VALUE')
        .setCheck(Number)
        .appendField(Blockly.LANG_MATH_CONSTRAIN_INPUT_CONSTRAIN);
    this.appendValueInput('LOW')
        .setCheck(Number)
        .appendField(Blockly.LANG_MATH_CONSTRAIN_INPUT_LOW);
    this.appendValueInput('HIGH')
        .setCheck(Number)
        .appendField(Blockly.LANG_MATH_CONSTRAIN_INPUT_HIGH);
    this.setInputsInline(true);
    this.setTooltip(Blockly.Msg.MATH_CONSTRAIN_TOOLTIP);
  }
};

Blockly.Blocks.base_map = {
  init: function() {
    this.setColour(Blockly.Blocks.math.HUE);
    this.appendValueInput("NUM", Number)
        .appendField(Blockly.MIXLY_MAP)
        .setCheck(Number);
    this.appendValueInput("fromLow", Number)
        .appendField(Blockly.MIXLY_MAP_FROM)
        .setCheck(Number);
    this.appendValueInput("fromHigh", Number)
        .appendField(",")
        .setCheck(Number);
    this.appendValueInput("toLow", Number)
        .appendField(Blockly.MIXLY_MAP_TO)
        .setCheck(Number);
    this.appendValueInput("toHigh", Number)
        .appendField(",")
        .setCheck(Number);
    this.appendDummyInput("")
	      .appendField("]");
    this.setInputsInline(true);
    this.setOutput(true);
	this.setTooltip(Blockly.MIXLY_TOOLTIP_MATH_MAP);
  }
};
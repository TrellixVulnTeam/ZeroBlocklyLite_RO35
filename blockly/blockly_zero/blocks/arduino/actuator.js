'use strict';

goog.provide('Blockly.Blocks.actuator');
goog.require('Blockly.Blocks');

Blockly.Blocks.actuator.HUE = 100;

Blockly.Blocks.servo_move = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_SERVO)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN");
    this.appendValueInput("DEGREE", Number)
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_DEGREE_0_180);
    this.appendValueInput("DELAY_TIME", Number)
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_DELAY + '(' + Blockly.MIXLY_MILLIS + ')');
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_SERVO_MOVE);
    this.setFieldValue("2", "PIN");
  }
};

Blockly.Blocks.servo_writeMicroseconds = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_SERVO)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN");
    this.appendValueInput("DEGREE", Number)
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_SERVO_WRITEMICROSECONDS);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_SERVO_WRITEMICROSECONDS);
    this.setFieldValue("2", "PIN");
  }
};

Blockly.Blocks.servo_read_degrees = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_SERVO)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN");
    this.appendDummyInput("")
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_READ_DEGREES)
    this.setOutput(true, Number);
    this.setInputsInline(true);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_SERVO_READ);
    this.setFieldValue("2", "PIN");
  }
};
var TONE_NOTES = [["NOTE_C3", "131"], ["NOTE_D3", "147"], ["NOTE_E3", "165"], ["NOTE_F3", "175"], ["NOTE_G3", "196"], ["NOTE_A3", "220"], ["NOTE_B3", "247"], ["NOTE_C4", "262"], ["NOTE_D4", "294"], ["NOTE_E4", "330"], ["NOTE_F4", "349"], ["NOTE_G4", "392"], ["NOTE_A4", "440"], ["NOTE_B4", "494"], ["NOTE_C5", "532"], ["NOTE_D5", "587"], ["NOTE_E5", "659"], ["NOTE_F5", "698"], ["NOTE_G5", "784"], ["NOTE_A5", "880"], ["NOTE_B5", "988"], ["NOTE_C6", "1047"], ["NOTE_D6", "1175"], ["NOTE_E6", "1319"], ["NOTE_F6", "1397"], ["NOTE_G6", "1568"], ["NOTE_A6", "1760"], ["NOTE_B6", "1976"], ["NOTE_C7", "2093"], ["NOTE_D7", "2349"], ["NOTE_E7", "2637"], ["NOTE_F7", "2794"], ["NOTE_G7", "3136"], ["NOTE_A7", "3520"], ["NOTE_B7", "3951"]];

Blockly.Blocks.tone_notes = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(new Blockly.FieldDropdown(TONE_NOTES), 'STAT');
    this.setOutput(true, Number);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_TONE_NOTE);
  }
};
Blockly.Blocks.controls_tone = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendValueInput("PIN", Number)
    .appendField(Blockly.MIXLY_TONE)
    .appendField(Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendValueInput('FREQUENCY')
    .setCheck(Number)
      //.setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_FREQUENCY);
      this.setInputsInline(true);
      this.setPreviousStatement(true);
      this.setNextStatement(true);
      this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_TONE);
    }
  };
  Blockly.Blocks.controls_notone = {
    init: function () {
      this.setColour(Blockly.Blocks.actuator.HUE);
      this.appendValueInput("PIN", Number)
      .appendField(Blockly.MIXLY_NOTONE)
      .appendField(Blockly.MIXLY_PIN)
      .setCheck(Number);
      this.setInputsInline(true);
      this.setPreviousStatement(true);
      this.setNextStatement(true);
      this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_NOTONE);
    }
  };
  Blockly.Blocks.controls_tone_noTimer = {
    init: function () {
      this.setColour(Blockly.Blocks.actuator.HUE);
      this.appendValueInput("PIN", Number)
      .appendField(Blockly.MIXLY_TONE_NOTIMER)
      .appendField(Blockly.MIXLY_PIN)
      .setCheck(Number);
      this.appendValueInput('FREQUENCY')
      .setCheck(Number)
      //.setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_FREQUENCY);
      this.appendValueInput('DURATION')
      .setCheck(Number)
      //.setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_DURATION);
      this.appendDummyInput("")
      .appendField(Blockly.MIXLY_MILLIS);
      this.setInputsInline(true);
      this.setPreviousStatement(true);
      this.setNextStatement(true);
      this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_TONE2);
    }
  };

  Blockly.Blocks.controls_notone_noTimer = {
    init: function () {
      this.setColour(Blockly.Blocks.actuator.HUE);
      this.appendValueInput("PIN", Number)
      .appendField(Blockly.MIXLY_NOTONE_NOTIMER)
      .appendField(Blockly.MIXLY_PIN)
      .setCheck(Number);
      this.setInputsInline(true);
      this.setPreviousStatement(true);
      this.setNextStatement(true);
      this.setTooltip(Blockly.MIXLY_TOOLTIP_BLOCKGROUP_NOTONE);
    }
  };

  Blockly.Blocks.group_stepper_setup = {
    init: function () {
      this.setColour(Blockly.Blocks.actuator.HUE);
      this.appendDummyInput()
      .appendField(Blockly.MIXLY_STEPPER_SETUP_STEPPER)
      .appendField(new Blockly.FieldTextInput('mystepper'), 'VAR');
      this.appendValueInput("PIN1", Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_PIN1)
      .setCheck(Number);
      this.appendValueInput("PIN2", Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_PIN2)
      .setCheck(Number);
      this.appendValueInput('steps')
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPSPERREVOLUTION);
      this.appendValueInput('speed')
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_SET_SPEED);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      this.setTooltip(Blockly.MIXLY_TOOLTIP_STEPPER_STEP);
    }
  }

  Blockly.Blocks.group_stepper_setup2 = {
    init: function () {
      this.setColour(Blockly.Blocks.actuator.HUE);
      this.appendDummyInput()
      .appendField(Blockly.MIXLY_STEPPER_SETUP_STEPPER)
      .appendField(new Blockly.FieldTextInput('mystepper'), 'VAR');
      this.appendValueInput("PIN1", Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_PIN1)
      .setCheck(Number);
      this.appendValueInput("PIN2", Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_PIN2)
      .setCheck(Number);
      this.appendValueInput("PIN3", Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_PIN3)
      .setCheck(Number);
      this.appendValueInput("PIN4", Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_PIN4)
      .setCheck(Number);
      this.appendValueInput('steps')
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPSPERREVOLUTION);
      this.appendValueInput('speed')
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_SET_SPEED);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      this.setTooltip(Blockly.MIXLY_TOOLTIP_STEPPER_STEP2);
    }
  }

  Blockly.Blocks.group_stepper_move = {
    init: function () {
      this.setColour(Blockly.Blocks.actuator.HUE);
      this.appendDummyInput()
      .appendField(Blockly.MIXLY_STEPPER)
      .appendField(new Blockly.FieldTextInput('mystepper'), 'VAR');
      this.appendValueInput('step')
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_STEPPER_STEP);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      this.setInputsInline(true);
      this.setTooltip(Blockly.MIXLY_TOOLTIP_STEPPER_MOVE);
    }
  }


  Blockly.Blocks.RGB_color_seclet = {
    init: function () {
      this.setColour(Blockly.Blocks.actuator.HUE);
      this.appendDummyInput("")
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(new Blockly.FieldColour("ff0000"), "COLOR");
      this.setInputsInline(true);
      this.setOutput(true, Number);
      this.setTooltip(Blockly.OLED_DRAW_PIXE_TOOLTIP);
    }
  };

  Blockly.Blocks.RGB_color_rgb = {
    init: function () {
      this.setColour(Blockly.Blocks.actuator.HUE);
      this.appendValueInput("R")
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_RGB_R);
      this.appendValueInput("G")
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_RGB_G);
      this.appendValueInput("B")
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_RGB_B);
      this.setInputsInline(true);
      this.setOutput(true);
      this.setTooltip('');
    }
  };

//RGB
Blockly.Blocks.display_rgb_init = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN")
    .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("LEDCOUNT")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_RGB_COUNT);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
    this.setFieldValue("12", "PIN");
  }
};

Blockly.Blocks.display_rgb_Brightness = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN")
    .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("Brightness")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_BRIGHTNESS);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
    this.setFieldValue("12", "PIN");
  }
};


Blockly.Blocks.display_rgb = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN")
    .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("_LED_")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_RGB_NUM);
    this.appendDummyInput("")
    .appendField(Blockly.Msg.HTML_COLOUR);
    this.appendValueInput("COLOR", Number)
    .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
    this.setFieldValue("12", "PIN");
  }
};

Blockly.Blocks.display_rgb_show = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB_SHOW)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN")
    .setAlign(Blockly.ALIGN_RIGHT);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

var DISPLAY_RAINBOW_TYPE = [
[Blockly.MIXLY_RGB_DISPLAY_RAINBOW_TYPE_1, "normal"],
[Blockly.MIXLY_RGB_DISPLAY_RAINBOW_TYPE_2, "change"]
];


Blockly.Blocks.display_rgb_rainbow1 = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN")
    .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("WAIT")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_RGBdisplay_rgb_rainbow1);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setFieldValue("12", "PIN");
  }
};

Blockly.Blocks.display_rgb_rainbow2 = {
  init: function () {
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN")
    .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("WAIT")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_RGBdisplay_rgb_rainbow2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setFieldValue("12", "PIN");
  }
};

Blockly.Blocks.display_rgb_rainbow3 = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB)
    .appendField(Blockly.MIXLY_PIN)
    .appendField(new Blockly.FieldDropdown(profile.default.digital), "PIN")
    .setAlign(Blockly.ALIGN_RIGHT);
    this.appendDummyInput("")
    .appendField(new Blockly.FieldDropdown(DISPLAY_RAINBOW_TYPE), "TYPE");
    this.appendValueInput("rainbow_color")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_RGB_display_rgb_rainbow3);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setFieldValue("12", "PIN");
  }
};

Blockly.Blocks.Mixly_motor = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField("L293/298N")
    .appendField(Blockly.MIXLY_MOTOR);
    this.appendDummyInput("")
    this.appendValueInput("PIN1")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_MOTOR_SPEED_PIN);
    this.appendValueInput("PIN2")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_MOTOR_DIR_PIN);
    this.appendValueInput('speed')
    .setCheck(Number)
    .appendField(Blockly.MIXLY_MOTOR_SPEED);
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
  }
};
Blockly.Blocks.Motor_8833 = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField("DRV8833")
    .appendField(Blockly.MIXLY_MOTOR);
    this.appendDummyInput("")
    this.appendValueInput("PIN1")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_PIN)
    .appendField("1");
    this.appendValueInput("PIN2")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_PIN)
    .appendField("2");
    this.appendValueInput('speed')
    .setCheck(Number)
    .appendField(Blockly.MIXLY_MOTOR_SPEED);
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
  }
};

//MP3播放控制
var GD5800_MP3_CONTROL_TYPE = [
[Blockly.MIXLY_MP3_PLAY, "play();"],
[Blockly.MIXLY_MP3_PAUSE, "pause();"],
[Blockly.MIXLY_MP3_NEXT, "next();"],
[Blockly.MIXLY_MP3_PREV, "prev();"],
[Blockly.MIXLY_MP3_VOL_UP, "volumeUp();"],
[Blockly.MIXLY_MP3_VOL_DOWN, "volumeDn();"]
];

//GD5800 MP3模块
Blockly.Blocks.GD5800_MP3_CONTROL = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.GD5800_MP3);
    this.appendValueInput("RXPIN", Number)
    .appendField("TX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendValueInput("TXPIN", Number)
    .appendField("RX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_STAT)
    .appendField(new Blockly.FieldDropdown(GD5800_MP3_CONTROL_TYPE), "CONTROL_TYPE");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip();
    this.setHelpUrl();
  }
};

//MP3循环模式
var GD5800_MP3_LOOP_MODE = [
[Blockly.MIXLY_MP3_LOOP_ALL, "MP3_LOOP_ALL"],
[Blockly.MIXLY_MP3_LOOP_FOLDER, "MP3_LOOP_FOLDER"],
[Blockly.MIXLY_MP3_LOOP_ONE, "MP3_LOOP_ONE"],
[Blockly.MIXLY_MP3_LOOP_RAM, "MP3_LOOP_RAM"]
];

//GD5800 MP3模块循环模式
Blockly.Blocks.GD5800_MP3_LOOP_MODE = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.GD5800_MP3);
    this.appendValueInput("RXPIN", Number)
    .appendField("TX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendValueInput("TXPIN", Number)
    .appendField("RX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_MP3_LOOP_MODE)
    .appendField(Blockly.MIXLY_STAT)
    .appendField(new Blockly.FieldDropdown(GD5800_MP3_LOOP_MODE), "LOOP_MODE");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip();
    this.setHelpUrl();
  }
};

//MP3 设置EQ
var GD5800_MP3_EQ_MODE = [
[Blockly.MIXLY_MP3_EQ_NORMAL, "MP3_EQ_NORMAL"],
[Blockly.MIXLY_MP3_EQ_POP, "MP3_EQ_POP"],
[Blockly.MIXLY_MP3_EQ_ROCK, "MP3_EQ_ROCK"],
[Blockly.MIXLY_MP3_EQ_JAZZ, "MP3_EQ_JAZZ"],
[Blockly.MIXLY_MP3_EQ_CLASSIC, "MP3_EQ_CLASSIC"],
[Blockly.MIXLY_MP3_EQ_BASS, "MP3_EQ_BASS"]
];

//GD5800 MP3模块EQ模式
Blockly.Blocks.GD5800_MP3_EQ_MODE = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.GD5800_MP3);
    this.appendValueInput("RXPIN", Number)
    .appendField("TX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendValueInput("TXPIN", Number)
    .appendField("RX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_MP3_EQ_MODE)
    .appendField(Blockly.MIXLY_STAT)
    .appendField(new Blockly.FieldDropdown(GD5800_MP3_EQ_MODE), "EQ_MODE");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip();
    this.setHelpUrl();
  }
};

//GD5800 MP3模块设置音量
Blockly.Blocks.GD5800_MP3_VOL = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.GD5800_MP3);
    this.appendValueInput("RXPIN", Number)
    .appendField("TX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendValueInput("TXPIN", Number)
    .appendField("RX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_MP3_VOL);
    this.appendValueInput("vol", Number)
    .appendField(Blockly.MIXLY_STAT)
    .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip();
    this.setHelpUrl();
  }
};

//GD5800 MP3模块播放第N首
Blockly.Blocks.GD5800_MP3_PLAY_NUM = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField(Blockly.GD5800_MP3);
    this.appendValueInput("RXPIN", Number)
    .appendField("TX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendValueInput("TXPIN", Number)
    .appendField("RX"+Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendValueInput("NUM", Number)
    .appendField(Blockly.MIXLY_MP3_PLAY_NUM)
    .setCheck(Number);
    this.appendDummyInput("")
    .appendField("首");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip();
    this.setHelpUrl();
  }
};

var VOICE_LIST = [["老师", "0x00"], ["爸爸", "0x01"], ["妈妈", "0x02"], ["爷爷", "0x03"], ["奶奶", "0x04"], ["姥姥", "0x05"], ["姥爷", "0x06"], ["哥哥", "0x07"], ["姐姐", "0x08"], ["叔叔", "0x09"], ["阿姨", "0x0A"], ["上午", "0x0B"], ["下午", "0x0C"], ["晚上", "0x0D"], ["前方", "0x0E"], ["厘米", "0x0F"], ["新年快乐", "0x10"], ["身体健康", "0x11"], ["工作顺利", "0x12"], ["学习进步", "0x13"], ["您好", "0x14"], ["谢谢", "0x15"], ["的", "0x16"], ["祝", "0x17"], ["慢走", "0x18"], ["欢迎光临", "0x19"], ["亲爱的", "0x1A"], ["同学们", "0x1B"], ["工作辛苦了", "0x1C"], ["点", "0x1D"], ["打开", "0x1E"], ["关闭", "0x1F"], ["千", "0x20"], ["百", "0x21"], ["十", "0x22"], ["1", "0x23"], ["2", "0x24"], ["3", "0x25"], ["4", "0x26"], ["5", "0x27"], ["6", "0x28"], ["7", "0x29"], ["8", "0x2A"], ["9", "0x2B"], ["0", "0x2C"], ["当前", "0x2D"], ["转", "0x2E"], ["左", "0x2F"], ["右", "0x30"], ["请", "0x31"], ["已", "0x32"], ["现在", "0x33"], ["是", "0x34"], ["红灯", "0x35"], ["绿灯", "0x36"], ["黄灯", "0x37"], ["温度", "0x38"], ["湿度", "0x39"], ["欢迎常来", "0x3A"], ["还有", "0x3B"], ["秒", "0x3C"], ["分", "0x3D"], ["变", "0x3E"], ["等", "0x3F"], ["下一次", "0x40"], ["功能", "0x41"], ["障碍物", "0x42"], ["世界那么大，我想去看看", "0x43"]];

Blockly.Blocks.voice_module = {
  init: function () {
    this.setColour(Blockly.Blocks.actuator.HUE);
    this.appendDummyInput("")
    .appendField("语音模块(68段日常用语)");
    this.appendValueInput("PIN", Number)
    .appendField(Blockly.MIXLY_PIN)
    .setCheck(Number);
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_MP3_PLAY)
    .appendField(new Blockly.FieldDropdown(VOICE_LIST), "VOICE");
    this.appendValueInput("WAIT").setCheck(Number).appendField(Blockly.MIXLY_MICROBIT_WAIT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
  }
};


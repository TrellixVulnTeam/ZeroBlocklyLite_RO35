# Author: qiren123
# This file is part of MicroPython MIDI Music
# Copyright (c) 2018 qiren123
#
# Licensed under the MIT license:
#   http://www.opensource.org/licenses/mit-license.php
#
#import matrix

DADADADUM = ('r4:2', 'g', 'g', 'g', 'eb:8', 'r:2', 'f', 'f', 'f', 'd:8')

ENTERTAINER = (
    'd4:1', 'd#', 'e', 'c5:2', 'e4:1', 'c5:2', 'e4:1', 'c5:3', 'c:1', 'd',
    'd#', 'e', 'c', 'd', 'e:2', 'b4:1', 'd5:2', 'c:4'
)


BLUES = (
    'c2:2', 'e', 'g', 'a', 'a#', 'a', 'g', 'e', 'c2:2', 'e', 'g', 'a', 'a#',
    'a', 'g', 'e', 'f', 'a', 'c3', 'd', 'd#', 'd', 'c', 'a2', 'c2:2', 'e', 'g',
    'a', 'a#', 'a', 'g', 'e', 'g', 'b', 'd3', 'f', 'f2', 'a', 'c3', 'd#',
    'c2:2', 'e', 'g', 'e', 'g', 'f', 'e', 'd'
)

BIRTHDAY = (
    'c4:4', 'c:1', 'd:4', 'c:4', 'f', 'e:8', 'c:3', 'c:1', 'd:4', 'c:4', 'g',
    'f:8', 'c:3', 'c:1', 'c5:4', 'a4', 'f', 'e', 'd', 'a#:3', 'a#:1', 'a:4',
    'f', 'g', 'f:8'
)


PYTHON = (
    'd5:1', 'b4', 'r', 'b', 'b', 'a#', 'b', 'g5', 'r', 'd', 'd', 'r', 'b4',
    'c5', 'r', 'c', 'c', 'r', 'd', 'e:5', 'c:1', 'a4', 'r', 'a', 'a', 'g#',
    'a', 'f#5', 'r', 'e', 'e', 'r', 'c', 'b4', 'r', 'b', 'b', 'r', 'c5', 'd:5',
    'd:1', 'b4', 'r', 'b', 'b', 'a#', 'b', 'b5', 'r', 'g', 'g', 'r', 'd', 'c#',
    'r', 'a', 'a', 'r', 'a', 'a:5', 'g:1', 'f#:2', 'a:1', 'a', 'g#', 'a',
    'e:2', 'a:1', 'a', 'g#', 'a', 'd', 'r', 'c#', 'd', 'r', 'c#', 'd:2', 'r:3'
)



normal_tone = {
    'A1': 55, 'B1': 62, 'C1': 33, 'D1': 37, 'E1': 41, 'F1': 44, 'G1': 49,
    'A2': 110, 'B2': 123, 'C2': 65, 'D2': 73, 'E2': 82, 'F2': 87, 'G2': 98,
    'A3': 220, 'B3': 247, 'C3': 131, 'D3': 147, 'E3': 165, 'F3': 175, 'G3': 196,
    'A4': 440, 'B4': 494, 'C4': 262, 'D4': 294, 'E4': 330, 'F4': 349, 'G4': 392,
    'A5': 880, 'B5': 988, 'C5': 523, 'D5': 587, 'E5': 659, 'F5': 698, 'G5': 784,
    'A6': 1760, 'B6': 1976, 'C6': 1047, 'D6': 1175, 'E6': 1319, 'F6': 1397, 'G6': 1568,
    'A7': 3520, 'B7': 3951, 'C7': 2093, 'D7': 2349, 'E7': 2637, 'F7': 2794, 'G7': 3135,
    'A8': 7040, 'B8': 7902, 'C8': 4186, 'D8': 4699, 'E8': 5274, 'F8': 5588, 'G8': 6271,
    'A9': 14080, 'B9': 15804
}

rising_tone = {
    'A1': 58, 'C1': 35, 'D1': 39, 'F1': 46, 'G1': 52,
    'A2': 117, 'C2': 69, 'D2': 78, 'F2': 93, 'G2': 104,
    'A3': 233, 'C3': 139, 'D3': 156, 'F3': 185, 'G3': 208,
    'A4': 466, 'C4': 277, 'D4': 311, 'F4': 370, 'G4': 415,
    'A5': 932, 'C5': 554, 'D5': 622, 'F5': 740, 'G5': 831,
    'A6': 1865, 'C6': 1109, 'D6': 1245, 'F6': 1480, 'G6': 1661,
    'A7': 3729, 'C7': 2217, 'D7': 2489, 'F7': 2960, 'G7': 3322,
    'A8': 7459, 'C8': 4435, 'D8': 4978, 'F8': 5920, 'G8': 6645,
    'A9': 14917
}

falling_tone = {
    'B1': 58, 'D1': 35, 'E1': 39, 'G1': 46, 'A1': 52,
    'B2': 117, 'D2': 69, 'E2': 78, 'G2': 93, 'A2': 104,
    'B3': 233, 'D3': 139, 'E3': 156, 'G3': 185, 'A3': 208,
    'B4': 466, 'D4': 277, 'E4': 311, 'G4': 370, 'A4': 415,
    'B5': 932, 'D5': 554, 'E5': 622, 'G5': 740, 'A5': 831,
    'B6': 1865, 'D6': 1109, 'E6': 1245, 'G6': 1480, 'A6': 1661,
    'B7': 3729, 'D7': 2217, 'E7': 2489, 'G7': 2960, 'A7': 3322,
    'B8': 7459, 'D8': 4435, 'E8': 4978, 'G8': 5920, 'A8': 6645,
    'B9': 14917
}

Letter = 'ABCDEFG#R'

class MIDI():
    def set_tempo(self, ticks=4, bpm=120):
        self.ticks = ticks
        self.bpm = bpm
        self.beat = 60000 / self.bpm / self.ticks

    def set_octave(self, octave=4):
        self.octave = octave

    def set_duration(self, duration=4):
        self.duration = duration

    def get_tempo(self):
        return (self.ticks, self.bpm)

    def get_octave(self):
        return self.octave

    def get_duration(self):
        return self.duration

    def reset(self):
        self.set_duration()
        self.set_octave()
        self.set_tempo()

    def __init__(self):
        self.reset()

    def parse(self, tone, dict):
        # print(tone)
        time = self.beat * self.duration
        pos = tone.find(':')
        if pos != -1:
            time = self.beat * int(tone[(pos + 1):])
            tone = tone[:pos]
        # print(tone)
        freq, tone_size = 1, len(tone)
        if 'R' in tone:
            freq = 1
        elif tone_size == 1:
            freq = dict[tone[0] + str(self.octave)]
        elif tone_size == 2:
            freq = dict[tone]
            self.set_octave(tone[1:])
        # print(int(freq), int(time))
        return int(freq), int(time)

    def midi(self, tone):
        # print(tone)
        pos = tone.find('#')
        if pos != -1:
            return self.parse(tone.replace('#', ''), rising_tone)
        pos = tone.find('B')
        if pos != -1 and pos != 0:
            return self.parse(tone.replace('B', ''), falling_tone)
        return self.parse(tone, normal_tone)

    def set_default(self, tone):
        pos = tone.find(':')
        if pos != -1:
            self.set_duration(int(tone[(pos + 1):]))
            tone = tone[:pos]

    def play(self, tune, pin=27, duration=None):
        from machine import Pin, PWM
        from utime import sleep_ms

        pwm = PWM(Pin(pin))
        if duration is None:
            self.set_default(tune[0])
        else:
            self.set_duration(duration)
        for tone in tune:
            tone = tone.upper()  # all to upper
            if tone[0] not in Letter:
                continue
            midi = self.midi(tone)
            pwm.freq(midi[0])  # set frequency
            #pwm.duty(midi[1])  # set duty cycle
            sleep_ms(midi[1])
        pwm.deinit()

    # def play_show(self, tune, pin=27, display=matrix.display, duration=None):
    #     from machine import Pin, PWM
    #     from utime import sleep_ms
    #     pwm = PWM(Pin(pin))
    #     if duration is None:
    #         self.set_default(tune[0])
    #     else:
    #         self.set_duration(duration)
    #     for tone in tune:
    #         tone = tone.upper()  # all to upper
    #         if tone[0] not in Letter:
    #             continue
    #         if len(tone)==4:
    #             display.showstatic(tone.replace(":",""))
    #         else:
    #             display.showstatic(tone)
    #         midi = self.midi(tone)
    #         pwm.freq(midi[0])  # set frequency
    #         #pwm.duty(midi[1])  # set duty cycle
    #         sleep_ms(midi[1])
    #     display.clear()
    #     pwm.deinit()

    def play_show(self, tune, pin=27, duration=None):
        from machine import Pin, PWM
        from utime import sleep_ms
        pwm = PWM(Pin(pin))
        if duration is None:
            self.set_default(tune[0])
        else:
            self.set_duration(duration)
        for tone in tune:
            tone = tone.upper()  # all to upper
            if tone[0] not in Letter:
                continue
            else:
                print(tone)
            midi = self.midi(tone)
            pwm.freq(midi[0])  # set frequency
            #pwm.duty(midi[1])  # set duty cycle
            sleep_ms(midi[1])
        pwm.deinit()

    def pitch(self, pin=27, freq=440, tim=0):
        from machine import Pin, PWM
        from utime import sleep_ms
        pwm = PWM(Pin(pin))
        if freq > 0:
            pwm.freq(int(freq)) # set frequency
        else:
            pwm.duty(0)
        if tim > 0:
            #pwm.duty(tim)  # set duty cycle
            sleep_ms(tim)
            pwm.deinit()

    def stop(self, pin=27):
        from machine import Pin, PWM
        pwm = PWM(Pin(pin))
        pwm.duty(0)
        pwm.freq(1)
        pwm.deinit()

__music__ = MIDI()

play = __music__.play
play_show = __music__.play_show
pitch = __music__.pitch
stop = __music__.stop
set_default = __music__.set_default
set_tempo = __music__.set_tempo
get_tempo = __music__.get_tempo
reset = __music__.reset
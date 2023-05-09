import time

import pyautogui
import keyboard  # using module keyboard
while True:  # making a loop

    if keyboard.is_pressed('r'):  # if key 'q' is pressed
        pyautogui.press('backspace')
        pyautogui.write('Dorty was here\n 29.04.2023\nDorty_Schmorty', interval=0.04)
        pyautogui.press('esc')
    time.sleep(0.02)

from selenium import webdriver
import time
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains





driver = webdriver.Chrome(
    executable_path="chromedriver.exe")
some_id = "cookie"


url = "https://garticphone.com/"



width = 1516
height = 848
from PIL import Image


try:
    driver.get(url)
    while(1):
        colors = []
        print('Жду ввода')
        input()

        print(driver.find_elements(By.XPATH, "//div[@style='background-color: rgb(0, 0, 0);']") )

        driver.find_element(By.XPATH, "//div[@style='background-color: rgb(0, 0, 0);']").click()

        stuff = driver.find_elements(By.XPATH, "//div")
        transform = 1
        for elem in stuff:
            strin = elem.get_attribute('style')

            print(strin)
            if strin.startswith('background-color: rgb('):


                strin3 = strin[strin.find('(') + 1:strin.find(');')]
                print(strin3)

                color = map(int, strin3.replace('(', '').replace(')', '').split(','))
                print(color)
                colors.append(color)





        elem = driver.find_elements(By.XPATH, "//canvas")[1]
        print(elem.size)
        ac = ActionChains(driver)
        print('345435')
        im = Image.open("img.jpg")
        rgb_im = im.convert('RGB')
        print('123')
        for x in range(im.width // 4):
            for y in range(im.height // 4):
                print(x, y)
                r, g, b = rgb_im.getpixel((x, y))
                print(x,y)
                print(r,g,b)
                if r+g+b > 350:
                    print('here')
                    true_x = int ( (elem.size['width']-30) * ( x*4 - im.width/2  ) / im.width)
                    true_y = int ( (elem.size['height']-30) * ( y*4 - im.height/2  ) / im.height )
                    print(true_x, true_y)

                    action = webdriver.common.action_chains.ActionChains(driver)
                    action.move_to_element_with_offset(elem, true_x // 5, true_y // 5)
                    action.click()
                    action.perform()

                    #ac.move_to_element(elem).move_by_offset(abs(true_x), abs(true_y)).click().perform()
                # ..
                pass


except Exception as ex:
    print(ex)
finally:
    print('I am NOT closing, lol')
    time.sleep(7200)
    driver.close()
    driver.quit()

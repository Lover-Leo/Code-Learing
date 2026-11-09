from getpass import getpass

from selenium import webdriver
from selenium.webdriver.common.by import By
import time

username = input("请输入 12306 账号：")
password = getpass("请输入 12306 密码：")

driver = webdriver.Chrome()
driver.get('https://kyfw.12306.cn/otn/resources/login.html')

username = driver.find_element(By.ID,'J-userName').send_keys(username)
password = driver.find_element(By.ID,'J-password').send_keys(password)
driver.find_element(By.ID,'J-login').click()

time.sleep(100)
import requests

url = 'https://www.autohome.com.cn/news/'
header = {
'User-Agent':"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/156.0.0.0 Safari/537.36"
}

res = requests.get(url=url,headers=header)
text = res.content.decode('gbk')

from bs4 import BeautifulSoup

soup_object = BeautifulSoup(text,"html.parser")

div_area = soup_object.find(name="div",attrs={"class":"editorblog"})
li_area_list = div_area.find_all(name='li')

for li_area in li_area_list:
    total_name = li_area.find(name='div',attrs={'class':'editorname'})
    a_name = total_name.find(name='a')
    print(a_name.text)


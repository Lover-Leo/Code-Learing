import requests
import prettytable as pt
import json
import os
#输入
date = input("请输入日期")
from_station = input("请输入起始站")
to_station = input("请输入终点站")

file = open("station_codes.json",'r',encoding='utf-8')
data = json.loads(file.read())

from_station_code = data['stations'][from_station]
to_station_code = data['stations'][to_station]

table = pt.PrettyTable()
table.field_names = [
    '序号',
    '车次',
    '出发时间',
    '到达时间',
    '总时间',
    '日期',
    '特等座',
    '一等座',
    '二等座',
    '硬卧',
    '硬座',
    '无座',
    '软卧'
]

url = f"https://kyfw.12306.cn/otn/leftTicket/queryG?leftTicketDTO.train_date={date}&leftTicketDTO.from_station={from_station_code}&leftTicketDTO.to_station={to_station_code}&purpose_codes=ADULT"
headers = {
    'user-agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/149.0.0.0 Safari/537.36 Edg/149.0.0.0'
}
cookie = os.getenv("RAILWAY_12306_COOKIE")
if cookie:
    headers["Cookie"] = cookie

response = requests.get(url=url,headers=headers)


for page,i in enumerate(response.json()['data']['result'],start=1):
    index = i.split('|')
    num = index[3] #车次
    go_time = index[8] #出发时间
    arrive_time = index[9] #到达时间
    during = index[10] #总时间
    date = index[13] #日期
    seat_0 = index[25] #特等座
    seat_1 = index[31] #一等座
    seat_2 = index[30] #二等座
    hard_sleeper = index[28] #硬卧
    hard_seat = index[29] #硬座
    no_seat = index[26] #无座
    soft_sleeper = index[23] #软卧
    table.add_row([page,
                   num,
                   go_time,
                   arrive_time,
                   during,
                   date,
                   seat_0,
                   seat_1,
                   seat_2,
                   hard_sleeper,
                   hard_seat,
                   no_seat,
                   soft_sleeper])


print(table)
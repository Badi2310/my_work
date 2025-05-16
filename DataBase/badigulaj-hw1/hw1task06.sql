select dt, high_price, vol
from coins
where symbol = 'DOGE' and dt >= '2018-01-01' and dt <'2019-01-01' and avg_price > 0.001
order by high_price, vol

select *
from coins
where avg_price < 100 and symbol = 'BTC';
